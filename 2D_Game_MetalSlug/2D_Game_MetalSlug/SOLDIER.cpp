#include "stdafx.h"
SOLDIER::SOLDIER()
{
}
SOLDIER::~SOLDIER()
{
}

void SOLDIER::Init(int xPos)
{

	isOff = false;
	_E.isDead = false;
	//temporary enemy position.
	_E.Pos = { xPos,350,xPos+50,400 };
	detectPlayerBoundary = _E.Pos;
	shootingPlayerBoundary = _E.Pos;

	//soilder 총알 초기화
	for (int i = 0; i < SOLDIER_BULLET_MAX; i++)
	{
		Ebullet[i].isFired = false;
		Ebullet[i].speed = SOLDIER_BULLET_SPEED;
		Ebullet[i].angle = 0;
		Ebullet[i].pos = { 0,0,1,1 };
	}
	//soldier gunpoints 초기화
	EgunPoints = { 0,0,0,0,0,0,false,false };

	//총이 SOLDIER_BULLET_DELAY 후에 나가도록
	bulletTimer = SOLDIER_BULLET_DELAY;

	//총알이 화면 주변에서 나갈 경우 이걸로 reset 시켜줌
	bulletBoarder = { 0,0,WINSIZEX ,WINSIZEY };



	//Enemy State
	enemyState = { 0, };

	//Image rendering
	m_enemy_rifle = NULL;
	currentFrameX = 0;
	currentFrameY = 0;
	frame_count = 0;
	frameTemp = 0;

	//m_rifle_idle = new Image;
	//m_rifle_idle->init("Image/enemy/rifle/idle/rifle_idle.bmp", 600, 100, 12, 2, true, RGB(255, 0, 255));
	//m_rifle_move = new Image;
	//m_rifle_move->init("Image/enemy/rifle/move/rifle_move.bmp", 700, 100, 14, 2, true, RGB(255, 0, 255));
	//m_rifle_shoot = new Image;
	//m_rifle_shoot->init("Image/enemy/rifle/shoot/rifle_shoot.bmp", 1000, 100, 20, 2, true, RGB(255, 0, 255));
	//m_dead_norm = new Image;
	//m_dead_norm->init("Image/enemy/dead/norm/dead_norm.bmp", 550, 100, 11, 2, true, RGB(255, 0, 255));

}
void SOLDIER::Update(RECT _playerPos, tagBULLET* _bullet, int n)
{
	if (_E.isDead) //죽었다면 더 이상 안움직이게 한다.
	{
		Dead();
		return;
	}	
		
	//Player에게 총에 맞았는지 확인하는 부분
	for (int i = 0; i < n; i++)
	{
		if (!_bullet[i].isFired)
			continue;
		if (IntersectRect(&tempRect, &_bullet[i].pos, &_E.Pos))//player의 bullet 과 enemy Pos check
		{
			_E.isDead = true;
			_bullet[i].isFired = false;	//맞은 총알 없애주기
			_bullet[i].pos = { 0, };	//맞은 총알 초기화해주기
			deathPoint.x = _E.Pos.left;
			deathPoint.y = _E.Pos.top;
			_E.Pos = { 0, };
			EgunPoints = { 0,0,0,0,0,0,false,false };
		}
	}

	//계속적으로 player의 위치를 얻어서 class 내에서 사용하자
	playerPos = _playerPos;	
	playerCenterDirection = { playerPos.left + (PLAYER_SIZE / 2),playerPos.top+ (PLAYER_SIZE / 2) };

	//2개의 enemy 바운더리 update;
	DetectorPositionUpdate();

	//player Detect : 만약 player의 Position이 detectPlayerBoundary에 들어오게 된다면 
	if (IntersectRect(&tempRect, &playerPos, &detectPlayerBoundary))
	{
		changeGunPos();	//근처에 player가 있으면 player을 향해 총을 향함
		//만약 player가 shootingPlayerBoundary안에 들어오게 될때까지 이동
		if (!IntersectRect(&tempRect, &playerPos, &shootingPlayerBoundary))
		{
			Move();
		}
		//shootingPlayerBoundary에 들어오면 공격
		else
		{
			Attack();
		}
	}
	//들어오지 않는다면 편하게 IDLE을 한다.
	else
		Idle();

	//총을 움직이게 하는 부분
	S_BulletMove();

	//총이 frame 밖으로 나가면 reset되도록
	for (int i = 0; i < SOLDIER_BULLET_MAX; i++)
	{
		if (!IntersectRect(&tempRect, &bulletBoarder, &Ebullet[i].pos/*&gun->getBulletPos(i)*/))
			setFired(i, false);
	}

	//FrameX count + 타이머등으로 사용
	frame_count++;
	if (frame_count % 6 == 0)
	{
		frameTemp++;
	}
}
void SOLDIER::Idle()
{
	enemyState.isIdle = true;
}
void SOLDIER::Attack()
{
	enemyState.isShoot = true;
	if (bulletTimer<0)
	{
		S_BulletFire(EgunPoints.endX, EgunPoints.endY, EgunPoints.angle);
		bulletTimer = SOLDIER_BULLET_DELAY;
	}
	bulletTimer--;
}
void SOLDIER::Move()
{
	enemyState.isMove = true;

	if (playerCenterDirection.x- _E.Pos.left+(SOLDIER_SIZE/2) < 0)
	{
		_E.Pos.left -= SOLDIER_SPEED;
		_E.Pos.right -= SOLDIER_SPEED;
	}
	else
	{
		_E.Pos.left += SOLDIER_SPEED;
		_E.Pos.right += SOLDIER_SPEED;
	}
}
void SOLDIER::Dead()
{
	if (death_frameCount > 12)
	{
		isOff = true;
		return;
	}
		
	if (frameTemp % 2 == 1)
	{
		//m_dead_norm->setFrameX(death_frameCount++);
		_m_->dead_norm->setFrameX(death_frameCount++);
	}
	
}
void SOLDIER::Render(HDC hdc)
{

	if (_E.isDead)	//죽었다면 더 이상 안움직이게 한다.
	{
		if (death_frameCount > 11)
			return;
		//m_dead_norm->frameRender(hdc, deathPoint.x, deathPoint.y);
		_m_->dead_norm->frameRender(hdc, deathPoint.x, deathPoint.y);
		return;
	}
	////paint enemy & boundaries
	//tempRect = detectPlayerBoundary;
	//Rectangle(hdc, tempRect.left, tempRect.top, tempRect.right, tempRect.bottom);
	//tempRect = shootingPlayerBoundary;
	//Rectangle(hdc, tempRect.left, tempRect.top, tempRect.right, tempRect.bottom);
	//tempRect = _E.Pos;
	//Rectangle(hdc, tempRect.left, tempRect.top, tempRect.right, tempRect.bottom);
	
	//paint Gun Handle 
	MoveToEx(hdc, EgunPoints.startX, EgunPoints.startY, NULL);	//먼저 hdc를 옴기고 
	LineTo(hdc, EgunPoints.endX, EgunPoints.endY);	//선을 그린다.

	
	//paint enemy bullet
	for (int i = 0; i < SOLDIER_BULLET_MAX; i++)
	{
		if (!Ebullet[i].isFired)
			continue;
		tempRect = getBulletPos(i);
		Rectangle(hdc, tempRect.left, tempRect.top, tempRect.right, tempRect.bottom);
	}


	//Enemy State에 따른 frame render
	if (enemyState.isShoot)
	{
		/*m_enemy_rifle = m_rifle_shoot;*/
		m_enemy_rifle = _m_->rifle_shoot;
		currentFrameX = frameTemp % 20;
	}
	else if (enemyState.isMove)
	{
		//m_enemy_rifle = m_rifle_move;
		m_enemy_rifle = _m_->rifle_move;
		currentFrameX = frameTemp % 14;
	}
	else 
	{
		/*m_enemy_rifle = m_rifle_idle;*/
		m_enemy_rifle = _m_->rifle_idle;
		currentFrameX = frameTemp % 12;
	}
	//여기에 스테이트 초기화 나중에 넣자 일단 저 아래 
	

	m_enemy_rifle->setFrameY(currentFrameY);
	m_enemy_rifle->setFrameX(currentFrameX);
	m_enemy_rifle->frameRender(hdc, _E.Pos.left, _E.Pos.top);
	enemyState = { 0, };
}
void SOLDIER::Release()
{
	//delete m_rifle_idle;
	//delete m_rifle_move;
	//delete m_rifle_shoot;
	//
	//delete m_dead_norm;
}



void SOLDIER::changeGunPos()
{
	//적의RECT 중심에 위치하도록 했다.
	EgunPoints.startX = _E.Pos.left + (SOLDIER_SIZE / 2);
	EgunPoints.startY = _E.Pos.top + (SOLDIER_SIZE / 2);
	
	//pLayer의 위치에 따라서 총구의 방향이 달라진다.
	if (playerCenterDirection.x - _E.Pos.left + (SOLDIER_SIZE / 2) < 0)
	{
		currentFrameY = 0;
		EgunPoints.angle = PI;
		EgunPoints.endX = -(SOLDIER_GUN_LENGTH) + EgunPoints.startX;
		EgunPoints.endY = EgunPoints.startY;
	}
	else
	{
		currentFrameY = 1;
		EgunPoints.angle = 0;
		EgunPoints.endX = SOLDIER_GUN_LENGTH +EgunPoints.startX;
		EgunPoints.endY = EgunPoints.startY;
	}
}
void SOLDIER::DetectorPositionUpdate()
{
	//Enemy의 detecting Boundary Update
	detectPlayerBoundary.top    = _E.Pos.top - SOLDIER_DETECTING_PLAYER_RANGE;
	detectPlayerBoundary.left   = _E.Pos.left - SOLDIER_DETECTING_PLAYER_RANGE;
	detectPlayerBoundary.right  = _E.Pos.right + SOLDIER_DETECTING_PLAYER_RANGE;
	detectPlayerBoundary.bottom = _E.Pos.bottom + SOLDIER_DETECTING_PLAYER_RANGE;

	//Enemy의 Shooting Range update
	shootingPlayerBoundary.top    = _E.Pos.top - SOLDIER_SHOOTING_PLAYER_RANGE;
	shootingPlayerBoundary.left   = _E.Pos.left - SOLDIER_SHOOTING_PLAYER_RANGE;
	shootingPlayerBoundary.right  = _E.Pos.right + SOLDIER_SHOOTING_PLAYER_RANGE;
	shootingPlayerBoundary.bottom = _E.Pos.bottom + SOLDIER_SHOOTING_PLAYER_RANGE;
}
void SOLDIER::S_BulletFire(int gunEndX, int gunEndY, float angle)
{
	for (int i = 0; i < SOLDIER_BULLET_MAX; i++)
	{
		if (!Ebullet[i].isFired)
		{
			Ebullet[i].isFired = true;
			Ebullet[i].pos.left = gunEndX;
			Ebullet[i].pos.top = gunEndY;
			Ebullet[i].pos.right = Ebullet[i].pos.left + SOLDIER_BULLET_SIZE;
			Ebullet[i].pos.bottom = Ebullet[i].pos.top + SOLDIER_BULLET_SIZE;
			Ebullet[i].angle = angle;
			break;
		}
	}
}
void SOLDIER::S_BulletMove()
{
	for (int i = 0; i < SOLDIER_BULLET_MAX; i++)
	{
		if (!Ebullet[i].isFired)
			continue;

		Ebullet[i].pos.left += cosf(Ebullet[i].angle )*Ebullet[i].speed;
		Ebullet[i].pos.top += -sinf(Ebullet[i].angle )*Ebullet[i].speed;
		Ebullet[i].pos.right = Ebullet[i].pos.left + SOLDIER_BULLET_SIZE;
		Ebullet[i].pos.bottom = Ebullet[i].pos.top + SOLDIER_BULLET_SIZE;
	}
}
