
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
	, m_nClk(FALSE)
	, m_Init(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSecureManagementProgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_SEARCH, m_cbSearchMenu);
	DDX_Control(pDX, IDC_LIST_RES, m_ListCtrl);
	DDX_Control(pDX, IDC_LISTBOX_RES, m_ListBox);
}

BEGIN_MESSAGE_MAP(CSecureManagementProgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(MSG_PROGRESS_UPDATE, &CSecureManagementProgDlg::OnProgressUpdate)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CSecureManagementProgDlg::OnBnClickedBtnSearch)
	ON_BN_CLICKED(IDC_BTN_STATUS, &CSecureManagementProgDlg::OnBnClickedBtnStatus)
	ON_CBN_SELCHANGE(IDC_CB_SEARCH, &CSecureManagementProgDlg::OnCbnSelchangeCbSearch)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CSecureManagementProgDlg::OnBnClickedBtnRefresh)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_RES, &CSecureManagementProgDlg::OnLvnItemchangedListRes)
	ON_LBN_SELCHANGE(IDC_LISTBOX_RES, &CSecureManagementProgDlg::OnLbnSelchangeListboxRes)
	ON_WM_SIZE()
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
	
	m_Init = TRUE;
	m_bSubDialog = FALSE;

	COperationStatus::SetHwnd(m_hWnd); //기능별 충돌 방지핸들 초기화
	InitSearchMenu();	//검색조건 초기화
	//AllocForm();			//보안프로그램 관리 기능 다이얼로그 붙이기
	ConntectSQL();		//Mysql 연결

	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("보안프로그램"), LVCFMT_CENTER, rt.Width() * 0.5);
	m_ListCtrl.InsertColumn(1, TEXT("필수 / 선택"), LVCFMT_CENTER, rt.Width() * 0.3);
	m_ListCtrl.InsertColumn(2, TEXT("설치 여부"), LVCFMT_CENTER, rt.Width() * 0.2);

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

void CSecureManagementProgDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_Init && !m_bSubDialog)
	{
		AllocForm();
	}
	else if (m_bSubDialog)
	{
		CRect rectOfPanelArea;
		GetDlgItem(IDC_PC_FEATURE)->GetWindowRect(&rectOfPanelArea);
		ScreenToClient(&rectOfPanelArea);
		m_CFeatureManager->MoveWindow(rectOfPanelArea);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

LRESULT CSecureManagementProgDlg::OnProgressUpdate(WPARAM wParam, LPARAM lParam)
{
	if (lParam == MSG_START)
	{
		switch (wParam)
		{
		case MSG_PROGRESS_SEARCH:
			break;
		case MSG_PROGRESS_DELETE:
			break;
		case MSG_PROGRESS_REFRESH:
			break;
		}
	}
	else
	{
	}

	return LRESULT();
}

void CSecureManagementProgDlg::ConntectSQL()
{
	m_CMySQL.ConnectToDB(&m_connection);
}

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
		CRect rt;
		this->GetWindowRect(&rt);
		ScreenToClient(&rt);
		::InvalidateRect(m_hWnd, rt, TRUE);

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
	CRect rtFeaturePCRect;
	CCreateContext context;
	ZeroMemory(&context, sizeof(context));

	GetDlgItem(IDC_PC_FEATURE)->GetWindowRect(&rtFeaturePCRect);
	ScreenToClient(&rtFeaturePCRect);

	m_pCFeatureManager = new CFeatureManager();
	m_pCFeatureManager->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rtFeaturePCRect, this, IDD_DIALOG1, &context);
	m_pCFeatureManager->OnInitialUpdate();
	m_pCFeatureManager->ShowWindow(SW_SHOW);
	//GetDlgItem(IDC_PC_FEATURE)->DestroyWindow();
}


void CSecureManagementProgDlg::OnBnClickedBtnSearch()
{
	CWinThread* p = NULL;
	p = AfxBeginThread(ThreadSearchSecureprog, this);

	if (p == NULL)  //쓰레드생성실패시에러메시지
		AfxMessageBox(L"ThreadLoadCSV Error");
}

UINT CSecureManagementProgDlg::ThreadSearchSecureprog(LPVOID pParam)
{
	COperationStatus::SetSearching(TRUE);
	CSecureManagementProgDlg* pSecureManagementProg = (CSecureManagementProgDlg*)pParam;
	pSecureManagementProg->SearchSecureProgram();
	COperationStatus::SetSearching(FALSE);

	return 0;
}

void CSecureManagementProgDlg::SearchSecureProgram()
{
	CString cstSearch;
	vector<CString> PfCode, SecName, PfName, PfType;
	GetDlgItemText(IDC_EDIT_SEARCH, cstSearch);
	if (cstSearch.IsEmpty())	return;
	m_nClk = TRUE;

	m_CPlatform.SetFindVar(cstSearch);
	m_CPlatform.GetColumns(&m_connection, &PfCode, &PfName,&PfType);
	m_ListBox.ResetContent();
	for (CString name : PfName)
	{
		m_ListBox.AddString(name);
	}



}

void CSecureManagementProgDlg::OnBnClickedBtnStatus()
{
	m_pCCurSecureManger = new CCurSecureManager();
	m_pCCurSecureManger->DoModal();
}

void CSecureManagementProgDlg::OnCbnSelchangeCbSearch()
{
	COperationStatus::SetSearching(TRUE);
	INT nCursel = m_cbSearchMenu.GetCurSel();
	m_SearchCondition = nCursel + 0X64;	//검색조건
	COperationStatus::SetSearching(FALSE);
}


BOOL CSecureManagementProgDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN)
	{
		OnBnClickedBtnSearch();
		return TRUE;
	}
	else if (pMsg->wParam == VK_ESCAPE)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSecureManagementProgDlg::OnBnClickedBtnRefresh()
{
	COperationStatus::SetRefresh(TRUE);
	UpdateData(TRUE);
	COperationStatus::SetRefresh(FALSE);
}


void CSecureManagementProgDlg::OnLvnItemchangedListRes(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	INT nCursel = m_ListCtrl.GetNextSelectedItem(pos);

	m_CFeatureManager->UpdateStatus(1,1);
	HWND hwnd = m_CFeatureManager->GetSafeHwnd();
	::SendMessage(hwnd, MSG_SECUREINIT, TRUE, NULL);
	*pResult = 0;
}


void CSecureManagementProgDlg::OnLbnSelchangeListboxRes()
{
	CString cstList;
	vector<CString> SecName, PfCode, PfName, PfType, Install;

	INT nCursel = m_ListBox.GetCurSel();
	if (nCursel != LB_ERR)
		m_ListBox.GetText(nCursel, cstList);

	m_CPlatform.SetFindVar(cstList);
	m_CPlatform.GetColumns(&m_connection, &PfCode, &PfName, &PfType);
	m_CSecurityprog.GetColumns(&m_connection, &SecName, PfCode, &Install);

	m_ListCtrl.DeleteAllItems();
	INT num = m_ListCtrl.GetItemCount();
	INT curNum(0);
	for (CString name : SecName)
	{
		m_ListCtrl.InsertItem(num, name);
		CString InstallChoice = (Install[curNum] == '1') ? (_T("필수")) : (_T("선택"));
		m_ListCtrl.SetItem(num, 1, LVIF_TEXT, InstallChoice, NULL, NULL, NULL, NULL);
		m_ListCtrl.SetItem(num, 2, LVIF_TEXT, _T("미설치"), NULL, NULL, NULL, NULL);
		curNum++;
	}
}



