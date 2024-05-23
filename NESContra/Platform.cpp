#include "Platform.h"
#include "Sprites.h"

void Platform::Render()
{
	if (this->length <= 0) return;
	float xx = x;
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteIdBegin)->Draw(xx, y);
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddle)->Draw(xx, y);
		xx += this->cellWidth;
	}
	if (length > 1)
		s->Get(this->spriteIdEnd)->Draw(xx, y);
}

RECT Platform::GetRect()
{
	return RECT();
}

RECT Platform::GetBoundingBox()
{
	float cellWidth_div_2 = this->cellWidth / 2;
	RECT rect;
	rect.left = x - cellWidth_div_2;
	rect.top = y + this->cellHeight / 2;
	rect.right = rect.left + this->cellWidth * this->length;
	rect.bottom = rect.top - this->cellHeight;
	return rect;
}

int Platform::IsDirectionColliable(float nx, float ny) 
{
	if (nx == 0 && ny == 1) return 1;
	else return 0;
}
