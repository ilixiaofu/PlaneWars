#include "MyWindow.h"
#include "resource.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)

{
	MyWindow myWindow(hInstance);
	// ��ʼ��ȫ���ַ���
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PLANEWARS, szWindowClass, MAX_LOADSTRING);
	HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLANEWARS));
	HICON hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	myWindow.InitWindowInstance(szWindowClass, szTitle, hIcon, hIconSm);
	return myWindow.exec();
}