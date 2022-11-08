
// SecureManagementProgDlg.h : header file
//
#include "CFeatureManager.h"
#include "CCurSecureManager.h"
#include "CFeatureManager.h"
#include "ProgressManager.h"
#include "OperationStatus.h"
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
	CFeatureManager*			m_CFeatureManager;
	CComboBox					m_cbSearchMenu;	//�˻����� Combobox

	BOOL							m_Init;
	BOOL							m_bSubDialog;
	BOOL							m_nClk;	//��ĪȮ��
	// Generated message map functions
	afx_msg void					OnSize(UINT nType, int cx, int cy);
	afx_msg void					OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void					OnPaint();
	afx_msg HCURSOR			OnQueryDragIcon();
	afx_msg LRESULT			OnProgressUpdate(WPARAM wParam, LPARAM lParam);

	afx_msg void					OnBnClickedBtnSearch();		//SearchButton Ŭ��
	afx_msg void					OnBnClickedBtnStatus();		//StatusButton Ŭ��
	afx_msg void					OnCbnSelchangeCbSearch();	//�˻� �������� ����
	afx_msg void					OnBnClickedBtnRefresh();
	afx_msg void					OnLvnItemchangedListRes(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void					OnLbnSelchangeListboxRes();
	virtual BOOL					PreTranslateMessage(MSG* pMsg);
	virtual BOOL					OnInitDialog();


	DECLARE_MESSAGE_MAP()

protected:
	void								ConntectSQL();	//SQL����
	void								InitSearchMenu();	//�˻� ���� �ʱ�ȭ
	void								AllocForm();	//Feature Dlg ���� ���̾�α׿� ���̱�
	void								SearchSecureProgram();
	
	static UINT						ThreadSearchSecureprog(LPVOID pParam);
public:
	CListBox						m_ListBox;
	CListCtrl							m_ListCtrl;
	HWND							m_childhwnd;
	INT								m_SearchCondition;	//�˻�����

public:


};
