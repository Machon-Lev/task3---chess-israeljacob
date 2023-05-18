#include "Board.h"



int* Board::convert_str_to_loc(std::string str_loc) const
{
	int int_loc[2];
	int_loc[0] = str_loc[0] >= 'a' ? str_loc[0] - 'a' : str_loc[0] - 'A';
	int_loc[1] = int(str_loc[1]) - '1';
	return int_loc;
}

Board::Board()
{
	pieces[0][0] = new Rook(WHITE_PLAYER);
	pieces[0][1] = nullptr; //new Knight(WHITE_PLAYER);
	pieces[0][2] = nullptr; //new Bishop(WHITE_PLAYER);
	pieces[0][3] = nullptr; //new Queen(WHITE_PLAYER);
	pieces[0][4] = nullptr; //new King(WHITE_PLAYER);
	pieces[0][5] = nullptr; //new Bishop(WHITE_PLAYER);
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
	pieces[7][2] = nullptr; //new Bishop(BLACK_PLAYER);
	pieces[7][3] = nullptr; //new Queen(BLACK_PLAYER);
	pieces[7][4] = nullptr; //new King(BLACK_PLAYER);
	pieces[7][5] = nullptr; //new Bishop(BLACK_PLAYER);
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

bool Board::there_is_a_piece(std::string str_loc) 
{
	int loc0 = convert_str_to_loc(str_loc)[0];
	int loc1 = convert_str_to_loc(str_loc)[1];
	return pieces[loc0][loc1] != nullptr;
}

Piece* Board::get_piece(int i, int j) const
{
	return pieces[i][j];
}

void Board::move_piece(std::string res)
{
	int int_src_loc0 = this->convert_str_to_loc(res.substr(0, 2))[0];
	int int_src_loc1 = this->convert_str_to_loc(res.substr(0, 2))[1];
	int int_dest_loc0 = this->convert_str_to_loc(res.substr(2, 2))[0];
	int int_dest_loc1 = this->convert_str_to_loc(res.substr(2, 2))[1];
	pieces[int_dest_loc0][int_dest_loc1] = pieces[int_src_loc0][int_src_loc1];
	pieces[int_src_loc0][int_src_loc1] = nullptr;
}

int Board::code_response(std::string res)
{
	std::string source = res.substr(0, 2);
	std::string dest = res.substr(2, 2);
	int int_source_loc0 = this->convert_str_to_loc(source)[0];
	int int_source_loc1 = this->convert_str_to_loc(source)[1];
	int int_dest_loc0 = this->convert_str_to_loc(dest)[0];
	int int_dest_loc1 = this->convert_str_to_loc(dest)[1];

	if (!this->there_is_a_piece(source))
		return 11;
	if (this->get_piece(int_source_loc0, int_source_loc1)->get_player() != whos_turn)
		return 12;
	if (this->there_is_a_piece(dest) && this->get_piece(int_dest_loc0, int_dest_loc1)->get_player() == whos_turn)
		return 13;
	if (!this->get_piece(int_source_loc0, int_source_loc1)->is_legal_move(res, *this))
		return 21;
	this->set_whos_turn();
	this->move_piece(res);
	return 42;
}



