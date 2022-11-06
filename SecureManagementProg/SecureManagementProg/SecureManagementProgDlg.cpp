
// SecureManagementProgDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SecureManagementProg.h"
#include "SecureManagementProgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CSecureManagementProgDlg dialog



CSecureManagementProgDlg::CSecureManagementProgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SECUREMANAGEMENTPROG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSecureManagementProgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_SEARCH, m_cbSearchMenu);
}

BEGIN_MESSAGE_MAP(CSecureManagementProgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CSecureManagementProgDlg::OnBnClickedBtnSearch)
	ON_BN_CLICKED(IDC_BTN_STATUS, &CSecureManagementProgDlg::OnBnClickedBtnStatus)
END_MESSAGE_MAP()


// CSecureManagementProgDlg message handlers

BOOL CSecureManagementProgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	InitSearchMenu();
	AllocForm();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSecureManagementProgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSecureManagementProgDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSecureManagementProgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSecureManagementProgDlg::InitSearchMenu()
{
	m_cbSearchMenu.AddString(_T("통합 검색"));
	m_cbSearchMenu.AddString(_T("제1금융권"));
	m_cbSearchMenu.AddString(_T("정부 기관"));
	m_cbSearchMenu.AddString(_T("비은행예금 취급기관"));
	m_cbSearchMenu.AddString(_T("증권 회사"));
	m_cbSearchMenu.AddString(_T("보험 회사"));
	m_cbSearchMenu.AddString(_T("기타 금용회사"));
	m_cbSearchMenu.AddString(_T("보안프로그램"));

	m_cbSearchMenu.SetCurSel(0);
}

void CSecureManagementProgDlg::AllocForm()
{
	CCreateContext context;
	ZeroMemory(&context, sizeof(context));

	CRect rtFeaturePCRect;

	GetDlgItem(IDC_PC_FEATURE)->GetWindowRect(&rtFeaturePCRect);
	ScreenToClient(&rtFeaturePCRect);

	m_pCFeatureManager = new CFeatureManager();
	m_pCFeatureManager->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rtFeaturePCRect, this, IDD_DIALOG1, &context);
	m_pCFeatureManager->OnInitialUpdate();
	m_pCFeatureManager->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_PC_FEATURE)->DestroyWindow();
}


void CSecureManagementProgDlg::OnBnClickedBtnSearch()
{
	// TODO: Add your control notification handler code here
}


void CSecureManagementProgDlg::OnBnClickedBtnStatus()
{
	m_pCCurSecureManger = new CCurSecureManager();
	m_pCCurSecureManger->DoModal();
}
