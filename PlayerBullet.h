#ifndef _PLAYER_BULLET_H
#define _PLAYER_BULLET_H

#include <Windows.h>


class PlayerBullet
{
public:
	PlayerBullet(int cx, int cy, int iWidth, int iHeight);
	virtual ~PlayerBullet();
	void move(int step);

public:
	int cx;
	int cy;
	int width;
	int height;
	static HBITMAP hbmp;
};

#endif