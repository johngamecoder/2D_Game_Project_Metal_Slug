#pragma once
#include"singletonBase.h"
#include<bitset>

#define KEYMAX 256
class keyManager : public singletonBase<keyManager>
{
private:
	std::bitset<KEYMAX> m_keyUp;
	std::bitset<KEYMAX> m_keyDown;
public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();

	//키가 한번만 눌렸냐
	bool isOnceKeyDown(int key);
	//한번 눌렀다가 띄었냐
	bool isOnceKeyUp(int key);
	//키가 계속 눌러져 있냐
	bool isStayKeyDown(int key);

	//토글키냐 캡스락 넘버락
	bool isToggleKey(int key);


};

