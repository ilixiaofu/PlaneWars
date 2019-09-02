#include "Monster.h"
#include "resource.h"
#include <mutex>

std::once_flag Monster_flag;
HBITMAP Monster::hbmp_f;
HBITMAP Monster::hbmp_b;

Monster::Monster(int cx, int cy, int iWidth, int iHeight) :cx(cx), cy(cy), width(iWidth), height(iHeight)
{
	std::call_once(Monster_flag, [this] {
		HINSTANCE hInstance = (HINSTANCE)GetModuleHandleW(NULL);
		this->hbmp_f = ::LoadBitmapW(hInstance, MAKEINTRESOURCE(IDB_BITMAP_MONSTER_F));
		this->hbmp_b = ::LoadBitmapW(hInstance, MAKEINTRESOURCE(IDB_BITMAP_MONSTER_B));
	});
}
Monster::~Monster()
{
}
void Monster::move(int boundary, int step)
{
	this->cx = this->cx + step * ditect;

	if (this->cx < 0)
	{
		ditect = 1;
	}
	if (this->cx > boundary)
	{
		ditect = -1;
	}
}

void Monster::shoot()
{
	int x = this->cx + this->width / 2 - 5;
	int y = this->height - 35;
	MonsterBullet monsterBullet(x, y, 15, 60);
	this->bullets.push_back(monsterBullet);
}
