#include "Platform.h"
#include "Sprites.h"

void Platform::Render()
{
	if (this->length <= 0) return;
	CSprites* sprites = CSprites::GetInstance();
	for (int i = 0; i < length; i++)
	{
		sprites->Get(this->spriteId)->Draw(x+i*cellWidth, y);		
	}	
}
