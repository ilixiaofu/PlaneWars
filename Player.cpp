#include "Player.h"
#include "resource.h"
#include <mutex>
#include "CriticalSection.h"

std::once_flag Player_flag;
HBITMAP Player::hbmp_f;
HBITMAP Player::hbmp_b;

extern CriticalSection* gcs2;

Player::Player(int cx, int cy, int iWidth, int iHeight) :cx(cx), cy(cy), width(iWidth), height(iHeight)
{
	std::call_once(Player_flag, [this] {
		HINSTANCE hInstance = (HINSTANCE)GetModuleHandleW(NULL);
		this->hbmp_f = ::LoadBitmapW(hInstance, MAKEINTRESOURCE(IDB_BITMAP_PLANE_F));
		this->hbmp_b = ::LoadBitmapW(hInstance, MAKEINTRESOURCE(IDB_BITMAP_PLANE_B));
	});
}
Player::~Player()
{

}
void Player::move(int step, int width, int height)
{
	if (this->_mDirect.UP)
	{
		this->cy -= step;
	}

	if (this->_mDirect.DOWN)
	{
		this->cy += step;
	}

	if (this->_mDirect.LEFT)
	{
		this->cx -= step;
	}

	if (this->_mDirect.RIGHT)
	{
		this->cx += step;
	}

	if (this->isShoot)
	{
		static int delay = 0;
		delay++;
		if (delay % 10 == 0)
		{
			delay = 0;
			gcs2->lock();
			this->shoot();
			gcs2->unlock();
		}
	}

	if (this->cx < 0)
	{
		this->cx = 0;
	}

	if (this->cx > width)
	{
		this->cx = width;
	}

	if (this->cy < 0)
	{
		this->cy = 0;
	}

	if (this->cy > height)
	{
		this->cy = height;
	}
}
void Player::shoot()
{
	int x = this->cx + 3;
	int y = this->cy + 10;
	PlayerBullet playerBullet1(x, y, 16, 16);
	this->bullets.push_back(playerBullet1);
	x = this->cx + this->width - 17;
	PlayerBullet playerBullet2(x, y, 16, 16);
	this->bullets.push_back(playerBullet2);
}