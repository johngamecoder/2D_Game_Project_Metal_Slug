#pragma once
class ENEMY_IMAGE_CONTAINER	//���� �̹����� �����ϸ� �ѹ��� �ҷ��� ����ȭ�� ���� ������� �Ѵ�.
{
public:
	Image * rifle_idle;
	Image* rifle_move;
	Image* rifle_shoot;
	Image* dead_norm;
public:
	ENEMY_IMAGE_CONTAINER();
	~ENEMY_IMAGE_CONTAINER();
	void Init();
	void Release();
};

