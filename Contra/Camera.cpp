#include "Camera.h"

Camera::Camera(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Camera::GetX()
{
	return this->x;
}

float Camera::GetY()
{
	return this->y;
}

void Camera::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}
