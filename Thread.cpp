#include "Thread.h"

Thread::Thread() : hThread(NULL), _id(0), fun(nullptr)
{
}

Thread::Thread(std::function<void(void)> fun) : hThread(NULL), _id(0), fun(fun)
{
}

Thread::~Thread()
{
	TerminateThread(this->hThread, 0);
	CloseHandle(this->hThread);
}

void Thread::start()
{
	this->hThread = CreateThread(NULL, 0, Thread::ThreadPro, this, 0, &(this->_id));
}

DWORD WINAPI Thread::ThreadPro(LPVOID lpThreadParameter)
{
	Thread* mThread = (Thread*)lpThreadParameter;
	mThread->run();
	// 终止线程 会清理当前线程堆栈
	//ExitThread(0);
	return 0;
}

void Thread::run()
{
	if (fun)
	{
		this->fun();
	}
}

int Thread::suspend()
{
	return SuspendThread(this->hThread);
}
int Thread::resume()
{
	return ResumeThread(this->hThread);
}
int Thread::join()
{
	return WaitForSingleObject(this->hThread, INFINITE);
}