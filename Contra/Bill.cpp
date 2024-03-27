#include "Bill.h"


void CBill::Update(DWORD dt)
{
	/*isGrounded = (y == GROUND_Y) ? true : false;
	
	vy = Gravity;
	Jump();*/

	x += vx * dt;
	//y += vy * dt;

	/*if (vx > 0 && x > 300) x = 300;
	if (vx < 0 && x < 5) x = 5;
	if (vy > 0 && y > 185) y = 185;
	if (vy < 0 && y < 15) y = 15;*/

	for (Bullet* bullet : bulletList)
	{
		if(bullet!=NULL)
			bullet->Update(dt);
	}

}

void CBill::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (aniId == -1) aniId = ID_ANI_BILL_IDLE_RIGHT;
	switch (state) {
	case BILL_STATE_WALKING_RIGHT:
		if (isShooting)
		{
			if (ny > 0) {
				aniId = ID_ANI_BILL_WALKING_RIGHT_LOOKUP;
			}
			else if (ny < 0)
			{
				aniId = ID_ANI_BILL_WALKING_RIGHT_LOOKDOWN;
			}
			else
			{
				aniId = ID_ANI_BILL_WALKING_RIGHT_SHOOTING;
			}
		}
		else {
			if (ny > 0) {
				aniId = ID_ANI_BILL_WALKING_RIGHT_LOOKUP;
			}
			else if(ny<0)
			{
				aniId = ID_ANI_BILL_WALKING_RIGHT_LOOKDOWN;
			}
			else 
			{
				aniId = ID_ANI_BILL_WALKING_RIGHT;
			}
		}	
		break;
	case BILL_STATE_WALKING_LEFT:
		if (isShooting)
		{
			if (ny > 0) {
				aniId = ID_ANI_BILL_WALKING_LEFT_LOOKUP;
			}
			else if (ny < 0)
			{
				aniId = ID_ANI_BILL_WALKING_LEFT_LOOKDOWN;
			}
			else
			{
				aniId = ID_ANI_BILL_WALKING_LEFT_SHOOTING;
			}
		}
		else {
			if (ny > 0) {
				aniId = ID_ANI_BILL_WALKING_LEFT_LOOKUP;
			}
			else if (ny < 0)
			{
				aniId = ID_ANI_BILL_WALKING_LEFT_LOOKDOWN;
			}
			else
			{
				aniId = ID_ANI_BILL_WALKING_LEFT;
			}		
		}
		break;
	case BILL_STATE_LIEING:
		if (isShooting)
		{
			if (nx < 0) {
				aniId = ID_ANI_BILL_LIEING_LEFT_SHOOTING;
			}
			else
			{
				aniId = ID_ANI_BILL_LIEING_RIGHT_SHOOTING;
			}
		}
		else {
			if (nx < 0) {
				aniId = ID_ANI_BILL_LIEING_LEFT;
			}
			else
			{
				aniId = ID_ANI_BILL_LIEING_RIGHT;
			}
		}
		
		break;
	case BILL_STATE_JUMP:
		aniId = ID_ANI_BILL_JUMP;
		break;
	case BILL_STATE_LOOKUP:
		if (isShooting)
		{
			if (nx < 0) {
				aniId = ID_ANI_BILL_LOOKUP_LEFT_SHOOTING;
			}
			else
			{
				aniId = ID_ANI_BILL_LOOKUP_RIGHT_SHOOTING;
			}
		}
		else
		{
			if (nx < 0) {
				aniId = ID_ANI_BILL_LOOKUP_LEFT;
			}
			else
			{
				aniId = ID_ANI_BILL_LOOKUP_RIGHT;
			}
		}
		break;
	case BILL_STATE_WALKING_DOWN:
		aniId = ID_ANI_BILL_WALKING_DOWN;
		break;
	case BILL_STATE_WALKING_UP:
		aniId = ID_ANI_BILL_WALKING_UP;
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
	default:
		aniId = ID_ANI_BILL_IDLE_RIGHT;
	}
	animations->Get(aniId)->Render(x, y);

	HandleBullet();
	for (Bullet* bullet : bulletList)
	{
		if (bullet != NULL)
			bullet->Render();
	}
}

void CBill::SetState(int state)
{
	switch (state)
	{
	case BILL_STATE_WALKING_RIGHT:
		vx = BILL_WALKING_SPEED;
		vy = 0;
		nx = 1;
		break;
	case BILL_STATE_WALKING_LEFT:
		vx = -BILL_WALKING_SPEED;
		vy = 0;
		nx = -1;
		break;
	case BILL_STATE_WALKING_DOWN:
		vy = BILL_WALKING_SPEED;
		vx = 0;
		break;
	case BILL_STATE_WALKING_UP:
		vy = -BILL_WALKING_SPEED;
		vx = 0;
		break;
	case BILL_STATE_IDLE:
		vx = 0.0f;
		vy = 0.0f;
		break;
	}

	CGameObject::SetState(state);
}

void CBill::UpdateState(D3DXVECTOR2 dir)
{
	/*if (dir.x > 0)
	{
		if (dir.y > 0)
		{	
			ny = 1;
		}
		else if (dir.y < 0)
		{
			ny = -1;
		}
		else {
			
			ny = 0;
			state = BILL_STATE_WALKING_RIGHT;
		}
		if (state != BILL_STATE_LIEING && state != BILL_STATE_LOOKUP)
		{
			vx = BILL_WALKING_SPEED;
		}
		
		nx = 1;
	}
	else if (dir.x <  0)
	{
		if (dir.y > 0)
		{
			
			ny=1;
		}
		else if (dir.y < 0)
		{
			
			ny = -1;
			
		}
		else {
		
			ny = 0;
			state = BILL_STATE_WALKING_LEFT;
		}
		if (state != BILL_STATE_LIEING && state != BILL_STATE_LOOKUP)
		{
			vx = -BILL_WALKING_SPEED;
		}
		nx = -1;
	}
	else {

		if (dir.y > 0)
		{
			state = BILL_STATE_LOOKUP;
			vx = 0;
		
			ny = 1;
		}
		else if (dir.y < 0)
		{			
			state = BILL_STATE_LIEING;			
			ny = -1;
			vx = 0;
		}
		else
		{
			vx = 0;
			ny = 0;
			state = BILL_STATE_IDLE;
		}		
		
	}
	CGameObject::SetState(state);*/

}


void CBill::Jump()
{
	/*CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_SPACE))
	{
		vy = -JumpForce;
		state = BILL_STATE_JUMP;
	}*/
	
}

void CBill::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_RIGHT:
		if (state != BILL_STATE_LIEING && state != BILL_STATE_JUMP)
			state = BILL_STATE_WALKING_RIGHT;
		nx = 1;
		break;
	case DIK_LEFT:
		if (state != BILL_STATE_LIEING && state != BILL_STATE_JUMP)
			state = BILL_STATE_WALKING_LEFT;
		nx = -1;
		break;
	case DIK_UP:
		if (state == BILL_STATE_LIEING || state == BILL_STATE_JUMP)
			return;
		if (state == BILL_STATE_WALKING_RIGHT || state == BILL_STATE_WALKING_LEFT)
			ny = 1;
		else
			state = BILL_STATE_LOOKUP;
		break;
	case DIK_DOWN:
		if (state == BILL_STATE_JUMP)
			return;
		if (state == BILL_STATE_WALKING_RIGHT || state == BILL_STATE_WALKING_LEFT)
			ny = -1;
		else
			state = BILL_STATE_LIEING;
		break;
	case DIK_Z:
		this->isShooting = true;
		break;
	}
	SetState(state);
}

void CBill::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_RIGHT:
		state = BILL_STATE_IDLE;
		break;
	case DIK_LEFT:
		state = BILL_STATE_IDLE;
		break;
	case DIK_UP:
		if(state==BILL_STATE_WALKING_RIGHT||state==BILL_STATE_WALKING_LEFT)
			ny = 0;
		else
			state = BILL_STATE_IDLE;
		break;
	case DIK_DOWN:
		if (state == BILL_STATE_WALKING_RIGHT || state == BILL_STATE_WALKING_LEFT)
			ny = 0;
		else
			state = BILL_STATE_IDLE;
		break;
	case DIK_Z:
		this->isShooting = false;
		break;
	}
}

void CBill::InputHandler(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	/*
	D3DXVECTOR2 dir = D3DXVECTOR2(0, 0);

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (state != BILL_STATE_LIEING && state != BILL_STATE_JUMP)
			state = BILL_STATE_WALKING_RIGHT;
		nx = 1;
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (state != BILL_STATE_LIEING && state != BILL_STATE_JUMP)
			state = BILL_STATE_WALKING_LEFT;
		nx = -1;
	}


	if (game->IsKeyDown(DIK_UP))
	{
		if (state == BILL_STATE_LIEING || state == BILL_STATE_JUMP)
			return;
		if (state == BILL_STATE_WALKING_RIGHT || state == BILL_STATE_WALKING_LEFT)
			ny = 1;
		else
			state = BILL_STATE_LOOKUP;
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		if (state == BILL_STATE_JUMP)
			return;
		if (state == BILL_STATE_WALKING_RIGHT || state == BILL_STATE_WALKING_LEFT)
			ny = -1;
		else
			state = BILL_STATE_LIEING;
	}
	else
	{
		ny = 0;
	}
	*/
	if (game->IsKeyDown(DIK_Z))
	{
		Shoot();
	}

	CGameObject::SetState(state);
}

void CBill::HandleBullet()
{
	for (int i = 0; i < bulletList.size(); i++)
	{
		Bullet* bullet = bulletList.at(i);
		if (bullet != NULL)
		{
			if (bullet->GetIsMove() == true)
			{
				bullet->HandMove();
			}
			else 
			{
				bulletList.erase(bulletList.begin() + i);
				if (bullet != NULL)
				{
					delete bullet;
					bullet = NULL;
				}
				
			}
		}
	}
}

void CBill::Shoot()
{
	if (!isShooting)
		return;
	int ox = 0;
	int oy = 0;
	Bullet* bullet = new Bullet();
	switch (state)
	{
	case BILL_STATE_WALKING_RIGHT:
		if (ny > 0) {
			bullet->SetDir(UpperRight);
		}
		else if (ny < 0)
		{
			bullet->SetDir(LowerRight);
		}
		else
		{
			ox = 15;
			oy = -5;
			bullet->SetDir(Right);
		}		
		break;
	case BILL_STATE_WALKING_LEFT:
		if (ny > 0) {
			bullet->SetDir(UpperLeft);
		}
		else if (ny < 0)
		{
			bullet->SetDir(LowerLeft);
		}
		else
		{
			bullet->SetDir(Left);
			ox = -15;
			oy = -5;
		}
		break;
	case BILL_STATE_LOOKUP:
		ox = 2;
		oy = -10;
		bullet->SetDir(Up);			
		break;
	case BILL_STATE_LIEING:
		if (nx < 0) {
			bullet->SetDir(Left);
		}
		else
		{
			bullet->SetDir(Right);
		}
	case BILL_STATE_IDLE:
		if (nx == 1)
		{
			bullet->SetDir(Right);
			ox = 15;
			oy = -5;
		}	
		else 
		{
			bullet->SetDir(Left);
			ox = -15;
			oy = -5;
		}
			
		break;
	default:
		bullet->SetDir(Right);
		ox = 15;
		break;
	}

	bullet->SetPosition(this->GetX() + ox, this->GetY() +oy);
	bullet->SetIsMove(true);
	bulletList.push_back(bullet);
	
}


