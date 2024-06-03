#include "Bridge.h"
#include "Sprites.h"
#include "Animation.h"
#include "Animations.h"

void Bridge::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BRIDGE_STATE_SELF_DESTRUCT)
	{
		destroyTimer -= dt;
		if (destroyTimer <= 0 && length > 0)
		{
			x += cellWidth;
			length--;
			destroyTimer = DESTROY_TIMER;
		}
	}
}

void Bridge::Render()
{
	if (this->length <= 0) return;
	float xx = x;
	
	CSprites* s = CSprites::GetInstance();
	if (length < originalLength)
	{
		s->Get(ID_SPRITE_BRIDGE_MID)->Draw(xx, y);
	}
	else {
		s->Get(this->spriteIdBegin)->Draw(xx, y);
	}
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(ID_SPRITE_BRIDGE_MID)->Draw(xx, y);
		xx += this->cellWidth;
	}
	if (length > 1) s->Get(this->spriteIdEnd)->Draw(xx, y);
	if (state == BRIDGE_STATE_SELF_DESTRUCT)
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_BRIDGE_EXPLOSION_LEFT)->Render(x - 10, y);
		animations->Get(ID_ANI_BRIDGE_EXPLOSION_TOP)->Render(x, y + 10);
		animations->Get(ID_ANI_BRIDGE_EXPLOSION_RIGHT)->Render(x + 10, y);
		animations->Get(ID_ANI_BRIDGE_EXPLOSION_CENTER)->Render(x, y);
	}
}

RECT Bridge::GetRect()
{
	return RECT();
}

RECT Bridge::GetBoundingBox()
{
	float cellWidth_div_2 = this->cellWidth / 2;
	RECT rect;
	if (state == BRIDGE_STATE_ACTIVE)
	{
		rect.left = x - cellWidth_div_2;
		rect.top = y + this->cellHeight / 2 + 100;
		rect.right = rect.left + this->cellWidth * this->length;
		rect.bottom = rect.top - this->cellHeight - 200;
	}
	else
	{
		rect.left = x - cellWidth_div_2;
		rect.top = y + this->cellHeight / 2;
		rect.right = rect.left + this->cellWidth * this->length;
		rect.bottom = rect.top - this->cellHeight;
	}
	return rect;
}

int Bridge::IsDirectionColliable(float nx, float ny)
{
	if(state != BRIDGE_STATE_ACTIVE && nx != 0) return 0;
	return 1;
}
