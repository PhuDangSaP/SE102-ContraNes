#pragma once
#include "GameObject.h"

#define	BRIDGE_STATE_ACTIVE	0
#define	BRIDGE_STATE_SELF_DESTRUCT	1
#define	BRIDGE_STATE_DESTROYED	2

#define DESTROY_TIMER	600.0f
#define ID_SPRITE_BRIDGE_BEGIN	17004
#define ID_SPRITE_BRIDGE_MID	17005
#define ID_SPRITE_BRIDGE_END	17006
#define ID_SPRITE_BRIDGE_BEGIN_DESTROYED	17007
#define ID_SPRITE_BRIDGE_MID_DESTROYED	17008
#define ID_SPRITE_BRIDGE_END_DESTROYED	17009

#define ID_ANI_BRIDGE_EXPLOSION_LEFT	3200
#define ID_ANI_BRIDGE_EXPLOSION_TOP	3201
#define ID_ANI_BRIDGE_EXPLOSION_RIGHT	3203
#define ID_ANI_BRIDGE_EXPLOSION_CENTER	3204

class Bridge :public CGameObject
{
protected:
	int length;				// Unit: cell 
	int originalLength;
	int cellDestroyed;
	float destroyTimer;
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
public:
	Bridge(float x, float y,
		float cell_width, float cell_height, int length) :CGameObject(x, y)
	{
		this->length = length;
		this->originalLength = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = ID_SPRITE_BRIDGE_BEGIN;
		this->spriteIdMiddle = ID_SPRITE_BRIDGE_MID;
		this->spriteIdEnd = ID_SPRITE_BRIDGE_END;
		this->cellDestroyed = 0;
		this->destroyTimer = DESTROY_TIMER;
		this->state = BRIDGE_STATE_ACTIVE;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	RECT GetRect();
	RECT GetBoundingBox();
	void RenderBoundingBox();
	int IsBlocking() { return (state == BRIDGE_STATE_DESTROYED) ? 0 : 1; }
	int IsDirectionColliable(float nx, float ny);
};

