#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"core_chessboard.h"
#include"client_ui.h"

char input[6];
char source_move[3];
char target_move[3];

void get_move(){
    printf("%s", "Enter moves in the format: \"e2,e4\" (no spaces)\n");
    printf("%s", "Enter your move: \n");
    scanf("%s\n", input);
    tokenize_moves();
}

void tokenize_moves(){
    char * parts = strtok(input, ",");
    char * moves[2];
    int i = 0;

    while(parts != NULL){
	moves[i] = parts;
	parts = strtok(NULL, ",");
	i++;
    }

    strcpy(source_move, moves[0]);
    strcpy(target_move, moves[1]);
}

void display_board(){
//    chessboard_t * board = malloc(sizeof(chessboard_t));
//    core_read_board(board);

    chessboard_t * board = malloc(sizeof(chessboard_t));
    board->pieces[0][0] = chess_create_piece(KING, BLACK);
    board->pieces[0][1] = chess_create_piece(KING, BLACK);
    board->pieces[0][2] = chess_create_piece(KING, BLACK);
    board->pieces[0][3] = chess_create_piece(KING, BLACK);
    board->pieces[0][4] = chess_create_piece(KING, BLACK);
    board->pieces[0][5] = chess_create_piece(KING, BLACK);
    board->pieces[0][6] = chess_create_piece(KING, BLACK);
    board->pieces[0][7] = chess_create_piece(KING, BLACK);

    printf("\033[40m\033[37m");
    printf("_|a b c d e f g h\n");

    for(int y = 8; y > 0; y--){
	for(int x = 0; x < 9; x++){
	    if(x == 0){
		printf("%d|", y);
	    }
	    else{

		if(chess_get_tile_color((x-1), (y)) == WHITE){
		    printf("\033[45m");
		}
		else{
		    printf("\033[44m");
		}
		switch(board->pieces[x-1][y-1].type){
		    case KING:
		    printf("\u265A ");
    		    //printf("K ");
		    break;

		    case QUEEN:
		    printf("Q ");
		    break;

		    case BISHOP:
		    printf("B ");
		    break;

		    case KNIGHT:
		    printf("N ");
		    break;

		    case ROOK:
		    printf("R ");
		    break;

		    case PAWN:
		    printf("\u2659 ");
		    //printf("P ");
		    break;

		    default:
		    printf("D ");
		}
	    }
	}//end x for
	printf("\033[40m\033[37m\n");
    }

//get_move();
}
