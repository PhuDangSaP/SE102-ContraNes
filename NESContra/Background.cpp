#include "Background.h"

CBackground::CBackground()
{
}

CBackground::CBackground(float bgX, float bgY, int bgAniId)
{
	this->x = bgX;
	this->y = bgY;
	this->aniId = bgAniId;
}

CBackground::~CBackground()
{
}

void CBackground::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
}
