#include "stdafx.h"
#include "PlayerTank.h"


PlayerTank::PlayerTank(int x, int y, TankType type, std::vector<SDL_Texture*>& vec):
	Tank(x, y, type)
{
	life = 3;
	currentDir = UP;
	setTextures(vec);
}

void PlayerTank::Draw(SDL_Renderer* renderer)
{
	int width = 0, height = 0;
	SDL_QueryTexture(textures[currentDir], NULL, NULL, &width, &height);
	SDL_Rect rect = {
		_x, _y, width, height
	};

	SDL_RenderCopy(renderer, textures[currentDir], NULL, &rect);
}

void PlayerTank::setTextures(std::vector<SDL_Texture*>& vec)
{
	std::vector<SDL_Texture*>::const_iterator it = vec.cbegin();
	for (; it != vec.cend(); ++it)
	{
		textures.push_back(*it);
	}
}

PlayerTank::~PlayerTank(void)
{
	// nothing to do
}
