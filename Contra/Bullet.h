#pragma once
#include "GameObject.h"

#define BULLET_SPEED 6

enum BulletType
{
	Normal
};

enum BulletDir
{
	Right,
	Left,
	Up,
	UpperRight,
	UpperLeft,
	LowerRight,
	LowerLeft
};
class Bullet : public CGameObject
{
private:
	BulletDir bulletDir;
	BulletType bulletType;
	bool isMove;
public:
	Bullet();
	~Bullet();
	void SetIsMove(const bool& isMove) { this->isMove = isMove; }
	bool GetIsMove() const { return isMove; }
	void SetDir(BulletDir bulletDir) { this->bulletDir = bulletDir; }
	void Update(DWORD dt);
	void Render();
	void HandMove();
};

