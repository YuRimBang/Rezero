#pragma once
#include "MenuManger.h"

// CFeatureManager dialog

class CFeatureManager : public CFormView
{
	DECLARE_DYNAMIC(CFeatureManager)

public:
	CFeatureManager(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CFeatureManager();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	
	afx_msg void OnBnClickedBtnDelete();	//Delete Button
	afx_msg void OnBnClickedBtnCheck();	//Activation checkbox
	afx_msg LRESULT UpdateStatus(WPARAM wparam, LPARAM lparam);
public:
	void ButtonStatusInit(BOOL IsStatus);	//��ư ���� �ʱ�ȭ
	void SetEditLink(CString link);	//�÷��� ��ũ ���

public:
	CButton m_chActivation;
	CEdit m_editDistk;
	CProgressCtrl m_Progress;
};
