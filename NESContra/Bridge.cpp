#include "Bridge.h"
#include "Sprites.h"
#include "Animation.h"
#include "Animations.h"

void Bridge::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state != BRIDGE_STATE_SELF_DESTRUCT) return;
	if (destroyTimer > 0)
	{
		destroyTimer -= dt;
	}
	else
	{
		if (cellDestroyed < length - 1)
		{
			cellDestroyed++;
			if (cellDestroyed == 1)
			{
				if (isStartFromLeftSide)
				{
					spriteIdBegin = ID_SPRITE_BRIDGE_BEGIN_DESTROYED;
				}
				else
				{
					spriteIdEnd = ID_SPRITE_BRIDGE_END_DESTROYED;
				}
			}
		}
		else
		{
			state = BRIDGE_STATE_DESTROYED;
			spriteIdBegin = ID_SPRITE_BRIDGE_BEGIN_DESTROYED;
			spriteIdEnd = ID_SPRITE_BRIDGE_END_DESTROYED;
		}
		this->destroyTimer = DESTROY_TIMER;
	}
}

void Bridge::Render()
{
	if (this->length <= 0) return;
	float xx = x;
	float explosionX = xx;
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteIdBegin)->Draw(xx, y);
	if (spriteIdBegin == ID_SPRITE_BRIDGE_BEGIN_DESTROYED)	explosionX = xx;
	xx += this->cellWidth;
	if (isStartFromLeftSide)
	{
		for (int i = 1; i < this->length - 1; i++)
		{
			if (i <= cellDestroyed - 1)
			{
				s->Get(ID_SPRITE_BRIDGE_MID_DESTROYED)->Draw(xx, y);
				if (i == cellDestroyed - 1)	explosionX = xx;
			}
			else
			{
				s->Get(ID_SPRITE_BRIDGE_MID)->Draw(xx, y);
			}
			xx += this->cellWidth;
		}
	}
	else
	{
		for (int i = 1; i < this->length - 1; i++)
		{
			if (i >= length - cellDestroyed)
			{
				s->Get(ID_SPRITE_BRIDGE_MID_DESTROYED)->Draw(xx, y);
			}
			else
			{
				s->Get(ID_SPRITE_BRIDGE_MID)->Draw(xx, y);
			}
			xx += this->cellWidth;
		}
	}
	if (length > 1)
	{
		s->Get(this->spriteIdEnd)->Draw(xx, y);
		if (spriteIdEnd == ID_SPRITE_BRIDGE_END_DESTROYED)	explosionX = xx;
	}
	if (state == BRIDGE_STATE_SELF_DESTRUCT)
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_BRIDGE_EXPLOSION_LEFT)->Render(explosionX - 15, y);
		animations->Get(ID_ANI_BRIDGE_EXPLOSION_TOP)->Render(explosionX, y + 15);
		animations->Get(ID_ANI_BRIDGE_EXPLOSION_RIGHT)->Render(explosionX + 15, y);
		animations->Get(ID_ANI_BRIDGE_EXPLOSION_CENTER)->Render(explosionX, y);
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
	if (state != BRIDGE_STATE_SELF_DESTRUCT)
	{
		rect.left = x - cellWidth_div_2;
		rect.top = y + this->cellHeight / 2;
		rect.right = rect.left + this->cellWidth * this->length;
		rect.bottom = rect.top - this->cellHeight;
	}
	else
	{
		if (isStartFromLeftSide)
		{
			rect.left = x - cellWidth_div_2 + cellWidth * cellDestroyed;
			rect.top = y + this->cellHeight / 2;
			rect.right = rect.left + this->cellWidth * (this->length - this->cellDestroyed);
			rect.bottom = rect.top - this->cellHeight;
		}
		else
		{
			rect.left = x - cellWidth_div_2;
			rect.top = y + this->cellHeight / 2;
			rect.right = rect.left + this->cellWidth * (this->length - this->cellDestroyed);
			rect.bottom = rect.top - this->cellHeight;
		}
	}
	return rect;
}

int Bridge::IsDirectionColliable(float nx, float ny)
{
	return 1;
}
