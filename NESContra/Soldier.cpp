#include "Soldier.h"

void CSoldier::Update(DWORD dt)
{
	
}

void CSoldier::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy -= GRAVITY * dt;
	isGrounded = false;
	CCollision::GetInstance()->Process(this, dt, coObjects);
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
	rect.left = x - rect.right / 2;
	rect.right = x + rect.right / 2;
	rect.top += y + rect.bottom / 2;
	rect.bottom = y - rect.bottom / 2;
	return rect;
}

void CSoldier::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CSoldier::RequestState(int reqState)
{
	int finalState = state;
	switch (state)
	{
	case SOLDIER_STATE_WALKING_RIGHT:
		switch (reqState)
		{
		case SOLDIER_STATE_WALKING_LEFT:
			nx = -1;
			vx = -SOLDIER_WALKING_SPEED;
			finalState = reqState;
			break;
		}
		break;
	case SOLDIER_STATE_WALKING_LEFT:
		switch (reqState)
		{
		case SOLDIER_STATE_WALKING_RIGHT:
			nx = 1;
			vx = SOLDIER_WALKING_SPEED;
			finalState = reqState;
			break;
		}
		break;
	}
	CGameObject::SetState(finalState);
}

void CSoldier::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny > 0) isGrounded = true;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}
}