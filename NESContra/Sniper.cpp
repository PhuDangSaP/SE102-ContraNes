#include "Sniper.h"
#include "Bill.h"
extern CBill* bill;

void CSniper::Update(DWORD dt)
{
	float xTarget, yTarget;
	bill->GetPos(xTarget, yTarget);
	yTarget += 5;
	if (abs(this->x - xTarget) < SCREEN_WIDTH / 2 - 25)
	{
		nx = (int)(xTarget - this->x);
		ny = (int)(yTarget - this->y);
		this->state = SNIPER_STATE_SHOOT;
	}
	else
	{
		this->state = SNIPER_STATE_IDLE;
	}
}

void CSniper::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	switch (this->state)
	{
	case SNIPER_STATE_SHOOT:
		if (ny <= 5 && ny >= -5)
		{
			if (nx <= 0)
			{
				aniId = ID_ANI_SNIPER_SHOOT_LEFT;
			}
			else
			{
				aniId = ID_ANI_SNIPER_SHOOT_RIGHT;
			}
		}
		else
		{
			if (ny > 0)
			{
				if (nx <= 0)
				{
					aniId = ID_ANI_SNIPER_SHOOT_TOP_LEFT;
				}
				else
				{
					aniId = ID_ANI_SNIPER_SHOOT_TOP_RIGHT;
				}
			}
			else
			{
				if (nx <= 0)
				{
					aniId = ID_ANI_SNIPER_SHOOT_BOTTOM_LEFT;
				}
				else
				{
					aniId = ID_ANI_SNIPER_SHOOT_BOTTOM_RIGHT;
				}
			}
		}
		break;
	case SNIPER_STATE_IDLE:
		if (ny <= 5 && ny >= -5)
		{
			if (nx <= 0)
			{
				aniId = ID_ANI_SNIPER_IDLE_LEFT;
			}
			else
			{
				aniId = ID_ANI_SNIPER_IDLE_RIGHT;
			}
		}
		else
		{
			if (ny > 0)
			{
				if (nx <= 0)
				{
					aniId = ID_ANI_SNIPER_IDLE_TOP_LEFT;
				}
				else
				{
					aniId = ID_ANI_SNIPER_IDLE_TOP_RIGHT;
				}
			}
			else
			{
				if (nx <= 0)
				{
					aniId = ID_ANI_SNIPER_IDLE_BOTTOM_LEFT;
				}
				else
				{
					aniId = ID_ANI_SNIPER_IDLE_BOTTOM_RIGHT;
				}
			}
		}
		break;
	defalt:
		aniId = ID_ANI_SNIPER_IDLE_LEFT;
	}
	animations->Get(aniId)->Render(x, y);
}

void CSniper::RequestState(int reqState)
{
	
}