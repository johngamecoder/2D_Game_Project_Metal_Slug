#include "stdafx.h"
#include "SOLDIER.h"

#define DETECTING_PLAYER_RANGE 200
#define SHOOTING_PLAYER_RANGE 100

SOLDIER::SOLDIER()
{
}


SOLDIER::~SOLDIER()
{
}

void SOLDIER::Init()
{
	//temporary enemy position.
	RECT temp = { 0,0,0,0 };
	ENEMY::Pos = temp;
	ENEMY::detectPlayerBoundary = temp;
	ENEMY::shootingPlayerBoundary = temp;
}

void SOLDIER::Update()
{
	//Enemy¿« detecting Boundary Update
	ENEMY::detectPlayerBoundary.top = ENEMY::Pos.top - DETECTING_PLAYER_RANGE;
	ENEMY::detectPlayerBoundary.left = ENEMY::Pos.left - DETECTING_PLAYER_RANGE;
	ENEMY::detectPlayerBoundary.right = ENEMY::Pos.right + DETECTING_PLAYER_RANGE;
	ENEMY::detectPlayerBoundary.bottom = ENEMY::Pos.bottom + DETECTING_PLAYER_RANGE;

	//Enemy¿« Shooting Range update
	ENEMY::shootingPlayerBoundary.top = ENEMY::Pos.top - SHOOTING_PLAYER_RANGE;
	ENEMY::shootingPlayerBoundary.left = ENEMY::Pos.left - SHOOTING_PLAYER_RANGE;
	ENEMY::shootingPlayerBoundary.right = ENEMY::Pos.right + SHOOTING_PLAYER_RANGE;
	ENEMY::shootingPlayerBoundary.bottom = ENEMY::Pos.bottom + SHOOTING_PLAYER_RANGE;
}

void SOLDIER::Idle()
{

}

void SOLDIER::Attack()
{
}

void SOLDIER::Move()
{
}

void SOLDIER::Dead()
{
}
