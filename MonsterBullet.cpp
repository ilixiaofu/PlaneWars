#include "MonsterBullet.h"
#include "resource.h"
#include <mutex>

std::once_flag MonsterBullet_flag;
HBITMAP MonsterBullet::hbmp;

MonsterBullet::MonsterBullet(int cx, int cy, int iWidth, int iHeight) :cx(cx), cy(cy), width(iWidth), height(iHeight)
{
	std::call_once(MonsterBullet_flag, [this] {
		HINSTANCE hInstance = (HINSTANCE)GetModuleHandleW(NULL);
		this->hbmp = ::LoadBitmapW(hInstance, MAKEINTRESOURCE(IDB_BITMAP_MONSTER_BULLET));
	});
}
MonsterBullet::~MonsterBullet()
{
}
void MonsterBullet::move(int step)
{
	this->cy += step;
}
