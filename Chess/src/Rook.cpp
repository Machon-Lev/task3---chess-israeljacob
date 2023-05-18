#include "Rook.h"
#include"Board.h"

Rook::Rook(Player player) : Piece(player)
{
}

bool Rook::is_legal_move(int int_source_loc0, int int_source_loc1, int int_dest_loc0, int int_dest_loc1, Board board)
{
    if (int_source_loc0 == int_dest_loc0)
    {
        int start = std::min(int_source_loc1, int_dest_loc1);
        int end = std::max(int_source_loc1, int_dest_loc1);
        for (size_t i = start + 1; i < end; i++)
        {
            if (board.get_piece(int_source_loc0, i) != nullptr)
                return false;
        }
        return true;
    }
    if (int_source_loc1 == int_dest_loc1)
    {
        int start = std::min(int_source_loc0, int_dest_loc0);
        int end = std::max(int_source_loc0, int_dest_loc0);
        for (size_t i = start + 1 ; i < end; i++)
        {
            if (board.get_piece(i, int_source_loc1) != nullptr)
                return false;
        }
        return true;
    }
    return false;
}
