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

    for(int y = 0; y < 9; y++){
	for(int x = 0; x < 9; x++){
	    if(y == 0){
		printf("_|a|b|c|d|e|f|g|h|_");
		break;
	    }
	    else if(x == 0 && (y != 0 && y != 9)){
		printf("%d|", y);
	    }
	    else{
		if(board->pieces[x-1][y-1].type == KING){
		//printf("\u2654");
		printf("K");
}
	    }
	}//end x for
	printf("\n");
    }


//get_move();
}
