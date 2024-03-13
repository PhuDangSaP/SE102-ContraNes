#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"
#include <random>
#include <cstdlib> 
#include <iostream> 
#include <time.h>

#define ENEMY_WALKING_SPEED		0.1f

#define ENEMY_STATE_IDLE			0
#define ENEMY_STATE_WALKING_RIGHT	100
#define ENEMY_STATE_WALKING_LEFT	200
#define ENEMY_STATE_WALKING_UP		300
#define ENEMY_STATE_WALKING_DOWN	400


#pragma region ANIMATION_ID

#define ID_ANI_ENEMY_IDLE_RIGHT 500
#define ID_ANI_ENEMY_IDLE_LEFT 501
			   
#define ID_ANI_ENEMY_WALKING_RIGHT	11111//600
#define ID_ANI_ENEMY_WALKING_LEFT	11120//601
#define ID_ANI_ENEMY_WALKING_UP		602
#define ID_ANI_ENEMY_WALKING_DOWN	603

class CEnemy : public CGameObject
{
	int result;
public:
	CEnemy(float x, float y) : CGameObject(x, y)
	{
		vx = ENEMY_WALKING_SPEED;
		state = ENEMY_STATE_WALKING_RIGHT;
		/*srand(time(0));
		result = rand() % 101;
		if (result >= 0 && result <= 20)
		{
			state = ENEMY_STATE_IDLE;
		}
		if (result >= 21 && result <= 40)
		{
			state = ENEMY_STATE_WALKING_RIGHT;
			vx = ENEMY_WALKING_SPEED;
			nx = 1;
		}
		if (result >= 41 && result <= 60)
		{
			state = ENEMY_STATE_WALKING_LEFT;
			vx = -ENEMY_WALKING_SPEED;
			nx = -1;
		}
		if (result >= 61 && result <= 80)
		{
			state = ENEMY_STATE_WALKING_DOWN;
			vy = ENEMY_WALKING_SPEED;
		}
		if (result >= 81 && result <= 100)
		{
			state = ENEMY_STATE_WALKING_UP;
			vy = -ENEMY_WALKING_SPEED;
		}*/
	}
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};