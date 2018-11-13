#include<stdio.h>
#include<string.h>

char input[6];
char source_move[3];
char target_move[3];

int client_ui_main(int argc, const char * argv[]){

}

void get_move(){
    printf("Enter moves in the format: \"e2,e4\" (no spaces)\n");
    printf("Enter your move: \n");
    scanf("%s\n", input);
}

void tokenize_moves(){
    char * parts = strtok(move, ",");
    char * moves[2];
    int i = 0;

    while(parts != NULL){
	moves[i] = parts;
	parts = strok(NULL, ",");
	i++;
    }

    strcpy(source_move, moves[0]);
    strcpy(target_move, moves[1]);
}
