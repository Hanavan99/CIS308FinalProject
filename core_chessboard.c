#include "core_chessboard.h"
#include <stdlib.h>
#include <string.h>

<<<<<<< HEAD
chessboard_t * chess_create_default_chessboard() {
	chessboard_t * board = malloc(sizeof(chessboard_t));
	board->turncolor = WHITE;
	piece_t * pieces[CHESSBOARD_SIZE][CHESSBOARD_SIZE] = {
	{ BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK },
	{ BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN },
=======
/*const piece_t black_pawn = chess_create_piece(PAWN, BLACK);
const piece_t black_rook = chess_create_piece(ROOK, BLACK);
const piece_t black_knight = chess_create_piece(KNIGHT, BLACK);
const piece_t black_bishop = chess_create_piece(BISHOP, BLACK);
const piece_t black_queen = chess_create_piece(QUEEN, BLACK);
const piece_t black_king = chess_create_piece(KING, BLACK);
const piece_t white_pawn = chess_create_piece(PAWN, WHITE);
const piece_t white_rook = chess_create_piece(ROOK, WHITE);
const piece_t white_knight = chess_create_piece(KNIGHT, WHITE);
const piece_t white_bishop = chess_create_piece(BISHOP, WHITE);
const piece_t white_queen = chess_create_piece(QUEEN, WHITE);
const piece_t white_king = chess_create_piece(KING, WHITE);

const piece_t[CHESSBOARD_SIZE][CHESSBOARD_SIZE] default_chessboard = {
	{ black_rook, black_knight, black_bishop, black_queen, black_king, black_bishop, black_knight, black_rook },
	{ black_pawn, black_pawn, black_pawn, black_pawn, black_pawn, black_pawn, black_pawn, black_pawn },
>>>>>>> bf9df00b5525a3faaf1ab084d80644af4e4a309b
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN },
	{ WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK }
	};
	memcpy(board->pieces, pieces, CHESSBOARD_SIZE * CHESSBOARD_SIZE);
	return board;
}*/

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

piece_t * chess_create_piece(type_t type, color_t color) {
    piece_t * piece = malloc(sizeof(piece_t));
    piece->type = type;
    piece->color = color;
    return piece;
}
