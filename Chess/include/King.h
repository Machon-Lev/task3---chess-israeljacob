#pragma once
#include "Piece.h"
#include"Board.h"

class King :
    public Piece
{
public:
    King(Player player);
    bool is_legal_move(int int_source_loc0, int int_source_loc1, int int_dest_loc0, int int_dest_loc1, Board board) override;

};

