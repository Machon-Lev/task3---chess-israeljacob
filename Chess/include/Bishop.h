#pragma once
#include "Piece.h"
#include"Board.h"

class Bishop :
	public Piece
{
public:
	Bishop(Player player);
	bool is_legal_move(int src_row, int src_col, int dest_row, int dest_col, Board board) override;
};

bool bishop_is_legal_move(int src_row, int src_col, int dest_row, int dest_col, Board board);
