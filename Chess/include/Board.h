#pragma once
#include"Piece.h"

class Piece;

class Board {
	Player whos_turn = WHITE_PLAYER;
	Piece* pieces[8][8];
	int* convert_str_to_loc(std::string str_loc);

public:
	Board();
	bool there_is_a_piece(std::string location);
	Piece* get_piece(const int* location)const;	

	friend class Piece;
};


