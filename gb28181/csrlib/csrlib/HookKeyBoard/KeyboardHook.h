#pragma once

#include <windows.h>

HHOOK g_hHook;

//��װ����
extern "C" __declspec(dllexport) BOOL WINAPI SetKeyHook(BOOL bInstall);

//���̹��Ӵ�����
LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wParam, LPARAM lParam);
