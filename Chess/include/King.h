#pragma once
#include "Piece.h"
#include"Board.h"

class King :
    public Piece
{
public:
    King(Player player);
    bool is_legal_move(const std::string str_loc, const Board board) override;
};

