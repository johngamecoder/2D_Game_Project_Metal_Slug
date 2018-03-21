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

//====================================
//내가 만든 헤더 추가
//====================================
#include "2D_Game_MetalSlug.h"
#include "PLAYER.h"
#include "GUN.h"
#include "DEFAULTGUN.h"
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
#define PI 3.14
#define GRAVITY 3.0f
#define PLAYER_POSITION_X 200
#define PLAYER_POSITION_Y 300
#define PLAYER_SIZE 50


//#define KEYMANAGER keyManager::getSingleton()

//printf 가능하게 만드는 부분
#include <stdio.h>
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

extern HWND hWnd;