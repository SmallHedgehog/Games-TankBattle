#pragma once

// Tank����

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
	// �Ƿ���Է����ӵ�
	bool CanLauncher() const { return this->IsCanLauncher; }
	void setIsCanLauncher(bool IsLaunchered) { this->IsCanLauncher = IsLaunchered; }
	bool Launch();

public:
	// Tank���Ͻ�����
	int _x;
	int _y;

	int speed;							// �ӵ��ٶ�
	int life;							// ����
	TankType type;						// ��ʾTank������
	std::vector<SDL_Texture*> textures;	// �洢��������

	int Distance;						// tankÿ�ƶ�һ�εľ���
	TankMoveDir currentDir;				// tank��ǰ���ƶ�����

	bool IsCanLauncher;					// tank�Ƿ���Է����ӵ�
};

