#pragma once
class Camera
{
public:
	Camera() { x = 0; y = 0; }
	void Update();
	void GetCamPos(float& cx, float& cy) { cx = x; cy = y; };
private:
	float x;
	float y;
};