#include "Board.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "Piece.h"
#include "Piece.h"
#include"King.h"
#include"Player.h"


int* Board::convert_str_to_loc(std::string str_loc)
{
	int* int_loc = new int[2];
	if (str_loc[0] >= 65 && str_loc[0] <= 72)
		int_loc[0] = int(str_loc[0]) - 65;
	else
		int_loc[0] = int(str_loc[0]) - 97;
	int_loc[1] = int(str_loc[1]) - 1;
	return int_loc;
}

Board::Board()
{
	pieces[0][0] = new Rook(WHITE_PLAYER);
	pieces[0][1] = new Knight(WHITE_PLAYER);
	pieces[0][2] = new Bishop(WHITE_PLAYER);
	pieces[0][3] = new Queen(WHITE_PLAYER);
	pieces[0][4] = new King(WHITE_PLAYER);
	pieces[0][5] = new Bishop(WHITE_PLAYER);
	pieces[0][6] = new Knight(WHITE_PLAYER);
	pieces[0][7] = new Rook(WHITE_PLAYER);

	for (size_t i = 2; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			pieces[i][j] = nullptr;
		}
	}

	pieces[7][0] = new Rook(WHITE_PLAYER);
	pieces[7][1] = new Knight(BLACK_PLAYER);
	pieces[7][2] = new Bishop(BLACK_PLAYER);
	pieces[7][3] = new Queen(BLACK_PLAYER);
	pieces[7][4] = new King(BLACK_PLAYER);
	pieces[7][5] = new Bishop(BLACK_PLAYER);
	pieces[7][6] = new Knight(BLACK_PLAYER);
	pieces[7][7] = new Rook(BLACK_PLAYER);
}

bool Board::there_is_a_piece(std::string str_loc) 
{
	int* loc = convert_str_to_loc(str_loc);
	return pieces[loc[0]][loc[1]] != nullptr;
}

Piece* Board::get_piece(const int* location) const
{
	return pieces[location[0]][location[1]];
}



