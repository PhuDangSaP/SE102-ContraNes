#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#include <vector>
#include "Bullet.h"

#define BILL_WALKING_SPEED		0.1f

#define BILL_STATE_IDLE				0
#define BILL_STATE_WALKING_RIGHT	100
#define BILL_STATE_WALKING_LEFT		200
#define BILL_STATE_LIEING 203
#define BILL_STATE_LOOKUP 204
#define BILL_STATE_JUMP 220

// không dùng
#define BILL_STATE_WALKING_UP		300
#define BILL_STATE_WALKING_DOWN		400

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
#define ID_ANI_BILL_LOOKUP_RIGHT 616
#define ID_ANI_BILL_LOOKUP_LEFT 617
#define ID_ANI_BILL_JUMP 620

#define ID_ANI_BILL_WALKING_RIGHT_SHOOTING 700
#define ID_ANI_BILL_WALKING_RIGHT_LOOKUP_SHOOTING 701
#define ID_ANI_BILL_WALKING_RIGHT_LOOKDOWN_SHOOTING 702
#define ID_ANI_BILL_WALKING_LEFT_SHOOTING 710
#define ID_ANI_BILL_WALKING_LEFT_LOOKUP_SHOOTING 711
#define ID_ANI_BILL_WALKING_LEFT_LOOKDOWN_SHOOTING 712
#define ID_ANI_BILL_LOOKUP_RIGHT_SHOOTING 750
#define ID_ANI_BILL_LOOKUP_LEFT_SHOOTING 751
#define ID_ANI_BILL_LIEING_RIGHT_SHOOTING 760
#define ID_ANI_BILL_LIEING_LEFT_SHOOTING 761

#define FIRE_RATE 15

#define GROUND_Y 100.0f
#define Gravity 0.8
#define JumpForce 0.3
class CBill : public CGameObject
{
private:
	//bool isGrounded;
	std::vector<Bullet*> bulletList;
	float nextTimeToFire;
	bool isShooting;
public:
	CBill(float x, float y) : CGameObject(x, y) { this->isShooting = false; }
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void UpdateState(D3DXVECTOR2 dir);
	void Jump();
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void InputHandler(BYTE* states);
	void SetIsShooting(bool isShooting) { this->isShooting = isShooting; }
	void SetBulletList(std::vector<Bullet*> bulletList) { this->bulletList = bulletList; }
	std::vector<Bullet*> GetBulletList() const { return this->bulletList; }
	void HandleBullet();
	void Shoot();
};