#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}

HRESULT keyManager::init()
{
	
	//키값을 전부 눌려있지 않은 상태로 초기화
	for ( int i = 0; i < KEYMAX; i++ )
	{
		m_keyUp.set(i, false);
		m_keyDown.set(i, false);
	}


	return S_OK;
}

void keyManager::release()
{
}

bool keyManager::isOnceKeyDown(int key)
{

	if ( GetAsyncKeyState(key) & 0x8000 )
	{
		if ( !m_keyDown[key] )
		{
			m_keyDown.set(key, true);
			return true;
		}
	}
	else
	{
		m_keyDown.set(key, false);
	}

	return false;
}

bool keyManager::isOnceKeyUp(int key)
{

	if ( GetAsyncKeyState(key) & 0x8000 )
	{
		m_keyUp.set(key, true);
	}
	else
	{
		if ( m_keyUp[key] )
		{
			m_keyUp.set(key, false);
			return false;
		}
	}
	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if ( GetAsyncKeyState(key) & 0x8000 )return true;
	return false;

	Sleep(100);
}

bool keyManager::isToggleKey(int key)
{
	if ( GetKeyState(key) & 0x0001 )return true;
	return false;
}
