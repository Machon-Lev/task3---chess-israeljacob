#include "King.h"


King::King(Player player) : Piece(player)
{

}

bool King::is_legal_move(int int_source_loc0, int int_source_loc1, int int_dest_loc0, int int_dest_loc1, Board board)
{
    if (abs(int_source_loc0 - int_dest_loc0) > 1 || abs(int_source_loc1 - int_dest_loc1) > 1)
        return false;
    return true;
}

