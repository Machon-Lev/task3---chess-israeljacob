#pragma once
#include"Piece.h"
#include"Board.h"

class Knight
	: public Piece
{

public:
	Knight(Player player);
	bool is_legal_move(int src_row, int src_col, int dest_row, int dest_colconst,const Board* board) override;
};
