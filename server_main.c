#include "core_chessboard.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 12345

int serversocket_fd = 0;
int teama_fd = 0;
int teamb_fd = 0;
chessboard_t * board;

void main(int argc, int* argv) {

	board = chess_create_default_chessboard();

	printf("Server initializing\n");
	serversocket_fd = socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1;
	setsockopt(serversocket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	printf("Binding to address\n");
	bind(serversocket_fd, (struct sockaddr *) &address, sizeof(address));

	printf("Server going into listen mode\n");
	listen(serversocket_fd, 2);

	struct sockaddr * addr;
	struct socklen_t * len;
	printf("Server waiting for client 1\n");
	teama_fd = accept(serversocket_fd, addr, len);

	printf("Server waiting for client 2\n");
	teamb_fd = accept(serversocket_fd, addr, len);

}
