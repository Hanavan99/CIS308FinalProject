#include "core_network.h"
#include "core_chessboard.h"
#include <sys/socket.h>
#include <netinet/in.h>

/*
 *  Reads the board from the provided socket.
 */
void core_read_board(int socket, board_t* board) {
//    if (board != NULL) {
  //      read(socket, board, sizeof(board_t));
   // }
}

/*
 *  Writes the board to the provided socket.
 */
void core_write_board(int socket, board_t* board) {
  //  if (board != NULL) {
    //    send(socket, board, sizeof(board_t), 0);
   // }
}
