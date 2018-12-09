#ifndef __core_chessboard_h__
#define __core_chessboard_h__

#define CHESSBOARD_SIZE 8

#define BLACK_PAWN chess_create_piece(PAWN, BLACK)
#define BLACK_ROOK chess_create_piece(ROOK, BLACK)
#define BLACK_KNIGHT chess_create_piece(KNIGHT, BLACK)
#define BLACK_BISHOP chess_create_piece(BISHOP, BLACK)
#define BLACK_QUEEN chess_create_piece(QUEEN, BLACK)
#define BLACK_KING chess_create_piece(KING, BLACK)
#define WHITE_PAWN chess_create_piece(PAWN, WHITE)
#define WHITE_ROOK chess_create_piece(ROOK, WHITE)
#define WHITE_KNIGHT chess_create_piece(KNIGHT, WHITE)
#define WHITE_BISHOP chess_create_piece(BISHOP, WHITE)
#define WHITE_QUEEN chess_create_piece(QUEEN, WHITE)
#define WHITE_KING chess_create_piece(KING, WHITE)


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
    piece_t * pieces[CHESSBOARD_SIZE][CHESSBOARD_SIZE];
} chessboard_t;

chessboard_t * chess_create_default_chessboard();
int chess_move_piece(int, int, int, int, chessboard_t *);
piece_t * chess_get_piece_at(int, int, chessboard_t *);
int chess_to_rank_index(int);
int chess_to_file_index(int);
char chess_get_piece_char(piece_t *);
color_t chess_get_tile_color(int, int);
piece_t * chess_create_piece(type_t, color_t);
int chess_piece_is_valid_move(piece_t *, int, int, piece_t *, int, int, int, chessboard_t *);
int chess_piece_is_piece_blocked(piece_t *, int, int, piece_t *, int, int, chessboard_t *);
int chess_can_piece_move_to(int, int, int, int, chessboard_t *);
int is_valid_board_position(int, int);

// chess piece move filters
int pawn_is_valid_move(piece_t *, int, int, piece_t *, int, int, int, chessboard_t *);
int pawn_is_piece_blocked(piece_t *, int, int, piece_t *, int, int, chessboard_t *);
int rook_is_valid_move(piece_t *, int, int, piece_t *, int, int, int, chessboard_t *);
int rook_is_piece_blocked(piece_t *, int, int, piece_t *, int, int, chessboard_t *);
int knight_is_valid_move(piece_t *, int, int, piece_t *, int, int, int, chessboard_t *);
int knight_is_piece_blocked(piece_t *, int, int, piece_t *, int, int, chessboard_t *);
int bishop_is_valid_move(piece_t *, int, int, piece_t *, int, int, int, chessboard_t *);
int bishop_is_piece_blocked(piece_t *, int, int, piece_t *, int, int, chessboard_t *);
int queen_is_valid_move(piece_t *, int, int, piece_t *, int, int, int, chessboard_t *);
int queen_is_piece_blocked(piece_t *, int, int, piece_t *, int, int, chessboard_t *);
int king_is_valid_move(piece_t *, int, int, piece_t *, int, int, int, chessboard_t *);
int king_is_piece_blocked(piece_t *, int, int, piece_t *, int, int, chessboard_t *);

#endif
