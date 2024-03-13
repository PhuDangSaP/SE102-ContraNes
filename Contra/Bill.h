#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define BILL_WALKING_SPEED		0.1f

#define BILL_STATE_IDLE				0
#define BILL_STATE_WALKING_RIGHT	100
#define BILL_STATE_WALKING_LEFT		200
#define BILL_STATE_WALKING_UP		300
#define BILL_STATE_WALKING_DOWN		400

#define BILL_STATE_LIEING 203
#define BILL_STATE_LOOKUP 204
#define BILL_STATE_JUMP 220

#pragma region ANIMATION_ID

#define ID_ANI_BILL_IDLE_RIGHT 500
#define ID_ANI_BILL_IDLE_LEFT 501

#define ID_ANI_BILL_WALKING_RIGHT 600
#define ID_ANI_BILL_WALKING_LEFT 601
#define ID_ANI_BILL_WALKING_UP 602
#define ID_ANI_BILL_WALKING_DOWN 603
#define ID_ANI_BILL_WALKING_RIGHT_LOOKUP 610
#define ID_ANI_BILL_WALKING_RIGHT_LOOKDOWN 611
#define ID_ANI_BILL_WALKING_LEFT_LOOKUP 612
#define ID_ANI_BILL_WALKING_LEFT_LOOKDOWN 613
#define ID_ANI_BILL_LIEING_RIGHT 614
#define ID_ANI_BILL_LIEING_LEFT 615
#define ID_ANI_BILL_LOOKUP 616
#define ID_ANI_BILL_JUMP 620

#define GROUND_Y 100.0f
#define Gravity 0.8
#define JumpForce 0.3
class CBill : public CGameObject
{
private:
	//bool isGrounded;
public:
	CBill(float x, float y) : CGameObject(x, y)
	{
	}
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void UpdateState(D3DXVECTOR2 dir);
	void Jump();
};