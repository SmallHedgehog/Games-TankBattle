#include "stdafx.h"
#include "Tank.h"


Tank::Tank(int x, int y, TankType type):
	type(type)
{
	_x = x;
	_y = y;
	speed = 0;
	life  = 0;
	Distance = SQUARE_LENGTH;
	currentDir = NONE;
	IsCanLauncher = true;
}

void Tank::Move(TankMoveDir dir)
{
	switch (dir)
	{
	case LEFT:
		_x -= SQUARE_LENGTH;
		break;
	case UP:
		_y -= SQUARE_LENGTH;
		break;
	case RIGHT:
		_x += SQUARE_LENGTH;
		break;
	case DOWN:
		_y += SQUARE_LENGTH;
		break;
	case NONE:
		break;
	default:
		break;
	}
}

void Tank::setCurrentDir(TankMoveDir dir)
{
	switch (dir)
	{
	case LEFT:
		currentDir = LEFT;
		break;
	case UP:
		currentDir = UP;
		break;
	case RIGHT:
		currentDir = RIGHT;
		break;
	case DOWN:
		currentDir = DOWN;
		break;
	case NONE:
		break;
	default:
		break;
	}
}

bool Tank::Launch()
{
	static int LaunchTime = rand() % 100;
	LaunchTime--;
	if (LaunchTime < 0)
	{
		LaunchTime = rand() % 100;
		return true;
	}
	else{
		return false;
	}
}

Tank::~Tank(void)
{
	// nothing to do
}
