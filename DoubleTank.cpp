#include "stdafx.h"
#include "DoubleTank.h"


DoubleTank::DoubleTank(int x, int y, TankType type, std::vector<std::vector<SDL_Texture*>>& vec):
	Tank(x, y, type)
{
	life = 200;
	speed = 10;
	Distance = SQUARE_LENGTH + speed;
	currentDir = TankMoveDir(rand() % 4);
	setTextures(vec);
}

void DoubleTank::setTextures(std::vector<std::vector<SDL_Texture*>>& vec)
{
	std::vector<SDL_Texture*>::const_iterator it = vec[type].begin();
	for (; it != vec[type].end(); ++it)
	{
		textures.push_back(*it);
	}
}

// ÷ÿ–¥Move()∑Ω∑®
void DoubleTank::Move(TankMoveDir dir)
{
	switch (dir)
	{
	case LEFT:
		_x -= (SQUARE_LENGTH + speed);
		break;
	case UP:
		_y -= (SQUARE_LENGTH + speed);
		break;
	case RIGHT:
		_x += (SQUARE_LENGTH + speed);
		break;
	case DOWN:
		_y += (SQUARE_LENGTH + speed);
		break;
	case NONE:
		break;
	default:
		break;
	}
}

void DoubleTank::Draw(SDL_Renderer* renderer)
{
	int width = 0, height = 0;
	SDL_QueryTexture(textures[currentDir], NULL, NULL, &width, &height);
	SDL_Rect rect = {
		_x, _y, width, height
	};

	SDL_RenderCopy(renderer, textures[currentDir], NULL, &rect);
}

DoubleTank::~DoubleTank(void)
{
	// nothing to do
}
