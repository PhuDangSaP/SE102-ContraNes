#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Bill.h"

extern CBill* bill;

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	/*switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	}*/
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	if (KeyCode == DIK_UP || KeyCode == DIK_DOWN)
	{
		bill->RequestState(BILL_STATE_IDLE);
	}
	/*switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}*/
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	CGame* game = CGame::GetInstance();
	bool isIdle = true;
	if (game->IsKeyDown(DIK_UP))
	{
		bill->RequestState(BILL_STATE_LOOKING_UP);
		isIdle = false;
	}
	if (game->IsKeyDown(DIK_DOWN))
	{
		bill->RequestState(BILL_STATE_LYING_DOWN);
		isIdle = false;
	}
	if (game->IsKeyDown(DIK_LEFT))
	{
		bill->RequestState(BILL_STATE_WALKING_LEFT);
		isIdle = false;
	}
	if (game->IsKeyDown(DIK_RIGHT))
	{
		bill->RequestState(BILL_STATE_WALKING_RIGHT);
		isIdle = false;
	}
	if (isIdle)
	{
		bill->RequestState(BILL_STATE_IDLE);
	}
}