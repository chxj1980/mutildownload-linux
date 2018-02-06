//�������Ĵ����ļ���  
/* 
message.h 
source.h 
source.cpp 
server.h 
server.cpp 
*/  
//�ͻ��˵Ĵ����ļ���  
/* 
message.h   �ͷ�������һ�� 
client.h 
client.cpp 
*/  
//message.h  
#pragma once  
#include<iostream>  
using namespace std;  
#define MAX_PACK_SIZE  10240   //���ݰ��ĳ���  
#define MAX_FILE_NAME_LENGTH 256  //�ļ����ĳ���  
#define INVALID_MSG -1       //��Ч����Ϣ  
#define MSG_FILE_LENGTH 1    //�ļ�����  
#define MSG_FILE_NAME 2    //�ļ���  
#define MSG_FILE   4     //�ļ�����  
#define MSG_READY   3     //׼������Ϣ  
#define MSG_SEND_FILE 5  //�����ļ�  
#define MSG_DOWNLOAD_FILE 6  //�����ļ�  
#define MSG_COMPLETE 7     //�����Ϣ  
class Message  
{  
public:  
    struct MsgHead     //ͷ��Ϣ  
    {  
        int msgId;    //��Ϣ��ʶ  
        MsgHead(int msg=INVALID_MSG):msgId(msg){};  
    };  
    struct MsgFileLength :public MsgHead  
    {  
        _int64 fileLength;   //�ļ�����  
        MsgFileLength():MsgHead(MSG_FILE_LENGTH){}  
    };  
    struct MsgFileName:public MsgHead  
    {  
        char fileName[MAX_FILE_NAME_LENGTH];  
        MsgFileName():MsgHead(MSG_FILE_NAME){}  
    };  
    struct MsgFile:public MsgHead  
    {  
        MsgFile():MsgHead(MSG_FILE){}  
    };  
    struct MsgReady:public MsgHead        //׼������Ϣ  
    {  
        MsgReady():MsgHead(MSG_READY){}  
    };  
    struct MsgSendFile:public MsgHead  //�����ļ���Ϣ  
    {  
        MsgSendFile():MsgHead(MSG_SEND_FILE){}  
    };  
    struct MsgDownLoadFile:public MsgHead     //�����ļ���Ϣ  
    {  
        MsgDownLoadFile():MsgHead(MSG_DOWNLOAD_FILE){}  
    };  
    struct MsgComplete:public MsgHead  
    {  
        MsgComplete():MsgHead(MSG_COMPLETE){}  
    };  
};  
//source.h   ��ȡָ���ļ����µķ���Ҫ����ļ�  
#pragma once  
#include<iostream>  
#include<fstream>  
#include<vector>  
#include<io.h>  
#include<string>  
using namespace std;  
class Source  
{  
public:  
    vector<string> catalogInfo;  
    void GetFiles(string path,string ext,vector<string> &files);//��ȡ�ļ�  
};  
//server.h  
#pragma once  
#include<iostream>  
#include<WinSock2.h>  
#include"message.h"  
#pragma comment(lib,"Ws2_32.lib")  
#define PORT 10000  
using namespace std;  
class Server  
{  
public:  
    SOCKET sd;  
    _int64 fileLength;  
    char fileName[MAX_FILE_NAME_LENGTH];  
    bool InitSock();    //��ʼwinsocket  
    SOCKET BindListen();  //�󶨼����׽���  
    SOCKET AcceptConnection(SOCKET sd);  //���տͻ���  
    bool ProcessConnection(SOCKET sd);  //��������  
    bool ReceiveFile(SOCKET sd);     //�����ļ�����  
    bool RecvFileName(SOCKET sd);     //�����ļ���  
    bool GetAndSendFileLength(SOCKET sd);    //��ȡ�ļ�����  
    bool SendFileName(SOCKET sd);    //�����ļ���  
    bool SendFile(SOCKET sd);      //�����ļ�  
    void CloseSocket();   //�ر��׽���  
};  
//source.cpp  
#pragma once  
#include<iostream>  
#include<vector>  
#include<io.h>  
#include<string>  
#include"source.h"  
using namespace std;  
void Source::GetFiles(string path,string ext,vector<string> &files)  
{  
    long hFile=0;    //�ļ����  
    _finddata_t fileInfo; //�ļ���Ϣ  
    string pathName;  
    if((hFile=_findfirst(pathName.assign(path).append("\\*").c_str(),&fileInfo))!=-1) //�ж�·���Ƿ���Ч����ȡ��һ���ļ�  
    {  
        do  
        {  
            if(fileInfo.attrib & _A_SUBDIR)   //��������ļ���  
            {  
                if(strcmp(fileInfo.name,".")!=0 && strcmp(fileInfo.name,"..")!=0)  
                {  
                    GetFiles(pathName.assign(path).append("\\").append(fileInfo.name),ext,files);  
                }  
            }  
            else  
            {  
                string filePath;  
                filePath=pathName.assign(path).append("\\").append(fileInfo.name);  
                char fileDrive[_MAX_DRIVE];  
                char fileDir[_MAX_DIR];  
                char fileName[_MAX_FNAME];  
                char fileExt[_MAX_EXT];  
                _splitpath(filePath.c_str(),fileDrive,fileDir,fileName,fileExt);  //�ֽ�·����ȡ������·���ļ�����׺  
                                if(strcmp(fileExt,ext.c_str())==0)  
                {  
                    files.push_back(filePath);  
                }  
            }  
        }while(_findnext(hFile,&fileInfo)==0);  
        _findclose(hFile);  
    }  
}  
//server.cpp  
#pragma once  
#include<iostream>  
#include<string>  
#include<fstream>  
#include<WinSock2.h>  
#include"message.h"  
#include"server.h"  
#include"source.h"  
using namespace std;  
int main()  
{  
    Server server;  
    if(!server.InitSock())   //��ʼ��ʧ��  
    {  
        cout<<"��ʼ��ʧ��"<<endl;  
    }  
    server.sd=server.BindListen();  
    if(server.sd==INVALID_SOCKET)  
    {  
        return -1;  
    }  
    SOCKET sdListen=server.AcceptConnection(server.sd);  
    if(sdListen==INVALID_SOCKET)  
    {  
        return -1;  
    }  
    while(server.ProcessConnection(sdListen))  
    {  
    }  
    server.CloseSocket();  
    return 0;  
}  
bool Server::InitSock()   //��ʼ��winsocket  
{  
    WSADATA wsData;  
    WORD wr=MAKEWORD(2,2);  
    if(WSAStartup(wr,&wsData)==0)  
    {  
        return true;  
    }  
    return false;  
}  
SOCKET Server::BindListen()  //���׽���  
{  
    SOCKET sd=socket(AF_INET,SOCK_STREAM,0);  
    if(sd==INVALID_SOCKET)  
    {  
        cout<<"�����׽���ʧ��"<<WSAGetLastError()<<endl;  
        return INVALID_SOCKET;  
    }  
    sockaddr_in sListen;  
    sListen.sin_family=AF_INET;  
    sListen.sin_addr.s_addr=htonl(INADDR_ANY);  
    sListen.sin_port=htons(PORT);  
    int nSize;  
    nSize=sizeof(sockaddr_in);  
    if(bind(sd,(sockaddr*)&sListen,nSize)==SOCKET_ERROR)  
    {  
        closesocket(sd);  
        cout<<"��ʧ��"<<WSAGetLastError()<<endl;  
        return INVALID_SOCKET;  
    }  
    if(listen(sd,10)==SOCKET_ERROR)  
    {  
        closesocket(sd);  
        cout<<"����ʧ��"<<WSAGetLastError()<<endl;  
        return INVALID_SOCKET;  
    }  
    return sd;  
      
}  
SOCKET Server::AcceptConnection(SOCKET sd)    //���տͻ���  
{  
    sockaddr_in saRemote;  
    int nSize=sizeof(sockaddr_in);  
    SOCKET sdListen=accept(sd,(sockaddr*)&saRemote,&nSize);  
    if(sdListen==INVALID_SOCKET)  
    {  
        cout<<"���տͻ���ʧ��"<<WSAGetLastError()<<endl;  
        return INVALID_SOCKET;  
    }  
    return sdListen;  
}  
bool Server::ReceiveFile(SOCKET sd)  
{  
    char buff[MAX_PACK_SIZE];  
    FILE *pFile;  
    pFile=fopen(fileName,"a+b");  
    _int64 i=0;  
    while(i+1<fileLength)  
    {  
        int nRecv=recv(sd,buff,MAX_PACK_SIZE,0);  
        if(nRecv==SOCKET_ERROR)  
        {  
           return false;  
        }  
        fwrite(buff,sizeof(char),nRecv,pFile);  
        i+=nRecv;  
        memset(buff,0,sizeof(char)*MAX_PACK_SIZE);  
    }  
    fclose(pFile);  
    return true;  
}  
void Server::CloseSocket()  
{  
    closesocket(sd);  
    WSACleanup();  
}  
bool Server::ProcessConnection(SOCKET sd)  
{  
    //----------------------------------------------  
    //���Խ�������뿴������ϵͳ������  
    int nRecvBuf=1024000;//����Ϊ1000K  
    setsockopt(sd,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));  
      //���ͻ�����  
    int nSendBuf=1024000;//����Ϊ1000K  
    setsockopt(sd,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));  
    //-------------------------------------------------------------  
    char buff[MAX_PACK_SIZE];  
    Message::MsgHead *msgHead;  
    if(recv(sd,buff,MAX_PACK_SIZE,0)==SOCKET_ERROR)  
    {  
        cout<<"����ʧ��"<<WSAGetLastError()<<endl;  
        return false;  
    }  
    msgHead=(Message::MsgHead *)&buff;  
    switch(msgHead->msgId)  
    {  
    case MSG_SEND_FILE:         //�ͻ���������������ļ�  
        cout<<"�ͻ�������������������ļ�"<<endl;  
        break;  
    case MSG_DOWNLOAD_FILE:      //�ͻ��˴ӷ����������ļ�  
        {  
            cout<<"�ͻ�������ӷ����������ļ�"<<endl;  
            Source source;      //������ȡָ���ļ����µĺ�׺Ϊjpg�ļ�  
            string sPath="E:\\ͼƬ";  
            string sExt=".jpg";  
            source.GetFiles(sPath,sExt,source.catalogInfo);  
            int nSize;  
            nSize=source.catalogInfo.size();  
            cout<<"�Ѽ���"<<nSize<<"���ļ�"<<endl;  
            char buff[MAX_PACK_SIZE];  
            for(int i=0;i<nSize;i++)   //��Ŀ¼��Ϣ���͵��ͻ���  
            {  
                strcpy(buff,source.catalogInfo[i].c_str());  
                //cout<<source.catalogInfo[i]<<endl;  
                if(send(sd,buff,MAX_PACK_SIZE,0)==SOCKET_ERROR)  
                {  
                    cout<<"����Ŀ¼��Ϣʧ��"<<WSAGetLastError()<<endl;  
                    return false;  
                }  
                Sleep(10);   //˯��10ms�ý��ն˽���Ϣȡ��  
            }  
            Message::MsgComplete msgComplete;  
            if(send(sd,(char *)&msgComplete,sizeof(Message::MsgComplete),0)==SOCKET_ERROR)  
            {  
                cout<<"���������Ϣʧ��"<<WSAGetLastError()<<endl;  
                return false;  
            }  
            Sleep(10);  
            if(!RecvFileName(sd))  
            {  
                return false;  
            }  
            Sleep(10);  
            if(!GetAndSendFileLength(sd))  
            {  
                return false;  
            }  
            Sleep(10);  
            if(!SendFileName(sd))  
            {  
                return false;  
            }  
            Sleep(10);  
            if(!SendFile(sd))  
            {  
                return false;  
            }  
        }  
        break;  
    case MSG_FILE_NAME:      //���͵��ļ���  
        {  
            Message::MsgFileName *msgFileName;  
            msgFileName=(Message::MsgFileName*)msgHead;  
            strcpy(fileName,msgFileName->fileName);  
            cout<<"�յ����������ļ���"<<fileName<<endl;  
        }  
        break;  
    case MSG_FILE_LENGTH:    //���͵��ļ�����  
        {  
            Message::MsgFileLength *msgFileLength;  
            msgFileLength=(Message::MsgFileLength *)msgHead;  
            fileLength=msgFileLength->fileLength;  
            cout<<"���յ��ļ��ĳ���Ϊ"<<fileLength<<endl;  
        }  
        break;  
    case MSG_FILE:     //���͵��ļ�����  
        {  
            cout<<"��ʼ�����ļ�"<<endl;  
            if(!ReceiveFile(sd))  
            {  
                cout<<"�����ļ�ʧ��"<<endl;  
                return false;  
            }  
        }  
        break;  
    default:  
        cout<<"�Ǳ�׼��Ϣ"<<endl;  
        return false;  
    }  
    return true;  
}  
bool Server::RecvFileName(SOCKET sd)  
{  
    //memset(fileName,0,sizeof(char)*MAX_FILE_NAME_LENGTH);  //���  
    char buff[MAX_PACK_SIZE];  
    Message::MsgFileName *msgFileName;  
    if(recv(sd,buff,MAX_PACK_SIZE,0)==SOCKET_ERROR)  
    {  
        cout<<"�����ļ���ʧ��"<<WSAGetLastError()<<endl;  
        return false;  
    }  
    msgFileName=(Message::MsgFileName *)buff;  
    strcpy(fileName,msgFileName->fileName);  
    cout<<"���յ��ļ���Ϊ"<<fileName<<endl;  
    return true;  
}  
bool Server::GetAndSendFileLength(SOCKET sd)       //��ȡ�ͻ���Ҫ���ص��ļ�����  
{  
    Message::MsgFileLength msgFileLength;  
    FILE *pFile;  
    pFile=fopen(fileName,"r+b");  
    if(pFile==NULL)  
    {  
        cout<<"���ļ�ʧ��"<<endl;  
        return false;  
    }  
    fseek(pFile,0,SEEK_END);  
    fileLength=_ftelli64(pFile);  
    fclose(pFile);  
    msgFileLength.fileLength=fileLength;  
    if(send(sd,(char*)&msgFileLength,sizeof(Message::MsgFileLength),0)==SOCKET_ERROR)  
    {  
        cout<<"�����ļ�����ʧ��"<<WSAGetLastError()<<endl;  
        return false;  
    }  
    return true;  
}  
bool Server::SendFileName(SOCKET sd)       //��ͻ��˷����ļ���  
{  
    Message::MsgFileName msgFileName;  
    char fileDrive[_MAX_DRIVE];  
    char fileDir[_MAX_DIR];  
    char Name[_MAX_FNAME];  
    char fileExt[_MAX_EXT];  
    _splitpath(fileName,fileDrive,fileDir,Name,fileExt);  
    strcat(Name,fileExt);  
    strcpy(msgFileName.fileName,Name);  
    cout<<"Ҫ���͵��ļ���Ϊ"<<Name<<endl;  
    if(send(sd,(char *)&msgFileName,sizeof(Message::MsgFileName),0)==SOCKET_ERROR)  
    {  
        cout<<"�����ļ�������"<<WSAGetLastError()<<endl;  
        return false;  
    }  
    return true;  
}  
bool Server::SendFile(SOCKET sd)  //��ͻ��˷����ļ�  
{  
    cout<<"���뵽�����ļ�����"<<endl;  
    cout<<"Ҫ���͵��ļ�Ϊ"<<fileName<<endl;  
    FILE *pFile;  
    pFile=fopen(fileName,"r+b");  
    fseek(pFile,0,SEEK_SET);   //��λ���ļ���λ��  
    _int64 i=0;  
    char buff[MAX_PACK_SIZE];  
    cout<<"Ҫ���͵��ļ�����Ϊ"<<fileLength<<endl;  
    while(i<fileLength)  
    {  
        int nSize;  
        if(i+MAX_PACK_SIZE>fileLength)  
        {  
            nSize=(int)(fileLength-i);  
        }  
        else  
        {  
            nSize=MAX_PACK_SIZE-1;  
        }  
        fread(buff,sizeof(char),nSize,pFile);  
        int nSend;  
        nSend=send(sd,buff,nSize,0);  
        if(nSend==SOCKET_ERROR)  
        {  
            cout<<"����ʧ��"<<WSAGetLastError()<<endl;  
            return false;  
        }  
        i+=nSend;  
        fseek(pFile,-(nSize-nSend),SEEK_CUR);  //��λ��ʵ���ѷ��͵���λ��  
        memset(buff,0,sizeof(char)*MAX_PACK_SIZE); //��buff���  
    }  
    fclose(pFile);  
    return true;  
}  
//client.h  
#pragma once  
#include<iostream>  
#include<fstream>  
#include<vector>  
#include<WinSock2.h>  
#pragma comment(lib,"Ws2_32.lib")  
using namespace std;  
#define SERVER_IP "127.0.0.1"  
#define PORT  10000  
class Client  
{  
public:  
    _int64 nFileLength;  
    char fileName[_MAX_FNAME+_MAX_EXT];  
    SOCKET sd;  
    bool InitSock();   //��ʼ��winsock  
    u_long ResolveAdress(char *serverIp);    //������������ַ  
    SOCKET ConnectServer(u_long serverIp,int port);//���ӷ�����  
    bool ProcessConnection(SOCKET sd);    //�ͻ��˷���������  
    void CloseSocket();         //�ͷ��׽���  
    bool SendFileLength(SOCKET sd,char *filePath);  //�����ļ�����  
    bool SendFile(SOCKET sd,char *filePath);    //�����ļ�  
    bool RecvCatalogInfo(SOCKET sd);     //����Ŀ¼��Ϣ  
    bool SendDownLoadFileName(SOCKET sd);  //����Ҫ���ص��ļ���  
    bool ReceiveFileLength(SOCKET sd);    //�����ļ�����  
    bool ReceiveFileName(SOCKET sd);   //�����ļ���  
    bool ReceiveFile(SOCKET sd);      //�����ļ�  
    //void DoWork();       //���庯��  
};  
//client.cpp  
#define _CRT_SECURE_NO_WARNINGS  
#pragma once  
#include<iostream>  
#include<vector>  
#include<WinSock2.h>  
#include"client.h"  
#include"message.h"  
using namespace std;  
int main()  
{  
    Client client;  
    if(!client.InitSock())  
    {  
        cout<<"��ʼsocketʧ��"<<endl;  
        return -1;  
    }  
    SOCKET saRemote=client.ConnectServer(client.ResolveAdress(SERVER_IP),PORT);  
    if(saRemote==INVALID_SOCKET)  
    {  
        cout<<"���ӷ�����ʧ��"<<endl;  
        return -1;  
    }  
    if(!client.ProcessConnection(saRemote))  
    {  
        return -1;  
    }  
    client.CloseSocket();  
    return 0;  
}  
bool Client::InitSock()    //��ʼsocket  
{  
    WSADATA wsData;  
    WORD wr=MAKEWORD(2,2);  
    if(WSAStartup(wr,&wsData)==0)  
    {  
        return true;  
    }  
    return false;  
}  
u_long Client::ResolveAdress(char *serverIp)   //����IP��ַ  
{  
    u_long nAddr=inet_addr(serverIp);  
    if(nAddr==INADDR_NONE)  //����serverIpʹ�õ�����������ʽ  
    {  
        hostent *ent=gethostbyname(serverIp);  
        if(ent==NULL)  
        {  
            cout<<"��ȡ����������"<<WSAGetLastError()<<endl;  
        }  
        else  
        {  
            nAddr=*((u_long *)ent->h_addr_list[0]);  
        }  
    }  
    if(nAddr==INADDR_NONE)  
    {  
        cout<<"����������ַʧ��"<<endl;  
    }  
    return nAddr;  
}  
SOCKET Client::ConnectServer(u_long serverIp,int port)   //���ӷ�����  
{  
    sd=socket(AF_INET,SOCK_STREAM,0);  
    if(sd==INVALID_SOCKET)  
    {  
        cout<<"�����׽���ʧ��"<<endl;  
        return INVALID_SOCKET;  
    }  
    sockaddr_in saServer;  
    saServer.sin_family=AF_INET;  
    saServer.sin_addr.S_un.S_addr=serverIp;  
    saServer.sin_port=htons(port);  
    if(connect(sd,(sockaddr*)&saServer,sizeof(sockaddr_in))==SOCKET_ERROR)  
    {  
        cout<<"���ӷ�����ʧ��"<<WSAGetLastError()<<endl;  
        closesocket(sd);  
        return INVALID_SOCKET;  
    }  
    return sd;  
}  
bool Client::ProcessConnection(SOCKET sd)      //����ͨ��  
{  
    //-------------------------------------------------  
    //���Խ�������뿴������ϵͳ������  
    int nRecvBuf=1024000;//����Ϊ1000K  
    setsockopt(sd,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));  
      //���ͻ�����  
    int nSendBuf=1024000;//����Ϊ1000K  
    setsockopt(sd,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));  
    //---------------------------------------------------------  
    while(true)  
    {  
        cout<<"��1��������������ļ�"<<endl;  
        cout<<"��2���ӷ����������ļ�"<<endl;  
        cout<<"��3���˳�ҵ��"<<endl;  
        int n;  
        loop:cin>>n;  
        switch(n)  
        {  
        case 1:  
            {  
                //����������ʹ����ļ���Ϣ  
                Message::MsgSendFile msgSendFile;  
                if(send(sd,(char *)&msgSendFile,sizeof(Message::MsgSendFile),0)==SOCKET_ERROR)  
                {  
                    cout<<"������Ϣʧ��"<<endl;  
                    return false;  
                }  
                Sleep(10);     //˯��10ms��֤�Է������͵���Ϣȡ��  
                char filePath[MAX_FILE_NAME_LENGTH];  
                cout<<"�������ļ�·���磺F:/a/b.jpg"<<endl;  
                cin>>filePath;  
                char fileDrive[_MAX_DRIVE];  
                char fileDir[_MAX_DIR];  
                char fileName[_MAX_FNAME];  
                char fileExt[_MAX_EXT];  
                _splitpath(filePath,fileDrive,fileDir,fileName,fileExt);  //���ļ�·������  
                Message::MsgFileName msgFileName;  
                strcat(fileName,fileExt);  
                strcpy(msgFileName.fileName,fileName);  
                if(send(sd,(char *)&msgFileName,sizeof(Message::MsgFileName),0)==SOCKET_ERROR)  //�����ļ���  
                {  
                    cout<<"�����ļ�������"<<WSAGetLastError()<<endl;  
                }  
                Sleep(10);  
                if(!SendFileLength(sd,filePath))  //�����ļ�����  
                {  
                    cout<<"�����ļ����ȳ���"<<endl;  
                    return false;  
                }  
                Sleep(10);  
                if(!SendFile(sd,filePath))  //�����ļ�  
                {  
                    cout<<"�����ļ�����"<<endl;  
                    return false;  
                }  
            }  
            break;  
        case 2:  
            {  
                Message::MsgDownLoadFile msgDownLoadFile;  
                if(send(sd,(char *)&msgDownLoadFile,sizeof(Message::MsgDownLoadFile),0)==SOCKET_ERROR)  
                {  
                    cout<<"���������ļ���Ϣʧ��"<<WSAGetLastError()<<endl;  
                    return false;  
                }  
                if(!RecvCatalogInfo(sd))  
                {  
                    return false;  
                }  
                if(!SendDownLoadFileName(sd))  
                {  
                    return false;  
                }  
                if(!ReceiveFileLength(sd))  
                {  
                    return false;  
                }  
                if(!ReceiveFileName(sd))  
                {  
                    return false;  
                }  
                if(!ReceiveFile(sd))  
                {  
                    return false;  
                }  
            }  
            break;  
        case 3:  
            break;  
        default:  
            cout<<"������Ĳ�����Ҫ����������"<<endl;  
            goto loop;  
        }  
    }  
    return true;  
}  
bool Client::SendFileLength(SOCKET sd,char *filePath)  
{  
      
    FILE *pFile;  
    pFile=fopen(filePath,"r+b");  
    fseek(pFile,0,SEEK_END);  
    nFileLength=_ftelli64(pFile);  
    Message::MsgFileLength msgFileLength;  
    msgFileLength.fileLength=nFileLength;  
    fclose(pFile);  
    if(send(sd,(char *)&msgFileLength,sizeof(Message::MsgFileLength),0)==SOCKET_ERROR)  
    {  
        return false;  
    }  
    return true;  
}  
bool Client::SendFile(SOCKET sd,char *filePath)   //�����ļ�  
{  
    cout<<"���뵽�����ļ�����"<<endl;  
    Message::MsgFile msgFile;  
    if(send(sd,(char *)&msgFile,sizeof(Message::MsgFile),0)==SOCKET_ERROR)  
    {  
        cout<<"�����ļ���Ϣ����"<<WSAGetLastError()<<endl;  
        return false;  
    }  
    Sleep(10);  
    FILE *pFile;  
    pFile=fopen(filePath,"r+b");  
    fseek(pFile,0,SEEK_SET);   //��λ���ļ���λ��  
    _int64 i=0;  
    char buff[MAX_PACK_SIZE];  
    while(i<nFileLength)  
    {  
        int nSize;  
        if(i+MAX_PACK_SIZE>nFileLength)  
        {  
            nSize=(int)(nFileLength-i);  
        }  
        else  
        {  
            nSize=MAX_PACK_SIZE-1;  
        }  
        fread(buff,sizeof(char),nSize,pFile);  
        int nSend;  
        nSend=send(sd,buff,nSize,0);  
        if(nSend==SOCKET_ERROR)  
        {  
            cout<<"����ʧ��"<<endl;  
            return false;  
        }  
        i+=nSend;  
        fseek(pFile,-(nSize-nSend),SEEK_CUR);  //��λ��ʵ���ѷ��͵���λ��  
        memset(buff,0,sizeof(char)*MAX_PACK_SIZE); //��buff���  
    }  
    fclose(pFile);  
    return true;  
}  
bool Client::RecvCatalogInfo(SOCKET sd)   //����Ŀ¼��Ϣ  
{  
    int flag=1;     //����Ŀ¼��Ϣ�ɹ���־  
    char buff[MAX_PACK_SIZE];  
    Message::MsgHead *msgHead;  
    while(true)  
    {  
        if(recv(sd,buff,MAX_PACK_SIZE,0)==SOCKET_ERROR)  
        {  
            cout<<"����Ŀ¼��Ϣʧ��"<<WSAGetLastError()<<endl;  
            flag=0;  
            break;  
        }  
        msgHead=(Message::MsgHead *)buff;  
        if(msgHead->msgId==MSG_COMPLETE)      //�ж���Ϣ�Ƿ��Ǳ�׼��Ϣ  
        {  
            cout<<"Ŀ¼��Ϣ�������"<<endl;  
            break;  
        }  
        else  
        {  
            cout<<buff<<endl;     //����������Ŀ¼��Ϣ�����ļ���  
        }  
    }  
    if(flag==0)  
    {  
        return false;  
    }  
    return true;  
}  
bool Client::SendDownLoadFileName(SOCKET sd)      //�������ص��ļ���  
{  
    cout<<"��������Ҫ���ص��ļ���"<<endl;  
    char fileName[_MAX_FNAME+_MAX_EXT];  
    cin>>fileName;  
    Message::MsgFileName msgFileName;  
    strcpy(msgFileName.fileName,fileName);  
    if(send(sd,(char *)&msgFileName,MAX_PACK_SIZE,0)==SOCKET_ERROR)  
    {  
        cout<<"���������ļ�������"<<WSAGetLastError()<<endl;  
        return false;  
    }  
    return true;  
}  
bool Client::ReceiveFileLength(SOCKET sd)     //�������ص��ļ�����  
{  
    char buff[MAX_PACK_SIZE];  
    Message::MsgFileLength *msgFileLength;  
    if(recv(sd,buff,MAX_PACK_SIZE,0)==SOCKET_ERROR)  
    {  
        cout<<"�����ļ�����ʧ��"<<WSAGetLastError()<<endl;  
        return false;  
    }  
    msgFileLength=(Message::MsgFileLength *)buff;  
    nFileLength=msgFileLength->fileLength;  
    cout<<"���յ��ļ�����"<<nFileLength<<endl;  
    return true;  
}  
bool Client::ReceiveFileName(SOCKET sd)   //�������ص��ļ���  
{  
    char buff[MAX_PACK_SIZE];  
    memset(fileName,0,sizeof(char)*(_MAX_FNAME+_MAX_EXT));  
    Message::MsgFileName *msgFileName;  
    if(recv(sd,buff,MAX_PACK_SIZE,0)==SOCKET_ERROR)  
    {  
        cout<<"�����ļ�������"<<endl;  
        return false;  
    }  
    msgFileName=(Message::MsgFileName *)buff;  
    strcpy(fileName,msgFileName->fileName);  
    cout<<"���յ��ļ���"<<fileName<<endl;  
    return true;  
}  
bool Client::ReceiveFile(SOCKET sd)      //�����ļ�����  
{  
   char buff[MAX_PACK_SIZE];  
   FILE *pFile;  
   pFile=fopen(fileName,"a+b");  
   _int64 i=0;  
   while(i+1<nFileLength)  
   {  
        int nRecv=recv(sd,buff,MAX_PACK_SIZE,0);  
        if(nRecv==SOCKET_ERROR)  
        {  
            return false;  
        }  
        fwrite(buff,sizeof(char),nRecv,pFile);  
        i+=nRecv;  
        memset(buff,0,sizeof(char)*MAX_PACK_SIZE);  
    }  
    fclose(pFile);  
    return true;  
}  
void Client::CloseSocket()   //�ر��׽���  
{  
    closesocket(sd);  
    WSACleanup();  
}  


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
void main() {
// ��ʼ��
    WSADATA wsaData;
    int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
    if ( iResult != NO_ERROR )
        printf("Error at WSAStartup()/n");
    // ����socket
    SOCKET server;
    server = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( server == INVALID_SOCKET ) {
        printf( "Error at socket(): %ld/n", WSAGetLastError() );
        WSACleanup();
        return;
    }
    // ��socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    service.sin_port = htons(8000);
    if ( bind( server, (SOCKADDR*) &service, sizeof(service) ) == SOCKET_ERROR ) {
        printf( "bind() failed./n" );
        closesocket(server);
        return;
    }
    
    // ���� socket
    if ( listen( server, 1 ) == SOCKET_ERROR )
        printf( "Error listening on socket./n");
    // ��������
    SOCKET AcceptSocket;
    printf( "Waiting for a client to connect.../n" );
    while (1) {
        AcceptSocket = SOCKET_ERROR;
        while ( AcceptSocket == SOCKET_ERROR ) {
            AcceptSocket = accept( server, NULL, NULL );
        }
        printf( "Client Connected./n");
        server = AcceptSocket; 
        break;
    }
    
    // ���ͽ�������
//    int bytesSent;
    char sendbuf[1024];//���ͻ�����
 //DWORD dwFileSize;//�ļ���С
 DWORD        dwRead;
    BOOL         bRet;
    char filename[]="c://MyMain.java";
 HANDLE hFile=CreateFile(filename,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
 //dwFileSize=GetFileSize(hFile,NULL);
 while(true)
    {
      bRet=ReadFile(hFile,sendbuf,1024,&dwRead,NULL);
      if(bRet==FALSE)
      {
        MessageBox(NULL,"Read Buf ERROR!","Error",MB_OK);
        break;
      }
      else if(dwRead==0)
      {
        MessageBox(NULL,"Send file OK!","OK",MB_OK);
        break;
      }
      else
      {
       send(server,sendbuf,dwRead,0);
      }
    };
    CloseHandle(hFile);
    return;
}
����
#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
void main() {
    // ��ʼ�� Winsock.
    WSADATA wsaData;
    int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
    if ( iResult != NO_ERROR )
        printf("Error at WSAStartup()/n");
    // ����socket socket.
    SOCKET client;
    client = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( client == INVALID_SOCKET ) {
        printf( "Error at socket(): %ld/n", WSAGetLastError() );
        WSACleanup();
        return;
    }
    // ���ӵ�������.
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    clientService.sin_port = htons( 8000 );
    if ( connect( client, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR) {
        printf( "Failed to connect./n" );
        WSACleanup();
        return;
    }
char recvbuf[1024];//���ͻ�����
 int read;
 DWORD        dwWrite;
    BOOL         bRet;
    // ���Ͳ���������.
    char filename[]="c://syn.txt";
 HANDLE hFile=CreateFile(filename,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
while(true)
    {
   read=recv( client, recvbuf, 1024, 0 );
   if(read==-1)break;
   bRet=WriteFile(hFile,recvbuf,read,&dwWrite,NULL);
      if(bRet==FALSE)
      {
        MessageBox(NULL,"Write Buf ERROR!","Error",MB_OK);
        break;
      }
           
    }
 MessageBox(NULL,"Receive file OK!","OK",MB_OK);
    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    afx_msg void OnBnClickedButton1();
public:
    BOOL InitSocket();    //��ʼ���������׽���

    static DWORD WINAPI ThreadProc(LPVOID lpParameter);    //�����߳�ȥִ�з�����accept()

	void CSendFileServerDlg::OnBnClickedButton1()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if (InitSocket())
    {
        GetDlgItem(IDC_EDIT1)->SetWindowText(_T("�������������������� \r\n"));

        //�����߳�
        HANDLE hThread = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);
        //�رոý����߳̾�����ͷ����ü���
        CloseHandle(hThread);
    }
}

BOOL CSendFileServerDlg::InitSocket()
{
    //�����׽��ֿ�
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD( 1, 1 );
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) 
    {
        return FALSE;
    }

    if ( LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1 ) 
    {
            WSACleanup( );
            return FALSE;
    }

    //�����׽���
    //SOCKET m_socket=socket(AF_INET,SOCK_STREAM,0);
    m_socket=socket(AF_INET,SOCK_STREAM,0);
    if (m_socket == INVALID_SOCKET)
    {
        AfxMessageBox(_T("�׽��ִ���ʧ�ܣ�"));
        return FALSE;
    }

    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
    addrSrv.sin_family=AF_INET;
    addrSrv.sin_port=htons(8099);

    err = bind(m_socket,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));    //�󶨱��ض˿�
    if (err==SOCKET_ERROR)
    {
        closesocket(m_socket);
        AfxMessageBox(_T("��ʧ�ܣ�"));
        return FALSE;
    }
    listen(m_socket,5);//��������

    return TRUE;

}

DWORD WINAPI CSendFileServerDlg::ThreadProc(LPVOID lpParameter)
{
    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);

    while (true)
    {
        SOCKET sockConn=accept(m_socket,(SOCKADDR*)&addrClient,&len);

        CString filename = _T("E:\\test.zip");
        HANDLE hFile;
        unsigned long long file_size = 0;

        char Buffer[1024];
        DWORD dwNumberOfBytesRead;

        hFile = CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
        file_size = GetFileSize(hFile,NULL);
        send(sockConn,(char*)&file_size,sizeof(unsigned long long)+1,NULL);

        do 
        {
            ::ReadFile(hFile,Buffer,sizeof(Buffer),&dwNumberOfBytesRead,NULL);
            ::send(sockConn,Buffer,dwNumberOfBytesRead,0);
        } while (dwNumberOfBytesRead);


        CloseHandle(hFile);
    }

    return 0;
}


public:
    afx_msg void OnBnClickedButton1();
 
    BOOL InitSocket();
    void ConnectServer();
    void ConnectRecvFileData(DWORD ip,int port);
	private:
    CProgressCtrl *m_progress; //������

	BOOL CRecvFileClientDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // ��������...���˵�����ӵ�ϵͳ�˵��С�

    // IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE);            // ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);        // ����Сͼ��

    // TODO: �ڴ���Ӷ���ĳ�ʼ������

    m_progress = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1); 
    m_progress->SetPos(0); 

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRecvFileClientDlg::OnBnClickedButton1()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    ConnectServer();
    
}


BOOL CRecvFileClientDlg::InitSocket()
{
    //�����׽��ֿ�
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD( 1, 1 );
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) 
    {
        return FALSE;
    }

    if ( LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1 ) 
    {
        WSACleanup( );
        return FALSE;
    }

    return TRUE;

}

void CRecvFileClientDlg::ConnectRecvFileData(DWORD ip,int port)
{
    
    unsigned long long file_size=0;
    SOCKET sockClient = socket(AF_INET,SOCK_STREAM,0);
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr=htonl(ip);
    addrSrv.sin_port=ntohs(port);
    addrSrv.sin_family = AF_INET;
    //connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
    //recv(sockClient,(char*)&file_size,sizeof(unsigned long long)+1,NULL);

    if (!connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)))
    {
        GetDlgItem(IDC_SHOWINFO)->SetWindowText(_T(""));
        GetDlgItem(IDC_SHOWINFO)->SetWindowText(_T("���ӷ������ɹ���\r\n"));

        

        recv(sockClient,(char*)&file_size,sizeof(unsigned long long)+1,NULL);

        unsigned short maxvalue = file_size;    //�˴���̫���� �����ݺܴ�ʱ���ܻ�����쳣
        m_progress->SetRange(0,maxvalue); 

        if (file_size>0)
        { 
            GetDlgItem(IDC_SHOWINFO)->SetWindowText(_T(""));
            GetDlgItem(IDC_SHOWINFO)->SetWindowText(_T("�ļ����ص����� d��\\test.zip \r\n"));

            DWORD dwNumberOfBytesRecv=0;
            DWORD dwCountOfBytesRecv=0;
            char Buffer[1024];
            CString filename = _T("d:\\test.zip");
            HANDLE hFile;
            hFile = CreateFile(filename,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

            do 
            {
                m_progress->SetPos(dwCountOfBytesRecv);//���½�����

                dwNumberOfBytesRecv = ::recv(sockClient,Buffer,sizeof(Buffer),0);
                ::WriteFile(hFile,Buffer,dwNumberOfBytesRecv,&dwNumberOfBytesRecv,NULL);
                dwCountOfBytesRecv += dwNumberOfBytesRecv;                
            } while (file_size - dwCountOfBytesRecv);


            CloseHandle(hFile);
            
            GetDlgItem(IDC_SHOWINFO)->SetWindowText(_T(""));
            GetDlgItem(IDC_SHOWINFO)->SetWindowText(_T("�ļ�������ϣ�\r\n"));
            AfxMessageBox(_T("�ļ��������!"));//��Ŀ����ע��
        }else
        {
            AfxMessageBox(_T("��ȡ�ļ��ܴ�Сʧ�ܣ�"));
        }
    }else
    {
        AfxMessageBox(_T("���ӷ�����ʧ�ܡ���ȷ��IP��ַ��˿ںţ�"));
    }
    
    

    closesocket(sockClient);//�ر��׽���


}

void CRecvFileClientDlg::ConnectServer()
{
    if (InitSocket())
    {
        DWORD strIp =NULL;
        CString strPort = _T("");

        ((CIPAddressCtrl*)GetDlgItem(IDC_IP))->GetAddress(strIp);
        GetDlgItem(IDC_PORT)->GetWindowText(strPort);

        if (strIp==NULL||strPort=="")
        {
            AfxMessageBox(_T("Ip��ַ��Port�˿ںŲ���Ϊ�գ�"));

        }else
        {
            int port = atoi(strPort.GetBuffer(1));
            ConnectRecvFileData(strIp,port);
            
        }
    }
}