#pragma once
#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define TURRET_STATE_IDLE		0
#define TURRET_STATE_OPENING	100
#define TURRET_STATE_ACTIVE		200


#pragma region ANIMATION_ID

#define ID_ANI_TURRET_IDLE				3100
#define ID_ANI_TURRET_ACTIVE_12_OCLOCK	3101
#define ID_ANI_TURRET_ACTIVE_1_OCLOCK	3102
#define ID_ANI_TURRET_ACTIVE_2_OCLOCK	3103
#define ID_ANI_TURRET_ACTIVE_3_OCLOCK	3104
#define ID_ANI_TURRET_ACTIVE_4_OCLOCK	3105
#define ID_ANI_TURRET_ACTIVE_5_OCLOCK	3106
#define ID_ANI_TURRET_ACTIVE_6_OCLOCK	3107
#define ID_ANI_TURRET_ACTIVE_7_OCLOCK	3108
#define ID_ANI_TURRET_ACTIVE_8_OCLOCK	3109
#define ID_ANI_TURRET_ACTIVE_9_OCLOCK	3110
#define ID_ANI_TURRET_ACTIVE_10_OCLOCK	3111
#define ID_ANI_TURRET_ACTIVE_11_OCLOCK	3112
#define ID_ANI_TURRET_OPENING			3113


class CWallTurret : public CGameObject
{
public:
	CWallTurret(float x, float y) : CGameObject(x, y)
	{
		this->state = TURRET_STATE_IDLE;
	}
	void RequestState(int state);
	void GetPos(float& x, float& y) { x = this->x; y = this->y; }
private:
	void Update(DWORD dt);
	void Render();
	long openTimer = 500;
	float angle;
};