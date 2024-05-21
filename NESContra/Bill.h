#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BILL_WALKING_SPEED		0.065f
#define BILL_JUMP_SPEED			0.25f
#define GRAVITY					0.0005f
#define BILL_DEFLECT_SPEED		0.1f

#define BILL_STATE_IDLE					0
#define BILL_STATE_WALKING_RIGHT		100
#define BILL_STATE_WALKING_LEFT			200
#define BILL_STATE_LOOKING_UP			300
#define BILL_STATE_LYING_DOWN			400
#define BILL_STATE_WALKING_LOOK_UP		500
#define BILL_STATE_WALKING_LOOK_DOWN	600
#define BILL_STATE_JUMP					700
#define BILL_STATE_DIE					800


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

#pragma region BBOX_VALUE

#define BILL_STAND_BBOX_WIDTH	24
#define BILL_STAND_BBOX_HEIGHT	36
#define BILL_LIE_DOWN_BBOX_WIDTH	32
#define BILL_LIE_DOWN_BBOX_HEIGHT	16
#define BILL_JUMP_BBOX_WIDTH	16
#define BILL_JUMP_BBOX_HEIGHT	16

#define BILL_LIE_DOWN_HEIGHT_ADJUST ((BILL_STAND_BBOX_HEIGHT-BILL_LIE_DOWN_BBOX_HEIGHT)/2)


class CBill : public CGameObject
{
private:
	bool isGrounded;
	void OnCollisionWithSoldier(LPCOLLISIONEVENT e);
	void OnCollisionWithWallTurret(LPCOLLISIONEVENT e);
public:
	CBill(float x, float y) : CGameObject(x, y)
	{
		ny = 0;
		SetState(BILL_STATE_JUMP);
		nx = 1;
		isGrounded = false;
		isMovable = true;
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