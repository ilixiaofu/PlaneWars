#ifndef _CRITICAL_SECTION_H_
#define _CRITICAL_SECTION_H_

#include <windows.h>

class CriticalSection
{
public:
	CriticalSection();
	virtual ~CriticalSection();

	void lock();
	void unlock();
	void destroy();

	CRITICAL_SECTION getCriticalSection();

private:
	CRITICAL_SECTION cs;
};

#endif