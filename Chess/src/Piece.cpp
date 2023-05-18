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

bool Piece::the_piece_belongs_to(const Player player, const std::string str_loc, Board board) const
{
	if (board.there_is_a_piece(str_loc))
	{
		int* int_loc = board.convert_str_to_loc(str_loc);
		if ((*board.get_piece(int_loc[0], int_loc[1]))._player != player)
			return true;
	}
	return false;
}


