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

color_t chess_get_tile_color(int rank, int file) {
    return (rank + file) % 2 == 0 ? WHITE : BLACK;
}

piece_t chess_create_piece(type_t type, color_t color) {
    piece_t piece;
    piece.type = type;
    piece.color = color;
    return piece;
}
