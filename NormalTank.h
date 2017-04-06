#pragma once

#include "tank.h"

class NormalTank :
	public Tank
{
public:
	NormalTank(int x, int y, TankType type, std::vector<std::vector<SDL_Texture*>>& vec);
	virtual void Draw(SDL_Renderer* renderer);
	virtual ~NormalTank(void);

private:
	void setTextures(std::vector<std::vector<SDL_Texture*>>& vec);
};

