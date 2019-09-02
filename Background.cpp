#include "Background.h"
#include "resource.h"
#include <mutex>

std::once_flag Background_flag;
HBITMAP Background::hbmp;

Background::Background(int cx, int cy, int iWidth, int iHeight):cx(cx), cy(cy), width(iWidth), height(iHeight)
{
	std::call_once(Background_flag, [this] {
		HINSTANCE hInstance = (HINSTANCE)GetModuleHandleW(NULL);
		this->hbmp = ::LoadBitmapW(hInstance, MAKEINTRESOURCE(IDB_BITMAP_BGIMAGE));
	});
}

Background::~Background()
{
}

void Background::scrollBackground(int boundary, int cy)
{
	this->cy++;
	if (this->cy > boundary)
	{
		this->cy = cy;
	}
}