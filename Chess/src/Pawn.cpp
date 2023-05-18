#include "Pawn.h"

Pawn::Pawn(Player player) : Piece(player)
{

}

bool Pawn::is_legal_move(int src_row, int src_col, int dest_row, int dest_col, Board board)
{
    return false;
}
