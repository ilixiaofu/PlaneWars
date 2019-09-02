#ifndef _THREAD_
#define _THREAD_

#include <Windows.h>
#include <functional>

class Thread
{
public:
	Thread();
	Thread(std::function<void(void)> fun);
	virtual ~Thread();
	void start();
	int suspend();
	int resume();
	int join();

protected:
	virtual void run();

private:
	static DWORD WINAPI ThreadPro(LPVOID lpThreadParameter);

private:
	HANDLE hThread;
	unsigned long _id;
	std::function<void(void)> fun;
};

#endif // _THREAD_