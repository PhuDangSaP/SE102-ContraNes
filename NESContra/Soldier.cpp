#include "Soldier.h"

void CSoldier::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (x < 10) 
	{
		x = 10; 
		vx = -vx;
	}
	if (x > 400)
	{
		x = 400;
		vx = -vx;
	}
}

void CSoldier::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Collision::Process(this, dt, coObjects);
	/*x += vx * dt;
	y += vy * dt;*/

	if (x < 0)
	{
		x = 0;
		vx = -vx;
	}
	if (x > 400)
	{
		x = 400;
		vx = -vx;
	}
	
}

void CSoldier::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (vx != 0)
	{
		if (vx > 0)
		{
			aniId = ID_ANI_SOLDIER_WALKING_RIGHT;
		}
		else
		{
			aniId = ID_ANI_SOLDIER_WALKING_LEFT;
		}
	}
	else
	{
		if (nx > 0)
		{
			aniId = ID_ANI_SOLDIER_IDLE_RIGHT;
		}
		else
		{
			aniId = ID_ANI_SOLDIER_IDLE_LEFT;
		}
	}
	animations->Get(aniId)->Render(x, y);
}

RECT CSoldier::GetRect()
{
	return CSprites::GetInstance()->Get(8001)->GetRect();
}

RECT CSoldier::GetBoundingBox()
{
	RECT rect;
	rect= CSprites::GetInstance()->Get(8001)->GetRect();
	return rect;
}

void CSoldier::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CSoldier::RequestState(int reqState)
{
	int finalState;
	switch (reqState)
	{
	case SOLDIER_STATE_WALKING_RIGHT:
		finalState = reqState;
		nx = 1;
		vx = SOLDIER_WALKING_SPEED;
		break;
	case SOLDIER_STATE_WALKING_LEFT:
		finalState = reqState;
		nx = -1;
		vx = -SOLDIER_WALKING_SPEED;
		break;
	case SOLDIER_STATE_IDLE:
		finalState = reqState;
		vx = 0;
		break;
	}
	CGameObject::SetState(finalState);
}