#include "Queen.h"

Queen::Queen(Player player) : Piece(player)
{
}

bool Queen::is_legal_move(int src_row, int src_col, int dest_row, int dest_col, Board board)
{
    return rook_is_legal_move(src_row, src_col, dest_row, dest_col, board)
        || bishop_is_legal_move(src_row, src_col, dest_row, dest_col, board);
}
