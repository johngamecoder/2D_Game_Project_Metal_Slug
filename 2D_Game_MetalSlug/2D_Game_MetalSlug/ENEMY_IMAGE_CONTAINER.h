#pragma once
class ENEMY_IMAGE_CONTAINER	//적의 이미지를 관리하며 한번만 불려서 과부화가 없게 만들려고 한다.
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

