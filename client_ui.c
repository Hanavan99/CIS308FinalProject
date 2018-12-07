#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"core_chessboard.h"
#include"client_ui.h"

char input[3];
char source_move[3];
char target_move[3];

void get_move(){
    int flag = 0;

    do{
        printf("Enter the coordinates (\"e2\") of the piece you would like to move: ");
        scanf("%s", input);
        printf("\n");
        flag = check_move(input, source_move);
    } while(flag == 0);
    flag = 0;

    do{
    printf("Enter the coordinates (\"e2\") of the location you would like to move your piece to: ");
    scanf("%s", input);
    printf("\n");
    flag = check_move(input, target_move);
    } while(flag == 0);
}

int check_move(char input [], char output []){

    switch(input[0]){
    	case 'a':
	case 'b':
  	case 'c':
  	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	break;
	default:
	printf("Invalid input\n\n");
	return 0;
    }

    switch(input[1]){
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	break;
	default:
	printf("Invalid input\n\n");
	return 0;
    }

    strcpy(output, input);
    return 1;
}

void display_board(){
    chessboard_t * board = chess_create_default_chessboard();

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
		switch(board->pieces[x-1][y-1]->type){
		    case KING:
		    if(board->pieces[x-1][y-1]->color == WHITE){
		        printf("\u2654 ");
		    }
		    else{
			printf("\u265A ");
		    }
    		    //printf("K ");
		    break;

		    case QUEEN:
		    if(board->pieces[x-1][y-1]->color == WHITE){
			printf("\u2655 ");
		    }
		    else{
			printf("\u265B ");
		    }
		    //printf("Q ");
		    break;

		    case ROOK:
		    if(board->pieces[x-1][y-1]->color == WHITE){
		    	printf("\u2656 ");
		    }
		    else {
			printf("\u265C ");
		    }
		    //printf("B ");
		    break;

		    case BISHOP:
		    if(board->pieces[x-1][y-1]->color == WHITE){
			printf("\u2657 ");
		    }
		    else{
			printf("\u2657D ");
		    }
		    //printf("N ");
		    break;

		    case KNIGHT:
		    if(board->pieces[x-1][y-1]->color == WHITE){
			printf("\u2658 ");
		    }
		    else{
			printf("\u265E ");
		    }
		    //printf("R ");
		    break;

		    case PAWN:
		    if(board->pieces[x-1][y-1]->color == WHITE){
			printf("\u2659 ");
		    }
		    else{
			printf("\u265F ");
		    }
		    //printf("P ");
		    break;

		    default:
		    printf(" ");
		}
	    }
	}//end x for
	printf("\033[40m\033[37m\n");
    }

//get_move();
}
