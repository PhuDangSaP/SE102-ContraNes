#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "Bill.h"

//extern CMario* mario;
extern CBill* bill;

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_S:
		//mario->SetState(MARIO_STATE_JUMP);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_S:
		//mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		//mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	CGame* game = CGame::GetInstance();	
	D3DXVECTOR2 dir =  D3DXVECTOR2(0, 0);

	if (game->IsKeyDown(DIK_RIGHT))
	{
		/*if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);*/

			//bill->SetState(BILL_STATE_WALKING_RIGHT);
		dir.x = 1;
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		/*if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);*/

			//bill->SetState(BILL_STATE_WALKING_LEFT);
		dir.x = -1;
	}
	
	if (game->IsKeyDown(DIK_DOWN))
	{
		//bill->SetState(BILL_STATE_WALKING_DOWN);
		dir.y = -1;
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		//bill->SetState(BILL_STATE_WALKING_UP);
		dir.y = 1;
	}

	/*if (game->IsKeyDown(DIK_SPACE))
	{
		bill->Jump();
	}*/
	//else
		//mario->SetState(MARIO_STATE_IDLE);
		//bill->SetState(BILL_STATE_IDLE);

	// Sitting state has higher priority 
	/*if (game->IsKeyDown(DIK_DOWN))
	{
		mario->SetState(MARIO_STATE_SIT);
	}*/
		bill->UpdateState(dir);
}