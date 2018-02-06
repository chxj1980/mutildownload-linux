
// ScreenScannerClientDlg.h : header file
//

#pragma once

#include <gdiplus.h>


using namespace Gdiplus;

//�Զ���һ����Ϣ
#define CM_RECEIVED  WM_USER+2
//����ÿ�����ݱ��а���λͼ���ݵĴ�С
#define GraphSize    40960

// CScreenScannerClientDlg dialog
class CScreenScannerClientDlg : public CDialogEx
{
// Construction
public:
	CScreenScannerClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREENSCANNERCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

public:
	int  SendData(UINT index, int mod, int bmpsize, int totalsize, int frames, char *pSendBuf, sockaddr_in &addr);
	afx_msg LRESULT OnReceived(WPARAM wParam, LPARAM lParam);

	afx_msg void OnTimer(UINT nIDEvent);
	
private:
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;

	SOCKET  m_Socket;		//�ͻ����׽���
	CString m_ServerIP;		//������IP
	BOOL	m_Confirm;		//ȷ����Ϣ
	int     m_FrameIndex;	//��¼����
	int     m_Mod;			//��¼����
	int     m_Count;		//ÿһ��λͼ�ֱ�������
	int     m_Bmpsize;		//λͼ��ʵ�ʴ�С
	char*	m_pSendBuf;		//���ͻ�����ָ��
	char*	m_pHeader;		//��ʱָ��
	sockaddr_in  m_Addr;	//�׽��ֵ�ַ
	BOOL    m_Received;		//�Ƿ���յ�������������ȷ����Ϣ
	int     m_Counter;		//������
	DWORD	m_JpegSize;		//JPEG�����ܴ�С
public:
	afx_msg void OnBnClickedBtnStart();
};
