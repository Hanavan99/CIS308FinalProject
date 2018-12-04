#ifndef __core_chessboard_h__
#define __core_chessboard_h__

#define CHESSBOARD_SIZE 8

typedef enum {
    BLACK,
    WHITE
} color_t;

typedef struct {
    enum {
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    } type;
    color_t color;
} piece_t;


typedef struct {
    color_t turncolor;
    color_t tiles[CHESSBOARD_SIZE][CHESSBOARD_SIZE];
    piece_t pieces[CHESSBOARD_SIZE][CHESSBOARD_SIZE];
} chessboard_t;

void chess_move_piece(chessboard_t *, int, int, int, int);
piece_t chess_get_piece_at(chessboard_t *, int, int);
int chess_to_rank_index(int);
int chess_to_file_index(int);
char chess_get_piece_char(piece_t);
color_t chess_get_tile_color(int, int);

#endif
