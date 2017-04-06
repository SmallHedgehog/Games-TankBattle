#include "stdafx.h"
#include "TDoublesTank.h"


TDoublesTank::TDoublesTank(int x, int y, TankType type, std::vector<std::vector<SDL_Texture*>>& vec):
	Tank(x, y, type)
{
	life = 400;
	currentDir = TankMoveDir(rand() % 4);
	setTextures(vec);
}

void TDoublesTank::setTextures(std::vector<std::vector<SDL_Texture*>>& vec)
{
	std::vector<SDL_Texture*>::const_iterator it = vec[type].begin();
	for (; it != vec[type].end(); ++it)
	{
		textures.push_back(*it);
	}
}

void TDoublesTank::Draw(SDL_Renderer* renderer)
{
	if (life <= 0)
		return ;
	
	int idx = life / 100 - 1;
	
	int width = 0, height = 0;
	SDL_QueryTexture(textures[idx * 4 + int(currentDir)], NULL, NULL, &width, &height);
	SDL_Rect rect = {
		_x, _y, width, height
	};

	SDL_RenderCopy(renderer, textures[idx * 4 + int(currentDir)], NULL, &rect);
}

TDoublesTank::~TDoublesTank(void)
{
	// noting to do
}
