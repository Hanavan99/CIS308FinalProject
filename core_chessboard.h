#ifndef __core_chessboard_h__
#define __core_chessboard_h__

#define CHESSBOARD_SIZE 8


typedef enum {
    BLACK,
    WHITE
} color_t;

typedef enum {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
} type_t;

typedef struct piece_t {
    type_t type;
    color_t color;
} piece_t;

typedef struct {
    color_t turncolor;
    piece_t pieces[CHESSBOARD_SIZE][CHESSBOARD_SIZE];
} chessboard_t;

chessboard_t * chess_create_default_chessboard();
void chess_move_piece(chessboard_t *, int, int, int, int);
piece_t chess_get_piece_at(chessboard_t *, int, int);
int chess_to_rank_index(int);
int chess_to_file_index(int);
char chess_get_piece_char(piece_t);
color_t chess_get_tile_color(int, int);
piece_t chess_create_piece(type_t, color_t);
int chess_piece_is_valid_move(piece_t, int, int, piece_t, int, int, int, chessboard_t *);
int chess_piece_is_piece_blocked(piece_t, int, int, piece_t, int, int, chessboard_t *);

// chess piece move filters
int pawn_is_valid_move(piece_t, int, int, piece_t, int, int, int, chessboard_t *);
int pawn_is_piece_blocked(piece_t, int, int, piece_t, int, int, chessboard_t *);
int rook_is_valid_move(piece_t, int, int, piece_t, int, int, int, chessboard_t *);
int rook_is_piece_blocked(piece_t, int, int, piece_t, int, int, chessboard_t *);
int knight_is_valid_move(piece_t, int, int, piece_t, int, int, int, chessboard_t *);
int knight_is_piece_blocked(piece_t, int, int, piece_t, int, int, chessboard_t *);
int bishop_is_valid_move(piece_t, int, int, piece_t, int, int, int, chessboard_t *);
int bishop_is_piece_blocked(piece_t, int, int, piece_t, int, int, chessboard_t *);
int queen_is_valid_move(piece_t, int, int, piece_t, int, int, int, chessboard_t *);
int queen_is_piece_blocked(piece_t, int, int, piece_t, int, int, chessboard_t *);
int king_is_valid_move(piece_t, int, int, piece_t, int, int, int, chessboard_t *);
int king_is_piece_blocked(piece_t, int, int, piece_t, int, int, chessboard_t *);

const piece_t black_pawn;
const piece_t black_rook;
const piece_t black_knight;
const piece_t black_bishop;
const piece_t black_queen;
const piece_t black_king;
const piece_t white_pawn;
const piece_t white_rook;
const piece_t white_knight;
const piece_t white_bishop;
const piece_t white_queen;
const piece_t white_king;

const piece_t[CHESSBOARD_SIZE][CHESSBOARD_SIZE] default_chessboard;

#endif
