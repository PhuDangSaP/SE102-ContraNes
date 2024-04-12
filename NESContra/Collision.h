#pragma once
#include <vector>
#include "Game.h"
using namespace std;

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CollisionEvent;
typedef CollisionEvent* LPCOLLISIONEVENT;

enum CollisionDir
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

struct CollisionEvent
{
	LPGAMEOBJECT obj; // target obj
	float t;
	CollisionDir dir;
	bool isDeleted;
	CollisionEvent(LPGAMEOBJECT obj, float t, CollisionDir dir)
	{
		this->obj = obj;
		this->t = t;
		this->dir = dir;
		this->isDeleted = false;
	}
	bool WasCollided() { return t >= 0.0f && t <= 1.0f; } // t > 1 : frame tiếp theo vẫn chưa va chạm, t<0 là đang va chạm
};
class Collision
{
public:
	static LPCOLLISIONEVENT SweptAABB(LPGAMEOBJECT objSrc, DWORD dt, LPGAMEOBJECT objDest);
	static void Scan(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* objDests, vector<LPCOLLISIONEVENT>& coEvents);
	static void Process(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* coObjects);

};

