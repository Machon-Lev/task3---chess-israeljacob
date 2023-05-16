#include "Board.h"

Board::Board()
{
	piecs[0][0] = new Rook(WHITE_PLAYER);
	piecs[0][1] = new Knight(WHITE_PLAYER);
	piecs[0][2] = new Bishop(WHITE_PLAYER);
	piecs[0][3] = new Queen(WHITE_PLAYER);
	piecs[0][4] = new King(WHITE_PLAYER);
	piecs[0][5] = new Bishop(WHITE_PLAYER);
	piecs[0][6] = new Knight(WHITE_PLAYER);
	piecs[0][7] = new Rook(WHITE_PLAYER);

	for (size_t i = 2; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			pieces[i][j] = nullptr;
		}
	}

	piecs[7][0] = new Rook(BLACK_PLAYER);
	piecs[7][1] = new Knight(BLACK_PLAYER);
	piecs[7][2] = new Bishop(BLACK_PLAYER);
	piecs[7][3] = new Queen(BLACK_PLAYER);
	piecs[7][4] = new King(BLACK_PLAYER);
	piecs[7][5] = new Bishop(BLACK_PLAYER);
	piecs[7][6] = new Knight(BLACK_PLAYER);
	piecs[7][7] = new Rook(BLACK_PLAYER);
}

int* Board::conversion_to_location(string loc)
{
	int* location = new int[2];
	if (loc[0] >= 65 && loc[0] <= 72)
		location[0] = int(loc[0]) - 65;
	else
		location[0] = int(loc[0]) - 97;
	location[1] = int(loc[1]) - 1;
}

bool Board::there_is_a_piece(string location)
{
	int* loc = conversion_to_location(location);
	return pieces[loc[0]][loc[1]] != nullptr;
}
