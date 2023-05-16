#pragma once
#include"Piece.h"
#include"Board.h"

class Queen :
	public Piece
{
public:
	Queen(Player player);
	bool is_legal_move(const std::string str_loc, const Board board) override;
};