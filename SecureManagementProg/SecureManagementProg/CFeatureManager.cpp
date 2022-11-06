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
}


BEGIN_MESSAGE_MAP(CFeatureManager, CFormView)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CFeatureManager::OnBnClickedBtnDelete)
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

void CFeatureManager::ButtonStatusInit(BOOL IsStatus)
{
	m_chActivation.EnableWindow(IsStatus);
	GetDlgItem(IDC_BTN_DELETE)->EnableWindow(IsStatus);
	GetDlgItem(IDC_BTN_ABOUT)->EnableWindow(IsStatus);
	GetDlgItem(IDC_EDIT_VOLUME)->EnableWindow(IsStatus);
	GetDlgItem(IDC_EDIT_DISK)->EnableWindow(IsStatus);
}

void CFeatureManager::OnBnClickedBtnDelete()
{
	// TODO: Add your control notification handler code here
}
