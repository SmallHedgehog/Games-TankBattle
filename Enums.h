#pragma once

/*
Defines const enum values
*/

// 定义障碍物枚举常量
enum BarrierType
{
	NORMAL_BARRIER,		// 普通障碍物
	STEEL_BARRIER,		// steel障碍物
	GRASS_BARRIER,		// grass障碍物
	WATER_BARRIER		// water障碍物
};

enum BarrierDir
{
	VERTICAL,			// 垂直方向
	HORIZONTAL			// 水平方向
};

// 定义坦克移动方向
enum TankMoveDir
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	NONE
};

// 定义坦克类型
enum TankType
{
	NORMAL_TANK,
	DOUBLE_TANK,
	TWO_DOUBLE_TANK,
	PLAYER_TANK,
	COMPUTER_TANK
};

// 定义子弹与其发生碰撞的类型
enum CollisionWithBulletType
{
	C_TANK,				// 电脑玩家坦克
	P_TANK,				// 游戏玩家坦克
	WALL,				// 屏幕区域
	BARRIER,			// 障碍物
	NOT_ALL
};