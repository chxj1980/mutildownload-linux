/*
	Created by: long;
	Edit:		2017.12.9,10:32;
*/

//ϵͳͷ�ļ�
#include  <windows.h>
#include <wingdi.h>
#include <Gdiplus.h>
#include <WinUser.h>
#include <atlimage.h>

//�Զ��庯��ͷ�ļ�
#include "ScreenCapture.h"
#include "resource.h"

//���������ռ�
using namespace Gdiplus;

//�꣬�ַ�����
#define MAX_LOADSTRING 100

//�����ȼ�
#define ID_CHANGE 1234
#define ID_HIDEWND 2468

//ȫ�ֱ���
//���������
HINSTANCE gInst;
TCHAR	  szTitle[MAX_LOADSTRING];
TCHAR     szWindowClass[MAX_LOADSTRING];
HWND      gNowWnd;

//�����������
PROCESS_INFORMATION gProcessInfo;
STARTUPINFO			gStartUpInfo;
HDESK				gHDesk;
HDESK				gOriginalThread;
HDESK				gOriginalInput;
BOOL				gIsInOriginalWnd;
BOOL				gIsShowWindow;

//�������
CaptureData gCapData;
CImage		gImage;
BOOL		gBIsMining;

//��Ϣ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//ʵ����
BOOL	InitInstance(HINSTANCE, int);

//ע�ắ��
ATOM   MyRegisterClass(HINSTANCE);

//���ں���
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

//������������
VOID	CreateNewVirtualDesk();

//���ش���
void HideNowWnd();

//�л���������
void ChangeDesktop();

//����CImage����
VOID    SetImage(const CString & strPath) { if (!gImage.IsNull()) gImage.Destroy(); HRESULT hr = gImage.Load(strPath);}

//������
INT_PTR WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//���Ծ���
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//��Ϣ�ȱ����������Լ���Ա��ʼ��
	MSG msg;
	HACCEL hAccelTable;
	gBIsMining = FALSE;
	gNowWnd = NULL;
	gIsInOriginalWnd = TRUE;
	gIsShowWindow = TRUE;

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDS_VIRTUALDESKTOP, szWindowClass, MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nShowCmd)) return FALSE;

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDS_VIRTUALDESKTOP));
	::RegisterHotKey(gNowWnd, ID_CHANGE, MOD_ALT, 'F');
	::RegisterHotKey(gNowWnd, ID_HIDEWND, MOD_ALT, 'T');
	SetWindowPos(gNowWnd, HWND_TOPMOST, 0, 0, 300, 300, SWP_NOMOVE | SWP_NOREDRAW);

	//����Ϣѭ��
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	gInst = hInstance;
	gNowWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!gNowWnd) return FALSE;
	ShowWindow(gNowWnd, nCmdShow);
	UpdateWindow(gNowWnd);
	return TRUE;
}

void ScreenCut()
{
	ConfigureCapture(gNowWnd, &gCapData);
	ShowWindow(gNowWnd, SW_HIDE);
	Sleep(500);
	CaptureScreen(&gCapData);
	ShowWindow(gNowWnd, SW_SHOW);
	gBIsMining = FALSE;
	if(gCapData.szCaptureFilename[0] != '\0')
	{
		CString strPathName(gCapData.szCapturePath);
		if (strPathName.Right(1) != "\\")
			strPathName += '\\';
		strPathName += gCapData.szCaptureFilename;
		SetImage(strPathName);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lPraram)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(lPraram);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(gInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_NEWDESK:
			CreateNewVirtualDesk();
			break;
		case ID_SCREENCUT:
			ScreenCut();
			break;
		default:
			DefWindowProc(hWnd, message, wParam, lPraram);
			break;
		}
	case WM_PAINT:
	{
		if (gImage.IsNull())
			return S_FALSE;
		hdc = BeginPaint(hWnd, &ps);
		CRect rect;
		GetClientRect(hWnd, &rect);
		HWND deskHwnd;
		deskHwnd = GetDesktopWindow();
		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, rect.Width(), rect.Height());
		Ellipse(hdc, 0, 0, rect.Width(), rect.Height());
		Ellipse(hdc, rect.Width() / 4, rect.Height() / 4,  rect.Width() / 4 * 3, rect.Height() / 4 * 3);

		gImage.StretchBlt(hdc, rect);
		BitBlt(hdc, 0, 0, rect.Width(), rect.Height(), hdc, 0, 0, SRCCOPY);
	}
	EndPaint(hWnd, &ps);
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_HOTKEY:
		wmId = LOWORD(wParam);
		switch (wmId)
		{
		case ID_CHANGE:
			ChangeDesktop();
			break;
		case ID_HIDEWND:
			HideNowWnd();
			break;
		default:
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lPraram);
		break;
	}
	return S_OK;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = WndProc;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VIRTUALDESKTOP));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = szWindowClass;
	wcex.lpszMenuName = (MAKEINTRESOURCE(IDR_MENU1));
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_VIRTUALDESKTOP));
	return RegisterClassEx(&wcex);
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	default:
		break;
	}
	return (INT_PTR)FALSE;
}

VOID CreateNewVirtualDesk()
{
	gHDesk = CreateDesktop(L"VirtualDesk", NULL, NULL, 0, GENERIC_ALL, NULL);
	if (gHDesk == NULL) return;

	//��ʼ�����̽ṹ��
	ZeroMemory(&gStartUpInfo, sizeof(gStartUpInfo));
	ZeroMemory(&gProcessInfo, sizeof(gProcessInfo));
	gStartUpInfo.cb = sizeof(gStartUpInfo);
	gStartUpInfo.lpDesktop = L"VirtualDesk";

	//��¼ԭʼ������
	gOriginalThread = GetThreadDesktop(GetCurrentThreadId());
	gOriginalInput = OpenInputDesktop(0, FALSE, DESKTOP_SWITCHDESKTOP);

	CreateProcess(L"notepad", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &gStartUpInfo, &gProcessInfo);

	gIsInOriginalWnd = FALSE;
	SetThreadDesktop(gHDesk);
	SwitchDesktop(gHDesk);
}

void HideNowWnd()
{
	if (gIsShowWindow)
		AnimateWindow(gNowWnd, 521, AW_BLEND | AW_HIDE);
	else
	{
		AnimateWindow(gNowWnd, 521, AW_BLEND);
		CRect rect;
		GetWindowRect(gNowWnd, rect);
		InvalidateRect(gNowWnd, rect, FALSE);
	}
	gIsShowWindow = !gIsShowWindow;
}

void ChangeDesktop()
{
	if (gIsInOriginalWnd)
	{
		gHDesk = CreateDesktop(L"VirtualDesk", NULL, NULL, 0, GENERIC_ALL, NULL);
		SetThreadDesktop(gHDesk);
		SwitchDesktop(gHDesk);
	}
	else
	{
		SetThreadDesktop(gOriginalThread);
		SwitchDesktop(gOriginalInput);
		CloseDesktop(gHDesk);
	}
	gIsInOriginalWnd = !gIsInOriginalWnd;
}
