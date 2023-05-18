#pragma once
#include "Piece.h"
#include"Board.h"

class Rook :
    public Piece
{
public:
    Rook(Player player);
    bool is_legal_move(const std::string str_loc, Board board) override;
};

