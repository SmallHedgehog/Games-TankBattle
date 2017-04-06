#pragma once

/*
Defines const enum values
*/

// �����ϰ���ö�ٳ���
enum BarrierType
{
	NORMAL_BARRIER,		// ��ͨ�ϰ���
	STEEL_BARRIER,		// steel�ϰ���
	GRASS_BARRIER,		// grass�ϰ���
	WATER_BARRIER		// water�ϰ���
};

enum BarrierDir
{
	VERTICAL,			// ��ֱ����
	HORIZONTAL			// ˮƽ����
};

// ����̹���ƶ�����
enum TankMoveDir
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	NONE
};

// ����̹������
enum TankType
{
	NORMAL_TANK,
	DOUBLE_TANK,
	TWO_DOUBLE_TANK,
	PLAYER_TANK,
	COMPUTER_TANK
};

// �����ӵ����䷢����ײ������
enum CollisionWithBulletType
{
	C_TANK,				// �������̹��
	P_TANK,				// ��Ϸ���̹��
	WALL,				// ��Ļ����
	BARRIER,			// �ϰ���
	NOT_ALL
};