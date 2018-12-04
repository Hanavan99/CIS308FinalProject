#include "core_chessboard.h"

void chess_move_piece(chessboard_t * board, int fromrank, int fromfile, int torank, int tofile) {
    // TODO implement
}

int chess_to_rank_index(int rank) {
    return CHESSBOARD_SIZE - rank;
}

int chess_to_file_index(int file) {
    return file - 1;
}

int chess_get_tile_color(int rank, int file) {
    return (rank + file) % 2 == 0 ? WHITE : BLACK;
}
