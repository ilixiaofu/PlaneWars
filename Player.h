#ifndef PLAYER
#define PLAYER

#include <Windows.h>
#include <vector>
#include "PlayerBullet.h"

typedef struct _Direct
{
	bool UP;
	bool DOWN;
	bool LEFT;
	bool RIGHT;
} Direct;

class Player
{
public:
	Player(int cx, int cy, int iWidth, int iHeight);
	virtual ~Player();
	void move(int step, int width, int height);
	void shoot();

public:
	int cx;
	int cy;
	int width;
	int height;
	static HBITMAP hbmp_f;
	static HBITMAP hbmp_b;
	Direct _mDirect{false};
	bool isShoot{false};
	std::vector<PlayerBullet> bullets;
};

#endif // !PLAYER