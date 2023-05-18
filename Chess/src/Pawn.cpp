#include "Pawn.h"

Pawn::Pawn(Player player) : Piece(player)
{

}

bool Pawn::is_legal_move(int src_row, int src_col, int dest_row, int dest_col, Board board)
{
    if (_player == WHITE_PLAYER && dest_row - src_row == 1 && abs(dest_col - src_col) == 1
        && board.getPiece(dest_row, dest_col) != nullptr)
        return true;
    else if (_player == BLACK_PLAYER && dest_row - src_row == -1 && abs(dest_col - src_col) == 1
        && board.getPiece(dest_row, dest_col) != nullptr)
        return true;

    if (src_col != dest_col)
        return false;

    if (_player == WHITE_PLAYER && dest_row != 3 && dest_row - src_row != 1)
        return false;
    else if(_player == BLACK_PLAYER && dest_row != 4 && dest_row - src_row != -1)
        return false;

    if (_player == WHITE_PLAYER)
        return !board.there_is_a_piece_directly(src_row, src_col, dest_row + 1, dest_col);
    else
        return !board.there_is_a_piece_directly(src_row, src_col, dest_row - 1, dest_col);
}
