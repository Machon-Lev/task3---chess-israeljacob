#include "Board.h"

/**
	* Constructs a new Board object and initializes the chessboard with the starting positions of the pieces.
	*/
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

	for (size_t j = 0; j < 8; j++)
	{
		pieces[1][j] = new Pawn(WHITE_PLAYER);
	}

	for (size_t i = 2; i < 6; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			pieces[i][j] = nullptr;
		}
	}

	for (size_t j = 0; j < 8; j++)
	{
		pieces[6][j] = new Pawn(BLACK_PLAYER);
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

/**
	 * Gets the piece at the specified row and column on the chessboard.
	 *
	 * @param row The row index.
	 * @param col The column index.
	 * @return A pointer to the Piece object at the specified position.
	 */
Piece* Board::getPiece(int row, int col)
{
	return pieces[row][col];
}

/**
	 * Checks a move specified by a string and returns a response code based on the move.
	 *
	 * @param res The move string representation.
	 * @return An integer response code indicating the outcome of the move.
	 */
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
	if (pieces[dest_row][dest_col] != nullptr && pieces[dest_row][dest_col]->get_player() == whos_turn)
		return 13;
	if (!pieces[src_row][src_col]
		->is_legal_move(src_row, src_col, dest_row, dest_col, *this))
		return 21;
	if (is_chess(src_row, src_col, dest_row, dest_col))
		return 31;
	whos_turn = Player((whos_turn + 1) % 2);
	return 42;
}

/**
	 * Checks if there is a piece directly between two positions on the chessboard.
	 *
	 * @param src_row The row index of the source position.
	 * @param src_col The column index of the source position.
	 * @param dest_row The row index of the destination position.
	 * @param dest_col The column index of the destination position.
	 * @return True if there is a piece directly between the source and destination positions, false otherwise.
	 */
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

/**
	 * Checks if there is a piece diagonally between two positions on the chessboard.
	 *
	 * @param src_row The row index of the source position.
	 * @param src_col The column index of the source position.
	 * @param dest_row The row index of the destination position.
	 * @param dest_col The column index of the destination position.
	 * @return True if there is a piece diagonally between the source and destination positions, false otherwise.
	 */
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

/**
	 * Converts a character representation of a location to the corresponding integer index.
	 *
	 * @param str_loc The character representation of the location.
	 * @return The integer index representing the location.
	 */
int Board::convert_str_to_loc(char str_loc) const
{
	if (str_loc >= 'a')
		return str_loc - 'a';
	if(str_loc >= 'A')
		return str_loc - 'A';
	return str_loc - '1';
}

/**
	 * Checks if a move results in a "check" situation for the current player.
	 *
	 * @param src_row The row index of the source position.
	 * @param src_col The column index of the source position.
	 * @param dest_row The row index of the destination position.
	 * @param dest_col The column index of the destination position.
	 * @return True if the move results in a "check" situation, false otherwise.
	 */
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

/**
	 * Helper function to check if the current player is in "check".
	 *
	 * @param row_to_check The row index of the position to check.
	 * @param col_to_check The column index of the position to check.
	 * @return True if the current player is in "check" at the specified position, false otherwise.
	 */
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

/**
	 * Moves a piece from the source position to the destination position on the chessboard.
	 *
	 * @param src_row The row index of the source position.
	 * @param src_col The column index of the source position.
	 * @param dest_row The row index of the destination position.
	 * @param dest_col The column index of the destination position.
	 */
void Board::move_piece(int src_row, int src_col, int dest_row, int dest_col)
{
	pieces[dest_row][dest_col] = pieces[src_row][src_col];
	pieces[src_row][src_col] = nullptr;
}

/**
	 * Finds the location of the king for the specified player on the chessboard.
	 *
	 * @param player The player whose king's location is to be found.
	 * @return An array of two integers representing the row and column indices of the king's location.
	 */
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

/**
	 * Calculates the iterator number based on the given source and destination indices.
	 *
	 * @param loc_row The source row index.
	 * @param loc_col The source column index.
	 * @return The iterator number (-1, 0, or 1) indicating the direction of movement.
	 */
int Board::get_iterator_num(int loc0, int loc1)
{
	if (loc1 > loc0)
		return 1;
	else if (loc1 < loc0)
		return -1;
	else
		return 0;
}




