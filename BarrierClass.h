#pragma once

// ��ʾ��Ϸ�е��ϰ���

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
	// ���Ʒ���
	void Draw(SDL_Renderer* renderer);

	int getX() const { return _x; }
	int getY() const { return _y; }
	BarrierType getType() const { return type; }
	int GetBarrierLength() const { return BarrierLength; }

private:
	// �ϰ������Ͻ�λ��
	int _x;
	int _y;

	int BarrierLength;					// �ϰ���߳�
	BarrierType type;					// �ϰ�������
	SDL_Texture* tex;					// �ϰ�������
};

