#include "Rook.h"
#include"Board.h"

Rook::Rook(Player player) : Piece(player)
{
}

bool Rook::is_legal_move(int src_row, int src_col, int dest_row, int dest_col, Board board)
{
	return rook_is_legal_move(src_row, src_col, dest_row, dest_col, board);
}

bool rook_is_legal_move(int src_row, int src_col, int dest_row, int dest_col, Board board)
{
	if (src_row != dest_row && src_col != dest_col)
		return false;

	return !board.there_is_a_piece_directly(src_row, src_col, dest_row, dest_col);
}
