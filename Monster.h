#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <Windows.h>
#include <vector>
#include "MonsterBullet.h"

class Monster
{
public:
	Monster(int cx, int cy, int iWidth, int iHeight);
	virtual ~Monster();
	void move(int boundary, int step);
	void shoot();

public:
	int cx;
	int cy;
	int width;
	int height;
	static HBITMAP hbmp_f;
	static HBITMAP hbmp_b;
	int ditect{1};
	std::vector<MonsterBullet> bullets;
};

#endif // _MONSTER_H_