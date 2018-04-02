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

	//soilder �Ѿ� �ʱ�ȭ
	for (int i = 0; i < SOLDIER_BULLET_MAX; i++)
	{
		Ebullet[i].isFired = false;
		Ebullet[i].speed = SOLDIER_BULLET_SPEED;
		Ebullet[i].angle = 0;
		Ebullet[i].pos = { 0,0,1,1 };
	}
	//soldier gunpoints �ʱ�ȭ
	EgunPoints = { 0,0,0,0,0,0,false,false };

	//���� SOLDIER_BULLET_DELAY �Ŀ� ��������
	bulletTimer = SOLDIER_BULLET_DELAY;

	//�Ѿ��� ȭ�� �ֺ����� ���� ��� �̰ɷ� reset ������
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
	if (_E.isDead) //�׾��ٸ� �� �̻� �ȿ����̰� �Ѵ�.
	{
		Dead();
		return;
	}	
		
	//Player���� �ѿ� �¾Ҵ��� Ȯ���ϴ� �κ�
	for (int i = 0; i < n; i++)
	{
		if (!_bullet[i].isFired)
			continue;
		if (IntersectRect(&tempRect, &_bullet[i].pos, &_E.Pos))//player�� bullet �� enemy Pos check
		{
			_E.isDead = true;
			_bullet[i].isFired = false;	//���� �Ѿ� �����ֱ�
			_bullet[i].pos = { 0, };	//���� �Ѿ� �ʱ�ȭ���ֱ�
			deathPoint.x = _E.Pos.left;
			deathPoint.y = _E.Pos.top;
			_E.Pos = { 0, };
			EgunPoints = { 0,0,0,0,0,0,false,false };
		}
	}

	//��������� player�� ��ġ�� �� class ������ �������
	playerPos = _playerPos;	
	playerCenterDirection = { playerPos.left + (PLAYER_SIZE / 2),playerPos.top+ (PLAYER_SIZE / 2) };

	//2���� enemy �ٿ���� update;
	DetectorPositionUpdate();

	//player Detect : ���� player�� Position�� detectPlayerBoundary�� ������ �ȴٸ� 
	if (IntersectRect(&tempRect, &playerPos, &detectPlayerBoundary))
	{
		changeGunPos();	//��ó�� player�� ������ player�� ���� ���� ����
		//���� player�� shootingPlayerBoundary�ȿ� ������ �ɶ����� �̵�
		if (!IntersectRect(&tempRect, &playerPos, &shootingPlayerBoundary))
		{
			Move();
		}
		//shootingPlayerBoundary�� ������ ����
		else
		{
			Attack();
		}
	}
	//������ �ʴ´ٸ� ���ϰ� IDLE�� �Ѵ�.
	else
		Idle();

	//���� �����̰� �ϴ� �κ�
	S_BulletMove();

	//���� frame ������ ������ reset�ǵ���
	for (int i = 0; i < SOLDIER_BULLET_MAX; i++)
	{
		if (!IntersectRect(&tempRect, &bulletBoarder, &Ebullet[i].pos/*&gun->getBulletPos(i)*/))
			setFired(i, false);
	}

	//FrameX count + Ÿ�̸ӵ����� ���
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

	if (_E.isDead)	//�׾��ٸ� �� �̻� �ȿ����̰� �Ѵ�.
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
	MoveToEx(hdc, EgunPoints.startX, EgunPoints.startY, NULL);	//���� hdc�� �ȱ�� 
	LineTo(hdc, EgunPoints.endX, EgunPoints.endY);	//���� �׸���.

	
	//paint enemy bullet
	for (int i = 0; i < SOLDIER_BULLET_MAX; i++)
	{
		if (!Ebullet[i].isFired)
			continue;
		tempRect = getBulletPos(i);
		Rectangle(hdc, tempRect.left, tempRect.top, tempRect.right, tempRect.bottom);
	}


	//Enemy State�� ���� frame render
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
	//���⿡ ������Ʈ �ʱ�ȭ ���߿� ���� �ϴ� �� �Ʒ� 
	

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
	//����RECT �߽ɿ� ��ġ�ϵ��� �ߴ�.
	EgunPoints.startX = _E.Pos.left + (SOLDIER_SIZE / 2);
	EgunPoints.startY = _E.Pos.top + (SOLDIER_SIZE / 2);
	
	//pLayer�� ��ġ�� ���� �ѱ��� ������ �޶�����.
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
	//Enemy�� detecting Boundary Update
	detectPlayerBoundary.top    = _E.Pos.top - SOLDIER_DETECTING_PLAYER_RANGE;
	detectPlayerBoundary.left   = _E.Pos.left - SOLDIER_DETECTING_PLAYER_RANGE;
	detectPlayerBoundary.right  = _E.Pos.right + SOLDIER_DETECTING_PLAYER_RANGE;
	detectPlayerBoundary.bottom = _E.Pos.bottom + SOLDIER_DETECTING_PLAYER_RANGE;

	//Enemy�� Shooting Range update
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
