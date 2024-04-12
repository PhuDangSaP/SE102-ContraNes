#pragma once
#include "Platform.h"
class Bridge :public Platform
{
public:
	Bridge(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :Platform(x, y,
			cell_width, cell_height, length,
			sprite_id_begin, sprite_id_middle, sprite_id_end)
	{
	}
	void Update(DWORD dt);
	void Render();
	RECT GetRect();
	RECT GetBoundingBox();
	void Explosion();
};

