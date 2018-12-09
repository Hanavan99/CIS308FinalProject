#include "client_ui.h"
#include "core_network.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void main(int argc, char ** argv) {
    if(argc != 3){
	printf("Invalid number of arguments. Usage ./client [ip] [port]\n");
    	return;
    }
    int socket = core_create_client_socket(argv[1], atoi(argv[2]));
    if(socket == -1){
	printf("Error creating socket: %s\n", strerror(errno));
	return;
    }
    color_t * color = malloc(sizeof(color_t));
    core_read_player_color(socket, color);
    chessboard_t * board = malloc(sizeof(chessboard_t));
    //core_read_board(socket, board);
    char * name = (char *)board;
    //for(int i = 0; i < sizeof(chessboard_t); i++){
//	printf("%d -> %d\n", i, (int)*(((char *) board) + i));
  //  }
    //printf("\n");
while(1){
    printf("\033[H\033[J");
    core_read_board(socket, board);
    display_board(board, * color);
if(board->turncolor == * color){
    	char move [4];
    	get_move(move);
    	core_write_move(socket, move);
    }
}
}
