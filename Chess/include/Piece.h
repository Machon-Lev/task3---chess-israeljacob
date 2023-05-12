#pragma once
#include <string>
#include "Player.h"
class Piece
{
private:
	std::string _name;
	Player _player;
protected:
	int _value;

public:
	Piece(std::string name, Player player);
	virtual void move() = 0;
};

