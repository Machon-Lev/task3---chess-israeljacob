#include "Rook.h"
#include"Board.h"

Rook::Rook(Player player) : Piece(player)
{
}

bool Rook::is_legal_move(int int_source_loc0, int int_source_loc1, int int_dest_loc0, int int_dest_loc1, Board board)
{
	if (int_source_loc0 != int_dest_loc0 && int_source_loc1 != int_dest_loc1)
		return false;

	return !board.there_is_a_piece_directly(int_source_loc0, int_source_loc1, int_dest_loc0, int_dest_loc1);
}
