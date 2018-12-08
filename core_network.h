#include "core_chessboard.h"

#ifndef __core_network_h__
#define __core_network_h__

int core_create_client_socket(char *, int);
void core_read_board(int, chessboard_t *);
void core_write_board(int, chessboard_t *);

#endif
