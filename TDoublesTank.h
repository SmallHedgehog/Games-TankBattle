#pragma once

#include "tank.h"

class TDoublesTank :
	public Tank
{
public:
	TDoublesTank(int x, int y, TankType type, std::vector<std::vector<SDL_Texture*>>& vec);
	virtual void Draw(SDL_Renderer* renderer);
	virtual ~TDoublesTank(void);

private:
	void setTextures(std::vector<std::vector<SDL_Texture*>>& vec);
};

