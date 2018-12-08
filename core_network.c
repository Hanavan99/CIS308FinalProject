#include "core_network.h"
#include "core_chessboard.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int core_create_client_socket(char * addr, int port){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    //address.sin_addr.s_addr = "129.130.10.39";
    address.sin_port = htons(port);
    inet_pton(AF_INET, addr, &address);
    connect(sockfd, (struct sockaddr *) &address, sizeof(address));

    return sockfd;
}

/*
 *  Reads the board from the provided socket.
 */
void core_read_board(int socket, chessboard_t * board) {
    if (board != NULL) {
        read(socket, (char *)board, sizeof(chessboard_t));
   }
}

/*
 *  Writes the board to the provided socket.
 */
void core_write_moves(int socket, char source_move[], char target_move[]) {
    if (source_move != NULL && target_move != NULL) {
	char sned [] = {source_move[0], source_move[1], target_move[0], target_move[1]};
        send(socket, sned, sizeof(char) * 4, 0);
    }
}
