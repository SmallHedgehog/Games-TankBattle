#pragma once

#include "tank.h"

class DoubleTank :
	public Tank
{
public:
	DoubleTank(int x, int y, TankType type, std::vector<std::vector<SDL_Texture*>>& vec);
	virtual void Draw(SDL_Renderer* renderer);
	virtual ~DoubleTank(void);

	// ÷ÿ–¥Move()∑Ω∑®
	virtual void Move(TankMoveDir dir);

private:
	void setTextures(std::vector<std::vector<SDL_Texture*>>& vec);
};

