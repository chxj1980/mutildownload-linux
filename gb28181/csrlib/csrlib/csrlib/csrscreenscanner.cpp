#include "csrscreenscanner.h"
#include "csrscreencututils.h"


#define BUFFER_SIZE 1024

//�������ܶ�
DWORD WINAPI udpscreenserver(LPWORD lpParam)
{
	WORD wVersionRequested;
	WSADATA wsadata;
	wVersionRequested = MAKEWORD(1, 1);
	int err = WSAStartup(wVersionRequested, &wsadata);
	if (err != 0)return 1;
	if (LOBYTE(wsadata.wVersion) != 1 || HIBYTE(wsadata.wVersion) != 1)
	{
		WSACleanup();
		return 1;
	}

	//����socket
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);

	//������ַ�˿�
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	//��
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[200];
	char buffer[BUFFER_SIZE];
	while (1)
	{
		//�Ƚ����ļ�����
		recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &len);
		//�ٽ����ļ�����
		//sendto(sockSrv, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrClient, len);
		//���ļ���׼��д��  
		FILE * fp = fopen(recvBuf, "wb");
		if (NULL == fp)
		{
			printf("File: %s Can Not Open To Write\n", recvBuf);
			system("pause");
			exit(1);
		}
		else
		{
			memset(buffer, 0, BUFFER_SIZE);
			int length = 0;
			while ((length = recv(sockSrv, buffer, BUFFER_SIZE, 0)) > 0)
			{
				if (buffer[0] == 'q')
					break;
				if (fwrite(buffer, sizeof(char), length, fp) < length)
				{
					printf("File: %s Write Failed\n", recvBuf);
					break;
				}
				memset(buffer, 0, BUFFER_SIZE);
			}

			printf("Receive File: %s From Server Successful!\n", recvBuf);
		}
		fclose(fp);
		break;
	}
	closesocket(sockSrv);
	WSACleanup();
	return NULL;
}


//���������
DWORD WINAPI udpscreenclient(LPWORD lpParam)
{
	CaptureData* lpData = (CaptureData*)lpParam;
	//�ȴ���socket��ز���

	//����ѭ�����ֱ�ӽ���
	WORD wVersionRequested;
	WSADATA wsadata;
	wVersionRequested = MAKEWORD(1, 1);
	int err = WSAStartup(wVersionRequested, &wsadata);
	if (err != 0)return 1;
	if (LOBYTE(wsadata.wVersion) != 1 || HIBYTE(wsadata.wVersion) != 1)
	{
		WSACleanup();
		return 1;
	}

	//����socket����
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	//��ʼ����ַ�ӿ�
	SOCKADDR_IN addrClient;
	addrClient.sin_addr.S_un.S_addr = inet_addr("192.168.100.24");
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(6000);
	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[200];
	char buffer[BUFFER_SIZE];
	int len = sizeof(SOCKADDR);
	while (1)
	{ 
		std::string strFilePath = lpData->szCapturePath;
		strFilePath += "\\";
		strFilePath += lpData->szCaptureFilename;

		//�ȷ����ļ�����
		sendto(sockClient, lpData->szCaptureFilename, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrClient, len);

		//�ٷ����ļ�����
		FILE * fp = fopen(strFilePath.c_str(), "rb");
		if (NULL == fp)
		{
			printf("File: %s Can Not Open To Write\n", strFilePath.c_str());
			system("pause");
			exit(1);
		}
		else
		{
			memset(buffer, 0, BUFFER_SIZE);
			int length = 0;

			while ((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0)
			{
				if (sendto(sockClient, buffer, length, 0, (SOCKADDR*)&addrClient, len) < 0)
				{
					printf("Send File: %s Failed\n", lpData->szCaptureFilename);
					break;
				}
				memset(buffer, 0, BUFFER_SIZE);
			}

			fclose(fp);
			printf("File: %s Transfer Successful!\n", lpData->szCaptureFilename);
		}
		
		//���ͽ�����
		strcpy(buffer, "q");
		sendto(sockClient, buffer, 10, 0, (SOCKADDR*)&addrClient, len);
	    fclose(fp);
		break;
	}
	closesocket(sockClient);
	WSACleanup();
	return NULL;
}
#undef BUFFER_SIZE

