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

/**
* The Board class represents a chessboard and manages the pieces on it.
*/

class Board {
	Player whos_turn = WHITE_PLAYER;
	Piece* pieces[8][8];

public:
	Board();
	Board(const Board& board);
	~Board();
	Piece* getPiece(const int row,const int col) const;
	int code_response(const std::string res);
	bool there_is_a_piece_directly(const int src_row, const int src_col, const int dest_row, const int dest_col) const;
	bool there_is_a_piece_diagonally(const int src_row, const int src_col, const int dest_row, const int dest_col) const;

private:
	int convert_str_to_loc(const char str_loc) const;
	bool is_check();
	bool help_is_check(const int row_to_check, const int col_to_check) const;
	void move_piece(const int src_row, const int src_col, const int dest_row, const int dest_col);
	int* king_loc(const Player player) const;
	int get_iterator_num(const int loc_row, const int loc_col) const ;
};