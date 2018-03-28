#include "stdafx.h"
#include "image.h"

//����
/*
1. bmp : ������ ������, ���ս� �������̹Ƿ� �ӵ��� ���� ����.
2. jpg : �ս� �����̹Ƿ� �������� �̹����� �ս��� �Ͼ, ��� �˰��� ���� ������ �Ǿ� �뷮�� ����.
3. png : �� �γ�� �ٸ��� ���İ��� ����. (alpha : ������ ä��)
*/


Image::Image() :m_imageInfo(nullptr), m_fileName(nullptr), m_isTrans(NULL), m_transColor(RGB(0, 0, 0))
{
}


Image::~Image()
{
}

HRESULT Image::init(int width, int height)
{
	//���ʱ�ȭ ������, �̹��������� ���� �ִٸ� ������
	if (m_imageInfo != nullptr) release();
	//DC�������� ���� �����쿡 ���� ȭ�� DC�� �ӽ������� �޾ƿ�
	HDC hdc = GetDC(hWnd);


	//��Ʈ���� ����ϱ� ���� �޸� dc�� ����� �ִ� �Լ�
	//CreateCompatibleBitmap
	//���� dc�� ȣȯ�Ǵ� ��Ʈ���� �������ִ� �Լ�
	//selectobject
	//������ ��Ʈ���� �ڵ��� ��ȯ�ϰ� ���ο� ��Ʈ���� �޸� dc�� �����ϰ� �޸� dc�� ��Ʈ���� �׷���

	//�̹��� ������ ��������
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_EMPTY;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;

	//���� �̸�
	m_fileName = nullptr;

	//����Ű �÷� ����
	m_isTrans = false;
	m_transColor = RGB(0, 0, 0);
	//���ҽ��� �����µ� ���� �����ÿ�
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(hWnd, hdc);//dc����


	return E_NOTIMPL;
}

HRESULT Image::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��������� ���� �ִٸ� ������
	if (m_imageInfo != nullptr) release();
	//DC�������� ���� �����쿡 ���� ȭ�� DC�� �ӽ������� �޾ƿ�
	HDC hdc = GetDC(hWnd);


	//��Ʈ���� ����ϱ� ���� �޸� dc�� ����� �ִ� �Լ�
	//CreateCompatibleBitmap
	//���� dc�� ȣȯ�Ǵ� ��Ʈ���� �������ִ� �Լ�
	//selectobject
	//������ ��Ʈ���� �ڵ��� ��ȯ�ϰ� ���ο� ��Ʈ���� �޸� dc�� �����ϰ� �޸� dc�� ��Ʈ���� �׷���

	//�̹��� ������ ��������
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_RESOURCE;
	m_imageInfo->resID = resID;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(m_imageInfo->resID)); // ������ ��Ʈ�ʿ� �ø���.
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;


	//���� �̸�
	m_fileName = nullptr;

	//����Ű �÷� ����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ҽ��� �����µ� ���� �����ÿ�
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(hWnd, hdc);//dc����
	return S_OK;
}

HRESULT Image::init(const char * fileName, int width, int height,  bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��������� ���� �ִٸ� ������
	if (m_imageInfo != nullptr) release();
	//DC�������� ���� �����쿡 ���� ȭ�� DC�� �ӽ������� �޾ƿ�
	HDC hdc = GetDC(hWnd);


	//��Ʈ���� ����ϱ� ���� �޸� dc�� ����� �ִ� �Լ�
	//CreateCompatibleBitmap
	//���� dc�� ȣȯ�Ǵ� ��Ʈ���� �������ִ� �Լ�
	//selectobject
	//������ ��Ʈ���� �ڵ��� ��ȯ�ϰ� ���ο� ��Ʈ���� �޸� dc�� �����ϰ� �޸� dc�� ��Ʈ���� �׷���

	//�̹��� ������ ��������
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_FILE;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadImage(g_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;






	//���� �̸�
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//����Ű �÷� ����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ҽ��� �����µ� ���� �����ÿ�
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(hWnd, hdc);//dc����
	return S_OK;

}

HRESULT Image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��������� ���� �ִٸ� ������
	if (m_imageInfo != nullptr) release();
	//DC�������� ���� �����쿡 ���� ȭ�� DC�� �ӽ������� �޾ƿ�
	HDC hdc = GetDC(hWnd);


	//��Ʈ���� ����ϱ� ���� �޸� dc�� ����� �ִ� �Լ�
	//CreateCompatibleBitmap
	//���� dc�� ȣȯ�Ǵ� ��Ʈ���� �������ִ� �Լ�
	//selectobject
	//������ ��Ʈ���� �ڵ��� ��ȯ�ϰ� ���ο� ��Ʈ���� �޸� dc�� �����ϰ� �޸� dc�� ��Ʈ���� �׷���

	//�̹��� ������ ��������
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_FILE;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadImage(g_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;
	m_imageInfo->maxFrameX = frameX - 1;
	m_imageInfo->maxFrameY = frameY - 1;
	m_imageInfo->frameWidth = width / frameX;
	m_imageInfo->frameHeight = height / frameY;

	//���� �̸�
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//����Ű �÷� ����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ҽ��� �����µ� ���� �����ÿ�
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(hWnd, hdc);//dc����
	return S_OK;



	return S_OK;

}

HRESULT Image::init(const char * fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��������� ���� �ִٸ� ������
	if (m_imageInfo != nullptr) release();
	//DC�������� ���� �����쿡 ���� ȭ�� DC�� �ӽ������� �޾ƿ�
	HDC hdc = GetDC(hWnd);


	//��Ʈ���� ����ϱ� ���� �޸� dc�� ����� �ִ� �Լ�
	//CreateCompatibleBitmap
	//���� dc�� ȣȯ�Ǵ� ��Ʈ���� �������ִ� �Լ�
	//selectobject
	//������ ��Ʈ���� �ڵ��� ��ȯ�ϰ� ���ο� ��Ʈ���� �޸� dc�� �����ϰ� �޸� dc�� ��Ʈ���� �׷���

	//�̹��� ������ ��������
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_FILE;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadImage(g_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->x = x - (width / frameX / 2);
	m_imageInfo->y = y - (height / frameY / 2);
	m_imageInfo->width = width;
	m_imageInfo->height = height;
	m_imageInfo->maxFrameX = frameX - 1;
	m_imageInfo->maxFrameY = frameY - 1;
	m_imageInfo->frameWidth = width / frameX;
	m_imageInfo->frameHeight = height / frameY;

	//���� �̸�
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//����Ű �÷� ����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ҽ��� �����µ� ���� �����ÿ�
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(hWnd, hdc);//dc����
	return S_OK;



	return S_OK;
}

void Image::setTransColor(bool isTrans, COLORREF transColor)
{
	m_isTrans = isTrans;
	m_transColor = transColor;
}

void Image::release()
{
	//�̹��� ������ �����մٸ�, ����� ����
	if (m_imageInfo)
	{
		SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
		DeleteObject(m_imageInfo->hOBit);
		DeleteObject(m_imageInfo->hMemDC);

		SAFE_DELETE(m_imageInfo);
		SAFE_DELETE(m_fileName);
		m_isTrans = false;
		m_transColor = RGB(0, 0, 0);
	}
}

void Image::render(HDC hdc)
{
	//���� ���ٰų�
	if (m_isTrans)
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�� ���� �����ϰ� �����ϴ� �Լ�
		//���ڰ� :  ����� ����� DC, ����� ��ǥ�� ������ X�� Y, ����� �̹����� ����ũ��� ����ũ��, ����� ����� DC, ����������� X��Y, ���� ������ ����ũ��, ����ũ��, �����Ҷ��� ������ ����
		GdiTransparentBlt(hdc, 0, 0,
			m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, m_imageInfo->width,
			m_imageInfo->height, m_transColor);
	}
	//���� �ȳ����� �����̹��� �״�� �̾Ƴ��ų�
	else
	{
		// SRCCOPY: �������ִ� ��, ���μ��θ� ������ �ؼ� ������
		// DC�� �������� ��Ӻ��� �ϴ� �༮
		BitBlt(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, SRCCOPY);


	}

}

void Image::render(HDC hdc, int destX, int destY)
{
	//���� ���ٰų�
	if (m_isTrans)
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�� ���� �����ϰ� �����ϴ� �Լ�
		//���ڰ� :  ����� ����� DC, ����� ��ǥ�� ������ X�� Y, ����� �̹����� ����ũ��� ����ũ��, ����� ����� DC, ����������� X��Y, ���� ������ ����ũ��, ����ũ��, �����Ҷ��� ������ ����
		GdiTransparentBlt(hdc,
			destX,
			destY,
			m_imageInfo->width,
			m_imageInfo->height,
			m_imageInfo->hMemDC,
			0,
			0,
			m_imageInfo->width,
			m_imageInfo->height,
			m_transColor);
	}
	//���� �ȳ����� �����̹��� �״�� �̾Ƴ��ų�
	else
	{
		// SRCCOPY: �������ִ� ��, ���μ��θ� ������ �ؼ� ������
		// DC�� �������� ��Ӻ��� �ϴ� �༮
		BitBlt(hdc, destX, destY, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, SRCCOPY);

	}
}

void Image::frameRender(HDC hdc, int destX, int destY)
{
	//���� ���ٰų�
	if (m_isTrans)
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�� ���� �����ϰ� �����ϴ� �Լ�
		//���ڰ� :  ����� ����� DC, ����� ��ǥ�� ������ X�� Y, ����� �̹����� ����ũ��� ����ũ��, ����� ����� DC, ����������� X��Y, ���� ������ ����ũ��, ����ũ��, �����Ҷ��� ������ ����
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			m_imageInfo->frameWidth,
			m_imageInfo->frameHeight,
			m_imageInfo->hMemDC,	//����� ��� DC
			m_imageInfo->currentFrameX * m_imageInfo->frameWidth, //���� ��������
			m_imageInfo->currentFrameY * m_imageInfo->frameHeight, //���� ��������
			m_imageInfo->frameWidth, //���� ���� ����ũ��
			m_imageInfo->frameHeight, //���� ���� ����ũ��
			m_transColor);
	}
	//���� �ȳ����� �����̹��� �״�� �̾Ƴ��ų�
	else
	{
		// SRCCOPY: �������ִ� ��, ���μ��θ� ������ �ؼ� ������
		// DC�� �������� ��Ӻ��� �ϴ� �༮
		BitBlt(hdc, destX, destY, m_imageInfo->frameWidth, m_imageInfo->frameHeight,
			m_imageInfo->hMemDC,
			m_imageInfo->currentFrameX * m_imageInfo->frameWidth,
			m_imageInfo->currentFrameY * m_imageInfo->frameHeight,
			SRCCOPY);

	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	m_imageInfo->currentFrameX = currentFrameX;
	m_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > m_imageInfo->maxFrameX)
	{
		m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
	}

	if (currentFrameY > m_imageInfo->maxFrameY)
	{
		m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
	}

		//���� ���ٰų�
		if (m_isTrans)
		{
			//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�� ���� �����ϰ� �����ϴ� �Լ�
			//���ڰ� :  ����� ����� DC, ����� ��ǥ�� ������ X�� Y, ����� �̹����� ����ũ��� ����ũ��, ����� ����� DC, ����������� X��Y, ���� ������ ����ũ��, ����ũ��, �����Ҷ��� ������ ����
			GdiTransparentBlt(
				hdc,
				destX,
				destY,
				m_imageInfo->frameWidth,
				m_imageInfo->frameHeight,
				m_imageInfo->hMemDC,	//����� ��� DC
				m_imageInfo->currentFrameX * m_imageInfo->frameWidth, //���� ��������
				m_imageInfo->currentFrameY * m_imageInfo->frameHeight, //���� ��������
				m_imageInfo->frameWidth, //���� ���� ����ũ��
				m_imageInfo->frameHeight, //���� ���� ����ũ��
				m_transColor);
		}
		//���� �ȳ����� �����̹��� �״�� �̾Ƴ��ų�
		else
		{
			// SRCCOPY: �������ִ� ��, ���μ��θ� ������ �ؼ� ������
			// DC�� �������� ��Ӻ��� �ϴ� �༮
			BitBlt(hdc, destX, destY, m_imageInfo->frameWidth, m_imageInfo->frameHeight,
				m_imageInfo->hMemDC,
				m_imageInfo->currentFrameX * m_imageInfo->frameWidth,
				m_imageInfo->currentFrameY * m_imageInfo->frameHeight,
				SRCCOPY);

		}

}

void Image::frameRender(HDC hdc, int desX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	m_imageInfo->currentFrameX = currentFrameX;
	m_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > m_imageInfo->maxFrameX)
	{
		m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
	}

	if (currentFrameY > m_imageInfo->maxFrameY)
	{
		m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
	}

}


