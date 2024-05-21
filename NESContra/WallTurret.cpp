#include "WallTurret.h"
#include "Bill.h"
extern CBill* bill;
void CWallTurret::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->state == TURRET_STATE_IDLE) return;
	if (this->state == TURRET_STATE_OPENING)
	{
		if (openTimer <= 0)
		{
			RequestState(TURRET_STATE_ACTIVE);
		}
		else 
		{
			openTimer -= dt;
		}
	}
	if (this->state == TURRET_STATE_ACTIVE)
	{
		if (scanTimer <= 0)
		{
			float xTarget, yTarget;
			bill->GetPos(xTarget, yTarget);
			xTarget -= this->x;
			yTarget -= this->y;
			newAngle = atan2f(yTarget, xTarget) * 180 / 3.141;
			if (newAngle < 0) newAngle += 360;
			floorf(newAngle);
			if (abs(newAngle - curAngle) < 30)
			{
				//shoot
			}
			else
			{
				if (abs(newAngle - curAngle) >= 180)
				{
					if (curAngle < newAngle)
					{
						curAngle -= 30;
					}
					else
					{
						curAngle += 30;
					}
				}
				else
				{
					if (curAngle < newAngle)
					{
						curAngle += 30;
					}
					else
					{
						curAngle -= 30;
					}
				}
				if (curAngle >= 360) curAngle -= 360;
				if (curAngle < 0) curAngle += 360;
				
			}
			scanTimer = SCAN_TIMER;
		}
		else
		{
			scanTimer -= dt;
		}
	}
}

void CWallTurret::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	switch (this->state)
	{
	case TURRET_STATE_IDLE:
		aniId = ID_ANI_TURRET_IDLE;
		break;
	case TURRET_STATE_OPENING:
		aniId = ID_ANI_TURRET_OPENING;
		break;
	case TURRET_STATE_ACTIVE:
		if (curAngle <= 15 || curAngle > 345)
		{
			aniId = ID_ANI_TURRET_ACTIVE_3_OCLOCK;
		}
		if (curAngle > 15 && curAngle <= 45)
		{
			aniId = ID_ANI_TURRET_ACTIVE_2_OCLOCK;
		}
		if (curAngle > 45 && curAngle <= 75)
		{
			aniId = ID_ANI_TURRET_ACTIVE_1_OCLOCK;
		}
		if (curAngle > 75 && curAngle <= 105)
		{
			aniId = ID_ANI_TURRET_ACTIVE_12_OCLOCK;
		}
		if (curAngle > 105 && curAngle <= 135)
		{
			aniId = ID_ANI_TURRET_ACTIVE_11_OCLOCK;
		}
		if (curAngle > 135 && curAngle <= 165)
		{
			aniId = ID_ANI_TURRET_ACTIVE_10_OCLOCK;
		}
		if (curAngle > 165 && curAngle <= 195)
		{
			aniId = ID_ANI_TURRET_ACTIVE_9_OCLOCK;
		}
		if (curAngle > 195 && curAngle <= 225)
		{
			aniId = ID_ANI_TURRET_ACTIVE_8_OCLOCK;
		}
		if (curAngle > 225 && curAngle <= 255)
		{
			aniId = ID_ANI_TURRET_ACTIVE_7_OCLOCK;
		}
		if (curAngle > 255 && curAngle <= 285)
		{
			aniId = ID_ANI_TURRET_ACTIVE_6_OCLOCK;
		}
		if (curAngle > 285 && curAngle <= 315)
		{
			aniId = ID_ANI_TURRET_ACTIVE_5_OCLOCK;
		}
		if (curAngle > 315 && curAngle <= 345)
		{
			aniId = ID_ANI_TURRET_ACTIVE_4_OCLOCK;
		}
		break;
	}
	animations->Get(aniId)->Render(x, y);
}

RECT CWallTurret::GetRect()
{
	return CSprites::GetInstance()->Get(6001)->GetRect();
}

RECT CWallTurret::GetBoundingBox()
{
	RECT rect;
	rect = CSprites::GetInstance()->Get(6001)->GetRect();
	rect.left = x - rect.right / 2;
	rect.right = x + rect.right / 2;
	rect.top += y + rect.bottom / 2;
	rect.bottom = y - rect.bottom / 2;
	if (this->state == TURRET_STATE_IDLE)
	{
		rect.left -= 50;
		rect.top += 50;
		rect.bottom -= 50;
	}
	return rect;
}

void CWallTurret::RequestState(int reqState)
{
	switch (this->state)
	{
	case TURRET_STATE_IDLE:
		switch (reqState)
		{
		case TURRET_STATE_OPENING:
			this->state = reqState;
			openTimer = OPEN_TIMER;
			break;
		case TURRET_STATE_ACTIVE:
			this->state = TURRET_STATE_OPENING;
			openTimer = OPEN_TIMER;
			break;
		case TURRET_STATE_IDLE:
			this->state = reqState;
			break;
		}
		break;
	case TURRET_STATE_OPENING:
		this->state = reqState;
		break;
	case TURRET_STATE_ACTIVE:
		break;
	}
}