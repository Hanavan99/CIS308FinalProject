#include "core_chessboard.h"
#include "core_network.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h>
#include <errno.h>

#define PORT 12345

int serversocket_fd = 0;
int teama_fd = 0;
int teamb_fd = 0;
chessboard_t * board;

void main(int argc, int* argv) {

	board = chess_create_default_chessboard();
	//board->pieces[4][4] = chess_create_piece(KING, WHITE);

	//printf("[6][4] = %d\n", board->pieces[6][4]->type);

	printf("Server initializing\n");
	serversocket_fd = socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1;
	setsockopt(serversocket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT | TCP_NODELAY, &opt, sizeof(opt));

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	int addrlen = sizeof(address);

	printf("Binding to address\n");
	bind(serversocket_fd, (struct sockaddr *) &address, sizeof(address));

	printf("Server going into listen mode\n");
	listen(serversocket_fd, 2);

	color_t * teama_color = malloc(sizeof(color_t));
	color_t * teamb_color = malloc(sizeof(color_t));
	*teama_color = WHITE;
	*teamb_color = BLACK;

	struct sockaddr * addr;
	struct socklen_t * len;
	printf("Server waiting for client 1\n");
	teama_fd = accept(serversocket_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
	printf(" --> Socket status: %s\n", strerror(errno));

	core_write_player_color(teama_fd, teama_color);
	core_write_board(teama_fd, board);

	printf("Server waiting for client 2\n");
	teamb_fd = accept(serversocket_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
	printf(" --> Socket status: %s\n", strerror(errno));

	core_write_player_color(teamb_fd, teamb_color);
	core_write_board(teamb_fd, board);
	printf("Starting game\n");

	int validmove = 0;
	int socket = teama_fd;
	char move[4];

	while (1) {

		printf("Currently %s's turn\n", board->turncolor == WHITE ? "white" : "black");

		while (!validmove) {

			core_read_move(socket, move);
			int fromFile = (int) (move[0] - 'a') + 1; // e2 == [4][6], e3 == [4][5]
			int fromRank = (int) (move[1] - '1') + 1;
			int toFile = (int) (move[2] - 'a') + 1;
			int toRank = (int) (move[3] - '1') + 1;

			printf("Player's move: %c%c to %c%c\n", move[0], move[1], move[2], move[3]);

			if (is_valid_board_position(fromRank, fromFile) && is_valid_board_position(toRank, toFile)) {

				if (chess_get_piece_at(fromRank, fromFile, board) != NULL && chess_get_piece_at(fromRank, fromFile, board)->color == board->turncolor) {
					validmove = chess_move_piece(fromRank, fromFile, toRank, toFile, board);
					printf("Player's move was %s.\n", validmove ? "valid" : "invalid");
				} else {
					printf("Player tried to move piece that wasn't theirs.\n");
				}

			} else {
				printf("Invalid move input\n");
			}

			core_write_board(socket, board);

		}


		printf("Player finished turn. Switching color.\n");

		// switch player
		socket = board->turncolor == WHITE ? teama_fd : teamb_fd;
		validmove = 0;

		// write board to other player
		core_write_board(socket, board);

	}

}
