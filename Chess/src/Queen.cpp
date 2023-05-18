#include "Queen.h"

Queen::Queen(Player player) : Piece(player)
{
}

bool Queen::is_legal_move(int src_row, int src_col, int dest_row, int dest_col, Board board)
{
    if ((src_row != dest_row && src_col != dest_col) 
        && abs(src_row - dest_row) != abs(src_col - dest_col))
        return false;
    if(abs(src_row - dest_row) == abs(src_col - dest_col))
        return !board.there_is_a_piece_diagonally(src_row, src_col, dest_row, dest_col);
    else
        return !board.there_is_a_piece_directly(src_row, src_col, dest_row, dest_col);
}
