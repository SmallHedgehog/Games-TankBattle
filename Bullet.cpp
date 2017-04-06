#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(int x, int y, TankMoveDir dir, SDL_Texture* texture, 
			   Tank* tank):
	tex(texture), dir(dir), tank(tank)
{
	_x = x;
	_y = y;
	bulletSpeed = INIT_BULLET_SPEED;
}

// 绘制方法
void Bullet::Draw(SDL_Renderer* renderer)
{
	int width = 0, height = 0;
	SDL_QueryTexture(tex, NULL, NULL, &width, &height);
	SDL_Rect rect = {
		_x, _y, width, height
	};

	SDL_RenderCopy(renderer, tex, NULL, &rect);
}

// 移动
void Bullet::Move()
{
	switch (dir)
	{
	case LEFT:
		_x -= bulletSpeed;
		break;
	case UP:
		_y -= bulletSpeed;
		break;
	case RIGHT:
		_x += bulletSpeed;
		break;
	case DOWN:
		_y += bulletSpeed;
		break;
	case NONE:
		break;
	default:
		break;
	}
}

bool Bullet::MoveSelf()
{
	if (!IsCollisionScreen()){
		Move();
		return false;
	}
	else{
		// 设置tank可以继续发射子弹
		tank->setIsCanLauncher(true);
		return true;
	}
}

// 检测子弹是否在屏幕范围之内
bool Bullet::IsCollisionScreen()
{
	bool result = false;
	switch (dir)
	{
	case LEFT:
		{
			if ((_x - bulletSpeed) < GAME_LEFT_AREA)
				result = true;
			else
				result = false;
		}
		break;
	case UP:
		{
			if ((_y - bulletSpeed) < GAME_TOP_AREA)
				result = true;
			else
				result = false;
		}
		break;
	case RIGHT:
		{
			if ((_x + bulletSpeed + BULLET_LENGTH) > GAME_RIGHT_AREA)
				result = true;
			else
				result = false;
		}
		break;
	case DOWN:
		{
			if ((_y + bulletSpeed + BULLET_LENGTH) > GAME_BOTTOM_AREA)
				result = true;
			else
				result = false;
		}
		break;
	case NONE:
		break;
	default:
		break;
	}

	return result;
}

Bullet::~Bullet(void)
{
	// nothing to do
}
