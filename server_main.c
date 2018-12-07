#include "core_chessboard.h"
#include <sys/socket.h>

int teama_fd = 0;
int teamb_fd = 0;
chessboard_t * board = chess_create_default_board();

void main(int argc, int* argv) {

	teama_fd = socket(AL_INET, SOCK_STREAM, 0);
	teamb_fd = socket(AL_INET, SOCK_STREAM, 0);

	

}
