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



