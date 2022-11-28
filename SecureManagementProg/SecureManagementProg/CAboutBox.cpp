// CAboutBox.cpp : implementation file
//

#include "pch.h"
#include "SecureManagementProg.h"
#include "CAboutBox.h"
#include "afxdialogex.h"



// CAboutBox dialog

IMPLEMENT_DYNAMIC(CAboutBox, CDialogEx)

CAboutBox::CAboutBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CAboutBox::~CAboutBox()
{
}

void CAboutBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PLATFORM, m_codeList);
}


BEGIN_MESSAGE_MAP(CAboutBox, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_PLATFORM, &CAboutBox::OnLbnSelchangeListPlatform)
END_MESSAGE_MAP()


// CAboutBox message handlers

void CAboutBox::OnLbnSelchangeListPlatform()
{
	// TODO: Add your control notification handler code here
}


BOOL CAboutBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!m_vfCode.empty())
		for (CString code : m_vfCode)
			m_codeList.AddString(code);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
