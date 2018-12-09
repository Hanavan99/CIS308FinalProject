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
	
	printf("%d\n", sizeof(chessboard_t));

	board = chess_create_default_chessboard();

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
//	char * data = malloc(sizeof(chessboard_t));
//	for (int i = 0; i < sizeof(chessboard_t); i++) {
//		printf("%d -> %d\n", i, (int) *(((char *) board) + i));
//		data[i] = (char) *(((char *) board) + i);
//	}
	//char * text = "test\n";
	//int sent = send(teama_fd, text, strlen(text), 0);
	//printf("Sent %d bytes\n", sent);
	//if (sent == -1) {
	//	printf(strerror(errno));
	//}
//	int sent = send(teama_fd, data, sizeof(chessboard_t), 0);
//	printf("Should send %d bytes and sent %d bytes\n", sizeof(chessboard_t), sent);

	printf("Server waiting for client 2\n");
	teamb_fd = accept(serversocket_fd, addr, len);

}
