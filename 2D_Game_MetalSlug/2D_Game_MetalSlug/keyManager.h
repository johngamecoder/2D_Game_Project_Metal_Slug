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

	//Ű�� �ѹ��� ���ȳ�
	bool isOnceKeyDown(int key);
	//�ѹ� �����ٰ� �����
	bool isOnceKeyUp(int key);
	//Ű�� ��� ������ �ֳ�
	bool isStayKeyDown(int key);

	//���Ű�� ĸ���� �ѹ���
	bool isToggleKey(int key);


};

