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
#include<string>

class Piece;

class Board {
	Player whos_turn = WHITE_PLAYER;
	Piece* pieces[8][8];
	void move_piece(int int_src_loc0, int int_src_loc1, int int_dest_loc0, int int_dest_loc1);
	bool help_is_chess(int row_to_check, int col_to_check);
	int get_iterator_num(int loc_row, int loc_col);

public:
	Board();
	Player get_whos_turn();
	void set_whos_turn();
	bool there_is_a_piece(int loc_row, int loc_col);
	Piece* get_piece(int i, int j)const;
	int code_response(std::string res);
	int* convert_str_to_loc(std::string str_loc) const;
	bool is_chess(int int_source_loc0, int int_source_loc1, int int_dest_loc0, int int_dest_loc1);
	int* king_loc(Player player);
	Piece* there_is_a_piece_diagonally(int int_source_loc0, int int_source_loc1, int int_dest_loc0, int int_dest_loc1);
	Piece* there_is_a_piece_directly(int int_source_loc0, int int_source_loc1, int int_dest_loc0, int int_dest_loc1);

	friend class Piece;
};


