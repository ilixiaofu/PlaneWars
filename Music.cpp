#include "Music.h"
#include "resource.h"

Music::Music()
{

}

Music::~Music()
{

}

void Music::player()
{
	//PlaySoundW(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_ASYNC | SND_LOOP);
	//mciSendString("open resources\\Music\\BGM.wav alias music", NULL, 0, NULL);
	//mciSendString("play music repeat", 0, 0, 0);
}
void Music::stop()
{
	//PlaySoundW(MAKEINTRESOURCE(IDB_BITMAP_PLANE_F), NULL, SND_ASYNC | SND_LOOP);
}