#include "Board.h"



int* Board::convert_str_to_loc(std::string str_loc) const
{
	int int_loc[2];
	int_loc[0] = str_loc[0] >= 'a' ? str_loc[0] - 'a' : str_loc[0] - 'A';
	int_loc[1] = int(str_loc[1]) - '1';
	return int_loc;
}

bool Board::is_chess(int int_source_loc0, int int_source_loc1, int int_dest_loc0, int int_dest_loc1)
{
	Piece* eaten = pieces[int_dest_loc0][int_dest_loc1];
	move_piece(int_source_loc0, int_source_loc1, int_dest_loc0, int_dest_loc1);
	int king_loc_row = king_loc(whos_turn)[0];
	int king_loc_col = king_loc(whos_turn)[1];

	if (help_is_chess(king_loc_row, king_loc_col))
	{
		move_piece(int_dest_loc0, int_dest_loc1, int_source_loc0, int_source_loc1);
		pieces[int_dest_loc0][int_dest_loc1] = eaten;
		return true;
	}
	return false;
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

Piece* Board::there_is_a_piece_diagonally(int int_source_loc0, int int_source_loc1, int int_dest_loc0, int int_dest_loc1)
{
	int row_num = get_iterator_num(int_source_loc0, int_dest_loc0);
	int col_num = get_iterator_num(int_source_loc1, int_dest_loc1);

	for (size_t i = int_source_loc0 + row_num, j = int_source_loc1 + col_num;
		(i < int_dest_loc0 || i == int_source_loc0) && (j < int_dest_loc1 || j == int_source_loc1);
		i += row_num, j += col_num)
	{
		if (pieces[i][j] != nullptr)
		{
			return pieces[i][j];
		}
	}
	return nullptr;
}

Piece* Board::there_is_a_piece_directly(int int_source_loc0, int int_source_loc1, int int_dest_loc0, int int_dest_loc1)
{
	if (int_source_loc0 == int_dest_loc0)
	{
		int start = std::min(int_source_loc1, int_dest_loc1);
		int end = std::max(int_source_loc1, int_dest_loc1);
		for (size_t i = start + 1; i < end; i++)
		{
			if (pieces[int_source_loc0][i] != nullptr)
				return pieces[int_source_loc0][i];
		}
		return nullptr;
	}
	if (int_source_loc1 == int_dest_loc1)
	{
		int start = std::min(int_source_loc0, int_dest_loc0);
		int end = std::max(int_source_loc0, int_dest_loc0);
		for (size_t i = start + 1; i < end; i++)
		{
			if (pieces[i][int_source_loc1] != nullptr)
				return pieces[i][int_source_loc1];
		}
		return nullptr;
	}
}

Board::Board()
{
	pieces[0][0] = new Rook(WHITE_PLAYER);
	pieces[0][1] = nullptr; //new Knight(WHITE_PLAYER);
	pieces[0][2] = new Bishop(WHITE_PLAYER);
	pieces[0][3] = nullptr; //new Queen(WHITE_PLAYER);
	pieces[0][4] = new King(WHITE_PLAYER);
	pieces[0][5] = new Bishop(WHITE_PLAYER);
	pieces[0][6] = nullptr; //new Knight(WHITE_PLAYER);
	pieces[0][7] = new Rook(WHITE_PLAYER);

	for (size_t i = 2; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			pieces[i][j] = nullptr;
		}
	}

	pieces[7][0] = new Rook(BLACK_PLAYER);
	pieces[7][1] = nullptr; //new Knight(BLACK_PLAYER);
	pieces[7][2] = new Bishop(BLACK_PLAYER);
	pieces[7][3] = nullptr; //new Queen(BLACK_PLAYER);
	pieces[7][4] = new King(BLACK_PLAYER);
	pieces[7][5] = new Bishop(BLACK_PLAYER);
	pieces[7][6] = nullptr; //new Knight(BLACK_PLAYER);
	pieces[7][7] = new Rook(BLACK_PLAYER);
}

Player Board::get_whos_turn()
{
	return whos_turn;
}

void Board::set_whos_turn()
{
	whos_turn = Player((whos_turn + 1) % 2);
}

bool Board::there_is_a_piece(int loc_row, int loc_col)
{
	return pieces[loc_row][loc_col] != nullptr;
}

Piece* Board::get_piece(int i, int j) const
{
	return pieces[i][j];
}

void Board::move_piece(int int_src_loc0, int int_src_loc1, int int_dest_loc0, int int_dest_loc1)
{
	pieces[int_dest_loc0][int_dest_loc1] = pieces[int_src_loc0][int_src_loc1];
	pieces[int_src_loc0][int_src_loc1] = nullptr;
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

int Board::get_iterator_num(int loc0, int loc1)
{
	if (loc1 > loc0)
		return 1;
	else if (loc1 < loc0)
		return -1;
	else
		return 0;
}

int Board::code_response(std::string res)
{
	std::string source = res.substr(0, 2);
	std::string dest = res.substr(2, 2);
	int int_source_loc0 = convert_str_to_loc(source)[0];
	int int_source_loc1 = convert_str_to_loc(source)[1];
	int int_dest_loc0 = convert_str_to_loc(dest)[0];
	int int_dest_loc1 = convert_str_to_loc(dest)[1];

	if (pieces[int_source_loc0][int_source_loc1] == nullptr)
		return 11;
	if (get_piece(int_source_loc0, int_source_loc1)->get_player() != whos_turn)
		return 12;
	if (pieces[int_dest_loc0][int_dest_loc1] != nullptr && get_piece(int_dest_loc0, int_dest_loc1)->get_player() == whos_turn)
		return 13;
	if (!get_piece(int_source_loc0, int_source_loc1)
		->is_legal_move(int_source_loc0, int_source_loc1, int_dest_loc0, int_dest_loc1, *this))
		return 21;
	if (is_chess(int_source_loc0, int_source_loc1, int_dest_loc0, int_dest_loc1))
		return 31;
	set_whos_turn();
	//this->move_piece(res);
	return 42;
}



