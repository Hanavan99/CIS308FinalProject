#include<stdio.h>
#include<string.h>

char input[6];
char source_move[3];
char target_move[3];


void get_move(){
    printf("%s", "Enter moves in the format: \"e2,e4\" (no spaces)\n");
    printf("%s", "Enter your move: \n");
    scanf("%s\n", input);
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

void displayBoard(){
    //getBoard
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
		printf("_|");
	    }
	}//end x for
	printf("\n");
    }

printf("\u2654");
}

int client_ui_main(int argc, char * argv){
    displayBoard();
    return 0;
}