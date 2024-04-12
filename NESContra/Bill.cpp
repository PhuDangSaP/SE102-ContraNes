#include "Bill.h"
#include "Collision.h"


void CBill::Update(DWORD dt)
{
	CGame* g = CGame::GetInstance();
	x += vx * dt;
	y += vy * dt;
	vy -= GRAVITY * dt;

	/*float camX, camY;
	g->GetCamera()->GetCamPos(camX, camY);
	if (x < camX)
		x = camX ;*/
	if (x < 10) { x = 10; }


	if (y < 130)
	{
		vy = 0;
		y = 130;
		isGrounded = true;
	}
	

}

void CBill::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isGrounded)
		vy = 0;
	Collision::Process(this, dt, coObjects);

	/*x += vx * dt;
	y += vy * dt;
	vy -= GRAVITY * dt;*/

	/*float camX, camY;
	g->GetCamera()->GetCamPos(camX, camY);
	if (x < camX)
		x = camX ;*/

	if (x < 10) { x = 10; }


	if (y < 130)
	{
		vy = 0;
		y = 130;
		isGrounded = true;
	}
	
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
	case BILL_STATE_JUMP:
		if (this->nx >= 0)
		{
			aniId = ID_ANI_BILL_JUMP_RIGHT;
		}
		else
		{
			aniId = ID_ANI_BILL_JUMP_LEFT;
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

	switch (this->state)
	{
	case BILL_STATE_IDLE:
		switch (reqState)
		{
		case BILL_STATE_WALKING_LEFT:
			vx = -BILL_WALKING_SPEED;
			nx = -1;
			finalState = reqState;
			break;
		case BILL_STATE_WALKING_RIGHT:
			vx = BILL_WALKING_SPEED;
			nx = 1;
			finalState = reqState;
			break;
		case BILL_STATE_LOOKING_UP:
			ny = 1;
			finalState = reqState;
			break;
		case BILL_STATE_LYING_DOWN:
			ny = -1;
			finalState = reqState;
			break;
		case BILL_STATE_JUMP:
			vy += BILL_JUMP_SPEED;
			isGrounded = false;
			finalState = reqState;
			break;
		}
		break;
	case BILL_STATE_WALKING_LEFT:
		switch (reqState)
		{
		case BILL_STATE_IDLE:
			vx = 0;
			finalState = reqState;
			break;
		case BILL_STATE_WALKING_RIGHT:
			vx = BILL_WALKING_SPEED;
			nx = 1;
			finalState = reqState;
			break;
		case BILL_STATE_LOOKING_UP:
			ny = 1;
			finalState = BILL_STATE_WALKING_LOOK_UP;
			break;
		case BILL_STATE_LYING_DOWN:
			ny = -1;
			finalState = BILL_STATE_WALKING_LOOK_DOWN;
			break;
		case BILL_STATE_JUMP:
			vy += BILL_JUMP_SPEED;
			isGrounded = false;
			finalState = reqState;
			break;
		}
		break;
	case BILL_STATE_WALKING_RIGHT:
		switch (reqState)
		{
		case BILL_STATE_IDLE:
			vx = 0;
			finalState = reqState;
			break;
		case BILL_STATE_WALKING_LEFT:
			vx = -BILL_WALKING_SPEED;
			nx = -1;
			finalState = reqState;
			break;
		case BILL_STATE_LOOKING_UP:
			ny = 1;
			finalState = BILL_STATE_WALKING_LOOK_UP;
			break;
		case BILL_STATE_LYING_DOWN:
			ny = -1;
			finalState = BILL_STATE_WALKING_LOOK_DOWN;
			break;
		case BILL_STATE_JUMP:
			vy += BILL_JUMP_SPEED;
			isGrounded = false;
			finalState = reqState;
			break;
		}
		break;
	case BILL_STATE_LOOKING_UP:
		switch (reqState)
		{
		case BILL_STATE_IDLE:
			ny = 0;
			finalState = reqState;
			break;
		case BILL_STATE_WALKING_RIGHT:
			vx = BILL_WALKING_SPEED;
			nx = 1;
			finalState = BILL_STATE_WALKING_LOOK_UP;
			break;
		case BILL_STATE_WALKING_LEFT:
			vx = -BILL_WALKING_SPEED;
			nx = -1;
			finalState = BILL_STATE_WALKING_LOOK_UP;
			break;
		case BILL_STATE_LYING_DOWN:
			ny = -1;
			finalState = reqState;
			break;
		case BILL_STATE_JUMP:
			vy += BILL_JUMP_SPEED;
			isGrounded = false;
			finalState = reqState;
			break;
		}
		break;
	case BILL_STATE_LYING_DOWN:
		switch (reqState)
		{
		case BILL_STATE_IDLE:
			ny = 0;
			finalState = reqState;
			break;
		case BILL_STATE_WALKING_RIGHT:
			vx = BILL_WALKING_SPEED;
			nx = 1;
			finalState = BILL_STATE_WALKING_LOOK_DOWN;
			break;
		case BILL_STATE_WALKING_LEFT:
			vx = -BILL_WALKING_SPEED;
			nx = -1;
			finalState = BILL_STATE_WALKING_LOOK_DOWN;
			break;
		case BILL_STATE_LOOKING_UP:
			ny = 1;
			finalState = reqState;
			break;
		}
		break;
	case BILL_STATE_WALKING_LOOK_UP:
		switch (reqState)
		{
		case BILL_STATE_IDLE:
			vx = 0;
			ny = 0;
			finalState = reqState;
			break;
		case BILL_STATE_LOOKING_UP:
			vx = 0;
			ny = 1;
			finalState = reqState;
			break;
		case BILL_STATE_LYING_DOWN:
			ny = -1;
			finalState = BILL_STATE_WALKING_LOOK_DOWN;
			break;
		case BILL_STATE_JUMP:
			vy += BILL_JUMP_SPEED;
			isGrounded = false;
			finalState = reqState;
			break;
		}
		break;
	case BILL_STATE_WALKING_LOOK_DOWN:
		switch (reqState)
		{
		case BILL_STATE_IDLE:
			vx = 0;
			ny = 0;
			finalState = reqState;
			break;
		case BILL_STATE_LOOKING_UP:
			ny = 1;
			finalState = BILL_STATE_WALKING_LOOK_UP;
			break;
		case BILL_STATE_LYING_DOWN:
			vx = 0;
			ny = -1;
			finalState = reqState;
			break;
		case BILL_STATE_JUMP:
			vy += BILL_JUMP_SPEED;
			isGrounded = false;
			finalState = reqState;
			break;
		}
		break;
	case BILL_STATE_JUMP:
		switch (reqState)
		{
		case BILL_STATE_IDLE:
			if (isGrounded)
			{
				vy = 0;
				vx = 0;
				finalState = reqState;
			}
			break;
		case BILL_STATE_WALKING_LEFT:
			nx = -1;
			vx = -BILL_WALKING_SPEED;
			if (isGrounded)
			{
				finalState = reqState;
			}
			break;
		case BILL_STATE_WALKING_RIGHT:
			nx = 1;
			vx = BILL_WALKING_SPEED;
			if (isGrounded)
			{
				finalState = reqState;
			}
			break;
		case BILL_STATE_LOOKING_UP:
			if (isGrounded)
			{
				vx = 0;
				ny = 1;
				finalState = reqState;
			}
			break;
		case BILL_STATE_LYING_DOWN:
			if (isGrounded)
			{
				vx = 0;
				ny = -1;
				finalState = reqState;
			}
			break;
		}
		break;
	}




	/*switch (reqState)
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
	}*/
	CGameObject::SetState(finalState);
}

RECT CBill::GetRect()
{
	RECT rect;
	return rect;
}

RECT CBill::GetBoundingBox()
{
	CSprites* sprites = CSprites::GetInstance();
	RECT rect;
	switch (state)
	{
	case BILL_STATE_JUMP:
		rect = sprites->Get(9091)->GetBoundingBox();
		break;
	case BILL_STATE_LYING_DOWN:
		rect = sprites->Get(9041)->GetBoundingBox();
		break;
	default:
		rect = sprites->Get(9001)->GetBoundingBox();
		break;
	}
	return rect;
}

void CBill::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	vy -= GRAVITY * dt;
	if (y < 130)
	{
		vy = 0;
		y = 130;
		isGrounded = true;
	}
}

void CBill::OnCollisionWith(LPCOLLISIONEVENT e)
{
	MessageBox(NULL, L"Collide", L"Collide", MB_OK); 
}
