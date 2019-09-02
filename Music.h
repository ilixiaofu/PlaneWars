#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

class Music
{
public:
	Music();
	virtual ~Music();

	void player();
	void stop();
};

#endif