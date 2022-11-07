// CPCControl.cpp : implementation file
//

#include "pch.h"
#include "SecureManagementProg.h"
#include "CPCControl.h"
#include "afxdialogex.h"


// CPCControl dialog

IMPLEMENT_DYNAMIC(CPCControl, CDialogEx)

CPCControl::CPCControl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SECUREMANAGEMENTPROG_DIALOG, pParent)
{

}

CPCControl::~CPCControl()
{
}

void CPCControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPCControl, CDialogEx)
END_MESSAGE_MAP()


// CPCControl message handlers
