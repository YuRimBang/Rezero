
// SecureManagementProgDlg.h : header file
//
#include "CFeatureManager.h"
#include "CCurSecureManager.h"
#include "CFeatureManager.h"
#include "CMySQL.h"
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
	MYSQL							m_connection;
	HICON							m_hIcon;
	CMySQL							m_CMySQL;
	CSecurityProg					m_CSecurityprog;
	CPlatform						m_CPlatform;
	CFeatureManager*			m_pCFeatureManager;
	CCurSecureManager*		m_pCCurSecureManger;
	CFeatureManager			m_CFeatureManager;
	CComboBox					m_cbSearchMenu;	//�˻����� Combobox

	BOOL							m_nClk;	//��ĪȮ��
	// Generated message map functions
	virtual BOOL					OnInitDialog();
	afx_msg void					OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void					OnPaint();
	afx_msg HCURSOR			OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	void								ConntectSQL();	//SQL����
	void								InitSearchMenu();	//�˻� ���� �ʱ�ȭ
	void								AllocForm();	//Feature Dlg ���� ���̾�α׿� ���̱�

public:
	CListBox						m_listbox;
	HWND							m_childhwnd;
	INT								m_SearchCondition;	//�˻�����

public:
	afx_msg void					OnBnClickedBtnSearch();
	afx_msg void					OnBnClickedBtnStatus();
	afx_msg void					OnLbnSelchangeListResbox();
	afx_msg void					OnCbnSelchangeCbSearch();
};
