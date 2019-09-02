#ifndef _MONSTER_BULLET_H_
#define _MONSTER_BULLET_H_

#include <Windows.h>

class MonsterBullet
{
public:
	MonsterBullet(int cx, int cy, int iWidth, int iHeight);
	virtual ~MonsterBullet();
	void move(int step);

public:
	int cx;
	int cy;
	int width;
	int height;
	static HBITMAP hbmp;
};

#endif
