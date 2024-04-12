﻿#include "Collision.h"
#include "GameObject.h"

#define BLOCK_PUSH_FACTOR 0.4f

LPCOLLISIONEVENT Collision::SweptAABB(LPGAMEOBJECT objSrc, DWORD dt, LPGAMEOBJECT objDest)
{
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	float t;
	CollisionDir dir;

	float Svx, Svy;
	objSrc->GetSpeed(Svx, Svy);
	float Sdx = Svx * dt;
	float Sdy = Svy * dt;


	float Dvx, Dvy;
	objDest->GetSpeed(Dvx, Dvy);
	float Ddx = Dvx * dt;
	float Ddy = Dvy * dt;

	float dx = Sdx - Ddx;
	float dy = Sdy - Ddy;


	RECT srcRect = objSrc->GetBoundingBox();
	RECT destRect = objDest->GetBoundingBox();


	// AABB
	float srcX, srcY;
	float destX, destY;

	objSrc->GetPosition(srcX, srcY);
	objDest->GetPosition(destX, destY);

	RECT rect; // cộng thêm 1 khoảng sau khi di chuyển
	rect.left = dx > 0 ? srcRect.left : srcRect.left + dx;
	rect.right = dx > 0 ? srcRect.right + dx : srcRect.right;
	rect.top = dy > 0 ? srcRect.top + dy : srcRect.top;
	rect.bottom = dy > 0 ? srcRect.bottom : srcRect.bottom + dy;

	if (srcX > 180)
	{
		RECT dsadsa = srcRect;
		RECT ddsada = destRect;
	}

	if (!IsColliding(rect, destRect))
		return NULL;

	if (dx == 0 && dy == 0)
		return NULL;



	if (dx > 0)
	{
		dx_entry = destRect.left - srcRect.right;
		dx_exit = destRect.right - srcRect.left;
	}
	else if (dx < 0)
	{
		dx_entry = destRect.right - srcRect.left;
		dx_exit = destRect.left - srcRect.right;
	}


	if (dy > 0)
	{
		dy_entry = destRect.bottom - srcRect.top;
		dy_exit = destRect.top - srcRect.bottom;

	}
	else if (dy < 0)
	{
		dy_entry = destRect.top - srcRect.bottom;
		dy_exit = destRect.bottom - srcRect.top;

	}

	if (dx == 0)
	{
		tx_entry = -numeric_limits<float>::infinity();
		tx_exit = numeric_limits<float>::infinity();
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -numeric_limits<float>::infinity();
		ty_exit = numeric_limits<float>::infinity();
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	// thời gian va chạm là thời gian lớn nhất của 2 trục (2 trục phải cùng tiếp xúc thì mới va chạm)
	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);


	if (t_entry > t_exit || t_entry > 1.0f || t_entry < 0.0f)
	{
		return nullptr;
	}
	t = t_entry;

	// lấy hướng va chạm
	if (tx_entry > ty_entry)
	{
		if (dx_entry > 0.0f)
		{
			dir = CollisionDir::RIGHT;
		}
		else
		{
			dir = CollisionDir::LEFT;
		}
	}
	else
	{
		if (dy_entry > 0.0f)
		{
			dir = CollisionDir::UP;
		}
		else
		{
			dir = CollisionDir::DOWN;
		}
	}
	if (t >= 0.0f && t <= 1.0f)
	{
		int ddasd = 123;
	}
	CollisionEvent* e = new CollisionEvent(objDest, t, dir);
	return e;
}

void Collision::Scan(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* objDests, vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < objDests->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABB(objSrc, dt, objDests->at(i));
		if (e == nullptr) continue;
		if (e->WasCollided() == 1)
			coEvents.push_back(e);
		else
			delete e;
	}
}

bool Collision::IsColliding(RECT objSrc, RECT objDest)
{
	return !(objDest.left > objSrc.right || objDest.right < objSrc.left || objDest.top < objSrc.bottom || objDest.bottom > objSrc.top);
}

void Collision::Process(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;

	coEvents.clear();

	if (objSrc->IsCollidable())
	{
		Scan(objSrc, dt, coObjects, coEvents);
	}
	// No collision detected
	if (coEvents.size() == 0)
	{
		objSrc->OnNoCollision(dt);
	}
	else
	{
		float x, y, vx, vy, dx, dy;
		objSrc->GetPosition(x, y);
		objSrc->GetSpeed(vx, vy);
		dx = vx * dt;
		dy = vy * dt;

		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (e->isDeleted) continue;
			if (!e->obj->IsBlocking()) continue;  // Skip non-blocking collisions

			// Resolve collision along X-axis
			if (e->dir == CollisionDir::RIGHT)
			{
				x += e->t * dx + BLOCK_PUSH_FACTOR;
			}
			else if (e->dir == CollisionDir::LEFT)
			{
				x += e->t * dx - BLOCK_PUSH_FACTOR;
			}

			// Resolve collision along Y-axis
			if (e->dir == CollisionDir::UP)
			{
				y += e->t * dy + BLOCK_PUSH_FACTOR;
			}
			else if (e->dir == CollisionDir::DOWN)
			{
				y += e->t * dy - BLOCK_PUSH_FACTOR;
			}
			objSrc->SetPosition(x, y);
			objSrc->OnCollisionWith(e);

			// Adjust position for further collision detection
			objSrc->GetPosition(x, y);
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}
