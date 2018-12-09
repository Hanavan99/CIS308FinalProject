#include "core_network.h"
#include "core_chessboard.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

int core_create_client_socket(char * addr, int port){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    int one = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
//printf("%d\n", one);
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    //address.sin_addr.s_addr = "129.130.10.39";
    address.sin_port = htons(port);
    int two = inet_pton(AF_INET, addr, &address.sin_addr);
//printf("%d\n", two);
    int three = connect(sockfd, (struct sockaddr *) &address, sizeof(address));
    if(three != 0){
	return -1;
    }
//printf("%s\n", strerror(errno));

    return sockfd;
}

/*
 *  Reads the board from the provided socket.
 */
void core_read_board(int socket, chessboard_t * board) {
    if (board != NULL) {
	char data [CHESSBOARD_SIZE * CHESSBOARD_SIZE * 2 + 1];
        read(socket, data, CHESSBOARD_SIZE * CHESSBOARD_SIZE * 2 + 1);
	board->turncolor = (color_t)data[0];

	for(int i = 0; i < CHESSBOARD_SIZE * CHESSBOARD_SIZE; i++){
//printf("%d\n", i);
	    if((int)data[(i*2+1)] != -1){
//printf("first if\n");
		board->pieces[i / CHESSBOARD_SIZE][i % CHESSBOARD_SIZE] = malloc(sizeof(piece_t));
		board->pieces[i / CHESSBOARD_SIZE][i % CHESSBOARD_SIZE]->type = (type_t)data[i*2+1];
		board->pieces[i / CHESSBOARD_SIZE][i % CHESSBOARD_SIZE]->color = (color_t)data[i*2+2];
	    }
	    else{
		board->pieces[i / CHESSBOARD_SIZE][i % CHESSBOARD_SIZE] = NULL;
	    }

	}
   }
}

void core_write_board(int socket, chessboard_t * board) {
	if (board != NULL) {
		char data[CHESSBOARD_SIZE * CHESSBOARD_SIZE * 2 + 1];
//		printf("size %d\n", CHESSBOARD_SIZE * CHESSBOARD_SIZE * 2 + 1);
		data[0] = (char) board->turncolor;
		for (int i = 0; i < CHESSBOARD_SIZE * CHESSBOARD_SIZE; i++) {
			//printf("%d %d -> ", i / CHESSBOARD_SIZE, i % CHESSBOARD_SIZE);
			piece_t * piece = board->pieces[i / CHESSBOARD_SIZE][i % CHESSBOARD_SIZE];
			if (piece != NULL) {
				data[i * 2 + 1] = (char) piece->type;
				data[i * 2 + 2] = (char) piece->color;
			} else {
				data[i * 2 + 1] = -1;
				data[i * 2 + 2] = -1;
			}
//			printf("byte %d: %d, %d (index [%d][%d])\n", i * 2 + 1, (int) data[i * 2 + 1], (int) data[i * 2 + 2], i / CHESSBOARD_SIZE, i % CHESSBOARD_SIZE);
		}
//		printf("Made it\n");
		int sent = send(socket, data, CHESSBOARD_SIZE * CHESSBOARD_SIZE * 2 + 1, 0);
//		printf("Sending %d bytes out of %d bytes\n", sent, CHESSBOARD_SIZE * CHESSBOARD_SIZE * 2 + 1);
	}
}

void core_read_move(int socket, char * move) {
	if (move != NULL) {
		read(socket, move, sizeof(char) * 4);
	}
}

/*
 *  Writes the board to the provided socket.
 */
void core_write_move(int socket, char * move) {
    if (move != NULL) {
        send(socket, move, sizeof(char) * 4, 0);
    }
}

void core_read_player_color(int socket, color_t * color) {
	read(socket, color, sizeof(color_t));
}

void core_write_player_color(int socket, color_t * color) {
	if (color != NULL) {
		send(socket, color, sizeof(color_t), 0);
	}
}
