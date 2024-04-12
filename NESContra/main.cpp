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

#include "Bill.h"
#include "Soldier.h"
#include "Sniper.h"
#include "WallTurret.h"
#include "Platform.h"
#include "Background.h"

#include "World.h"
#include "SampleKeyEventHandler.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"NES - Contra"
#define WINDOW_ICON_PATH L"mario.ico"


#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255, 0.0f)



#define ID_TEX_PLAYER	0
#define ID_TEX_ENEMY	10
#define ID_TEX_TURRET	20
#define ID_TEX_LEVEL_1 -10


#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_PLAYER TEXTURES_DIR "\\player.png"
#define TEXTURE_PATH_ENEMY TEXTURES_DIR "\\enemy.png"
#define TEXTURE_PATH_TURRET TEXTURES_DIR "\\turrets.gif"
#define TEXTURE_PATH_LEVEL_1 TEXTURES_DIR "\\level1.png"

#define BILL_START_X 100.0f
#define BILL_START_Y 130.0f


CBill* bill = NULL;
CSoldier* soldier = NULL;
CSniper* sniper = NULL;
CWallTurret* wT = NULL;
World* root = NULL;
Platform* grass = NULL;

CSampleKeyHandler* keyHandler;

vector<LPGAMEOBJECT> objects;
vector<LPBACKGROUND> sections;

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
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	textures->Add(ID_TEX_PLAYER, TEXTURE_PATH_PLAYER);
	textures->Add(ID_TEX_ENEMY, TEXTURE_PATH_ENEMY);
	textures->Add(ID_TEX_TURRET, TEXTURE_PATH_TURRET);
	textures->Add(ID_TEX_LEVEL_1, TEXTURE_PATH_LEVEL_1);
	LPTEXTURE texBill = textures->Get(ID_TEX_PLAYER);
	LPTEXTURE texEnemies = textures->Get(ID_TEX_ENEMY);
	LPTEXTURE texTurret = textures->Get(ID_TEX_TURRET);
	LPTEXTURE texLevel1 = textures->Get(ID_TEX_LEVEL_1);
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

	//BILL LOOKING UP
	sprites->Add(9031, 806, 13, 821, 59, texBill);
	sprites->Add(9032, 821, 13, 806, 59, texBill);

	//BILL LYING DOWN
	sprites->Add(9041, 926, 42, 958, 57, texBill);
	sprites->Add(9042, 958, 42, 926, 57, texBill);

	//BILL WALKING LOOKING UP
	//RIGHT
	sprites->Add(9051, 25, 89, 43, 124, texBill);
	sprites->Add(9052, 90, 90, 109, 123, texBill);
	sprites->Add(9053, 157, 89, 173, 124, texBill);
	sprites->Add(9054, 220, 90, 238, 124, texBill);
	sprites->Add(9055, 285, 91, 304, 123, texBill);
	sprites->Add(9056, 352, 90, 368, 124, texBill);
	//LEFT
	sprites->Add(9061, 43, 89, 25, 124, texBill);
	sprites->Add(9062, 109, 90, 90, 123, texBill);
	sprites->Add(9063, 173, 89, 157, 124, texBill);
	sprites->Add(9064, 238, 90, 220, 124, texBill);
	sprites->Add(9065, 304, 91, 285, 123, texBill);
	sprites->Add(9066, 368, 90, 352, 124, texBill);

	//BILL WALKING LOOKING DOWN
	//RIGHT
	sprites->Add(9071, 415, 89, 435, 124, texBill);
	sprites->Add(9072, 480, 90, 500, 123, texBill);
	sprites->Add(9073, 545, 89, 565, 124, texBill);
	sprites->Add(9074, 610, 90, 630, 124, texBill);
	sprites->Add(9075, 675, 91, 695, 123, texBill);
	sprites->Add(9076, 740, 90, 760, 124, texBill);
	//LEFT
	sprites->Add(9081, 435, 89, 415, 124, texBill);
	sprites->Add(9082, 500, 90, 480, 123, texBill);
	sprites->Add(9083, 565, 89, 545, 124, texBill);
	sprites->Add(9084, 630, 90, 610, 124, texBill);
	sprites->Add(9085, 695, 91, 675, 123, texBill);
	sprites->Add(9086, 760, 90, 740, 124, texBill);

	//BILL JUMPING
	//RIGHT
	sprites->Add(9091, 805, 98, 820, 117, texBill);
	sprites->Add(9092, 868, 99, 886, 114, texBill);
	sprites->Add(9093, 935, 96, 950, 115, texBill);
	sprites->Add(9094, 999, 99, 1017, 114, texBill);

	//LEFT
	sprites->Add(9095, 820, 98, 805, 117, texBill);
	sprites->Add(9096, 886, 99, 868, 114, texBill);
	sprites->Add(9097, 950, 96, 935, 115, texBill);
	sprites->Add(9098, 1017, 99, 999, 114, texBill);

	ani = new CAnimation(100);
	ani->Add(9001);
	animations->Add(ID_ANI_BILL_IDLE_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(9002);
	animations->Add(ID_ANI_BILL_IDLE_LEFT, ani);

	ani = new CAnimation(150);
	ani->Add(9011);
	ani->Add(9012);
	ani->Add(9013);
	ani->Add(9014);
	ani->Add(9015);
	ani->Add(9016);
	animations->Add(ID_ANI_BILL_WALKING_RIGHT, ani);

	ani = new CAnimation(150);
	ani->Add(9021);
	ani->Add(9022);
	ani->Add(9023);
	ani->Add(9024);
	ani->Add(9025);
	ani->Add(9026);
	animations->Add(ID_ANI_BILL_WALKING_LEFT, ani);

	ani = new CAnimation(450);
	ani->Add(9031);
	animations->Add(ID_ANI_BILL_LOOKING_UP_RIGHT, ani);

	ani = new CAnimation(450);
	ani->Add(9032);
	animations->Add(ID_ANI_BILL_LOOKING_UP_LEFT, ani);

	ani = new CAnimation(450);
	ani->Add(9041);
	animations->Add(ID_ANI_BILL_LYING_DOWN_RIGHT, ani);

	ani = new CAnimation(450);
	ani->Add(9042);
	animations->Add(ID_ANI_BILL_LYING_DOWN_LEFT, ani);

	ani = new CAnimation(150);
	ani->Add(9051);
	ani->Add(9052);
	ani->Add(9053);
	ani->Add(9054);
	ani->Add(9055);
	ani->Add(9056);
	animations->Add(ID_ANI_BILL_WALKING_LOOKING_UP_RIGHT, ani);

	ani = new CAnimation(150);
	ani->Add(9061);
	ani->Add(9062);
	ani->Add(9063);
	ani->Add(9064);
	ani->Add(9065);
	ani->Add(9066);
	animations->Add(ID_ANI_BILL_WALKING_LOOKING_UP_LEFT, ani);

	ani = new CAnimation(150);
	ani->Add(9071);
	ani->Add(9072);
	ani->Add(9073);
	ani->Add(9074);
	ani->Add(9075);
	ani->Add(9076);
	animations->Add(ID_ANI_BILL_WALKING_LOOKING_DOWN_RIGHT, ani);

	ani = new CAnimation(150);
	ani->Add(9081);
	ani->Add(9082);
	ani->Add(9083);
	ani->Add(9084);
	ani->Add(9085);
	ani->Add(9086);
	animations->Add(ID_ANI_BILL_WALKING_LOOKING_DOWN_LEFT, ani);

	ani = new CAnimation(75);
	ani->Add(9091);
	ani->Add(9092);
	ani->Add(9093);
	ani->Add(9094);
	animations->Add(ID_ANI_BILL_JUMP_RIGHT, ani);

	ani = new CAnimation(75);
	ani->Add(9095);
	ani->Add(9096);
	ani->Add(9097);
	ani->Add(9098);
	animations->Add(ID_ANI_BILL_JUMP_LEFT, ani);

	bill = new CBill(BILL_START_X - 50, BILL_START_Y + 50);
	
	//objects.push_back(bill);

	//SOLDIER IDLE RIGHT AND LEFT
	sprites->Add(8001, 192, 17, 207, 48, texEnemies);
	sprites->Add(8002, 207, 17, 192, 48, texEnemies);

	//SOLDIER WALKING RIGHT
	sprites->Add(8011, 158, 17, 173, 48, texEnemies);
	sprites->Add(8012, 175, 17, 190, 48, texEnemies);
	sprites->Add(8013, 192, 17, 207, 48, texEnemies);
	sprites->Add(8014, 209, 17, 224, 48, texEnemies);
	sprites->Add(8015, 226, 17, 241, 48, texEnemies);
	sprites->Add(8016, 243, 17, 258, 48, texEnemies);

	//SOLDIER WALKING LEFT
	sprites->Add(8021, 173, 17, 158, 48, texEnemies);
	sprites->Add(8022, 190, 17, 175, 48, texEnemies);
	sprites->Add(8023, 207, 17, 192, 48, texEnemies);
	sprites->Add(8024, 224, 17, 209, 48, texEnemies);
	sprites->Add(8025, 241, 17, 226, 48, texEnemies);
	sprites->Add(8026, 258, 17, 243, 48, texEnemies);

	ani = new CAnimation(100);
	ani->Add(8001);
	animations->Add(ID_ANI_SOLDIER_IDLE_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(8002);
	animations->Add(ID_ANI_SOLDIER_IDLE_LEFT, ani);

	ani = new CAnimation(150);
	ani->Add(8011);
	ani->Add(8012);
	ani->Add(8013);
	ani->Add(8014);
	ani->Add(8015);
	ani->Add(8016);
	animations->Add(ID_ANI_SOLDIER_WALKING_RIGHT, ani);

	ani = new CAnimation(150);
	ani->Add(8021);
	ani->Add(8022);
	ani->Add(8023);
	ani->Add(8024);
	ani->Add(8025);
	ani->Add(8026);
	animations->Add(ID_ANI_SOLDIER_WALKING_LEFT, ani);

	soldier = new CSoldier(BILL_START_X+100, BILL_START_Y );
	objects.push_back(soldier);

	//LEVEL1
	//SECTION1
	sprites->Add(101, 0, 0, 690, 223, texLevel1);
	//SECTION2
	sprites->Add(102, 691, 0, 1381, 223, texLevel1);
	//SECTION3
	sprites->Add(103, 1382, 0, 2072, 223, texLevel1);
	//SECTION4
	sprites->Add(104, 2073, 0, 2763, 223, texLevel1);
	//SECTION5
	sprites->Add(105, 2763, 0, 3455, 223, texLevel1);

	ani = new CAnimation(100);
	ani->Add(101);
	animations->Add(ID_ANI_LEVEL_1_SECTION_1, ani);

	ani = new CAnimation(100);
	ani->Add(102);
	animations->Add(ID_ANI_LEVEL_1_SECTION_2, ani);

	ani = new CAnimation(100);
	ani->Add(103);
	animations->Add(ID_ANI_LEVEL_1_SECTION_3, ani);

	ani = new CAnimation(100);
	ani->Add(104);
	animations->Add(ID_ANI_LEVEL_1_SECTION_4, ani);

	ani = new CAnimation(100);
	ani->Add(105);
	animations->Add(ID_ANI_LEVEL_1_SECTION_5, ani);

	CBackground* l1s1 = new CBackground(690 / 2, 223 / 2, ID_ANI_LEVEL_1_SECTION_1);
	CBackground* l1s2 = new CBackground(690 / 2 + 691, 223 / 2, ID_ANI_LEVEL_1_SECTION_2);
	CBackground* l1s3 = new CBackground(690 / 2 + 1382, 223 / 2, ID_ANI_LEVEL_1_SECTION_3);
	CBackground* l1s4 = new CBackground(690 / 2 + 2073, 223 / 2, ID_ANI_LEVEL_1_SECTION_4);
	CBackground* l1s5 = new CBackground(691 / 2 + 2763, 223 / 2, ID_ANI_LEVEL_1_SECTION_5);
	sections.push_back(l1s1);
	sections.push_back(l1s2);
	sections.push_back(l1s3);
	sections.push_back(l1s4);
	sections.push_back(l1s5);

	//SNIPER IDLE AND SHOOT RIGHT
	sprites->Add(7001, 91, 17, 114, 48, texEnemies);
	sprites->Add(7002, 116, 18, 139, 48, texEnemies);

	//SNIPER IDLE AND SHOOT LEFT
	sprites->Add(7003, 114, 17, 91, 48, texEnemies);
	sprites->Add(7004, 139, 18, 116, 48, texEnemies);

	//SNIPER IDLE AND SHOOT TOP RIGHT
	sprites->Add(7005, 51, 9, 69, 48, texEnemies);
	sprites->Add(7006, 71, 10, 89, 48, texEnemies);

	//SNIPER IDLE AND SHOOT TOP LEFT
	sprites->Add(7007, 69, 9, 51, 48, texEnemies);
	sprites->Add(7008, 89, 10, 71, 48, texEnemies);

	//SNIPER IDLE AND SHOOT BOTTOM RIGHT
	sprites->Add(7009, 1, 17, 24, 48, texEnemies);
	sprites->Add(7010, 26, 18, 49, 48, texEnemies);

	//SNIPER IDLE AND SHOOT BOTTOM LEFT
	sprites->Add(7011, 24, 17, 1, 48, texEnemies);
	sprites->Add(7012, 49, 18, 26, 48, texEnemies);

	ani = new CAnimation(500);
	ani->Add(7001);
	animations->Add(ID_ANI_SNIPER_IDLE_RIGHT, ani);

	ani = new CAnimation(500);
	ani->Add(7001);
	ani->Add(7002);
	animations->Add(ID_ANI_SNIPER_SHOOT_RIGHT, ani);

	ani = new CAnimation(500);
	ani->Add(7003);
	animations->Add(ID_ANI_SNIPER_IDLE_LEFT, ani);

	ani = new CAnimation(500);
	ani->Add(7003);
	ani->Add(7004);
	animations->Add(ID_ANI_SNIPER_SHOOT_LEFT, ani);

	ani = new CAnimation(500);
	ani->Add(7005);
	animations->Add(ID_ANI_SNIPER_IDLE_TOP_RIGHT, ani);

	ani = new CAnimation(500);
	ani->Add(7005);
	ani->Add(7006);
	animations->Add(ID_ANI_SNIPER_SHOOT_TOP_RIGHT, ani);

	ani = new CAnimation(500);
	ani->Add(7007);
	animations->Add(ID_ANI_SNIPER_IDLE_TOP_LEFT, ani);

	ani = new CAnimation(500);
	ani->Add(7007);
	ani->Add(7008);
	animations->Add(ID_ANI_SNIPER_SHOOT_TOP_LEFT, ani);

	ani = new CAnimation(500);
	ani->Add(7009);
	animations->Add(ID_ANI_SNIPER_IDLE_BOTTOM_RIGHT, ani);

	ani = new CAnimation(500);
	ani->Add(7009);
	ani->Add(7010);
	animations->Add(ID_ANI_SNIPER_SHOOT_BOTTOM_RIGHT, ani);

	ani = new CAnimation(500);
	ani->Add(7011);
	animations->Add(ID_ANI_SNIPER_IDLE_BOTTOM_LEFT, ani);

	ani = new CAnimation(500);
	ani->Add(7011);
	ani->Add(7012);
	animations->Add(ID_ANI_SNIPER_SHOOT_BOTTOM_LEFT, ani);

	/*sniper = new CSniper(250, 50);
	objects.push_back(sniper);
	sniper = new CSniper(320, 36);
	objects.push_back(sniper);
	sniper = new CSniper(640, 36);
	objects.push_back(sniper);
	sniper = new CSniper(1278, 130);
	objects.push_back(sniper);
	sniper = new CSniper(2486, 103);
	objects.push_back(sniper);*/

	//WALLTURRET IDLE
	sprites->Add(6001, 39, 106, 70, 137, texTurret);
	sprites->Add(6002, 141, 106, 172, 137, texTurret);
	sprites->Add(6003, 243, 106, 274, 137, texTurret);

	//WALLTURRET OPENING
	sprites->Add(6004, 39, 72, 70, 103, texTurret);
	sprites->Add(6005, 141, 72, 172, 103, texTurret);
	sprites->Add(6006, 243, 72, 274, 103, texTurret);

	//WALLTURRET ACTIVE
	//12 O'CLOCK
	sprites->Add(6007, 39, 38, 70, 69, texTurret);
	sprites->Add(6008, 141, 38, 172, 69, texTurret);
	sprites->Add(6009, 243, 38, 274, 69, texTurret);

	//1 O'CLOCK
	sprites->Add(6010, 73, 38, 104, 69, texTurret);
	sprites->Add(6011, 175, 38, 206, 69, texTurret);
	sprites->Add(6012, 277, 38, 308, 69, texTurret);

	//2 O'CLOCK
	sprites->Add(6013, 73, 72, 104, 103, texTurret);
	sprites->Add(6014, 175, 72, 206, 103, texTurret);
	sprites->Add(6015, 277, 72, 308, 103, texTurret);

	//3 O'CLOCK
	sprites->Add(6016, 73, 106, 104, 137, texTurret);
	sprites->Add(6017, 175, 106, 206, 137, texTurret);
	sprites->Add(6018, 277, 106, 308, 137, texTurret);

	//4 O'CLOCK
	sprites->Add(6019, 73, 140, 104, 171, texTurret);
	sprites->Add(6020, 175, 140, 206, 171, texTurret);
	sprites->Add(6021, 277, 140, 308, 171, texTurret);

	//5 O'CLOCK
	sprites->Add(6022, 73, 174, 104, 205, texTurret);
	sprites->Add(6023, 175, 174, 206, 205, texTurret);
	sprites->Add(6024, 277, 174, 308, 205, texTurret);

	//6 O'CLOCK
	sprites->Add(6025, 39, 174, 70, 205, texTurret);
	sprites->Add(6026, 141, 174, 172, 205, texTurret);
	sprites->Add(6027, 243, 174, 274, 205, texTurret);

	//7 O'CLOCK
	sprites->Add(6028, 5, 174, 36, 205, texTurret);
	sprites->Add(6029, 107, 174, 138, 205, texTurret);
	sprites->Add(6030, 209, 174, 240, 205, texTurret);

	//8 O'CLOCK
	sprites->Add(6031, 5, 140, 36, 171, texTurret);
	sprites->Add(6032, 107, 140, 138, 171, texTurret);
	sprites->Add(6033, 209, 140, 240, 171, texTurret);

	//9 O'CLOCK
	sprites->Add(6034, 5, 106, 36, 137, texTurret);
	sprites->Add(6035, 107, 106, 138, 137, texTurret);
	sprites->Add(6036, 209, 106, 240, 137, texTurret);

	//10 O'CLOCK
	sprites->Add(6037, 5, 72, 36, 103, texTurret);
	sprites->Add(6038, 107, 72, 138, 103, texTurret);
	sprites->Add(6039, 209, 72, 240, 103, texTurret);

	//11 O'CLOCK
	sprites->Add(6040, 5, 38, 36, 69, texTurret);
	sprites->Add(6041, 107, 38, 138, 69, texTurret);
	sprites->Add(6042, 209, 38, 240, 69, texTurret);

	ani = new CAnimation(200);
	ani->Add(6001);
	ani->Add(6002);
	ani->Add(6003);
	animations->Add(ID_ANI_TURRET_IDLE, ani);

	ani = new CAnimation(100);
	ani->Add(6004);
	ani->Add(6005);
	ani->Add(6006);
	animations->Add(ID_ANI_TURRET_OPENING, ani);

	ani = new CAnimation(200);
	ani->Add(6007);
	ani->Add(6008);
	ani->Add(6009);
	animations->Add(ID_ANI_TURRET_ACTIVE_12_OCLOCK, ani);

	ani = new CAnimation(200);
	ani->Add(6010);
	ani->Add(6011);
	ani->Add(6012);
	animations->Add(ID_ANI_TURRET_ACTIVE_1_OCLOCK, ani);

	ani = new CAnimation(200);
	ani->Add(6013);
	ani->Add(6014);
	ani->Add(6015);
	animations->Add(ID_ANI_TURRET_ACTIVE_2_OCLOCK, ani);

	ani = new CAnimation(200);
	ani->Add(6016);
	ani->Add(6017);
	ani->Add(6018);
	animations->Add(ID_ANI_TURRET_ACTIVE_3_OCLOCK, ani);

	ani = new CAnimation(200);
	ani->Add(6019);
	ani->Add(6020);
	ani->Add(6021);
	animations->Add(ID_ANI_TURRET_ACTIVE_4_OCLOCK, ani);

	ani = new CAnimation(200);
	ani->Add(6022);
	ani->Add(6023);
	ani->Add(6024);
	animations->Add(ID_ANI_TURRET_ACTIVE_5_OCLOCK, ani);

	ani = new CAnimation(200);
	ani->Add(6025);
	ani->Add(6026);
	ani->Add(6027);
	animations->Add(ID_ANI_TURRET_ACTIVE_6_OCLOCK, ani);

	ani = new CAnimation(200);
	ani->Add(6028);
	ani->Add(6029);
	ani->Add(6030);
	animations->Add(ID_ANI_TURRET_ACTIVE_7_OCLOCK, ani);

	ani = new CAnimation(200);
	ani->Add(6031);
	ani->Add(6032);
	ani->Add(6033);
	animations->Add(ID_ANI_TURRET_ACTIVE_8_OCLOCK, ani);

	ani = new CAnimation(200);
	ani->Add(6034);
	ani->Add(6035);
	ani->Add(6036);
	animations->Add(ID_ANI_TURRET_ACTIVE_9_OCLOCK, ani);

	ani = new CAnimation(200);
	ani->Add(6037);
	ani->Add(6038);
	ani->Add(6039);
	animations->Add(ID_ANI_TURRET_ACTIVE_10_OCLOCK, ani);

	ani = new CAnimation(200);
	ani->Add(6040);
	ani->Add(6041);
	ani->Add(6042);
	animations->Add(ID_ANI_TURRET_ACTIVE_11_OCLOCK, ani);

	wT = new CWallTurret(1264, 71);
	objects.push_back(wT);
	wT = new CWallTurret(1647.1, 102.5);
	objects.push_back(wT);
	wT = new CWallTurret(1839, 102.5);
	objects.push_back(wT);

	sprites->Add(17000, 31, 105, 46, 119, texLevel1); // grass begin
	sprites->Add(17001, 47, 105, 62, 119, texLevel1); // grass end
	grass = new Platform(31, 120, 15, 14, 2, 17000,17000,17001);
	//objects.push_back(grass);

	root = new World(0, 0, 3455, 223);
	root->SetObjects(objects);
	root->Build();
	
	objects.clear();
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	objects.clear();
	root->GetObjectColliderWithWiewport( objects);
	CGame* g = CGame::GetInstance();
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.erase(remove(coObjects.begin(), coObjects.end(), objects[i]), coObjects.end());

		objects[i]->Update(dt, &coObjects);

		coObjects.push_back(objects[i]);
	}
	bill->Update(dt, &coObjects);
	g->GetCamera()->Update();
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

	spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

	for (int i = 0; i < (int)sections.size(); i++)
	{
		sections[i]->Render();
	}
	
	bill->Render();

	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Render();
	}

	for (LPGAMEOBJECT obj : objects)
	{
		if (obj->GetIsMovable())
			root->AddObjectToTree(obj);
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