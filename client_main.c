#include "client_ui.h"
#include "core_network.h"
#include <stdlib.h>

void main(int argc, const char* argv[]) {
    int socket = core_create_client_socket("129.130.10.39", 12345);
    chessboard_t * board = malloc(sizeof(chessboard_t));
    core_read_board(socket, board);

    display_board(board);
    get_move();
}
