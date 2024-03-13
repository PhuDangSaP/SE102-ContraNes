#include "Enemy.h"

void CEnemy::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	/*if (vx > 0 && x > 300) {
		x = 300;
		this->SetState(ENEMY_STATE_WALKING_DOWN);
	}
	if (vx < 0 && x < 5) {
		x = 5;
		this->SetState(ENEMY_STATE_WALKING_UP);
	}
	if (vy > 0 && y > 185) {
		y = 185;
		this->SetState(ENEMY_STATE_WALKING_LEFT);
	}
	if (vy < 0 && y < 15) {
		y = 15;
		this->SetState(ENEMY_STATE_WALKING_RIGHT);
	}*/

	if (vx > 0 && x > 300) {
		x = 300;
		vx = -ENEMY_WALKING_SPEED;
		this->SetState(ENEMY_STATE_WALKING_LEFT);
	}
	if (vx < 0 && x < 5) {
		x = 5;
		vx = ENEMY_WALKING_SPEED;
		this->SetState(ENEMY_STATE_WALKING_RIGHT);
	}
	

	/*if (state == ENEMY_STATE_IDLE)
	{
		result = result = rand() % 101;
	}
	if (vx > 0 && x > 300) {
		x = 300;
		do {
			result = result = rand() % 101;
		} while (result >= 21 && result <= 40);
	}
	if (vx < 0 && x < 5) {
		x = 5;
		do {
			result = result = rand() % 101;
		} while (result >= 41 && result <= 60);
	}
	if (vy > 0 && y > 185) {
		y = 185;
		do {
			result = result = rand() % 101;
		} while (result >= 61 && result <= 80);
	}
	if (vy < 0 && y < 15) {
		y = 15;
		do {
			result = result = rand() % 101;
		} while (result >= 81 && result <= 100);
	}

	if (result >= 0 && result <= 20)
	{
		this->SetState(ENEMY_STATE_IDLE);
	}
	if (result >= 21 && result <= 40)
	{
		this->SetState(ENEMY_STATE_WALKING_RIGHT);
	}
	if (result >= 41 && result <= 60)
	{
		this->SetState(ENEMY_STATE_WALKING_LEFT);
	}
	if (result >= 61 && result <= 80)
	{
		this->SetState(ENEMY_STATE_WALKING_DOWN);
	}
	if (result >= 81 && result <= 100)
	{
		this->SetState(ENEMY_STATE_WALKING_UP);
	}*/
}

void CEnemy::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (aniId == -1) aniId = ID_ANI_ENEMY_IDLE_RIGHT;
	switch (state) {
	case ENEMY_STATE_WALKING_RIGHT:
		aniId = ID_ANI_ENEMY_WALKING_RIGHT;
		break;
	case ENEMY_STATE_WALKING_LEFT:
		aniId = ID_ANI_ENEMY_WALKING_LEFT;
		break;
	case ENEMY_STATE_WALKING_DOWN:
		aniId = ID_ANI_ENEMY_WALKING_DOWN;
		break;
	case ENEMY_STATE_WALKING_UP:
		aniId = ID_ANI_ENEMY_WALKING_UP;
		break;
	case ENEMY_STATE_IDLE:
		if (nx < 0) {
			aniId = ID_ANI_ENEMY_IDLE_LEFT;
		}
		else
		{
			aniId = ID_ANI_ENEMY_IDLE_RIGHT;
		}
		break;
	default:
		aniId = ID_ANI_ENEMY_IDLE_RIGHT;
	}
	animations->Get(aniId)->Render(x, y);
}

void CEnemy::SetState(int state)
{
	switch (state)
	{
	case ENEMY_STATE_WALKING_RIGHT:
		vx = ENEMY_WALKING_SPEED;
		vy = 0;
		nx = 1;
		break;
	case ENEMY_STATE_WALKING_LEFT:
		vx = -ENEMY_WALKING_SPEED;
		vy = 0;
		nx = -1;
		break;
	case ENEMY_STATE_WALKING_DOWN:
		vy = ENEMY_WALKING_SPEED;
		vx = 0;
		break;
	case ENEMY_STATE_WALKING_UP:
		vy = -ENEMY_WALKING_SPEED;
		vx = 0;
		break;
	case ENEMY_STATE_IDLE:
		vx = 0.0f;
		vy = 0.0f;
		break;
	}

	CGameObject::SetState(state);
}