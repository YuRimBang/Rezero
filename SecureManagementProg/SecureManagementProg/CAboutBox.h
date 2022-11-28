#pragma once
#include "CMySQL.h"
#include <vector>

using namespace std;
// CAboutBox dialog

class CAboutBox : public CDialogEx
{
	DECLARE_DYNAMIC(CAboutBox)

public:
	CAboutBox(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAboutBox();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	CMySQL m_MySQL;
	vector<CString> m_vfCode;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void SetCodeList(vector<CString> npfcode) { m_vfCode.swap(npfcode); };

	afx_msg void OnLbnSelchangeListPlatform();
	virtual BOOL OnInitDialog();

protected:
public:
	CListBox m_codeList;
};
