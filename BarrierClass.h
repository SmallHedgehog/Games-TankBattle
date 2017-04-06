#pragma once

// 表示游戏中的障碍物

#include <vector>
#include "Square.h"
#include "Enums.h"
#include "Defines.h"

class BarrierClass
{
public:
	BarrierClass(int x, int y, BarrierType type, SDL_Texture* texture);
	~BarrierClass(void);

public:
	// 绘制方法
	void Draw(SDL_Renderer* renderer);

	int getX() const { return _x; }
	int getY() const { return _y; }
	BarrierType getType() const { return type; }
	int GetBarrierLength() const { return BarrierLength; }

private:
	// 障碍物左上角位置
	int _x;
	int _y;

	int BarrierLength;					// 障碍物边长
	BarrierType type;					// 障碍物类型
	SDL_Texture* tex;					// 障碍物纹理
};

