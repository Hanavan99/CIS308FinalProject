#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"core_chessboard.h"
#include"client_ui.h"

char input[100];
char source_move[3];
char target_move[3];

void get_move(char move []){
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

    move[0] = source_move[0];
    move[1] = source_move[1];
    move[2] = target_move[0];
    move[3] = target_move[1];
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

void display_board(chessboard_t * board, color_t color){
//printf("%ld\n", sizeof(chessboard_t));
    printf("\033[00m\033[37m");
    if(color == WHITE) { printf("_|a b c d e f g h\n"); }
    else{ printf("_|h g f e d c b a\n"); }

    for(int y = 8; y > 0; y--){
	for(int x = 0; x < 9; x++){
	    if(x == 0){
		if(color == WHITE) { printf("%d|", y); }
		else{ printf("%d|", (8-y)+1); }
	    }
	    else{

		if(chess_get_tile_color((x-1), (y)) == WHITE){
		    printf("\033[45m");
		}
		else{
		    printf("\033[44m");
		}

		piece_t * piece = board->pieces[color == WHITE ? 8-y : y-1][color == WHITE ? x-1 : 8-x];
//printf("got the board piece\n");
		if(piece == NULL) {
		    printf("  ");
		    continue;
		}
//printf("%d\n", piece->type);
		switch(piece->type){
		    case KING:
//printf("king swithc\n");
		    if(piece->color == WHITE){
		        printf("\033[37m\u2654 ");
		    }
		    else{
			printf("\033[30m\u265A ");
		    }
    		    //printf("K ");
		    break;

		    case QUEEN:
		    if(piece->color == WHITE){
			printf("\033[37m\u2655 ");
		    }
		    else{
			printf("\033[30m\u265B ");
		    }
		    //printf("Q ");
		    break;

		    case ROOK:
//printf("rook switch\n");
		    if(piece->color == WHITE){
		    	printf("\033[37m\u2656 ");
		    }
		    else {
			printf("\033[30m\u265C ");
		    }
		    //printf("B ");
		    break;

		    case BISHOP:
		    if(piece->color == WHITE){
			printf("\033[37m\u2657 ");
		    }
		    else{
			printf("\033[30m\u265D ");
		    }
		    //printf("N ");
		    break;

		    case KNIGHT:
		    if(piece->color == WHITE){
			printf("\033[37m\u2658 ");
		    }
		    else{
			printf("\033[30m\u265E ");
		    }
		    //printf("R ");
		    break;

		    case PAWN:
		    if(piece->color == WHITE){
			printf("\033[37m\u2659 ");
		    }
		    else{
			printf("\033[30m\u265F ");
		    }
		    //printf("P ");
		    break;

		    default:
		    printf(" ");
		}
	    }
	}//end x for
	printf("\033[00m\033[37m\n");
    }
}
