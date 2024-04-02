#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define SNIPER_STATE_IDLE	0
#define SNIPER_STATE_SHOOT	100


#pragma region ANIMATION_ID

#define ID_ANI_SNIPER_IDLE_LEFT				3000
#define ID_ANI_SNIPER_IDLE_RIGHT			3001
#define	ID_ANI_SNIPER_IDLE_TOP_LEFT			3002
#define	ID_ANI_SNIPER_IDLE_TOP_RIGHT		3003
#define	ID_ANI_SNIPER_IDLE_BOTTOM_LEFT		3004
#define	ID_ANI_SNIPER_IDLE_BOTTOM_RIGHT		3005

#define ID_ANI_SNIPER_SHOOT_LEFT			3006
#define ID_ANI_SNIPER_SHOOT_RIGHT			3007
#define	ID_ANI_SNIPER_SHOOT_TOP_LEFT		3008
#define	ID_ANI_SNIPER_SHOOT_TOP_RIGHT		3009
#define	ID_ANI_SNIPER_SHOOT_BOTTOM_LEFT		3010
#define	ID_ANI_SNIPER_SHOOT_BOTTOM_RIGHT	3011

class CSniper : public CGameObject
{
public:
	CSniper(float x, float y) : CGameObject(x, y)
	{
		state = SNIPER_STATE_SHOOT;
		nx = -1;
		ny = 0;
	}
	void RequestState(int state);
	void GetPos(float& x, float& y) { x = this->x; y = this->y; }
private:
	void Update(DWORD dt);
	void Render();
};