
// SecureManagementProgDlg.h : header file
//
#include "CUrlAccess.h"
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
	
	/*mysql table*/
	CMySQL							m_CMySQL;
	CSecurityProg					m_CSecurityprog;
	CPlatform						m_CPlatform;
	CPlatformInformation		m_CPlatformInformation;
	
	CUrlAccess					m_CUrlAccess;
	CFeatureManager*			m_pCFeatureManager;
	CCurSecureManager*		m_pCCurSecureManger;
	CFeatureManager*			m_CFeatureManager;
	CComboBox					m_cbSearchMenu;	//검색조건 Combobox

	BOOL							m_Init;
	BOOL							m_bSubDialog;
	BOOL							m_nClk;	//서칭확인
	
	// Generated message map functions
	afx_msg void					OnSize(UINT nType, int cx, int cy);		//Dailog size
	afx_msg void					OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void					OnPaint();
	afx_msg HCURSOR			OnQueryDragIcon();
	afx_msg LRESULT			OnProgressUpdate(WPARAM wParam, LPARAM lParam);

	afx_msg void					OnBnClickedBtnSearch();		//SearchButton 클릭
	afx_msg void					OnBnClickedBtnStatus();		//StatusButton 클릭
	afx_msg void					OnCbnSelchangeCbSearch();	//검색 제약조건 설정
	afx_msg void					OnBnClickedBtnRefresh();	//Refresh Button 클릭
	afx_msg void					OnLvnItemchangedListRes(NMHDR* pNMHDR, LRESULT* pResult);		//보안프로그램 list 클릭시 발생
	afx_msg void					OnLbnSelchangeListboxRes();	//플랫폼 list 클릭 시 발생
	
	virtual BOOL					PreTranslateMessage(MSG* pMsg);
	virtual BOOL					OnInitDialog();


	DECLARE_MESSAGE_MAP()

protected:
	void								SetUpForDynamicLayout();
	void								ConntectSQL();	//SQL연결
	void								InitSearchMenu();	//검색 조건 초기화
	void								AllocForm();	//Feature Dlg 메인 다이얼로그에 붙이기
	void								SearchSecureProgram();
	
	BOOL							IsFileExist(CString Filename);	//파일이 존재하는지
	CString							csIsInstall(CString secname);
	BOOL							IsInstall(CString secname);
	static UINT						ThreadSearchSecureprog(LPVOID pParam);
public:
	CString							m_mayLink;	//임시 저장소 링크
	CListBox						m_ListBox;
	CListCtrl							m_ListCtrl;
	CImage							m_Image;
	HWND							m_childhwnd;
	INT								m_SearchCondition;	//검색조건

public:


	CStatic m_pcPlatformImg;
	CEdit m_edLink;
};
