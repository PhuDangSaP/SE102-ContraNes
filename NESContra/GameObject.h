#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include "Collision.h"

#define GRAVITY					0.0005f

using namespace std;

class CGameObject
{
protected:
	float x; 
	float y;

	float vx;
	float vy;

	int nx;
	int ny;

	int state;		
	bool isMovable = false;
	bool isDeleted = false;
public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }
	bool IsDeleted() { return isDeleted; }

	bool GetIsMovable() { return this->isMovable; }
	virtual int IsCollidable() { return 0; }
	CGameObject();
	CGameObject(float x, float y):CGameObject() { this->x = x; this->y = y; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;
	virtual RECT GetRect() = 0;
	virtual RECT GetBoundingBox() = 0;

	virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }
	virtual int IsBlocking() { return 1; }
	~CGameObject() {};
};

typedef CGameObject* LPGAMEOBJECT;