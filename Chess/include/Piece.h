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
	bool the_piece_belongs_to(const Player player,const std::string str_loc, Board board) const;
	virtual bool is_legal_move(const std::string str_loc,const Board board) = 0;
};
