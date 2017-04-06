#include "stdafx.h"
#include "BarrierClass.h"


BarrierClass::BarrierClass(int x, int y, BarrierType type, SDL_Texture* texture):
	type(type), tex(texture)
{
	_x = x;
	_y = y;

	switch (type)
	{
	case NORMAL_BARRIER:
		BarrierLength = SQUARE_LENGTH;
		break;
	case STEEL_BARRIER:
		BarrierLength = SQUARE_LENGTH;
		break;
	case GRASS_BARRIER:
		BarrierLength = SQUARE_LENGTH * 2;
		break;
	case WATER_BARRIER:
		BarrierLength = SQUARE_LENGTH * 2;
		break;
	default:
		break;
	}
}

// »æÖÆ·½·¨
void BarrierClass::Draw(SDL_Renderer* renderer)
{
	int width = 0, height = 0;
	SDL_QueryTexture(tex, NULL, NULL, &width, &height);
	SDL_Rect rect = {
		_x, _y, width, height
	};

	SDL_RenderCopy(renderer, tex, NULL, &rect);
}

BarrierClass::~BarrierClass(void)
{
	// nothing to do
}
