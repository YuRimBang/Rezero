
// SecureManagementProgDlg.h : header file
//
#include "CFeatureManager.h"
#include "CCurSecureManager.h"
#pragma once


// CSecureManagementProgDlg dialog
class CSecureManagementProgDlg : public CDialogEx
{
// Construction
public:
	CSecureManagementProgDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SECUREMANAGEMENTPROG_DIALOG };
#endif

	protected:
	virtual void						DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON							m_hIcon;
	CFeatureManager*			m_pCFeatureManager;
	CCurSecureManager*		m_pCCurSecureManger;

	CComboBox					m_cbSearchMenu;	//검색조건 Combobox

	// Generated message map functions
	virtual BOOL					OnInitDialog();
	afx_msg void					OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void					OnPaint();
	afx_msg HCURSOR			OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	void								InitSearchMenu();	//검색 조건 초기화
	void								AllocForm();	//Feature Dlg 메인 다이얼로그에 붙이기
public:
	afx_msg void					OnBnClickedBtnSearch();
	
	afx_msg void OnBnClickedBtnStatus();
};
