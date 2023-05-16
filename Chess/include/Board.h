#pragma once
#include<string>
#include"Piece.h"
#include"Player.h"

using namespace std::string;

class Piece;
int SIZE = 8;
class Board {
	Player whos_turn = WHITE_PLAYER;
	Piece pieces[SIZE][SIZE];

	int* conversion_to_location(string loc);
public:
	Board();
	bool there_is_a_piece(string location);
};