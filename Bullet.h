#pragma once

// �ӵ�

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
	// ���Ʒ���
	void Draw(SDL_Renderer* renderer);
	// �ƶ�
	void Move();
	bool MoveSelf();

// ������ײ����߼�
public:
	// �ӵ��Ƿ�����Ļ������ײ
	bool IsCollisionScreen();

private:
	// �ӵ����Ͻ�����
	int _x;
	int _y;
	
	int bulletSpeed;			// �ӵ��ٶ�
	SDL_Texture* tex;			// �ӵ���������

	// ��¼�ӵ����ĸ�tank������Լ������ӵ�ʱ�ķ���
	TankMoveDir dir;
	Tank* tank;
};

