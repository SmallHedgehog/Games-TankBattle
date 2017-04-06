#pragma once

// 子弹

#include "Tank.h"

class Bullet
{
public:
	Bullet(int x, int y, TankMoveDir dir, SDL_Texture* texture, Tank* tank);
	~Bullet(void);

public:
	int getX() const { return _x; }
	int getY() const { return _y; }
	void setSpeed(int speed) { this->bulletSpeed = speed; }
	int getSpeed() const { return this->bulletSpeed; }
	TankMoveDir getDir() const { return dir; }
	Tank* getTank() { return tank; }
	// 绘制方法
	void Draw(SDL_Renderer* renderer);
	// 移动
	void Move();
	bool MoveSelf();

// 处理碰撞检测逻辑
public:
	// 子弹是否与屏幕发生碰撞
	bool IsCollisionScreen();

private:
	// 子弹左上角坐标
	int _x;
	int _y;
	
	int bulletSpeed;			// 子弹速度
	SDL_Texture* tex;			// 子弹纹理数据

	// 记录子弹是哪个tank发射的以及发射子弹时的方向
	TankMoveDir dir;
	Tank* tank;
};

