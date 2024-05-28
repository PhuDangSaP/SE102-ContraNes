#pragma once
#include "GameObject.h"

class Water :public CGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
public:
	Water(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
	}

	void Render();
	void Update(DWORD dt) {}
	RECT GetRect();
	RECT GetBoundingBox();
	void RenderBoundingBox();
	int IsBlocking() { return 1; }
	int IsCollidable() { return 1; }
	int IsDirectionColliable(float nx, float ny);
};