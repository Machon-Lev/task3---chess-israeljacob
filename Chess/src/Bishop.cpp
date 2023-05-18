#include "Bishop.h"

Bishop::Bishop(Player player) :Piece(player)
{

}

bool Bishop::is_legal_move(int int_source_loc0, int int_source_loc1, int int_dest_loc0, int int_dest_loc1, Board board)
{
    if (abs(int_source_loc0 - int_dest_loc0) != abs(int_source_loc1 - int_dest_loc1))
        return false;
    return !board.there_is_a_piece_diagonally(int_source_loc0, int_source_loc1, int_dest_loc0, int_dest_loc1);
}
