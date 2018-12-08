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

int is_valid_move(piece_t fromPiece, int fromRank, int fromFile, piece_t toPiece, int toRank, int toFile, chessboard_t * board) {

	// check if the piece is moving vertically
		if (fromFile == toFile) {

			// check if the piece is moving nowhere
			if (fromRank == toRank) {
				return true;
			}

			if (toRank > fromRank) {
				for (int i = fromRank + 1; i <= toRank; i++) {
					if (isPieceBlocking(fromPiece, board.getPieceAt(i, fromFile), i == toRank)) {
						return true;
					}
				}
				return false;
			} else {
				for (int i = fromRank - 1; i >= toRank; i--) {
					if (isPieceBlocking(fromPiece, board.getPieceAt(i, fromFile), i == toRank)) {
						return true;
					}
				}
				return false;
			}
		} else if (fromRank == toRank) {

			if (toFile > fromFile) {
				for (int i = fromFile + 1; i <= toFile; i++) {
					if (isPieceBlocking(fromPiece, board.getPieceAt(fromRank, i), i == toFile)) {
						return true;
					}
				}
				return false;
			} else {
				for (int i = fromFile - 1; i >= toFile; i--) {
					if (isPieceBlocking(fromPiece, board.getPieceAt(fromRank, i), i == toFile)) {
						return true;
					}
				}
				return false;
			}

			// check if we are moving on the bottom left to top right axis
		} else if (toRank - fromRank == toFile - fromFile) {
			if (toFile > fromFile) {
				int[] pos = new int[] { fromRank, fromFile };
				while (pos[0] != toRank && pos[1] != toFile) {
					moveRight(pos);
					moveUp(pos);
					if (board.isValidBoardPosition(pos[0], pos[1]) && isPieceBlocking(fromPiece, board.getPieceAt(pos[0], pos[1]), pos[1] == toFile)) {
						return true;
					}
				}
				return false;
			} else {
				int[] pos = new int[] { fromRank, fromFile };
				while (pos[0] != toRank && pos[1] != toFile) {
					moveLeft(pos);
					moveDown(pos);
					if (board.isValidBoardPosition(pos[0], pos[1]) && isPieceBlocking(fromPiece, board.getPieceAt(pos[0], pos[1]), pos[1] == toFile)) {
						return true;
					}
				}
				return false;
			}
			/*
			 * if (toRank > fromRank) { for (int i = fromRank + 1; i <= toRank; i++) { if
			 * (isPieceBlocking(fromPiece, board.getPieceAt(i, i - fromRank - 1 + fromFile),
			 * i == toRank)) { return true; } } return false; } else { for (int i = fromRank
			 * - 1; i >= toRank; i--) { if (isPieceBlocking(fromPiece, board.getPieceAt(i, i
			 * - fromRank - 1 + toFile), i == toRank)) { return true; } } return false; }
			 */

			// check if we are moving on the top left to bottom right axis
		} else if (toRank - fromRank == -(toFile - fromFile)) {
			if (toFile > fromFile) {
				int[] pos = new int[] { fromRank, fromFile };
				while (pos[0] != toRank && pos[1] != toFile) {
					moveLeft(pos);
					moveUp(pos);
					if (board.isValidBoardPosition(pos[0], pos[1]) && isPieceBlocking(fromPiece, board.getPieceAt(pos[0], pos[1]), pos[1] == toFile)) {
						return true;
					}
				}
				return false;
			} else {
				int[] pos = new int[] { fromRank, fromFile };
				while (pos[0] != toRank && pos[1] != toFile) {
					
					moveRight(pos);
					moveDown(pos);
					if (board.isValidBoardPosition(pos[0], pos[1]) && isPieceBlocking(fromPiece, board.getPieceAt(pos[0], pos[1]), pos[1] == toFile)) {
						return true;
					}
				}
				return false;
			}
			/*
			 * if (toRank > fromRank) { for (int i = fromRank + 1; i <= toRank; i++) { if
			 * (isPieceBlocking(fromPiece, board.getPieceAt(i, i - fromRank - 1 + toFile), i
			 * == toRank)) { return true; } } return false; } else { for (int i = fromRank -
			 * 1; i >= toRank; i--) { if (isPieceBlocking(fromPiece, board.getPieceAt(i, i -
			 * fromRank - 1 + fromFile), i == toRank)) { return true; } } return false; }
			 * 
			 */}

		return true;

}

int pawn_is_valid_move(piece_t fromPiece, int fromRank, int fromFile, piece_ toPiece, int toRank, int toFile, int firstMove, chessboard_t * board) {

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
