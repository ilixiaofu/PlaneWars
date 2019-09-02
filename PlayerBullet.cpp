#include "PlayerBullet.h"
#include "resource.h"
#include <mutex>

std::once_flag PlayerBullet_flag;
HBITMAP PlayerBullet::hbmp;

PlayerBullet::PlayerBullet(int cx, int cy, int iWidth, int iHeight) :cx(cx), cy(cy), width(iWidth), height(iHeight)
{
	std::call_once(PlayerBullet_flag, [this] {
		HINSTANCE hInstance = (HINSTANCE)GetModuleHandleW(NULL);
		this->hbmp = ::LoadBitmapW(hInstance, MAKEINTRESOURCE(IDB_BITMAP_PLAYER_BULLET));
	});
}
PlayerBullet::~PlayerBullet()
{

}
void PlayerBullet::move(int step)
{
	this->cy += step;
}
