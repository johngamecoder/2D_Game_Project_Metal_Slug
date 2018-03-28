// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
struct tagKEYBOARD
{
	bool leftKeyPressed;
	bool rightKeyPressed;
	bool downKeyPressed;
	bool upKeyPressed;
	bool Q_KeyPressed;
	bool W_KeyPressed;
	bool E_KeyPressed;

	void operator =(const tagKEYBOARD& keyBoard)
	{
		leftKeyPressed = keyBoard.leftKeyPressed;
		rightKeyPressed = keyBoard.rightKeyPressed;
		downKeyPressed = keyBoard.downKeyPressed;
		upKeyPressed = keyBoard.upKeyPressed;
		Q_KeyPressed = keyBoard.Q_KeyPressed;
		W_KeyPressed = keyBoard.W_KeyPressed;
		E_KeyPressed = keyBoard.E_KeyPressed;
	}
};
//총알 구조체
struct tagBULLET
{
	bool isFired;
	RECT pos;
	float speed;
	float angle;
};
//총 손잡이? 에 대한 구조체
struct tagGunPoints
{
	int startX, startY;
	int endX, endY;
	float angle;
	float prevAngle;
	bool isUpKeyPressed;
	bool isDownKeyPressed;

	void operator =(const tagGunPoints& temp)
	{
		startX = temp.startX;
		startY = temp.startY;
		endX = temp.endX;
		endY = temp.endY;
		angle = temp.angle;
	}
};
struct tagCHARACTER
{
	bool isDead;
	RECT Pos;
	void operator =(const tagCHARACTER& temp)
	{
		isDead = temp.isDead;
		Pos = temp.Pos;
	}	
};
//====================================
//내가 만든 헤더 추가
//====================================
#include "2D_Game_MetalSlug.h"
#include "Image.h"
#include "PLAYER.h"
#include "GUN.h"
#include "DEFAULTGUN.h"
#include "GROUNDnOBSTACLE.h"
#include "ENEMY.h"
#include "SOLDIER.h"
#include "GAMEMANAGER.h"
#include "keyManager.h"





//====================================
//디파인문 선언
//====================================
#define WINSTARTX 100
#define WINSTARTY 30
#define WINSIZEX 800
#define WINSIZEY 600
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define TIMER_ID 123
#define PI 3.141592654
#define GRAVITY 3.0f
#define PLAYER_POSITION_X 100
#define PLAYER_POSITION_Y 100



//#define KEYMANAGER keyManager::getSingleton()

////printf 가능하게 만드는 부분
//#include <stdio.h>
//#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

extern HWND hWnd;
extern HINSTANCE g_hInst;
