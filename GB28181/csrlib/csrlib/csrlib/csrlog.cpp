#include "csrlog.h"
#include "csrfilesystem.h"

HANDLE hOutputHandle;

/*
AllocConsole();
freopen("CONOUT$", "w", stdout);
std::cout << "This is a test info" << std::endl;
BOOL AllocConsole(void);
FILE *freopen(const char *path, const char *mode, FILE *stream);
GetConsoleScreenBufferInfo ����// �������ڴ�С����Ļ��������С����ɫ����
SetConsoleWindowInfo ���������� // �ı����̨���ڴ�С
SetConsoleScreenBufferSize���� // �ı����̨��Ļ��������С
SetConsoleTextAttribute����    // ������ɫ����
SetConsoleTitle����������������  // ���ÿ���̨���ڱ���
GetConsoleTitle����������������  // ��ȡ����̨���ڱ���
*/


bool InitLogSys()
{
	AllocConsole();//Ϊ���̴���һ���µĿ���̨
	//hOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);//��ÿ���̨������
	//freopen("CONOUT$", "w", stdout);
	//���ϵͳʱ��
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	//��ó���Ŀ¼
	std::string strLogFilePath = GetModlePath();
	char chBuf[200];
	sprintf(chBuf, "%04d-%02d-%02d-%02d-%02d-%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	strLogFilePath += chBuf;
	strLogFilePath += ".txt";
	if (freopen(strLogFilePath.c_str(), "wt", stdout) == NULL)
		return false;
	return true;
}

void LogWrite(std::string strLog)
{
	DWORD nRet = 0;
	//TCHAR buf[100] = { 0 };//��������ַ��Ļ�����
	//lstrcpy(buf, _T("Hello"));
	CString cstrLog = strLog.c_str();
	//WriteConsole(hOutputHandle, strLog.c_str(), lstrlen(cstrLog), &nRet, NULL);
	//std::cout << cstrLog << std::endl;
	printf("%s", strLog.c_str());
	std::cout << "---csrlog.end" << std::endl;
}

void EndLogSys()
{
	FreeConsole();
}

