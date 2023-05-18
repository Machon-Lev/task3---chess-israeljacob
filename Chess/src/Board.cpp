#include "Board.h"

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

	pieces[7][0] = new Rook(BLACK_PLAYER);
	pieces[7][1] = new Knight(BLACK_PLAYER);
	pieces[7][2] = new Bishop(BLACK_PLAYER);
	pieces[7][3] = new Queen(BLACK_PLAYER);
	pieces[7][4] = new King(BLACK_PLAYER);
	pieces[7][5] = new Bishop(BLACK_PLAYER);
	pieces[7][6] = new Knight(BLACK_PLAYER);
	pieces[7][7] = new Rook(BLACK_PLAYER);
}

int Board::code_response(std::string res)
{
	int src_row = convert_str_to_loc(res[0]);
	int src_col = convert_str_to_loc(res[1]);
	int dest_row = convert_str_to_loc(res[2]);
	int dest_col = convert_str_to_loc(res[3]);

	if (pieces[src_row][src_col] == nullptr)
		return 11;
	if (pieces[src_row][src_col]->get_player() != whos_turn)
		return 12;
	if (pieces[dest_row][dest_col] != nullptr && pieces[src_row][src_col]->get_player() == whos_turn)
		return 13;
	if (!pieces[src_row][src_col]
		->is_legal_move(src_row, src_col, dest_row, dest_col, *this))
		return 21;
	if (is_chess(src_row, src_col, dest_row, dest_col))
		return 31;
	whos_turn = Player((whos_turn + 1) % 2);
	return 42;
}

bool Board::there_is_a_piece_directly(int src_row, int src_col, int dest_row, int dest_col)
{
	if (src_row == dest_row)
	{
		int start = std::min(src_col, dest_col);
		int end = std::max(src_col, dest_col);
		for (size_t i = start + 1; i < end; i++)
		{
			if (pieces[src_row][i] != nullptr)
				return true;
		}
		return false;
	}
	if (src_col == dest_col)
	{
		int start = std::min(src_row, dest_row);
		int end = std::max(src_row, dest_row);
		for (size_t i = start + 1; i < end; i++)
		{
			if (pieces[i][src_col] != nullptr)
				return true;
		}
		return 	false;
	}
}

bool Board::there_is_a_piece_diagonally(int src_row, int src_col, int dest_row, int dest_col)
{
	int row_num = get_iterator_num(src_row, dest_row);
	int col_num = get_iterator_num(src_col, dest_col);

	for (size_t i = src_row + row_num, j = src_col + col_num;
		(i < dest_row || i == src_row) && (j < dest_col || j == src_col);
		i += row_num, j += col_num)
	{
		if (pieces[i][j] != nullptr)
		{
			return true;
		}
	}
	return false;
}

int Board::convert_str_to_loc(char str_loc) const
{
	if (str_loc >= 'a')
		return str_loc - 'a';
	if(str_loc >= 'A')
		return str_loc - 'A';
	return str_loc - '1';
}

bool Board::is_chess(int src_row, int src_col, int dest_row, int dest_col)
{
	Piece* eaten = pieces[dest_row][dest_col];
	move_piece(src_row, src_col, dest_row, dest_col);
	int king_loc_row = king_loc(whos_turn)[0];
	int king_loc_col = king_loc(whos_turn)[1];

	if (help_is_chess(king_loc_row, king_loc_col))
	{
		move_piece(dest_row, dest_col, src_row, src_col);
		pieces[dest_row][dest_col] = eaten;
		return true;
	}
	return false;
}

bool Board::help_is_chess(int row_to_check, int col_to_check)
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if ((i!= row_to_check || j!= col_to_check) && pieces[i][j] != nullptr 
				&& pieces[i][j]->get_player() != whos_turn
				&& pieces[i][j]->is_legal_move(i, j, row_to_check, col_to_check, *this))
				return true;
		}
	}
	return false;
}

void Board::move_piece(int src_row, int src_col, int dest_row, int dest_col)
{
	pieces[dest_row][dest_col] = pieces[src_row][src_col];
	pieces[src_row][src_col] = nullptr;
}

int* Board::king_loc(Player player)
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (pieces[i][j] != nullptr && dynamic_cast<King*>(pieces[i][j]) && pieces[i][j]->get_player() == player)
			{
				int result[2] = { i , j };
				return result;
			}
		}
	}
}

int Board::get_iterator_num(int loc0, int loc1)
{
	if (loc1 > loc0)
		return 1;
	else if (loc1 < loc0)
		return -1;
	else
		return 0;
}




