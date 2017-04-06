#include "stdafx.h"
#include "NormalTank.h"


NormalTank::NormalTank(int x, int y, TankType type, std::vector<std::vector<SDL_Texture*>>& vec):
	Tank(x, y, type)
{
	life = 100;
	currentDir = TankMoveDir(rand() % 4);
	setTextures(vec);
}

void NormalTank::setTextures(std::vector<std::vector<SDL_Texture*>>& vec)
{
	std::vector<SDL_Texture*>::const_iterator it = vec[type].begin();
	for (; it != vec[type].end(); ++it)
	{
		textures.push_back(*it);
	}
}

void NormalTank::Draw(SDL_Renderer* renderer)
{
	int width = 0, height = 0;
	SDL_QueryTexture(textures[currentDir], NULL, NULL, &width, &height);
	SDL_Rect rect = {
		_x, _y, width, height
	};

	SDL_RenderCopy(renderer, textures[currentDir], NULL, &rect);
}

NormalTank::~NormalTank(void)
{
	// nothing to do
}
