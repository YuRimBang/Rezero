
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
	, m_bSQL(FALSE)
	, m_cstInternet(_T("chrome.exe"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSecureManagementProgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_SEARCH, m_cbSearchMenu);
	DDX_Control(pDX, IDC_LIST_RES, m_ListCtrl);
	DDX_Control(pDX, IDC_LISTBOX_RES, m_ListBox);
	DDX_Control(pDX, IDC_PC_IMG, m_pcPlatformImg);
	DDX_Control(pDX, IDC_EDIT_LINK, m_edLink);
	DDX_Control(pDX, IDC_CB_INTERNET, m_cbInternet);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
}

BEGIN_MESSAGE_MAP(CSecureManagementProgDlg, CDialogEx)
	ON_WM_SIZE()
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
	ON_STN_CLICKED(IDC_STATIC_HYPERLINK, &CSecureManagementProgDlg::OnStnClickedStaticHyperlink)
	ON_CBN_SELCHANGE(IDC_CB_INTERNET, &CSecureManagementProgDlg::OnCbnSelchangeCbInternet)
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

	COperationStatus::SetHwnd(m_hWnd); //?????? ???? ???????? ??????
	InitSearchMenu();	//???????? ??????
	InitInternetMenu();
	AllocForm();			//???????????? ???? ???? ?????????? ??????
	SetUpForDynamicLayout();	//DynamicLayout
	GetDlgItem(IDC_STATIC_HYPERLINK)->SetWindowTextW(L"?????? ????????");	//??????
	ConntectSQL();		//Mysql ????
	m_progress.SetBarColor(RGB(204,102,204));
	m_progress.SetRange(0, 100); 

	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("????????????"), LVCFMT_CENTER, rt.Width() * 0.5);
	m_ListCtrl.InsertColumn(1, TEXT("???? / ????"), LVCFMT_CENTER, rt.Width() * 0.3);
	m_ListCtrl.InsertColumn(2, TEXT("???? ????"), LVCFMT_CENTER, rt.Width() * 0.2);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSecureManagementProgDlg::SetUpForDynamicLayout()
{
	this->EnableDynamicLayout();

	auto move_x_100 = CMFCDynamicLayout::MoveSettings{};
	move_x_100.m_nXRatio = 100;

	auto move_none = CMFCDynamicLayout::MoveSettings{};

	auto size_none = CMFCDynamicLayout::SizeSettings{};
	
	auto size_x_100 = CMFCDynamicLayout::SizeSettings{};
	size_x_100.m_nXRatio = 100;

	auto size_both = CMFCDynamicLayout::SizeSettings{};
	size_both.m_nXRatio = 100;
	size_both.m_nYRatio = 100;

	auto ManagerMainView = this->GetDynamicLayout();
	ManagerMainView->Create(this);

	ManagerMainView->AddItem(IDC_BTN_SEARCH, move_x_100, size_none);
	ManagerMainView->AddItem(IDC_BTN_STATUS, move_x_100, size_none);
	ManagerMainView->AddItem(IDC_BTN_REFRESH, move_x_100, size_none);
	ManagerMainView->AddItem((IDC_EDIT_LINK), move_x_100, size_none);
	ManagerMainView->AddItem((IDC_STATIC_LINK), move_x_100, size_none);
	ManagerMainView->AddItem((IDC_PC_FEATURE), move_x_100, size_none);
	ManagerMainView->AddItem((IDC_PC_IMG), move_x_100, size_none);
	ManagerMainView->AddItem((IDC_CB_INTERNET), move_x_100, size_none);
	ManagerMainView->AddItem((IDC_STATIC_HYPERLINK), move_x_100, size_none);
	ManagerMainView->AddItem((IDC_PROGRESS), move_x_100, size_none);

	ManagerMainView->AddItem(IDC_EDIT_SEARCH, move_none, size_x_100);
	ManagerMainView->AddItem(IDC_LIST_RES, move_none, size_both);
	ManagerMainView->AddItem(IDC_LISTBOX_RES, move_none, size_x_100);
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
		m_bSubDialog = TRUE;
	}
	else if (m_bSubDialog)
	{
		CRect rectOfPanelArea;
		GetDlgItem(IDC_PC_FEATURE)->GetWindowRect(&rectOfPanelArea);
		ScreenToClient(&rectOfPanelArea);
		
		CCreateContext context;
		ZeroMemory(&context, sizeof(context));

		CFeatureManager* m_pFeature = (CFeatureManager*)GetDlgItem(IDD_DIALOG1);
		m_pFeature->MoveWindow(rectOfPanelArea);

		CRect rt;
		m_ListCtrl.GetWindowRect(&rt);
		m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

		m_ListCtrl.InsertColumn(0, TEXT("????????????"), LVCFMT_LEFT, rt.Width() * 0.5);
		m_ListCtrl.InsertColumn(1, TEXT("???? / ????"), LVCFMT_CENTER, rt.Width() * 0.3);
		m_ListCtrl.InsertColumn(2, TEXT("???? ????"), LVCFMT_CENTER, rt.Width() * 0.2);
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
		case MSG_PROGRESS_ACCESS:
			GetDlgItem(IDC_STATIC_HYPERLINK)->SetWindowTextW(L"??????...");
			break;
		}
	}
	else if(lParam ==MSG_END)
	{
		switch (wParam)
		{
		case MSG_PROGRESS_ACCESS:
			GetDlgItem(IDC_STATIC_HYPERLINK)->SetWindowTextW(L"?????? ????????");
			break;
		}
	}

	return LRESULT();
}

void CSecureManagementProgDlg::ConntectSQL()
{
	if (m_CMySQL.ConnectToDB(&m_connection, m_char))
		m_bSQL = TRUE;
	else
		AfxMessageBox(_T("MySQL?? ???? ?????? ??????????????."));
}

void CSecureManagementProgDlg::FreeSQL()
{
	MYSQL_RES res;
	m_CMySQL.FreeSQL(&res);
	m_bSQL = FALSE;
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
		if (!m_cstImg.IsEmpty())
			DrawImage(m_cstImg);

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
	m_cbSearchMenu.AddString(_T("????IP"));
	m_cbSearchMenu.AddString(_T("????IP"));
	m_cbSearchMenu.AddString(_T("??pc"));

	//m_cbSearchMenu.AddString(_T("???? ????"));
	//m_cbSearchMenu.AddString(_T("??1??????"));
	//m_cbSearchMenu.AddString(_T("???? ????"));
	//m_cbSearchMenu.AddString(_T("?????????? ????????"));
	//m_cbSearchMenu.AddString(_T("???? ????"));
	//m_cbSearchMenu.AddString(_T("???? ????"));
	//m_cbSearchMenu.AddString(_T("???? ????????"));
	//m_cbSearchMenu.AddString(_T("????????????"));

	m_cbSearchMenu.SetCurSel(0);
}

void CSecureManagementProgDlg::InitInternetMenu()
{
	m_cbInternet.AddString(_T("????"));
	m_cbInternet.AddString(_T("??????????"));
	m_cbInternet.AddString(_T("?????????????? ????"));
	m_cbInternet.AddString(_T("?????? ????"));

	m_cbInternet.SetCurSel(0);
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

	if (p == NULL)  //??????????????????????????
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
	m_progress.SetPos(0);
	if (!m_bSQL)
		return;
	CString cstSearch;
	vector<CString> PfCode, SecName, PfName, PfType;
	GetDlgItemText(IDC_EDIT_SEARCH, cstSearch);
	if (cstSearch.IsEmpty())	return;
	m_nClk = TRUE;
	m_progress.OffsetPos(10);
	m_CPlatform.SetFindVar(cstSearch);
	m_CPlatform.GetColumns(&m_connection, &PfCode, &PfName, &PfType);
	m_ListBox.ResetContent();
	m_progress.OffsetPos(10);
	for (CString name : PfName)
	{
		m_ListBox.AddString(name);
	}
	m_progress.OffsetPos(10);
}

void CSecureManagementProgDlg::OnBnClickedBtnStatus()
{
	vector<CString> cstsecname;

	m_pCCurSecureManger = new CCurSecureManager();
	m_CSecurityprog.GetAllSecName(&m_connection,&cstsecname);
	m_pCCurSecureManger->GetSecList(cstsecname);
	m_pCCurSecureManger->DoModal();
}

void CSecureManagementProgDlg::OnCbnSelchangeCbSearch()
{
	COperationStatus::SetSearching(TRUE);
	INT nCursel = m_cbSearchMenu.GetCurSel();
	m_SearchCondition = nCursel + 0X64;	//????????

	if (nCursel == 0 || nCursel == 2)
	{
		m_char = DB_MYHOST;
	}
	else
		m_char = DB_HOST;

	FreeSQL();
	ConntectSQL();

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
	::InvalidateRect(m_hWnd, NULL, FALSE);
	UpdateWindow();
	
	m_ListBox.ResetContent();
	m_ListCtrl.DeleteAllItems();
	m_edLink.Clear();

	COperationStatus::SetRefresh(FALSE);
}


void CSecureManagementProgDlg::OnLvnItemchangedListRes(NMHDR* pNMHDR, LRESULT* pResult)
{
	vector<CString> vPfCode;
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);	
	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();	//?????? ????????
	INT nCursel = m_ListCtrl.GetNextSelectedItem(pos);	//pos to int

	CString secname = m_ListCtrl.GetItemText(nCursel, 0);

	CFeatureManager* m_pFeature = (CFeatureManager*)GetDlgItem(IDD_DIALOG1);
	m_pFeature->UpdateStatus(IsInstall(secname), NULL);
	m_pFeature->SetEditLink(m_mayLink);
	m_pFeature->GetSecname(&secname);
	vPfCode.swap(m_CPlatform.GetPfNamebyCode(&m_connection, m_CSecurityprog.GetPlatformbySec(&m_connection, secname)));
	m_pFeature->GetCode(&vPfCode);

	if (secname == L"AhnLab Safe Transaction Application")
		m_pFeature->SetActivation(TRUE);
	else
		m_pFeature->SetActivation(FALSE);
	*pResult = 0;
}


void CSecureManagementProgDlg::OnLbnSelchangeListboxRes()
{
	CString cstList;
	vector<CString> SecName, PfCode, PfName, PfType, Install;

	//Feature ????????
	CFeatureManager* m_pFeature = (CFeatureManager*)GetDlgItem(IDD_DIALOG1);
	m_pFeature->UpdateStatus(FALSE, NULL);

	//ListBox Index ????????
	INT nCursel = m_ListBox.GetCurSel();
	if (nCursel != LB_ERR)
		m_ListBox.GetText(nCursel, cstList);

	m_CPlatform.SetFindVar(cstList);

	m_CPlatform.GetColumns(&m_connection, &PfCode, &PfName, &PfType);	//?????? ?????? ???? ????????
	m_CSecurityprog.GetColumns(&m_connection, &SecName, PfCode, &Install);	//?????? ?????? ???????????? ????????

	//?????? ?????? ???? ????????
	CString cstSite, cstImg;
	m_CPlatformInformation.GetColumns(&m_connection, PfCode[0], &cstSite, &cstImg);
	m_cstSite = cstSite;
	m_edLink.Clear();
	SetDlgItemText(IDC_EDIT_LINK, cstSite);	
	
	//?????? ?????? ?????? ????
	CRect rtPfImg;
	CImage Img;
	CString SavedImgPath;
	CDC* dc = m_pcPlatformImg.GetDC();
	
	SavedImgPath.Format(_T("PFImge.png"));
	m_pcPlatformImg.GetWindowRect(&rtPfImg);
	ScreenToClient(&rtPfImg);
	
	if (!m_CUrlAccess.DownloadImageFromHttp(cstImg, SavedImgPath))
	{
		AfxMessageBox(_T("Fail to download Image.."));
	}
	else
	{
		m_cstImg =SavedImgPath;
		Img.Load(SavedImgPath);		//??????????
		Img.StretchBlt(dc->m_hDC, 0, 0, rtPfImg.Width(), rtPfImg.Height(), SRCCOPY);	//?????? ????????
		//::InvalidateRect(m_hWnd, rtPfImg, TRUE);
	}

	ReleaseDC(dc);

	//?????? ???????? ???????????? ????
	m_ListCtrl.DeleteAllItems();		//???????? ??????
	INT num = m_ListCtrl.GetItemCount();
	INT curNum(0);

	for (CString name : SecName)
	{
		m_ListCtrl.InsertItem(num, name);
		CString InstallChoice = (Install[curNum] == '1') ? (_T("????")) : (_T("????"));
		m_ListCtrl.SetItem(num, 1, LVIF_TEXT, InstallChoice, NULL, NULL, NULL, NULL);
		m_ListCtrl.SetItem(num, 2, LVIF_TEXT, csIsInstall(name), NULL, NULL, NULL, NULL);
		curNum++;
	}
}

void CSecureManagementProgDlg::DrawImage(CString img)
{
	CImage Img;
	Img.Load(img);		//??????????

	CRect pcRect;
	GetDlgItem(IDC_PC_IMG)->GetClientRect(&pcRect);

	Img.StretchBlt(GetDlgItem(IDC_PC_IMG)->GetDC()->m_hDC, 0, 0, pcRect.Width(), pcRect.Height(), SRCCOPY);	//?????? ????????
}

#include <io.h>

BOOL CSecureManagementProgDlg::IsFileExist(CString Filename)
{
	return (_access(m_CMySQL.CStringToChar(Filename), 0) != -1) ? (TRUE) : (FALSE);
}

CString CSecureManagementProgDlg::csIsInstall(CString secname)
{
	CString _InstallationFT;

	if (secname == "AhnLab Safe Transaction Application")
		_InstallationFT = IsFileExist(_T("C:\\Program Files\\AhnLab\\Safe Transaction\\stsess.exe")) ? (_T("??????")) : (_T("??????"));
	else if (secname == "veraport G3")
		_InstallationFT = IsFileExist(_T("C:\\Program Files\\Wizvera\\Veraport20\\veraport-x64.exe")) ? (_T("??????")) : (_T("??????"));
	else if(secname =="TouchEn nxKey")
		_InstallationFT = IsFileExist(_T("C:\\Users\\KOREA\\Downloads\\TouchEn_nxKey_32bit.exe")) ? (_T("??????")) : (_T("??????"));
	else
		_InstallationFT.Format(_T("??????"));

	return _InstallationFT;
}

BOOL CSecureManagementProgDlg::IsInstall(CString secname)
{
	if (!m_mayLink.IsEmpty())
		m_mayLink.Format(_T("initial"));
	if (secname == "AhnLab Safe Transaction Application")
		m_mayLink.Format(_T("C:\\Program Files\\AhnLab\\Safe Transaction\\stsess.exe"));
	else if (secname == "veraport G3")
		m_mayLink.Format(_T("C:\\Program Files\\Wizvera\\Veraport20\\veraport-x64.exe"));
	else if (secname == "TouchEn nxKey")
		m_mayLink.Format(_T("C:\\Users\\KOREA\\Downloads\\TouchEn_nxKey_32bit.exe"));

	return IsFileExist(m_mayLink);
}


void CSecureManagementProgDlg::OnStnClickedStaticHyperlink()
{
	if (m_cstSite.IsEmpty())
	{
		AfxMessageBox(_T("???????? ???? ????????????:)!"));
		return;
	}
	COperationStatus::SetAccess(TRUE);
	ShellExecute(NULL, L"open", m_cstInternet, m_cstSite, NULL, SW_SHOW);
	COperationStatus::SetAccess(FALSE);
}


void CSecureManagementProgDlg::OnCbnSelchangeCbInternet()
{
	INT nCursel;
	nCursel = m_cbInternet.GetCurSel();

	switch (nCursel)
	{
	case CHROME:
		m_cstInternet = _T("chrome.exe");
		break;
	case EXPLORE:
		m_cstInternet = _T("iexplore.exe");
		break;
	case MICOROSOFT_EDGE:
		m_cstInternet = _T("msedge.exe");
		break;
	case WHALE:
		m_cstInternet = _T("whale.exe");
	default:
		break;
	}
}
