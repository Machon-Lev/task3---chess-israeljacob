#include "Piece.h"
#include"Board.h"

class Board;

Piece::Piece(Player player)
{
	_player = player;
}

Player Piece::get_player() const
{
	return _player;
}

bool Piece::the_piece_belongs_to(const Player player, const int loc_row, const int loc_col, Board board) const
{
	if (board.there_is_a_piece(loc_row, loc_col))
	{
		if ((*board.get_piece(loc_row, loc_col))._player != player)
			return true;
	}
	return false;
}



