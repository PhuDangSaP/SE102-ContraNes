#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define WATER_SPLASH_TIMER		250.0f

#define BILL_WALKING_SPEED		0.065f
#define BILL_JUMP_SPEED			0.225f
#define BILL_DEFLECT_SPEED		0.1f

#define BILL_STATE_IDLE					0
#define BILL_STATE_WALKING_RIGHT		100
#define BILL_STATE_WALKING_LEFT			110
#define BILL_STATE_LOOKING_UP			120
#define BILL_STATE_LYING_DOWN			130
#define BILL_STATE_WALKING_LOOK_UP		140
#define BILL_STATE_WALKING_LOOK_DOWN	150
#define BILL_STATE_JUMP					160
#define BILL_STATE_DIE					170
#define BILL_STATE_SPLASH				180
#define BILL_STATE_CLIMB				190


#pragma region ANIMATION_ID

#define ID_ANI_BILL_IDLE_RIGHT 1000
#define ID_ANI_BILL_IDLE_LEFT 1001

#define ID_ANI_BILL_WALKING_RIGHT 1100
#define ID_ANI_BILL_WALKING_LEFT 1101
#define ID_ANI_BILL_LOOKING_UP_RIGHT 1102
#define ID_ANI_BILL_LOOKING_UP_LEFT 1103
#define ID_ANI_BILL_LYING_DOWN_RIGHT 1104
#define ID_ANI_BILL_LYING_DOWN_LEFT	 1105
#define ID_ANI_BILL_WALKING_LOOKING_UP_RIGHT 1106
#define ID_ANI_BILL_WALKING_LOOKING_UP_LEFT 1107
#define ID_ANI_BILL_WALKING_LOOKING_DOWN_RIGHT 1108
#define ID_ANI_BILL_WALKING_LOOKING_DOWN_LEFT 1109
#define ID_ANI_BILL_JUMP_RIGHT	1110
#define ID_ANI_BILL_JUMP_LEFT	1111

#define ID_ANI_BILL_DIE_RIGHT	1112
#define ID_ANI_BILL_DIE_LEFT	1113
#define ID_ANI_BILL_DIE_LYING_RIGHT	1114
#define ID_ANI_BILL_DIE_LYING_LEFT	1115

#define ID_ANI_BILL_FREE_FALL_RIGHT	1116
#define ID_ANI_BILL_FREE_FALL_LEFT 1117

#define ID_ANI_BILL_IDLE_UNDER_WATER_RIGHT	1118
#define ID_ANI_BILL_IDLE_UNDER_WATER_LEFT	1119

#define ID_ANI_BILL_HIDE_UNDER_WATER	1120

#define ID_ANI_BILL_SWIM_RIGHT	1121
#define ID_ANI_BILL_SWIM_LEFT	1122

#define ID_ANI_BILL_LAND_IN_WATER	1123
#define ID_ANI_BILL_CLIMB_OUT_WATER_RIGHT	1124
#define ID_ANI_BILL_CLIMB_OUT_WATER_LEFT	1125

#define ID_ANI_BILL_SWIM_SHOOT_UP_RIGHT	1126	//SHOOT STRAIGHT UP
#define ID_ANI_BILL_SWIM_SHOOT_UP_LEFT	1127	//SHOOT STRAIGHT UP

#define ID_ANI_BILL_SWIM_SHOOT_TOP_RIGHT	1128
#define ID_ANI_BILL_SWIM_SHOOT_TOP_LEFT	1129



#pragma region BBOX_VALUE

#define BILL_STAND_BBOX_WIDTH	24
#define BILL_STAND_BBOX_HEIGHT	36

#define BILL_LIE_DOWN_BBOX_WIDTH	32
#define BILL_LIE_DOWN_BBOX_HEIGHT	16

#define BILL_JUMP_BBOX_WIDTH	16
#define BILL_JUMP_BBOX_HEIGHT	16

#define BILL_SWIM_BBOX_WIDTH	15	//Can also be use for idle, hide, climb, land in water
#define BILL_SWIM_BBOX_HEIGHT	15	//Can also be use for idle, hide, climb, land in water


#define BILL_LIE_DOWN_HEIGHT_ADJUST ((BILL_STAND_BBOX_HEIGHT-BILL_LIE_DOWN_BBOX_HEIGHT)/2)
#define BILL_SWIM_HEIGHT_ADJUST ((BILL_STAND_BBOX_HEIGHT-BILL_SWIM_BBOX_HEIGHT)/2)



class CBill : public CGameObject
{
private:
	bool isGrounded;
	bool isOnDropablePlatform;
	bool isInWater;
	float splashTimer;
	float climbTimer;
	float climbTargetX;
	float climbTargetY;
	void OnCollisionWithSoldier(LPCOLLISIONEVENT e);
	void OnCollisionWithWallTurret(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatform(LPCOLLISIONEVENT e);
	void OnCollisionWithWater(LPCOLLISIONEVENT e);
	void GetInWaterAnimations(int& aniId, float& d);
	void GetDefaultAnimations(int& aniId, float& d);
	void RequestUnderWaterState(int reqState, int& finalState);
public:
	CBill(float x, float y) : CGameObject(x, y)
	{
		ny = 0;
		SetState(BILL_STATE_JUMP);
		nx = 1;
		isGrounded = false;
		isOnDropablePlatform = false;
		isInWater = false;
		isMovable = true;
		splashTimer = WATER_SPLASH_TIMER;
		climbTimer = WATER_SPLASH_TIMER;

	}
	void RequestState(int state);
	void GetPos(float& x, float& y) { x = this->x; y = this->y; }
	bool fireIsletGo = true;
	//void Fire();
	void Update(DWORD dt);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	RECT GetRect();
	RECT GetBoundingBox();
	int IsCollidable() { return 1 ;}
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
};