#include "client_ui.h"
#include "core_network.h"
#include <stdlib.h>
#include <stdio.h>

void main(int argc, const char* argv[]) {
    int socket = core_create_client_socket("129.130.10.39", 12345);
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
    core_read_board(socket, board);
    display_board(board, * color);
if(board->turncolor == * color){
    	char move [4];
    	get_move(move);
    	core_write_move(socket, move);
    }
}
}
