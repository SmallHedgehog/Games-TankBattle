#pragma once

#include "tank.h"

class PlayerTank :
	public Tank
{
public:
	PlayerTank(int x, int y, TankType type, std::vector<SDL_Texture*>& vec);
	virtual void Draw(SDL_Renderer* renderer);
	virtual ~PlayerTank(void);

private:
	void setTextures(std::vector<SDL_Texture*>& vec);
};

