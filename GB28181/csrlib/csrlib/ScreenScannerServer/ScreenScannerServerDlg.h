
// ScreenScannerServerDlg.h : header file
//

#pragma once

#include <gdiplus.h>

//�����ռ�
using namespace Gdiplus;

//�Զ�����Ϣ
#define CM_RECEIVED  WM_USER+1001

#pragma comment(lib, "ws2_32.lib")

// CScreenScannerServerDlg dialog
class CScreenScannerServerDlg : public CDialogEx
{
// Construction
public:
	CScreenScannerServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREENSCANNERSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

public://�Զ��庯��
	void ShowJPEG(void* pData, int DataSize);
	afx_msg LRESULT OnReceived(WPARAM wParam, LPARAM lParam);

private://ͨѶ���
	SOCKET  m_Socket;					//�����׽���
	CString m_ClientIP;					//�ͻ���IP
	UINT    m_ClientPort;				//�ͻ��˶˿�
	
private://�������
	char*	m_BmpData;					//λͼ����ָ��
	char*   m_Header;					//��ʱָ��
	BOOL    m_ShowBmp;					//�Ƿ���ʾλͼ
	char*   m_TempData;					//��ʱ����ָ��
	int     m_BmpSize;					//��¼λͼ��С
	int     m_RecSize;					//ʵ�ʽ��յĴ�С
	DWORD   m_JPGSize;					//JPG���ݵ��ܴ�С
	BOOL    m_IsScreen;					//�Ƿ�ȫ����ʾ
	WINDOWPLACEMENT m_OldPlacement;		//ԭ���Ĵ���ģʽ
	CRect m_FullScreenRect;				//ȫ����ʾ����
	IStream *m_pStm;
	Bitmap  *m_pNewBmp;
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;
public:
	//afx_msg void OnBnClickedStart();
};
