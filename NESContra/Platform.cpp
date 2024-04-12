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
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = this->cellWidth * this->length;
	rect.bottom = this->cellHeight * this->length;
	return rect;
}
