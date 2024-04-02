#include "Bill.h"

void CBill::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (x < 10) { x = 10; }
}

void CBill::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	float d = 0;
	if (aniId == -1) aniId = ID_ANI_BILL_IDLE_RIGHT;
	switch (state) {
	case BILL_STATE_WALKING_RIGHT:
		aniId = ID_ANI_BILL_WALKING_RIGHT;
		break;
	case BILL_STATE_WALKING_LEFT:
		aniId = ID_ANI_BILL_WALKING_LEFT;
		break;
	case BILL_STATE_LYING_DOWN:
		if (this->nx >= 0)
		{
			aniId = ID_ANI_BILL_LYING_DOWN_RIGHT;
		}
		else
		{
			aniId = ID_ANI_BILL_LYING_DOWN_LEFT;
		}
		d = -10;
		break;
	case BILL_STATE_LOOKING_UP:
		if (this->nx >= 0)
		{
			aniId = ID_ANI_BILL_LOOKING_UP_RIGHT;
		}
		else
		{
			aniId = ID_ANI_BILL_LOOKING_UP_LEFT;
		}
		d = 5;
		break;
	case BILL_STATE_IDLE:
		if (nx < 0) {
			aniId = ID_ANI_BILL_IDLE_LEFT;
		}
		else
		{
			aniId = ID_ANI_BILL_IDLE_RIGHT;
		}
		break;
	case BILL_STATE_WALKING_LOOK_UP:
		if (this->nx >= 0)
		{
			aniId = ID_ANI_BILL_WALKING_LOOKING_UP_RIGHT;
		}
		else
		{
			aniId = ID_ANI_BILL_WALKING_LOOKING_UP_LEFT;
		}
		break;
	case BILL_STATE_WALKING_LOOK_DOWN:
		if (this->nx >= 0)
		{
			aniId = ID_ANI_BILL_WALKING_LOOKING_DOWN_RIGHT;
		}
		else
		{
			aniId = ID_ANI_BILL_WALKING_LOOKING_DOWN_LEFT;
		}
		break;
	default:
		aniId = ID_ANI_BILL_IDLE_RIGHT;
	}
	animations->Get(aniId)->Render(x, y + d);
}

void CBill::RequestState(int reqState)
{
	int finalState = this->state;
	switch (reqState)
	{
	case BILL_STATE_WALKING_RIGHT:
		if (ny != 0)
		{
			if (ny > 0)
			{
				finalState = BILL_STATE_WALKING_LOOK_UP;
			}
			else
			{
				finalState = BILL_STATE_WALKING_LOOK_DOWN;
			}
		}
		else
		{
			finalState = reqState;
		}
		nx = 1;
		vx = BILL_WALKING_SPEED;
		break;
	case BILL_STATE_WALKING_LEFT:
		if (ny != 0)
		{
			if (ny > 0)
			{
				finalState = BILL_STATE_WALKING_LOOK_UP;
			}
			else
			{
				finalState = BILL_STATE_WALKING_LOOK_DOWN;
			}
		}
		else
		{
			finalState = reqState;
		}
		nx = -1;
		vx = -BILL_WALKING_SPEED;
		break;
	case BILL_STATE_LOOKING_UP:
		ny = 1;
		if (this->GetState() == BILL_STATE_WALKING_LEFT || this->GetState() == BILL_STATE_WALKING_RIGHT)
		{
			finalState = BILL_STATE_WALKING_LOOK_UP;
		}
		else
		{
			finalState = reqState;
			vx = 0;
		}
		break;
	case BILL_STATE_LYING_DOWN:
		ny = -1;
		if (this->GetState() == BILL_STATE_WALKING_LEFT || this->GetState() == BILL_STATE_WALKING_RIGHT)
		{
			finalState = BILL_STATE_WALKING_LOOK_DOWN;
		}
		else
		{
			finalState = reqState;
			vx = 0;
		}
		break;
	case BILL_STATE_IDLE:
		finalState = reqState;
		vx = 0;
		ny = 0;
		break;
	}
	CGameObject::SetState(finalState);
}