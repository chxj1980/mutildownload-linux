
// DocManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DocManager.h"
#include "DocManagerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDocManagerDlg �Ի���



CDocManagerDlg::CDocManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DOCMANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDocManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RECENT, m_RecentList);
}

BEGIN_MESSAGE_MAP(CDocManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CDocManagerDlg ��Ϣ�������

BOOL CDocManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//if (m_RecentImageList.GetSafeHandle() == NULL)
	//{
	//	m_RecentImageList.Create(80, 80, ILC_MASK | ILC_COLOR32, 0, 0);
	//	m_RecentImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	//	m_RecentList.SetImageList(&m_RecentImageList, LVSIL_NORMAL);
	//}

	//����BMPͼƬ
	//if (m_RecentImageList.GetSafeHandle() == NULL)
	//{
	//	CBitmap Image;
	//	BITMAP ImageInfo;
	//	Image.LoadBitmap(L"E:\\�鼮\\��Ƶ\\�ļ�\\2015task\\arm\\ͼƬ�ļ�\\water.bmp");
	//	Image.GetBitmap(&ImageInfo);
	//	m_RecentImageList.Create(18, ImageInfo.bmHeight, ILC_COLOR16 | ILC_MASK, 0, 0);
	//	m_RecentImageList.Add(&Image, RGB(255, 0, 255));
	//}

	//m_RecentList.SetImageList(&m_RecentImageList, LVSIL_SMALL);

	//m_RecentList.SetExtendedStyle(m_RecentList.GetExtendedStyle() | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES);
	//m_RecentList.InsertColumn(0, L"#", LVCFMT_CENTER, 0);
	//m_RecentList.InsertColumn(1, _T("T1"), LVCFMT_LEFT, 100);
	//m_RecentList.InsertColumn(2, _T("A1"), LVCFMT_LEFT, 190);
	//m_RecentList.InsertColumn(3, _T("A2"), LVCFMT_LEFT, 190);

	//m_RecentImageList.Create(150, 200, ILC_COLOR32 | ILC_MASK, 8, 1);   //----- ʵ��ͼ���
	//HBITMAP hBitmap;
	//CBitmap *pBitmap;
	//CString FilePathName = L"E:\\�鼮\\��Ƶ\\�ļ�\\2015task\\arm\\ͼƬ�ļ�\\water.bmp";   //����Դ��IDB_BITMAP1�ļ�����face.bmp�����
	//pBitmap = new  CBitmap;
	//hBitmap = (HBITMAP)LoadImage(NULL, FilePathName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//pBitmap->Attach(hBitmap);
	//m_RecentImageList.Add(pBitmap, RGB(0, 0, 0));

	//m_RecentList.SetImageList(&m_RecentImageList, LVSIL_SMALL);

	//DWORD dw = m_RecentImageList.GetImageCount();
	//CString str;
	//for (int j = 0;j < 3;j++) {
	//	m_RecentList.InsertItem(j, L"123", 0);
	//	LVITEM item = { 0 };
	//	item.iItem = j;
	//	item.iSubItem = 2;
	//	item.mask = LVIF_TEXT | LVIF_IMAGE;
	//	item.iImage = 0;                  //ͼƬ����ֵ
	//	item.pszText = _T("Virqin");
	//	item.lParam = (LPARAM)m_hWnd;
	//	m_RecentList.SetItem(&item);
	//}
	//m_RecentImageList.Detach();

	//ʹ��ICON
	/*CImageList m_ImageList;*/
	//m_RecentList.SetExtendedStyle(m_RecentList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);
	//m_RecentImageList.Create(32, 16, ILC_COLOR, 8, 4);

	//int m_nIdxIco1 = m_RecentImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));  //ʹ������  
	//int m_nIdxIco2 = m_RecentImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	//int m_nIdxIco3 = m_RecentImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	//int m_nIdxIco4 = m_RecentImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	//m_RecentList.SetImageList(&m_RecentImageList, LVSIL_SMALL);
	//m_RecentList.InsertColumn(0, L"ColName1", LVCFMT_CENTER, 40);
	//m_RecentList.InsertColumn(1, L"ColName2", LVCFMT_LEFT, 50);
	//m_RecentList.InsertItem(0, L"", m_nIdxIco1);
	//m_RecentList.InsertItem(1, L"", m_nIdxIco2);
	//m_RecentList.InsertItem(2, L"", m_nIdxIco3);
	//m_RecentList.InsertItem(3, L"", m_nIdxIco4);

	//m_RecentImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));  //��ʹ������  
	//m_RecentImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	//m_RecentImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	//m_RecentImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	//m_RecentList.SetImageList(&m_RecentImageList, LVSIL_SMALL);
	//m_RecentList.InsertColumn(0, L"ColName1", LVCFMT_CENTER, 40);
	//m_RecentList.InsertColumn(1, L"ColName2", LVCFMT_LEFT, 50);
	//m_RecentList.InsertItem(0, L"", 0);
	//m_RecentList.InsertItem(1, L"", 1);
	//m_RecentList.InsertItem(2, L"", 2);
	//m_RecentList.InsertItem(3, L"", 3);
	//m_RecentList.SetItem(0, 1, LVIF_TEXT, L"111", 0, 0, 0, 0);
	//m_RecentList.SetItem(1, 1, LVIF_IMAGE, L"222", 1, 0, 0, 0);
	//m_RecentList.SetItem(2, 1, LVIF_TEXT, L"333", 2, 0, 0, 0);
	//m_RecentList.SetItem(3, 1, LVIF_IMAGE, L"444", 3, 0, 0, 0);

	m_RecentList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_RecentList.SetIconSpacing(CSize(140, 130));



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDocManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDocManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDocManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

