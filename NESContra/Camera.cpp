#include "Camera.h"
#include "Bill.h"
extern CBill* bill;

void Camera::Update()
{
	/*float billX, billY;
	bill->GetPosition(billX, billY);
	if (billX > x + SCREEN_WIDTH / 2)
		x = billX - SCREEN_WIDTH / 2;;*/
	bill->GetPosition(x,y);
	x -= SCREEN_WIDTH / 2;
	y = 0;
	if (x < 0) { x = 0; }
}
