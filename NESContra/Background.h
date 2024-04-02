#pragma once
#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LEVEL_1_SECTION_1	101
#define ID_ANI_LEVEL_1_SECTION_2	102
#define ID_ANI_LEVEL_1_SECTION_3	103
#define ID_ANI_LEVEL_1_SECTION_4	104
#define ID_ANI_LEVEL_1_SECTION_5	105

class CBackground
{
public:
	CBackground();
	CBackground(float bgX, float bgY, int bgAniId);
	~CBackground();
	void Render();
private:
	float x;
	float y;
	int aniId;
};
typedef CBackground* LPBACKGROUND;
