#pragma once
#include<string>
#include "Player.h"

class Board;

class Piece
{
private:
	Player _player;

public:
	Piece(Player player);
	Player get_player() const;
	bool the_piece_belongs_to(const Player player, const int loc_row, const int loc_col, Board board) const;
	virtual bool is_legal_move(int int_source_loc0, int int_source_loc1, int int_dest_loc0, int int_dest_loc1, const Board board) = 0;
};
