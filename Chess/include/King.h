#pragma once
#include "Piece.h"
#include"Board.h"

class King :
    public Piece
{
public:
    King(Player player);
    bool is_legal_move(int src_row, int src_col, int dest_row, int dest_col, Board board) override;

};

