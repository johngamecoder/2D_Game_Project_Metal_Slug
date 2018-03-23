#pragma once
#define SAFE_DELETE(p)				{if(p) {delete	 (p);   (p)=NULL;}}
class Image
{
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE, //
		LOAD_FILE,
		LOAD_EMPTY,
		LOAD_END,
	};

	typedef struct tagImage
	{
		DWORD resID;		//리소스 아이디
		HDC hMemDC;			//메모리 DC
		HBITMAP hBit;		//비트맵(새로운 비트맵 핸들)
		HBITMAP hOBit;		//올드 비트맵(기존 비트맵 핸들)
		float x;			//좌표
		float y;			//좌표
		int width;			//이미지 가로크기
		int height;			//세로
		int currentFrameX;	//현재 프레임x
		int currentFrameY;	//현재 프레임y
		int maxFrameX;		//최대 프레임x
		int maxFrameY;		//현재 프레임y
		int frameWidth;
		int frameHeight;

		BYTE loadType;		//타입

		tagImage()
		{
			resID = 0;
			hMemDC = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

public:
	Image();
	~Image();
	RECT RectMakeCenter(int x, int y, int width, int height)
	{
		RECT rc = { x - (width / 2),y - (height / 2), x + (width / 2), y + (height / 2) };


		return rc;
	}
	//빈 비트맵 초기화
	HRESULT init(int width, int heigt);
	//이미지 리소스 초기화
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	//이미지 파일 초기화
	//HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char * fileName, int width, int height, int loc, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	//프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	HRESULT init(const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	//투명키 세팅
	void setTransColor(bool isTrans, COLORREF transColor);

	//릴리즈
	void release();
	
	//그리는 녀석(일반 렌더)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);

	//프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);


	//DC를 얻어온다.
	inline HDC getMemDC() { return m_imageInfo->hMemDC; }
	
	//이미지 좌표 x 얻기
	inline float getX() { return m_imageInfo->x; }
	inline void setX(float x) { m_imageInfo->x = x; }
	
	//이미지 좌표 y 얻기
	inline float getY() { return m_imageInfo->y; }
	inline void setY(float y) { m_imageInfo->y = y; }

	//이미지 센터 좌표 세팅
	inline void setCenter(float x, float y)
	{
		m_imageInfo->x = x - (m_imageInfo->width / 2);
		m_imageInfo->y = y - (m_imageInfo->height / 2);

	}

	//가로 세로 크기 얻기
	inline int getWidth() { return m_imageInfo->width; }
	inline int getHeight() { return m_imageInfo->height; }

	//바운딩 박스(충돌용)
	inline RECT getBoundingBox()
	{
		RECT rc = RectMakeCenter(m_imageInfo->x, m_imageInfo->y, m_imageInfo->width, m_imageInfo->height);
	}

	inline int getFrameX() { return m_imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		m_imageInfo->currentFrameX = frameX;
		if (frameX > m_imageInfo->maxFrameX)
		{
			m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
		}
	}

	inline int getFrameY() { return m_imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		m_imageInfo->currentFrameY = frameY;
		if (frameY > m_imageInfo->maxFrameY)
		{
			m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
		}
	}

	//1프레임 가로세로 크기
	inline int getFrameWidth() { return m_imageInfo->frameWidth; }
	inline int getFrameHeight() { return m_imageInfo->frameHeight; }

	//맥스 프레임
	inline int getMaxFrameX() { return m_imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return m_imageInfo->maxFrameY; }


private:
	LPIMAGE_INFO m_imageInfo; //이미지 정보
	char* m_fileName;//이미지 이름
	bool m_isTrans; //
	COLORREF m_transColor; //
};

