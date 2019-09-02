#include "CriticalSection.h"

CriticalSection::CriticalSection()
{
	// ��ʼ���ٽ���
	InitializeCriticalSection(&this->cs);
}

CriticalSection::~CriticalSection()
{
	this->destroy();
}

/*�����ٽ���*/
void CriticalSection::lock()
{
	EnterCriticalSection(&this->cs);
}

/*�뿪�ٽ���*/
void CriticalSection::unlock()
{
	LeaveCriticalSection(&this->cs);
}

/*�����ٽ���*/
void CriticalSection::destroy()
{
	DeleteCriticalSection(&this->cs);
}

CRITICAL_SECTION CriticalSection::getCriticalSection()
{
	return this->cs;
}
