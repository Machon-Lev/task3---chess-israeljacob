#include "Bishop.h"

Bishop::Bishop(Player player) :Piece(player)
{

}

bool Bishop::is_legal_move(int src_row, int src_col, int dest_row, int dest_col,const Board* board)
{
    return bishop_is_legal_move(src_row, src_col, dest_row, dest_col, board);
}

bool bishop_is_legal_move(int src_row, int src_col, int dest_row, int dest_col,const Board* board)
{
    if (abs(src_row - dest_row) != abs(src_col - dest_col))
        return false;
    return !(*board).there_is_a_piece_diagonally(src_row, src_col, dest_row, dest_col);
}
