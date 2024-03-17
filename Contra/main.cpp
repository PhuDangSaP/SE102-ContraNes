/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 03 - KEYBOARD AND OBJECT STATE

	This sample illustrates how to:

		1/ Process keyboard input
		2/ Control object state with keyboard events
================================================================ */

#include <windows.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Animation.h"
#include "Animations.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Mario.h"
#include "Brick.h"
#include "Bill.h"
#include "Enemy.h"
#include "Platform.h"

#include "SampleKeyEventHandler.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Contra"
#define WINDOW_ICON_PATH L"mario.ico"


#define BACKGROUND_COLOR D3DXCOLOR (200.0f/255, 200.0f/255, 255.0f/255, 0.0f)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_BILL 30
#define ID_TEX_STAGE1 41

#define ID_TEX_BILL 555
#define ID_TEX_CONTRA_ENEMY 111

#define ID_SPRITE_BRICK 20001

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_MARIO TEXTURES_DIR "\\mario.png"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\misc.png"
#define TEXTURE_PATH_BILL TEXTURES_DIR "\\Players2.png"
#define TEXTURE_PATH_CONTRA_ENEMY TEXTURES_DIR "\\Enemies2.png"
#define TEXTURE_PATH_STAGE1 TEXTURES_DIR "\\Stage1.png"

#define MARIO_START_X 200.0f
#define MARIO_START_Y 100.0f

#define BRICK_X 0.0f
#define BRICK_Y GROUND_Y + 20.0f
#define NUM_BRICKS 50

CMario* mario = NULL;
CBill* bill = NULL;
CEnemy* enemy = NULL;
Platform* platform = NULL;

CSampleKeyHandler* keyHandler;

vector<LPGAMEOBJECT> objects;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();
	LPANIMATION ani;

	textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);
	textures->Add(ID_TEX_BILL, TEXTURE_PATH_BILL);
	textures->Add(ID_TEX_CONTRA_ENEMY, TEXTURE_PATH_CONTRA_ENEMY);
	textures->Add(ID_TEX_STAGE1, TEXTURE_PATH_STAGE1);

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPTEXTURE texBill = textures->Get(ID_TEX_BILL);
	//IDLE RIGHT AND LEFT
	sprites->Add(9001, 546, 24, 569, 59, texBill);
	sprites->Add(9002, 569, 24, 546, 59, texBill);

	//BILL WALKING RIGHT
	sprites->Add(9011, 25, 24, 43, 59, texBill);
	sprites->Add(9012, 90, 25, 109, 58, texBill);
	sprites->Add(9013, 157, 24, 172, 59, texBill);
	sprites->Add(9014, 220, 24, 237, 59, texBill);
	sprites->Add(9015, 285, 25, 304, 58, texBill);
	sprites->Add(9016, 353, 24, 368, 59, texBill);

	//BILL WALKING LEFT
	sprites->Add(9021, 43, 24, 25, 59, texBill);
	sprites->Add(9022, 109, 25, 90, 58, texBill);
	sprites->Add(9023, 172, 24, 157, 59, texBill);
	sprites->Add(9024, 237, 24, 220, 59, texBill);
	sprites->Add(9025, 304, 25, 285, 58, texBill);
	sprites->Add(9026, 368, 24, 353, 59, texBill);

	//BILL WALKING UP
	sprites->Add(9031, 673, 221, 693, 261, texBill);
	sprites->Add(9032, 739, 223, 759, 263, texBill);

	//BILL WALKING DOWN
	sprites->Add(9041, 693, 261, 673, 221, texBill);
	sprites->Add(9042, 759, 263, 739, 223, texBill);


	//walking right look up 
	sprites->Add(9101, 25, 89, 43, 123, texBill);
	sprites->Add(9102, 90, 89, 109, 123, texBill);
	sprites->Add(9103, 157, 89, 172, 123, texBill);
	sprites->Add(9104, 220, 89, 237, 123, texBill);
	sprites->Add(9105, 285, 89, 304, 123, texBill);
	sprites->Add(9106, 353, 89, 368, 123, texBill);
	
	ani = new CAnimation(150);
	ani->Add(9101);
	ani->Add(9102);
	ani->Add(9103);
	ani->Add(9104);
	ani->Add(9105);
	ani->Add(9106);
	animations->Add(ID_ANI_BILL_WALKING_RIGHT_LOOKUP, ani);
	//walking right look down
	sprites->Add(9111, 415, 89, 435, 123, texBill);
	sprites->Add(9112, 480, 89, 500, 123, texBill);
	sprites->Add(9113, 545, 89, 565, 123, texBill);
	sprites->Add(9114, 610, 89, 630, 123, texBill);
	sprites->Add(9115, 675, 89, 695, 123, texBill);
	sprites->Add(9116, 740, 89, 760, 123, texBill);

	ani = new CAnimation(150);
	ani->Add(9111);
	ani->Add(9112);
	ani->Add(9113);
	ani->Add(9114);
	ani->Add(9115);
	ani->Add(9116);
	animations->Add(ID_ANI_BILL_WALKING_RIGHT_LOOKDOWN, ani);

	//walking left look up 
	sprites->Add(9201, 43, 89, 25, 123, texBill);
	sprites->Add(9202, 109, 89, 90, 123, texBill);
	sprites->Add(9203, 175, 89, 157, 123, texBill);
	sprites->Add(9204, 237, 89, 220, 123, texBill);
	sprites->Add(9205, 304, 89, 285, 123, texBill);
	sprites->Add(9206, 368, 89, 353, 123, texBill);

	ani = new CAnimation(150);
	ani->Add(9201);
	ani->Add(9202);
	ani->Add(9203);
	ani->Add(9204);
	ani->Add(9205);
	ani->Add(9206);
	animations->Add(ID_ANI_BILL_WALKING_LEFT_LOOKUP, ani);
	//walking left look down
	sprites->Add(9211, 435, 89, 415, 123, texBill);
	sprites->Add(9212, 500, 89, 480, 123, texBill);
	sprites->Add(9213, 565, 89, 545, 123, texBill);
	sprites->Add(9214, 630, 89, 610, 123, texBill);
	sprites->Add(9215, 695, 89, 675, 123, texBill);
	sprites->Add(9216, 760, 89, 740, 123, texBill);

	ani = new CAnimation(150);
	ani->Add(9211);
	ani->Add(9212);
	ani->Add(9213);
	ani->Add(9214);
	ani->Add(9215);
	ani->Add(9216);
	animations->Add(ID_ANI_BILL_WALKING_LEFT_LOOKDOWN, ani);

	// lieing right
	sprites->Add(9300, 919, 43, 958, 58, texBill);
	ani = new CAnimation(150);
	ani->Add(9300);
	//ani->Add(9301);
	animations->Add(ID_ANI_BILL_LIEING_RIGHT, ani);

	// lieing left
	sprites->Add(9302, 958, 42, 919, 57, texBill);
	ani = new CAnimation(150);
	ani->Add(9302);
	animations->Add(ID_ANI_BILL_LIEING_LEFT, ani);

	// look up
	sprites->Add(9400, 806, 13, 821, 58, texBill);
	ani = new CAnimation(150);
	ani->Add(9400);
	animations->Add(ID_ANI_BILL_LOOKUP, ani);

	// jump
	sprites->Add(9500, 805, 98, 820, 117, texBill);
	sprites->Add(9501, 868, 99, 886, 114, texBill);
	sprites->Add(9502, 935, 96, 950, 115, texBill);
	sprites->Add(9503, 9999, 99, 1017, 114, texBill);
	ani = new CAnimation(100);
	ani->Add(9500);
	ani->Add(9501);
	ani->Add(9502);
	ani->Add(9503);
	animations->Add(ID_ANI_BILL_JUMP, ani);


	// enemy
	ani = new CAnimation(100);
	ani->Add(9001);
	animations->Add(ID_ANI_BILL_IDLE_RIGHT, ani);
	//animations->Add(ID_ANI_ENEMY_IDLE_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(9002);
	animations->Add(ID_ANI_BILL_IDLE_LEFT, ani);
	//animations->Add(ID_ANI_ENEMY_IDLE_LEFT, ani);

	ani = new CAnimation(150);
	ani->Add(9011);
	ani->Add(9012);
	ani->Add(9013);
	ani->Add(9014);
	ani->Add(9015);
	ani->Add(9016);
	animations->Add(ID_ANI_BILL_WALKING_RIGHT, ani);
	//animations->Add(ID_ANI_ENEMY_WALKING_RIGHT, ani);

	ani = new CAnimation(150);
	ani->Add(9021);
	ani->Add(9022);
	ani->Add(9023);
	ani->Add(9024);
	ani->Add(9025);
	ani->Add(9026);
	animations->Add(ID_ANI_BILL_WALKING_LEFT, ani);
	//animations->Add(ID_ANI_ENEMY_WALKING_LEFT, ani);

	ani = new CAnimation(450);
	ani->Add(9031);
	ani->Add(9032);
	animations->Add(ID_ANI_BILL_WALKING_UP, ani);
	//animations->Add(ID_ANI_ENEMY_WALKING_UP, ani);

	ani = new CAnimation(450);
	ani->Add(9041);
	ani->Add(9042);
	animations->Add(ID_ANI_BILL_WALKING_DOWN, ani);
	//animations->Add(ID_ANI_ENEMY_WALKING_DOWN, ani);

	LPTEXTURE texEnemy = textures->Get(ID_TEX_CONTRA_ENEMY);

	// enemy run right
	sprites->Add(11111, 157, 17, 173, 48, texEnemy);
	sprites->Add(11112, 175, 17, 190, 48, texEnemy);
	sprites->Add(11113, 192, 17, 207, 48, texEnemy);
	sprites->Add(11114, 209, 17, 224, 48, texEnemy);
	sprites->Add(11115, 226, 17, 241, 48, texEnemy);
	sprites->Add(11116, 243, 17, 258, 48, texEnemy);

	// enemy run left
	sprites->Add(11121, 173, 17, 157, 48, texEnemy);
	sprites->Add(11122, 190, 17, 175, 48, texEnemy);
	sprites->Add(11123, 207, 17, 192, 48, texEnemy);
	sprites->Add(11124, 224, 17, 209, 48, texEnemy);
	sprites->Add(11125, 241, 17, 226, 48, texEnemy);
	sprites->Add(11126, 258, 17, 243, 48, texEnemy);

	ani = new CAnimation(150);
	ani->Add(11111);
	ani->Add(11112);
	ani->Add(11113);
	ani->Add(11114);
	ani->Add(11115);
	ani->Add(11116);
	animations->Add(ID_ANI_ENEMY_WALKING_RIGHT, ani);
	ani = new CAnimation(150);
	ani->Add(11121);
	ani->Add(11122);
	ani->Add(11123);
	ani->Add(11124);
	ani->Add(11125);
	ani->Add(11126);
	animations->Add(ID_ANI_ENEMY_WALKING_LEFT, ani);

	// stage1
	LPTEXTURE texStage1 = textures->Get(ID_TEX_STAGE1);
	sprites->Add(20001, 31, 105, 63, 135, texStage1);// ground
	
	sprites->Add(20003, 31, 72, 63, 104, texStage1);// tree
	

	platform = new Platform(50, 105, 32, 23, 20001);
	objects.push_back(platform);
	
	/*platform = new Platform(50, 72, 32, 23, 20003);
	objects.push_back(platform);*/


	bill = new CBill(10, 70);
	objects.push_back(bill);
	enemy = new CEnemy(100.0f, 150.0f);
	objects.push_back(enemy);


	
	mario = new CMario(MARIO_START_X, MARIO_START_Y);
	//objects.push_back(mario)
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Update(dt);
	}

	CGame* g = CGame::GetInstance();
	if (bill->GetX() > g->GetBackBufferWidth()/2 + g->GetCam()->GetX())
	{
		float newCamX = bill->GetX() - g->GetBackBufferWidth()/2;
		g->GetCam()->SetPosition(newCamX, bill->GetY());
	}
}

void Render()
{
	CTextures* textures = CTextures::GetInstance();
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

	spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), BACKGROUND_COLOR, 0xffffffff);

	g->Draw(2455/2, 244/2, textures->Get(ID_TEX_STAGE1), NULL);
	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Render();
	}

	spriteHandler->End();
	pSwapChain->Present(0, 0);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			CGame::GetInstance()->ProcessKeyboard();
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDebugWindow(hWnd);

	CGame* game = CGame::GetInstance();
	game->Init(hWnd, hInstance);

	keyHandler = new CSampleKeyHandler();
	game->InitKeyboard(keyHandler);

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	LoadResources();

	Run();

	return 0;
}