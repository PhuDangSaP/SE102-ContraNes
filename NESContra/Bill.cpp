#include "Bill.h"
#include "Collision.h"
#include "Soldier.h"
#include "WallTurret.h"
#include "Platform.h"
#include "Water.h"


void CBill::Update(DWORD dt)
{
	
}

void CBill::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy -= GRAVITY * dt;
	if (x < 10) { x = 10; }
	if (isInWater && splashTimer > 0)
	{
		if (splashTimer == WATER_SPLASH_TIMER)
		{
			RequestState(BILL_STATE_SPLASH);
		}
		splashTimer -= dt;
	}
	if (state == BILL_STATE_CLIMB && climbTimer > 0)
	{
		SetPosition(climbTargetX, climbTargetY);
		climbTimer -= dt;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBill::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	float d = 0;
	if (isInWater)
	{
		GetInWaterAnimations(aniId, d);
	}
	else
	{
		GetDefaultAnimations(aniId, d);
	}
	animations->Get(aniId)->Render(x, y + d);
}

void CBill::RequestState(int reqState)
{
	if (state == BILL_STATE_DIE)return;
	int finalState = state;
	if (isInWater && splashTimer <= 0)
	{
		RequestUnderWaterState(reqState, finalState);
	}
	else
	{
		switch (state)
		{
		case BILL_STATE_CLIMB:
			if (climbTimer <= 0)
			{
				y += BILL_SWIM_HEIGHT_ADJUST;
				finalState = reqState;
			}
			break;
		case BILL_STATE_IDLE:
			switch (reqState)
			{
			case BILL_STATE_SPLASH:
				y -= BILL_SWIM_HEIGHT_ADJUST;
				finalState = reqState;
				break;
			case BILL_STATE_DIE:
				vx = -nx * BILL_DEFLECT_SPEED;
				vy = BILL_DEFLECT_SPEED;
				isGrounded = false;
				finalState = reqState;
				break;
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
				if (isGrounded && !isInWater)
				{
					ny = -1;
					y -= BILL_LIE_DOWN_HEIGHT_ADJUST;
					finalState = reqState;
				}
				break;
			case BILL_STATE_JUMP:
				if (isGrounded)
				{
					vy += BILL_JUMP_SPEED;
					isGrounded = false;
					finalState = reqState;
				}
				break;
			}
			break;
		case BILL_STATE_WALKING_LEFT:
			switch (reqState)
			{
			case BILL_STATE_SPLASH:
				y -= BILL_SWIM_HEIGHT_ADJUST;
				finalState = reqState;
				break;
			case BILL_STATE_DIE:
				vx = -nx * BILL_DEFLECT_SPEED;
				vy = BILL_DEFLECT_SPEED;
				isGrounded = false;
				finalState = reqState;
				break;
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
			case BILL_STATE_SPLASH:
				y -= BILL_SWIM_HEIGHT_ADJUST;
				finalState = reqState;
				break;
			case BILL_STATE_DIE:
				vx = -nx * BILL_DEFLECT_SPEED;
				vy = BILL_DEFLECT_SPEED;
				isGrounded = false;
				finalState = reqState;
				break;
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
			case BILL_STATE_SPLASH:
				y -= BILL_SWIM_HEIGHT_ADJUST;
				finalState = reqState;
				break;
			case BILL_STATE_DIE:
				vx = -nx * BILL_DEFLECT_SPEED;
				vy = BILL_DEFLECT_SPEED;
				isGrounded = false;
				finalState = reqState;
				break;
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
				y -= BILL_LIE_DOWN_HEIGHT_ADJUST;
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
			case BILL_STATE_SPLASH:
				finalState = reqState;
				break;
			case BILL_STATE_JUMP:
				if (isOnDropablePlatform)
				{
					isGrounded = false;
					finalState = BILL_STATE_IDLE;
				}
				break;
			case BILL_STATE_DIE:
				vx = -nx * BILL_DEFLECT_SPEED;
				vy = BILL_DEFLECT_SPEED;
				isGrounded = false;
				finalState = reqState;
				break;
			case BILL_STATE_IDLE:
				ny = 0;
				y += BILL_LIE_DOWN_HEIGHT_ADJUST;
				finalState = reqState;
				break;
			case BILL_STATE_WALKING_RIGHT:
				vx = BILL_WALKING_SPEED;
				y += BILL_LIE_DOWN_HEIGHT_ADJUST;
				nx = 1;
				finalState = BILL_STATE_WALKING_LOOK_DOWN;
				break;
			case BILL_STATE_WALKING_LEFT:
				vx = -BILL_WALKING_SPEED;
				y += BILL_LIE_DOWN_HEIGHT_ADJUST;
				nx = -1;
				finalState = BILL_STATE_WALKING_LOOK_DOWN;
				break;
			case BILL_STATE_LOOKING_UP:
				ny = 1;
				y += BILL_LIE_DOWN_HEIGHT_ADJUST;
				finalState = reqState;
				break;
			}
			break;
		case BILL_STATE_WALKING_LOOK_UP:
			switch (reqState)
			{
			case BILL_STATE_SPLASH:
				y -= BILL_SWIM_HEIGHT_ADJUST;
				finalState = reqState;
				break;
			case BILL_STATE_DIE:
				vx = -nx * BILL_DEFLECT_SPEED;
				vy = BILL_DEFLECT_SPEED;
				isGrounded = false;
				finalState = reqState;
				break;
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
				y -= BILL_LIE_DOWN_HEIGHT_ADJUST;
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
			case BILL_STATE_SPLASH:
				y -= BILL_SWIM_HEIGHT_ADJUST;
				finalState = reqState;
				break;
			case BILL_STATE_DIE:
				vx = -nx * BILL_DEFLECT_SPEED;
				vy = BILL_DEFLECT_SPEED;
				isGrounded = false;
				finalState = reqState;
				break;
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
				y -= BILL_LIE_DOWN_HEIGHT_ADJUST;
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
			case BILL_STATE_SPLASH:
				finalState = reqState;
				break;
			case BILL_STATE_DIE:
				vx = -nx * BILL_DEFLECT_SPEED;
				vy = BILL_DEFLECT_SPEED;
				isGrounded = false;
				finalState = reqState;
				break;
			case BILL_STATE_IDLE:
				if (isGrounded)
				{
					vy = 0;
					vx = 0;
					y += BILL_LIE_DOWN_HEIGHT_ADJUST;
					finalState = reqState;
				}
				break;
			case BILL_STATE_WALKING_LEFT:
				nx = -1;
				vx = -BILL_WALKING_SPEED;
				if (isGrounded)
				{
					y += BILL_LIE_DOWN_HEIGHT_ADJUST;
					finalState = reqState;
				}
				break;
			case BILL_STATE_WALKING_RIGHT:
				nx = 1;
				vx = BILL_WALKING_SPEED;
				if (isGrounded)
				{
					y += BILL_LIE_DOWN_HEIGHT_ADJUST;
					finalState = reqState;
				}
				break;
			case BILL_STATE_LOOKING_UP:
				if (isGrounded)
				{
					vx = 0;
					y += BILL_LIE_DOWN_HEIGHT_ADJUST;
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
	}
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
	if ((isInWater || state == BILL_STATE_CLIMB) && state != BILL_STATE_DIE)
	{
		rect.left = x - BILL_SWIM_BBOX_WIDTH / 2;
		rect.top = y + BILL_SWIM_BBOX_HEIGHT / 2;
		rect.right = rect.left + BILL_SWIM_BBOX_WIDTH;
		rect.bottom = rect.top - BILL_SWIM_BBOX_HEIGHT;
	}
	else
	{
		switch (state)
		{
		case BILL_STATE_JUMP:
			rect.left = x - BILL_JUMP_BBOX_WIDTH / 2;
			rect.top = y + BILL_JUMP_BBOX_HEIGHT / 2;
			rect.right = rect.left + BILL_JUMP_BBOX_WIDTH;
			rect.bottom = rect.top - BILL_JUMP_BBOX_HEIGHT;
			break;
		case BILL_STATE_LYING_DOWN:
			rect.left = x - BILL_LIE_DOWN_BBOX_WIDTH / 2;
			rect.top = y + BILL_LIE_DOWN_BBOX_HEIGHT / 2;
			rect.right = rect.left + BILL_LIE_DOWN_BBOX_WIDTH;
			rect.bottom = rect.top - BILL_LIE_DOWN_BBOX_HEIGHT;
			break;
		case BILL_STATE_DIE:
			rect.left = x - BILL_LIE_DOWN_BBOX_WIDTH / 2;
			rect.top = y + BILL_LIE_DOWN_BBOX_HEIGHT / 2;
			rect.right = rect.left + BILL_LIE_DOWN_BBOX_WIDTH;
			rect.bottom = rect.top - BILL_LIE_DOWN_BBOX_HEIGHT;
		default:
			rect.left = x - BILL_STAND_BBOX_WIDTH / 2;
			rect.top = y + BILL_STAND_BBOX_HEIGHT / 2;
			rect.right = rect.left + BILL_STAND_BBOX_WIDTH;
			rect.bottom = rect.top - BILL_STAND_BBOX_HEIGHT;
			break;
		}
	}
	
	return rect;
}

void CBill::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	if (state != BILL_STATE_DIE) {
		isGrounded = false;
		splashTimer = WATER_SPLASH_TIMER;
	}
}

void CBill::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if(e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny > 0) isGrounded = true;
		if (state == BILL_STATE_DIE ) vx = 0;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		if (!dynamic_cast<Platform*>(e->obj))
		{
			vx = 0;
		}
	}
	//MessageBox(NULL, L"Collide", L"Collide", MB_OK);
	if (dynamic_cast<Platform*>(e->obj))
		OnCollisionWithPlatform(e);
	if (dynamic_cast<Water*>(e->obj))
		OnCollisionWithWater(e);
	if (dynamic_cast<CSoldier*>(e->obj))
		OnCollisionWithSoldier(e);
	if (dynamic_cast<CWallTurret*>(e->obj))
		OnCollisionWithWallTurret(e);
}

void CBill::OnCollisionWithSoldier(LPCOLLISIONEVENT e)
{
	if (state != BILL_STATE_DIE)
	{
		RequestState(BILL_STATE_DIE);
	}
}

void CBill::OnCollisionWithWallTurret(LPCOLLISIONEVENT e)
{
	CWallTurret* wT = dynamic_cast<CWallTurret*>(e->obj);
	if (wT->GetState() != TURRET_STATE_IDLE)
		return;
	wT->RequestState(TURRET_STATE_OPENING);
}

void CBill::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	Platform* p = dynamic_cast<Platform*>(e->obj);
	if (isInWater)
	{
		RECT r = p->GetBoundingBox();
		if (x <= r.left)
		{
			climbTargetX = r.left;
		}
		if (x >= r.right)
		{
			climbTargetX = r.right;
		}
		climbTargetY = r.top + BILL_SWIM_BBOX_HEIGHT / 2 + 1.0f;
		isInWater = false;
		climbTimer = WATER_SPLASH_TIMER;
		state = BILL_STATE_CLIMB;
	}
	isOnDropablePlatform = p->IsDropable();
}

void CBill::OnCollisionWithWater(LPCOLLISIONEVENT e)
{
	isInWater = true;
}

void CBill::GetInWaterAnimations(int& aniId, float& d)
{
	switch (state) {
	case BILL_STATE_SPLASH:
		aniId = ID_ANI_BILL_LAND_IN_WATER;
		break;
	case BILL_STATE_DIE:
		if (nx < 0)
		{
			aniId = ID_ANI_BILL_DIE_RIGHT;
		}
		else
		{
			aniId = ID_ANI_BILL_DIE_LEFT;
		}
		break;
	case BILL_STATE_WALKING_RIGHT:
		aniId = ID_ANI_BILL_SWIM_RIGHT;
		break;
	case BILL_STATE_WALKING_LEFT:
		aniId = ID_ANI_BILL_SWIM_LEFT;
		break;
	case BILL_STATE_LYING_DOWN:
		aniId = ID_ANI_BILL_HIDE_UNDER_WATER;
		d = -10;
		break;
	case BILL_STATE_LOOKING_UP:
		if (this->nx >= 0)
		{
			aniId = ID_ANI_BILL_SWIM_RIGHT;
		}
		else
		{
			aniId = ID_ANI_BILL_SWIM_LEFT;
		}
		break;
	case BILL_STATE_IDLE:
		if (nx < 0)
		{
			aniId = ID_ANI_BILL_IDLE_UNDER_WATER_LEFT;
		}
		else
		{
			aniId = ID_ANI_BILL_IDLE_UNDER_WATER_RIGHT;
		}
		break;
	case BILL_STATE_WALKING_LOOK_UP:
		if (this->nx >= 0)
		{
			aniId = ID_ANI_BILL_SWIM_RIGHT;
		}
		else
		{
			aniId = ID_ANI_BILL_SWIM_LEFT;
		}
		break;
	default:
		aniId = ID_ANI_BILL_IDLE_RIGHT;
	}
}

void CBill::GetDefaultAnimations(int& aniId, float& d)
{
	switch (state) {
	case BILL_STATE_DIE:
		if (nx < 0)
		{
			if (isGrounded)
			{
				aniId = ID_ANI_BILL_DIE_LYING_RIGHT;
				d = -10;
			}
			else
			{
				aniId = ID_ANI_BILL_DIE_RIGHT;
			}
		}
		else
		{
			if (isGrounded)
			{
				aniId = ID_ANI_BILL_DIE_LYING_LEFT;
				d = -10;
			}
			else
			{
				aniId = ID_ANI_BILL_DIE_LEFT;
			}
		}
		break;
	case BILL_STATE_WALKING_RIGHT:
		if (isGrounded)
		{
			aniId = ID_ANI_BILL_WALKING_RIGHT;
		}
		else
		{
			aniId = ID_ANI_BILL_FREE_FALL_RIGHT;
		}
		break;
	case BILL_STATE_WALKING_LEFT:
		if (isGrounded)
		{
			aniId = ID_ANI_BILL_WALKING_LEFT;
		}
		else
		{
			aniId = ID_ANI_BILL_FREE_FALL_LEFT;
		}
		break;
	case BILL_STATE_LYING_DOWN:
		if (this->nx >= 0)
		{
			if (isGrounded)
			{
				aniId = ID_ANI_BILL_LYING_DOWN_RIGHT;
			}
			else
			{
				aniId = ID_ANI_BILL_FREE_FALL_RIGHT;
			}
		}
		else
		{
			if (isGrounded)
			{
				aniId = ID_ANI_BILL_LYING_DOWN_LEFT;
			}
			else
			{
				aniId = ID_ANI_BILL_FREE_FALL_LEFT;
			}
		}
		break;
	case BILL_STATE_LOOKING_UP:
		if (this->nx >= 0)
		{
			if (isGrounded)
			{
				aniId = ID_ANI_BILL_LOOKING_UP_RIGHT;
				d = 5;
			}
			else
			{
				aniId = ID_ANI_BILL_FREE_FALL_RIGHT;
			}
		}
		else
		{
			if (isGrounded)
			{
				aniId = ID_ANI_BILL_LOOKING_UP_LEFT;
				d = 5;
			}
			else
			{
				aniId = ID_ANI_BILL_FREE_FALL_LEFT;
			}
		}
		break;
	case BILL_STATE_IDLE:
		if (nx < 0)
		{
			if (isGrounded)
			{
				aniId = ID_ANI_BILL_IDLE_LEFT;
			}
			else
			{
				aniId = ID_ANI_BILL_FREE_FALL_LEFT;
			}
		}
		else
		{
			if (isGrounded)
			{
				aniId = ID_ANI_BILL_IDLE_RIGHT;
			}
			else
			{
				aniId = ID_ANI_BILL_FREE_FALL_RIGHT;
			}
		}
		break;
	case BILL_STATE_WALKING_LOOK_UP:
		if (this->nx >= 0)
		{
			if (isGrounded)
			{
				aniId = ID_ANI_BILL_WALKING_LOOKING_UP_RIGHT;
			}
			else
			{
				aniId = ID_ANI_BILL_FREE_FALL_RIGHT;
			}
		}
		else
		{
			if (isGrounded)
			{
				aniId = ID_ANI_BILL_WALKING_LOOKING_UP_LEFT;
			}
			else
			{
				aniId = ID_ANI_BILL_FREE_FALL_LEFT;
			}
		}
		break;
	case BILL_STATE_WALKING_LOOK_DOWN:
		if (this->nx >= 0)
		{
			if (isGrounded)
			{
				aniId = ID_ANI_BILL_WALKING_LOOKING_DOWN_RIGHT;
			}
			else
			{
				aniId = ID_ANI_BILL_FREE_FALL_RIGHT;
			}
		}
		else
		{
			if (isGrounded)
			{
				aniId = ID_ANI_BILL_WALKING_LOOKING_DOWN_LEFT;
			}
			else
			{
				aniId = ID_ANI_BILL_FREE_FALL_LEFT;
			}
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
	case BILL_STATE_CLIMB:
		if (this->nx >= 0)
		{
			aniId = ID_ANI_BILL_CLIMB_OUT_WATER_RIGHT;
		}
		else
		{
			aniId = ID_ANI_BILL_CLIMB_OUT_WATER_LEFT;
		}
		break;
	default:
		aniId = ID_ANI_BILL_IDLE_RIGHT;
	}
}

void CBill::RequestUnderWaterState(int reqState, int& finalState)
{
	switch (state)
	{
	case BILL_STATE_SPLASH:
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
		case BILL_STATE_WALKING_RIGHT:
			vx = BILL_WALKING_SPEED;
			nx = 1;
			finalState = reqState;
			break;
		case BILL_STATE_LOOKING_UP:
			finalState = reqState;
			break;
		case BILL_STATE_LYING_DOWN:
			vx = 0;
			finalState = reqState;
			break;
		}
		break;
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
			finalState = reqState;
			break;
		case BILL_STATE_LYING_DOWN:
			vx = 0;
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
			finalState = reqState;
			break;
		case BILL_STATE_LYING_DOWN:
			vx = 0;
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
			finalState = reqState;
			break;
		case BILL_STATE_LYING_DOWN:
			vx = 0;
			finalState = reqState;
			break;
		}
		break;
	case BILL_STATE_LOOKING_UP:
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
		case BILL_STATE_WALKING_RIGHT:
			vx = BILL_WALKING_SPEED;
			nx = 1;
			finalState = reqState;
			break;
		case BILL_STATE_LYING_DOWN:
			vx = 0;
			finalState = reqState;
			break;
		}
		break;
	case BILL_STATE_LYING_DOWN:
		switch (reqState)
		{
		case BILL_STATE_IDLE:
			vx = 0;
			finalState = reqState;
			break;
		case BILL_STATE_WALKING_LEFT:
			vx = 0;
			nx = -1;
			break;
		case BILL_STATE_WALKING_RIGHT:
			vx = 0;
			nx = 1;
			break;
		case BILL_STATE_LOOKING_UP:
			finalState = reqState;
			break;
		}
		break;
	}
}
