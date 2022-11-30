// CFeatureManager.cpp : implementation file
//

#include "pch.h"
#include "SecureManagementProg.h"
#include "CFeatureManager.h"
#include "afxdialogex.h"


// CFeatureManager dialog

IMPLEMENT_DYNAMIC(CFeatureManager, CFormView)

CFeatureManager::CFeatureManager(CWnd* pParent /*=nullptr*/)
	: CFormView(IDD_DIALOG1)
{

}

CFeatureManager::~CFeatureManager()
{
}

void CFeatureManager::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_ACTIVATION, m_chActivation);
	DDX_Control(pDX, IDC_EDIT_DISK, m_editDistk);
	//DDX_Control(pDX, IDC_CHK_ACTIVATION, m_chkActivation);
}


BEGIN_MESSAGE_MAP(CFeatureManager, CFormView)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CFeatureManager::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CFeatureManager::OnBnClickedBtnAbout)
	ON_BN_CLICKED(IDC_CHK_ACTIVATION, &CFeatureManager::OnBnClickedBtnCheck)
	ON_MESSAGE(MSG_SECUREINIT, &CFeatureManager::UpdateStatus)
END_MESSAGE_MAP()


// CFeatureManager message handlers


BOOL CFeatureManager::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CFeatureManager::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ButtonStatusInit(FALSE);
}

LRESULT CFeatureManager::UpdateStatus(WPARAM wparam, LPARAM lparam)
{
	ButtonStatusInit(wparam);
	return LRESULT();
}

void CFeatureManager::ButtonStatusInit(BOOL IsStatus)
{
 	m_chActivation.EnableWindow(IsStatus);
	GetDlgItem(IDC_BTN_DELETE)->EnableWindow(IsStatus);
	//GetDlgItem(IDC_BTN_ABOUT)->EnableWindow(IsStatus);
	GetDlgItem(IDC_EDIT_VOLUME)->EnableWindow(IsStatus);
	GetDlgItem(IDC_EDIT_DISK)->EnableWindow(IsStatus);
	GetDlgItem(IDC_CHK_ACTIVATION)->EnableWindow(IsStatus);
}

void CFeatureManager::SetEditLink(CString link)
{
	m_editDistk.Clear();		//edit창 지우기
	SetDlgItemText(IDC_EDIT_DISK, _T(""));
	if( link !="initial")
		SetDlgItemText(IDC_EDIT_DISK, link);
}

void CFeatureManager::SetActivation(BOOL chk)
{
	//m_chkActivation.SetCheck(chk);
	((CButton*)GetDlgItem(IDC_CHK_ACTIVATION))->SetCheck(chk);
}

void CFeatureManager::OnBnClickedBtnCheck()
{
	if (((CButton*)GetDlgItem(IDC_CHK_ACTIVATION))->GetCheck())
		AfxMessageBox(_T("활성화 되었습니다!"));
	else
		AfxMessageBox(_T("비활성화 되었습니다!"));
}

void CFeatureManager::OnBnClickedBtnDelete()
{
	if (MessageBox(_T("삭제하시겠습니까??"), _T("삭제"), MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2) == IDYES)
		AfxMessageBox(_T("Fail to Delete!"));
}

void CFeatureManager::OnBnClickedBtnAbout()
{
	m_pCAboutBox = new CAboutBox();
	m_pCAboutBox->SetCodeList(m_vnPfCode);
	m_pCAboutBox->DoModal();
}