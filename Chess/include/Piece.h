#pragma once
#include <string>
#include "Player.h"
class Piece
{
private:
	Player _player;

public:
	Piece(Player player);
	virtual void move() = 0;
};

