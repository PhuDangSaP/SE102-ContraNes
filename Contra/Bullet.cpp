#include "Bullet.h"
#include "Sprites.h"

Bullet::Bullet()
{
	isMove = false;
}

Bullet::~Bullet()
{
	
}

void Bullet::Update(DWORD dt)
{
	CGame* game = CGame::GetInstance();
	if (x -game->GetCam()->GetX()> 320 || x - game->GetCam()->GetX() <0)
	{
		isMove = false;
	}
	
}

void Bullet::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(77777)->Draw(x, y);
}

void Bullet::HandMove()
{
	switch (bulletDir)
	{
	case Right:
		x += BULLET_SPEED;
		break;
	case Left:
		x -= BULLET_SPEED;
		break;
	case Up:
		y -= BULLET_SPEED;
		break;
	case UpperRight:
		x += BULLET_SPEED+2;
		y -= BULLET_SPEED;
		break;
	case UpperLeft:
		x -= BULLET_SPEED + 2;
		y -= BULLET_SPEED;
		break;
	case LowerRight:
		x += BULLET_SPEED + 2;
		y += BULLET_SPEED;
		break;
	case LowerLeft:
		x -= BULLET_SPEED + 2;
		y += BULLET_SPEED;
		break;
	}
	
}
