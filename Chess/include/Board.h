#pragma once
#include"Piece.h"
#include<vector>
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include"King.h"
#include"Pawn.h"
#include"Player.h"

class Piece;

class Board {
	Player whos_turn = WHITE_PLAYER;
	Piece* pieces[8][8];

public:
	Board();
	Piece* getPiece(int row, int col);
	int code_response(std::string res);
	bool there_is_a_piece_directly(int src_row, int src_col, int dest_row, int dest_col);
	bool there_is_a_piece_diagonally(int src_row, int src_col, int dest_row, int dest_col);

private:
	int convert_str_to_loc(char str_loc) const;
	bool is_chess(int src_row, int src_col, int dest_row, int dest_col);
	bool help_is_chess(int row_to_check, int col_to_check);
	void move_piece(int src_row, int src_col, int dest_row, int dest_col);
	int* king_loc(Player player);
	int get_iterator_num(int loc_row, int loc_col);
};


