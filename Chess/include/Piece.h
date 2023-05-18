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
	virtual bool is_legal_move(int source_row, int source_col, int dest_row, int dest_col , const Board board) = 0;
};
