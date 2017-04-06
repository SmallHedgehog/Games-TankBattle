#pragma once

// Tank基类

#include <vector>
#include <SDL.h>
#include "Defines.h"
#include "Enums.h"

class Tank
{
public:
	Tank(int x, int y, TankType type);
	virtual void Draw(SDL_Renderer* renderer) = 0;
	virtual ~Tank(void);

public:
	void setX(int x) { this->_x = x; }
	void setY(int y) { this->_y = y; }
	void setLife(int life) { this->life = life; }
	int getX() const { return this->_x; }
	int getY() const { return this->_y; }
	int getLife() const { return this->life; }
	int getDistance() const { return this->Distance; }

	virtual void Move(TankMoveDir dir);
	void setCurrentDir(TankMoveDir dir);
	// 是否可以发射子弹
	bool CanLauncher() const { return this->IsCanLauncher; }
	void setIsCanLauncher(bool IsLaunchered) { this->IsCanLauncher = IsLaunchered; }
	bool Launch();

public:
	// Tank左上角坐标
	int _x;
	int _y;

	int speed;							// 子弹速度
	int life;							// 生命
	TankType type;						// 表示Tank的类型
	std::vector<SDL_Texture*> textures;	// 存储纹理数据

	int Distance;						// tank每移动一次的距离
	TankMoveDir currentDir;				// tank当前的移动方向

	bool IsCanLauncher;					// tank是否可以发射子弹
};

