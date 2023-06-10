#include "Board.h"
#include<typeinfo>

/**
 * Constructs a new Board object and initializes the chessboard with the starting positions of the pieces.
 *
 * @param board A string representing the starting positions of the pieces on the chessboard.
 */
Board::Board(std::string board)
{
	int i = 0;
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			switch (board[i])
			{
			case 'r':
				pieces[row][col] = new Rook(BLACK_PLAYER);
				break;
			case 'n':
				pieces[row][col] = new Knight(BLACK_PLAYER);
				break;
			case 'b':
				pieces[row][col] = new Bishop(BLACK_PLAYER);
				break;
			case 'q':
				pieces[row][col] = new Queen(BLACK_PLAYER);
				break;
			case 'k':
				pieces[row][col] = new King(BLACK_PLAYER);
				black_king_place[0] = row;
				black_king_place[1] = col;
				break;
			case 'p':
				pieces[row][col] = new Pawn(BLACK_PLAYER);
				break;
			case 'R':
				pieces[row][col] = new Rook(WHITE_PLAYER);
				break;
			case 'N':
				pieces[row][col] = new Knight(WHITE_PLAYER);
				break;
			case 'B':
				pieces[row][col] = new Bishop(WHITE_PLAYER);
				break;
			case 'Q':
				pieces[row][col] = new Queen(WHITE_PLAYER);
				break;
			case 'K':
				pieces[row][col] = new King(WHITE_PLAYER);
				white_king_place[0] = row;
				white_king_place[1] = col;
				break;
			case 'P':
				pieces[row][col] = new Pawn(WHITE_PLAYER);
				break;
			default:
				pieces[row][col] = nullptr;
				break;
			}
			++i;
		}
	}
}

/**
 * Creates a copy of a Board object.
 *
 * @param other The Board object to be copied.
 */	
Board::Board(const Board& other) {
	// Copy the pieces from the other board
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (other.pieces[row][col] != nullptr) {
				pieces[row][col] = other.pieces[row][col]; 
				if(dynamic_cast<King*>(pieces[row][col]))
				{
					if (pieces[row][col]->get_player() == BLACK_PLAYER)
					{
						black_king_place[0] = row;
						black_king_place[1] = col;
					}
					else
					{
						white_king_place[0] = row;
						white_king_place[1] = col;
					}
				}
			}
			else {
				pieces[row][col] = nullptr;
			}
		}
	}
}

/**
 * Moves the pieces from another Board object to a new Board object.
 *
 * @param other The Board object to be moved.
 */
Board::Board(Board&& other) noexcept{
	// Move the pieces from the other board
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			pieces[row][col] = other.pieces[row][col];
			if (dynamic_cast<King*>(pieces[row][col]))
			{
				if (pieces[row][col]->get_player() == BLACK_PLAYER)
				{
					black_king_place[0] = row;
					black_king_place[1] = col;
				}
				else
				{
					white_king_place[0] = row;
					white_king_place[1] = col;
				}
			}
			other.pieces[row][col] = nullptr;
		}
	}
}

/**
 * Destroys the Board object and frees memory allocated for dynamically allocated Piece objects.
 */
Board::~Board()
{
	// Delete all dynamically allocated Piece objects
	for (size_t row = 0; row < 8; ++row)
	{
		for (size_t col = 0; col < 8; ++col)
		{
			delete pieces[row][col];
		}
		//delete[] pieces;
	}
}

/**
* Gets the piece at the specified row and column on the chessboard.
*
* @param row The row index.
* @param col The column index.
* @return A pointer to the Piece object at the specified position.
*/
Piece* Board::getPiece(const int row,const int col) const
{
	return pieces[row][col];
}

/**
* Checks a move specified by a string and returns a response code based on the move.
*
* @param res The move string representation.
* @return An integer response code indicating the outcome of the move.
*/
int Board::code_response(const std::string res)
{
	int src_row = convert_str_to_loc(res[0]);
	int src_col = convert_str_to_loc(res[1]);
	int dest_row = convert_str_to_loc(res[2]);
	int dest_col = convert_str_to_loc(res[3]);

	if (pieces[src_row][src_col] == nullptr) // There is not piece at the source
		return 11;
	if (pieces[src_row][src_col]->get_player() != whos_turn) // The piece in the source is piece of the opponent
		return 12;
	if (pieces[dest_row][dest_col] != nullptr && pieces[dest_row][dest_col]->get_player() == whos_turn) // There one of player pieces at the destination
		return 13;
	if (!pieces[src_row][src_col]
		->is_legal_move(src_row, src_col, dest_row, dest_col, this)) // Illegal movement of that piece
		return 21;

	// If the move is legal
	Piece* eaten = pieces[dest_row][dest_col];
	move_piece(src_row, src_col, dest_row, dest_col);

	if (is_check()) // This movement will cause you checkmate
	{
		// Take back the move
		move_piece(dest_row, dest_col, src_row, src_col);
		pieces[dest_row][dest_col] = eaten;
		return 31;
	}

	whos_turn = Player((whos_turn + 1) % 2);

	if (is_check()) // The last movement was legal and cause check
		return 41;
	return 42; // The last movement was legal
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
bool Board::there_is_a_piece_directly(const int src_row,const int src_col,const int dest_row,const int dest_col) const
{
	if (src_row == dest_row) // Horizontal move
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
	if (src_col == dest_col) // Vertical move
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
bool Board::there_is_a_piece_diagonally(const int src_row, const int src_col, const int dest_row, const int dest_col) const
{
	int row_num = get_iterator_num(src_row, dest_row);
	int col_num = get_iterator_num(src_col, dest_col);

	for (size_t i = src_row + row_num, j = src_col + col_num;
		i * row_num < dest_row * row_num, j * col_num < dest_col * col_num; i += row_num, j += col_num)
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
	 * @return True if the move results in a "check" situation, false otherwise.
	 */
bool Board::is_check()
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (whos_turn == BLACK_PLAYER && 
				(i!= black_king_place[0] || j!= black_king_place[1]) && pieces[i][j] != nullptr
				&& pieces[i][j]->get_player() != whos_turn
				&& pieces[i][j]->is_legal_move(i, j, black_king_place[0], black_king_place[1], this))
				return true;
			else if(whos_turn == WHITE_PLAYER &&
				(i != white_king_place[0] || j != white_king_place[1]) && pieces[i][j] != nullptr
				&& pieces[i][j]->get_player() != whos_turn
				&& pieces[i][j]->is_legal_move(i, j, white_king_place[0], white_king_place[1], this))
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
void Board::move_piece(const int src_row, const int src_col, const int dest_row, const int dest_col)
{
	if (dynamic_cast<King*>(pieces[src_row][src_col]))
	{
		if (whos_turn == BLACK_PLAYER)
		{
			black_king_place[0] = dest_row;
			black_king_place[1] = dest_col;
		}
		else
		{
			white_king_place[0] = dest_row;
			white_king_place[1] = dest_col;
		}
	}
	pieces[dest_row][dest_col] = pieces[src_row][src_col];
	pieces[src_row][src_col] = nullptr;
}

/**
* Calculates the iterator number based on the given source and destination indices.
*
* @param loc_row The source row index.
* @param loc_col The source column index.
* @return The iterator number (-1, 0, or 1) indicating the direction of movement.
*/
int Board::get_iterator_num(const int loc0, const int loc1) const
{
	if (loc1 > loc0)
		return 1;
	else if (loc1 < loc0)
		return -1;
	else
		return 0;
}




