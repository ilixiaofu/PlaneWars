#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <Windows.h>

class Background
{
public:
	Background(int cx, int cy, int iWidth, int iHeight);
	virtual ~Background();
	void scrollBackground(int boundary, int cy);
public:
	int cx;
	int cy;
	int width;
	int height;
	static HBITMAP hbmp;
};

#endif // _BACKGROUND_H_