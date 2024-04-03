#include "Camera.h"
#include "Bill.h"
extern CBill* bill;

void Camera::Update()
{
	bill->GetPosition(x, y);
	x -= SCREEN_WIDTH / 2;
	y = 0;
	if (x < 0) { x = 0; }
}
