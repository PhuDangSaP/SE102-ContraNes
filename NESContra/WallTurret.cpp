#include "WallTurret.h"
#include "Bill.h"
extern CBill* bill;
void CWallTurret::Update(DWORD dt)
{
	float xTarget, yTarget;
	bill->GetPos(xTarget, yTarget);
	if (abs(this->x - xTarget) < SCREEN_WIDTH / 2 - 25)
	{
		xTarget -= this->x;
		yTarget -= this->y;
		angle = atan2f(yTarget, xTarget) * 180 / 3.141;
		floorf(angle);
		openTimer -= dt;
		if (openTimer > 0)
		{
			this->state = TURRET_STATE_OPENING;
		}
		if (openTimer <= 0)
		{
			this->state = TURRET_STATE_ACTIVE;
		}
	}
	else
	{
		this->state = TURRET_STATE_IDLE;
		openTimer = 500;
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
		if (angle <= 15 && angle > -15)
		{
			aniId = ID_ANI_TURRET_ACTIVE_3_OCLOCK;
		}
		if (angle > 15 && angle <= 45)
		{
			aniId = ID_ANI_TURRET_ACTIVE_2_OCLOCK;
		}
		if (angle > 45 && angle <= 75)
		{
			aniId = ID_ANI_TURRET_ACTIVE_1_OCLOCK;
		}
		if (angle > 75 && angle <= 105)
		{
			aniId = ID_ANI_TURRET_ACTIVE_12_OCLOCK;
		}
		if (angle > 105 && angle <= 135)
		{
			aniId = ID_ANI_TURRET_ACTIVE_11_OCLOCK;
		}
		if (angle > 135 && angle <= 165)
		{
			aniId = ID_ANI_TURRET_ACTIVE_10_OCLOCK;
		}
		if (angle > 165 && angle <= -165)
		{
			aniId = ID_ANI_TURRET_ACTIVE_9_OCLOCK;
		}
		if (angle > -165 && angle <= -135)
		{
			aniId = ID_ANI_TURRET_ACTIVE_8_OCLOCK;
		}
		if (angle > -135 && angle <= -105)
		{
			aniId = ID_ANI_TURRET_ACTIVE_7_OCLOCK;
		}
		if (angle > -105 && angle <= -75)
		{
			aniId = ID_ANI_TURRET_ACTIVE_6_OCLOCK;
		}
		if (angle > -75 && angle <= -45)
		{
			aniId = ID_ANI_TURRET_ACTIVE_5_OCLOCK;
		}
		if (angle > -45 && angle <= -15)
		{
			aniId = ID_ANI_TURRET_ACTIVE_4_OCLOCK;
		}
	}
	animations->Get(aniId)->Render(x, y);
}

void CWallTurret::RequestState(int reqState)
{
	/*int finalState;
	
	CGameObject::SetState(finalState);*/
}