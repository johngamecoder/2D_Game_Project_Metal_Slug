#include "stdafx.h"
#include "image.h"

//참고
/*
1. bmp : 제약이 많지만, 무손실 무압축이므로 속도가 가장 빠름.
2. jpg : 손실 압축이므로 원래가진 이미지의 손실이 일어남, 어떠한 알고리즘에 의해 압축이 되어 용량이 작음.
3. png : 위 두놈과 다르게 알파값이 없다. (alpha : 반투명 채널)
*/


Image::Image() :m_imageInfo(nullptr), m_fileName(nullptr), m_isTrans(NULL), m_transColor(RGB(0, 0, 0))
{
}


Image::~Image()
{
}

HRESULT Image::init(int width, int height)
{
	//재초기화 방지용, 이미지정보에 값이 있다면 릴리즈
	if (m_imageInfo != nullptr) release();
	//DC가져오기 현재 윈도우에 대한 화면 DC를 임시적으로 받아옴
	HDC hdc = GetDC(hWnd);


	//비트맵을 출력하기 위해 메모리 dc를 만들어 주는 함수
	//CreateCompatibleBitmap
	//원본 dc와 호환되는 비트맵을 생성해주는 함수
	//selectobject
	//기존의 비트맵을 핸들을 반환하고 새로운 비트맥을 메모리 dc가 선택하고 메모리 dc에 비트맵이 그려짐

	//이미지 정보를 생성하자
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_EMPTY;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;

	//파일 이름
	m_fileName = nullptr;

	//투명키 컬러 셋팅
	m_isTrans = false;
	m_transColor = RGB(0, 0, 0);
	//리소스를 얻어오는데 실패 했을시에
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(hWnd, hdc);//dc해제


	return E_NOTIMPL;
}

HRESULT Image::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지정보에 값이 있다면 릴리즈
	if (m_imageInfo != nullptr) release();
	//DC가져오기 현재 윈도우에 대한 화면 DC를 임시적으로 받아옴
	HDC hdc = GetDC(hWnd);


	//비트맵을 출력하기 위해 메모리 dc를 만들어 주는 함수
	//CreateCompatibleBitmap
	//원본 dc와 호환되는 비트맵을 생성해주는 함수
	//selectobject
	//기존의 비트맵을 핸들을 반환하고 새로운 비트맥을 메모리 dc가 선택하고 메모리 dc에 비트맵이 그려짐

	//이미지 정보를 생성하자
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_RESOURCE;
	m_imageInfo->resID = resID;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(m_imageInfo->resID)); // 파일을 비트맵에 올린다.
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;


	//파일 이름
	m_fileName = nullptr;

	//투명키 컬러 셋팅
	m_isTrans = isTrans;
	m_transColor = transColor;

	//리소스를 얻어오는데 실패 했을시에
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(hWnd, hdc);//dc해제
	return S_OK;
}

HRESULT Image::init(const char * fileName, int width, int height,  bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지정보에 값이 있다면 릴리즈
	if (m_imageInfo != nullptr) release();
	//DC가져오기 현재 윈도우에 대한 화면 DC를 임시적으로 받아옴
	HDC hdc = GetDC(hWnd);


	//비트맵을 출력하기 위해 메모리 dc를 만들어 주는 함수
	//CreateCompatibleBitmap
	//원본 dc와 호환되는 비트맵을 생성해주는 함수
	//selectobject
	//기존의 비트맵을 핸들을 반환하고 새로운 비트맥을 메모리 dc가 선택하고 메모리 dc에 비트맵이 그려짐

	//이미지 정보를 생성하자
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_FILE;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadImage(g_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;






	//파일 이름
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	m_isTrans = isTrans;
	m_transColor = transColor;

	//리소스를 얻어오는데 실패 했을시에
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(hWnd, hdc);//dc해제
	return S_OK;

}

HRESULT Image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지정보에 값이 있다면 릴리즈
	if (m_imageInfo != nullptr) release();
	//DC가져오기 현재 윈도우에 대한 화면 DC를 임시적으로 받아옴
	HDC hdc = GetDC(hWnd);


	//비트맵을 출력하기 위해 메모리 dc를 만들어 주는 함수
	//CreateCompatibleBitmap
	//원본 dc와 호환되는 비트맵을 생성해주는 함수
	//selectobject
	//기존의 비트맵을 핸들을 반환하고 새로운 비트맥을 메모리 dc가 선택하고 메모리 dc에 비트맵이 그려짐

	//이미지 정보를 생성하자
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

	//파일 이름
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	m_isTrans = isTrans;
	m_transColor = transColor;

	//리소스를 얻어오는데 실패 했을시에
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(hWnd, hdc);//dc해제
	return S_OK;



	return S_OK;

}

HRESULT Image::init(const char * fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지정보에 값이 있다면 릴리즈
	if (m_imageInfo != nullptr) release();
	//DC가져오기 현재 윈도우에 대한 화면 DC를 임시적으로 받아옴
	HDC hdc = GetDC(hWnd);


	//비트맵을 출력하기 위해 메모리 dc를 만들어 주는 함수
	//CreateCompatibleBitmap
	//원본 dc와 호환되는 비트맵을 생성해주는 함수
	//selectobject
	//기존의 비트맵을 핸들을 반환하고 새로운 비트맥을 메모리 dc가 선택하고 메모리 dc에 비트맵이 그려짐

	//이미지 정보를 생성하자
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

	//파일 이름
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	m_isTrans = isTrans;
	m_transColor = transColor;

	//리소스를 얻어오는데 실패 했을시에
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(hWnd, hdc);//dc해제
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
	//이미지 정보가 남아잇다면, 릴리즈를 하자
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
	//배경색 없앨거냐
	if (m_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정 색을 제외하고 복사하는 함수
		//인자값 :  복사될 장소의 DC, 복사될 좌표의 시작점 X와 Y, 복사될 이미지의 가로크기와 세로크기, 복사될 대상의 DC, 복사시작지점 X와Y, 복사 영역의 가로크기, 세로크기, 복사할때의 제외할 색상
		GdiTransparentBlt(hdc, 0, 0,
			m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, m_imageInfo->width,
			m_imageInfo->height, m_transColor);
	}
	//배경색 안날리고 원본이미지 그대로 뽑아낼거냐
	else
	{
		// SRCCOPY: 복사해주는 놈, 가로세로를 재정의 해서 복사함
		// DC간 영역끼리 고속복사 하는 녀석
		BitBlt(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, SRCCOPY);


	}

}

void Image::render(HDC hdc, int destX, int destY)
{
	//배경색 없앨거냐
	if (m_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정 색을 제외하고 복사하는 함수
		//인자값 :  복사될 장소의 DC, 복사될 좌표의 시작점 X와 Y, 복사될 이미지의 가로크기와 세로크기, 복사될 대상의 DC, 복사시작지점 X와Y, 복사 영역의 가로크기, 세로크기, 복사할때의 제외할 색상
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
	//배경색 안날리고 원본이미지 그대로 뽑아낼거냐
	else
	{
		// SRCCOPY: 복사해주는 놈, 가로세로를 재정의 해서 복사함
		// DC간 영역끼리 고속복사 하는 녀석
		BitBlt(hdc, destX, destY, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, SRCCOPY);

	}
}

void Image::frameRender(HDC hdc, int destX, int destY)
{
	//배경색 없앨거냐
	if (m_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정 색을 제외하고 복사하는 함수
		//인자값 :  복사될 장소의 DC, 복사될 좌표의 시작점 X와 Y, 복사될 이미지의 가로크기와 세로크기, 복사될 대상의 DC, 복사시작지점 X와Y, 복사 영역의 가로크기, 세로크기, 복사할때의 제외할 색상
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			m_imageInfo->frameWidth,
			m_imageInfo->frameHeight,
			m_imageInfo->hMemDC,	//복사될 대상 DC
			m_imageInfo->currentFrameX * m_imageInfo->frameWidth, //복사 시작지점
			m_imageInfo->currentFrameY * m_imageInfo->frameHeight, //복사 시작지점
			m_imageInfo->frameWidth, //복사 영역 가로크기
			m_imageInfo->frameHeight, //복사 영역 세로크기
			m_transColor);
	}
	//배경색 안날리고 원본이미지 그대로 뽑아낼거냐
	else
	{
		// SRCCOPY: 복사해주는 놈, 가로세로를 재정의 해서 복사함
		// DC간 영역끼리 고속복사 하는 녀석
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

		//배경색 없앨거냐
		if (m_isTrans)
		{
			//GdiTransparentBlt : 비트맵을 불러올때 특정 색을 제외하고 복사하는 함수
			//인자값 :  복사될 장소의 DC, 복사될 좌표의 시작점 X와 Y, 복사될 이미지의 가로크기와 세로크기, 복사될 대상의 DC, 복사시작지점 X와Y, 복사 영역의 가로크기, 세로크기, 복사할때의 제외할 색상
			GdiTransparentBlt(
				hdc,
				destX,
				destY,
				m_imageInfo->frameWidth,
				m_imageInfo->frameHeight,
				m_imageInfo->hMemDC,	//복사될 대상 DC
				m_imageInfo->currentFrameX * m_imageInfo->frameWidth, //복사 시작지점
				m_imageInfo->currentFrameY * m_imageInfo->frameHeight, //복사 시작지점
				m_imageInfo->frameWidth, //복사 영역 가로크기
				m_imageInfo->frameHeight, //복사 영역 세로크기
				m_transColor);
		}
		//배경색 안날리고 원본이미지 그대로 뽑아낼거냐
		else
		{
			// SRCCOPY: 복사해주는 놈, 가로세로를 재정의 해서 복사함
			// DC간 영역끼리 고속복사 하는 녀석
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


