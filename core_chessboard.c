#include "core_chessboard.h"
#include <stdlib.h>
#include <string.h>

chessboard_t * chess_create_default_chessboard() {
	chessboard_t * board = malloc(sizeof(chessboard_t));
	board->turncolor = WHITE;
	piece_t * pieces[CHESSBOARD_SIZE][CHESSBOARD_SIZE] = {
	{ BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK },
	{ BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN },
	{ WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK }
	};
	memcpy(board->pieces, pieces, CHESSBOARD_SIZE * CHESSBOARD_SIZE * sizeof(piece_t));
	return board;
}

void chess_move_piece(int fromRank, int fromFile, int toRank, int toFile, chessboard_t * board) {
	piece_t * fromPiece = chess_get_piece_at(fromRank, fromFile, board);
	if (fromPiece != NULL && chess_can_piece_move_to(fromRank, fromFile, toRank, toFile, board)) {
		board->pieces[chess_to_rank_index(toRank)][chess_to_file_index(toFile)] = fromPiece;
		board->pieces[chess_to_rank_index(fromRank)][chess_to_file_index(fromFile)] = NULL;
		board->turncolor = board->turncolor == WHITE ? BLACK : WHITE;
	}
}

int chess_to_rank_index(int rank) {
    return CHESSBOARD_SIZE - rank;
}

int chess_to_file_index(int file) {
    return file - 1;
}

piece_t * chess_get_piece_at(int rank, int file, chessboard_t * board) {
	return board->pieces[chess_to_rank_index(rank)][chess_to_file_index(file)];
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

int is_piece_blocking(piece_t * fromPiece, piece_t * piece, int end) {
	if (piece == NULL) {
		return 0;
	} else {
		return end ? (fromPiece->color == piece->color) : 1;
	}
}

int move_up(int pos[]) {
	pos[1]++;
}

int move_down(int pos[]) {
	pos[1]--;
}

int move_left(int pos[]) {
	pos[0]--;
}

int move_right(int pos[]) {
	pos[0]++;
}

int is_valid_board_position(int rank, int file) {
	return rank >= 1 && rank <= CHESSBOARD_SIZE && file >= 1 && file <= CHESSBOARD_SIZE;
}

int chess_can_piece_move_to(int fromRank, int fromFile, int toRank, int toFile, chessboard_t * board) {
	piece_t * fromPiece = chess_get_piece_at(fromRank, fromFile, board);
	piece_t * toPiece = chess_get_piece_at(fromRank, fromFile, board);
	int firstMove = 1; // TODO make a function for this

	int validMove = 0;
	switch (fromPiece->type) {
	case PAWN:
		validMove = pawn_is_valid_move(fromPiece, fromRank, fromFile, toPiece, toRank, toFile, firstMove, board);
		break;
	case ROOK:
		validMove = rook_is_valid_move(fromPiece, fromRank, fromFile, toPiece, toRank, toFile, firstMove, board);
		break;
	case KNIGHT:
		validMove = knight_is_valid_move(fromPiece, fromRank, fromFile, toPiece, toRank, toFile, firstMove, board);
		break;
	case BISHOP:
		validMove = bishop_is_valid_move(fromPiece, fromRank, fromFile, toPiece, toRank, toFile, firstMove, board);
		break;
	case QUEEN:
		validMove = queen_is_valid_move(fromPiece, fromRank, fromFile, toPiece, toRank, toFile, firstMove, board);
		break;
	case KING:
		validMove = king_is_valid_move(fromPiece, fromRank, fromFile, toPiece, toRank, toFile, firstMove, board);
		break;
	}

	int blocked;
	switch (fromPiece->type) {
	case PAWN:
		blocked = pawn_is_piece_blocked(fromPiece, fromRank, fromFile, toPiece, toRank, toFile, board);
		break;
	case ROOK:
		blocked = rook_is_piece_blocked(fromPiece, fromRank, fromFile, toPiece, toRank, toFile, board);
		break;
	case KNIGHT:
		blocked = knight_is_piece_blocked(fromPiece, fromRank, fromFile, toPiece, toRank, toFile, board);
		break;
	case BISHOP:
		blocked = bishop_is_piece_blocked(fromPiece, fromRank, fromFile, toPiece, toRank, toFile, board);
		break;
	case QUEEN:
		blocked = queen_is_piece_blocked(fromPiece, fromRank, fromFile, toPiece, toRank, toFile, board);
		break;
	case KING:
		blocked = king_is_piece_blocked(fromPiece, fromRank, fromFile, toPiece, toRank, toFile, board);
		break;
	}
	return !blocked && validMove;
}

int is_valid_move(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, chessboard_t * board) {

	// check if the piece is moving vertically
	if (fromFile == toFile) {

		// check if the piece is moving nowhere
		if (fromRank == toRank) {
			return 1;
		}

		if (toRank > fromRank) {
			for (int i = fromRank + 1; i <= toRank; i++) {
				if (is_piece_blocking(fromPiece, chess_get_piece_at(i, fromFile, board), i == toRank)) {
					return 1;
				}
			}
			return 0;
		} else {
			for (int i = fromRank - 1; i >= toRank; i--) {
				if (is_piece_blocking(fromPiece, chess_get_piece_at(i, fromFile, board), i == toRank)) {
					return 1;
				}
			}
			return 0;
		}
	} else if (fromRank == toRank) {

		if (toFile > fromFile) {
			for (int i = fromFile + 1; i <= toFile; i++) {
				if (is_piece_blocking(fromPiece, chess_get_piece_at(fromRank, i, board), i == toFile)) {
					return 1;
				}
			}
			return 0;
		} else {
			for (int i = fromFile - 1; i >= toFile; i--) {
				if (is_piece_blocking(fromPiece, chess_get_piece_at(fromRank, i, board), i == toFile)) {
					return 1;
				}
			}
			return 0;
		}

		// check if we are moving on the bottom left to top right axis
		} else if (toRank - fromRank == toFile - fromFile) {
		if (toFile > fromFile) {
			int pos[2] = { fromRank, fromFile };
			while (pos[0] != toRank && pos[1] != toFile) {
				move_right(pos);
				move_up(pos);
				if (is_valid_board_position(pos[0], pos[1]) && is_piece_blocking(fromPiece, chess_get_piece_at(pos[0], pos[1], board), pos[1] == toFile)) {
					return 1;
				}
			}
			return 0;
		} else {
			int pos[2] = { fromRank, fromFile };
			while (pos[0] != toRank && pos[1] != toFile) {
				move_left(pos);
				move_down(pos);
				if (is_valid_board_position(pos[0], pos[1]) && is_piece_blocking(fromPiece, chess_get_piece_at(pos[0], pos[1], board), pos[1] == toFile)) {
					return 1;
				}
			}
			return 0;
		}

		// check if we are moving on the top left to bottom right axis
	} else if (toRank - fromRank == -(toFile - fromFile)) {
		if (toFile > fromFile) {
			int pos[2] = { fromRank, fromFile };
			while (pos[0] != toRank && pos[1] != toFile) {
				move_left(pos);
				move_up(pos);
				if (is_valid_board_position(pos[0], pos[1]) && is_piece_blocking(fromPiece, chess_get_piece_at(pos[0], pos[1], board), pos[1] == toFile)) {
					return 1;
				}
			}
			return 0;
		} else {
			int pos[2] = { fromRank, fromFile };
			while (pos[0] != toRank && pos[1] != toFile) {
				move_right(pos);
				move_down(pos);
				if (is_valid_board_position(pos[0], pos[1]) && is_piece_blocking(fromPiece, chess_get_piece_at(pos[0], pos[1], board), pos[1] == toFile)) {
					return 1;
				}
			}
			return 0;
		}
	}
	return 1;

}

int pawn_is_valid_move(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, int firstMove, chessboard_t * board) {

	color_t color = fromPiece->color;
	if (toRank - fromRank == (color == WHITE ? 2 : -2) && firstMove && toFile - fromFile == 0) {
		return toPiece == NULL;
	} else if (toRank - fromRank == (color == WHITE ? 1 : -1)) {
		if (toFile - fromFile == 0) {
			return toPiece == NULL;
		} else if (toFile - fromFile == 1 || toFile - fromFile == -1) {
			if (toPiece != NULL) {
				return toPiece->color != fromPiece->color;
			}
		}
	}


}

int rook_is_valid_move(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, int firstMove, chessboard_t * board) { return 0; }
int knight_is_valid_move(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, int firstMove, chessboard_t * board) { return 0; }
int bishop_is_valid_move(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, int firstMove, chessboard_t * board) { return 0; }
int queen_is_valid_move(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, int firstMove, chessboard_t * board) { return 0; }
int king_is_valid_move(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, int firstMove, chessboard_t * board) { return 0; }
int pawn_is_piece_blocked(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, chessboard_t * board) { return 1; }
int rook_is_piece_blocked(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, chessboard_t * board) { return 1; }
int knight_is_piece_blocked(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, chessboard_t * board) { return 1; }
int bishop_is_piece_blocked(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, chessboard_t * board) { return 1; }
int queen_is_piece_blocked(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, chessboard_t * board) { return 1; }
int king_is_piece_blocked(piece_t * fromPiece, int fromRank, int fromFile, piece_t * toPiece, int toRank, int toFile, chessboard_t * board) { return 1; }

