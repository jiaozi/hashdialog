
// hashdialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hashdialog.h"
#include "hashdialogDlg.h"
#include "afxdialogex.h"
#include "sha1.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// ChashdialogDlg dialog



ChashdialogDlg::ChashdialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChashdialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ChashdialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ChashdialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &ChashdialogDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ChashdialogDlg message handlers

BOOL ChashdialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
    GetDlgItem(IDC_EDIT1)->SetWindowTextW(L"text");
    GetDlgItem(IDC_EDIT2)->SetWindowTextW(L"sha1 hash value");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void ChashdialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void ChashdialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
        if (hashString.size() > 0) GetDlgItem(IDC_EDIT2)->SetWindowTextW(hashString.data());
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR ChashdialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void ChashdialogDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    CString  str;
    GetDlgItem(IDC_EDIT1)->GetWindowText(str);
    int strLength = str.GetLength();
    int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
    char *pCharStr = new char[len + 1];
    WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), pCharStr, len, NULL, NULL);
    pCharStr[len + 1] = '\0';
    unsigned char hash[20];
    sha1::calc(pCharStr, len, hash);
    for (int i = 0; i < 20; ++i)
    {
        std::wostringstream ostr;
        ostr << "\\" << static_cast<int>(hash[i]);
        hashString.append(ostr.str());
    }

    pCharStr = NULL;
    GetDlgItem(IDC_EDIT2)->SetWindowText(hashString.data());
    //CDialogEx::OnOK();
}
