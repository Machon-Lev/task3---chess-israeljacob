#pragma once
#include"Piece.h"
#include<vector>
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include"King.h"
#include"Player.h"
#include<string>

class Piece;

class Board {
	Player whos_turn = WHITE_PLAYER;
	Piece* pieces[8][8];
	void move_piece(std::string res);

public:
	Board();
	Player get_whos_turn();
	void set_whos_turn();
	bool there_is_a_piece(std::string location);
	Piece* get_piece(int i, int j)const;
	int code_response(std::string res);
	int* convert_str_to_loc(std::string str_loc) const;

	friend class Piece;
};


