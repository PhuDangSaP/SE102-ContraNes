#pragma once
class Camera
{
private:
	float x;
	float y;
public:
	Camera(float x,float y);
	float GetX();	
	float GetY();
	void SetPosition(float x,float y);
};

