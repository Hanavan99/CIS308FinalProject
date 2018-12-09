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
	board->pieces[4][4] = chess_create_piece(KING, WHITE);

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

	struct sockaddr * addr;
	struct socklen_t * len;
	printf("Server waiting for client 1\n");
	printf(strerror(errno));
	teama_fd = accept(serversocket_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
	printf(strerror(errno));

	core_write_board(teama_fd, board);

	printf("Server waiting for client 2\n");
	teamb_fd = accept(serversocket_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen);

	core_write_board(teama_fd, board);

	while (1) {

		

	}

}
