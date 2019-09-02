#include "MyWindow.h"
#include "Background.h"
#include "Monster.h"
#include "Player.h"
#include "Thread.h"
#include "resource.h"
#include "CriticalSection.h"
#include "Music.h"

Thread* gthread1, * gthread2, * gthread3, * gthread4, * gthread5;
CriticalSection* gcs1, *gcs2;

Background* gBackgroundA, * gBackgroundB;
Monster* gmonster;
Player* gplayer;
Music* gMusic;

VOID CALLBACK TimerProcedure(HWND hwnd, UINT message, UINT_PTR uTimerID, DWORD lParam)
{
	// HDC hdc;
	// hdc = GetDC(hwnd);
	// ReleaseDC(hwnd, hdc);
	// PrintWindow(hWnd, );
	//HBITMAP hbmp = (HBITMAP)LoadImageW(hInstance, MAKEINTRESOURCE(IDB_BITMAP_BGIMAGE), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// HWND hq=FindWindow("kwmusicmaindlg",NULL);
	// HWND hd=GetDesktopWindow();
	// MoveWindow(hq,100,100,w,h,false);
	//GetWindowRect(hq, &rect);
	InvalidateRect(hwnd, NULL, FALSE);
	UpdateWindow(hwnd);
}

MyWindow::MyWindow(HINSTANCE hInstance) :MainWindow(hInstance)
{
}

MyWindow::~MyWindow()
{
}

LRESULT MyWindow::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		this->OnResize(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_ERASEBKGND:
		return 0;
	case WM_KEYUP:
		this->OnKeyUp(wParam);
		return 0;
	case WM_KEYDOWN:
		this->OnKeyDown(wParam);
		return 0;
	default:
		return MainWindow::HandleMessage(hWnd, message, wParam, lParam);
	}
}

void MyWindow::OnDestroy()
{
	KillTimer(this->getHWnd(), 1);
	delete gthread1;
	delete gthread2;
	delete gthread3;
	delete gthread4;
	delete gthread5;
	delete gcs1;
	delete gcs2;
	delete gBackgroundA;
	delete gBackgroundB;
	delete gmonster;
	delete gplayer;
	MainWindow::OnDestroy();
}

void MyWindow::OnResize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void MyWindow::OnCreate()
{
	RECT rect;
	GetClientRect(this->getHWnd(), &rect);
	this->width = rect.right - rect.left;
	this->height = rect.bottom - rect.top;

	gcs1 = new CriticalSection();
	gcs2 = new CriticalSection();

	gBackgroundA = new Background(0, 0, 1280, 800);
	gBackgroundB = new Background(0, 0 - this->height, 1280, 800);

	gmonster = new Monster(this->width / 4, 2, 466, 140);

	gplayer = new Player(this->width / 2 - 55 / 2, this->height - 55, 55, 55);

	SetTimer(this->getHWnd(), 1, 5, TimerProcedure);

	gthread1 = new Thread([=]() {
		while (true)
		{
			gBackgroundA->scrollBackground(this->height, 0 - this->height);
			gBackgroundB->scrollBackground(this->height, 0 - this->height);
			gmonster->move(this->width - gmonster->width, 2);
			Sleep(15);
		}
		});
	gthread1->start();

	gthread2 = new Thread([=]() {
		while (true)
		{
			gcs1->lock();
			gmonster->shoot();
			gcs1->unlock();
			Sleep(700);
		}
	});
	gthread2->start();

	gthread3 = new Thread([=]() {
		while (true)
		{
			gplayer->move(4, this->width - gplayer->width, this->height - gplayer->height);
			Sleep(5);
		}
		});
	gthread3->start();

	gthread4 = new Thread([=]() {
		while (true)
		{
			gcs1->lock();
			for (auto it = gmonster->bullets.begin(); it != gmonster->bullets.end();)
			{
				it->move(5);
				if (it->cy > this->height) {
					it = gmonster->bullets.erase(it);
				}
				else {
					++it;
				}
			}
			gcs1->unlock();
			Sleep(15);
		}
		});
	gthread4->start();

	gthread5 = new Thread([=]() {
		while (true)
		{
			gcs2->lock();
			for (auto it = gplayer->bullets.begin(); it != gplayer->bullets.end();)
			{
				it->move(-5);
				if (it->cy < 0) {
					it = gplayer->bullets.erase(it);
				}
				else {
					++it;
				}
			}
			gcs2->unlock();
			Sleep(15);
		}
		});
	gthread5->start();
}

VOID DrawHBitmapOnMDC(HDC mdc, HDC bufdc, int xDes, int yDes, int widthSrc, int heightSrc, HBITMAP hbmp, DWORD rop)
{
	SelectObject(bufdc, hbmp);
	BitBlt(mdc, xDes, yDes, widthSrc, heightSrc, bufdc, 0, 0, rop);
}

template<class T>
VOID DrawBullet(HDC mdc, HDC bufdc, std::vector<T> &bullets)
{
	for (auto it = bullets.begin(); it!= bullets.end(); ++it)
	{
		DrawHBitmapOnMDC(mdc, bufdc, it->cx, it->cy, it->width, it->height, it->hbmp, SRCCOPY);
	}
}

void MyWindow::OnPaint(HDC hdc, PAINTSTRUCT ps)
{
	int w = ps.rcPaint.right - ps.rcPaint.left;
	int h = ps.rcPaint.bottom - ps.rcPaint.top;
	HDC mdc = CreateCompatibleDC(hdc);
	HDC bufdc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(mdc, hbmp);

	DrawHBitmapOnMDC(mdc, bufdc, gBackgroundA->cx, gBackgroundA->cy, gBackgroundA->width, gBackgroundA->height, gBackgroundA->hbmp, SRCCOPY);
	DrawHBitmapOnMDC(mdc, bufdc, gBackgroundB->cx, gBackgroundB->cy, gBackgroundB->width, gBackgroundB->height, gBackgroundB->hbmp, SRCCOPY);

	DrawHBitmapOnMDC(mdc, bufdc, gmonster->cx, gmonster->cy, gmonster->width, gmonster->height, gmonster->hbmp_b, SRCAND);
	DrawHBitmapOnMDC(mdc, bufdc, gmonster->cx, gmonster->cy, gmonster->width, gmonster->height, gmonster->hbmp_f, SRCPAINT);

	DrawHBitmapOnMDC(mdc, bufdc, gplayer->cx, gplayer->cy, gplayer->width, gplayer->height, gplayer->hbmp_b, SRCAND);
	DrawHBitmapOnMDC(mdc, bufdc, gplayer->cx, gplayer->cy, gplayer->width, gplayer->height, gplayer->hbmp_f, SRCPAINT);

	DrawBullet(mdc, bufdc, gmonster->bullets);
	DrawBullet(mdc, bufdc, gplayer->bullets);

	BitBlt(hdc, 0, 0, w, h, mdc, 0, 0, SRCCOPY);

	DeleteObject(hbmp);
	DeleteDC(bufdc);
	DeleteDC(mdc);
	
	//::Rectangle(hdc, 0, 0, 200, 200);
}

void MyWindow::OnKeyUp(WPARAM keyCode)
{
	switch (keyCode)
	{
	case 'w':
	case 'W':
	case VK_UP:
	{
		gplayer->_mDirect.UP = FALSE;
		break;
	}
	case 's':
	case 'S':
	case VK_DOWN:
	{
		gplayer->_mDirect.DOWN = FALSE;
		break;
	}

	case 'a':
	case 'A':
	case VK_LEFT:
	{
		gplayer->_mDirect.LEFT = FALSE;
		break;
	}
	case 'd':
	case 'D':
	case VK_RIGHT:
	{
		gplayer->_mDirect.RIGHT = FALSE;
		break;
	}
	case VK_SPACE:
	{
		gplayer->isShoot = false;
		gcs2->lock();
		gplayer->shoot();
		gcs2->unlock();
		break;
	}
	}
}
void MyWindow::OnKeyDown(WPARAM keyCode)
{
	switch (keyCode)
	{
		case 'w':
		case 'W':
		case VK_UP:
		{
			gplayer->_mDirect.UP = TRUE;
			break;
		}
		case 's':
		case 'S':
		case VK_DOWN:
		{
			gplayer->_mDirect.DOWN = TRUE;
			break;
		}

		case 'a':
		case 'A':
		case VK_LEFT:
		{
			gplayer->_mDirect.LEFT = TRUE;
			break;
		}
		case 'd':
		case 'D':
		case VK_RIGHT:
		{
			gplayer->_mDirect.RIGHT = TRUE;
			break;
		}

		case VK_SPACE:
		{
			gplayer->isShoot = true;
			break;
		}
	}
}