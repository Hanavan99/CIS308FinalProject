#include "core_chessboard.h"

#ifndef __core_network_h__
#define __core_network_h__

int core_create_client_socket(char *, int);
void core_read_board(int, chessboard_t *);
void core_write_board(int, chessboard_t *);
void core_read_move(int, char *);
void core_write_move(int, char *);
void core_read_player_color(int, color_t *);
void core_write_player_color(int, color_t *);

#endif
