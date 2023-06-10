#include "Piece.h"
#include"Board.h"

class Board;

/**
	 * Constructs a new Piece object with the specified player.
	 *
	 * @param player The player who owns the piece.
	 */
Piece::Piece(Player player)
{
	_player = player;
}

/**
	 * Gets the player who owns the piece.
	 *
	 * @return The player who owns the piece.
	 */
Player Piece::get_player() const
{
	return _player;
}



