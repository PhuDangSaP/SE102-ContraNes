#pragma once
#include "GameObject.h"
class Platform : public CGameObject
{
private:
	float cellWidth;
	int length;
	int spriteId;	
public:
	Platform(float x,float y,float cellWidth,int length, int spriteId)
	{
		this->x = x;
		this->y = y;
		this->cellWidth = cellWidth;
		this->length = length;
		this->spriteId = spriteId;
	}
	void Update(DWORD dt) {}
	void Render();
};

