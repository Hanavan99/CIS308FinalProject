#ifndef __core_chessboard_h__
#define __core_chessboard_h__

typedef enum {
    BLACK,
    WHITE
} team_t;

typedef enum {
    BLACK,
    WHITE
} tile_t;

typedef struct {
    enum {
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    } piecetype;
    team_t team;
} piece_t;


typedef struct {
    tile_t tiles[8][8];
    piece_t pieces[8][8];
} board_t;

#endif
