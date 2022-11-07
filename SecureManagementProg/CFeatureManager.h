#pragma once
#include "MenuManger.h"

// CFeatureManager dialog

class CFeatureManager : public CFormView
{
	DECLARE_DYNAMIC(CFeatureManager)

public:
	CFeatureManager(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CFeatureManager();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	
	
	afx_msg void OnBnClickedBtnDelete();
	afx_msg LRESULT UpdateStatus(WPARAM wparam, LPARAM lparam);
public:
	void ButtonStatusInit(BOOL IsStatus);

	/*Setter*/
	void SetParenthwnd(HWND hwnd) { hwnd = m_hWnd; }
public:
	CButton m_chActivation;
};
