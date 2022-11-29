#pragma once
#include <list>
#include <vector>
using namespace std;
// CCurSecureManager dialog

class CCurSecureManager : public CDialogEx
{
	DECLARE_DYNAMIC(CCurSecureManager)

public:
	CCurSecureManager(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCurSecureManager();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void GetSecList(vector<CString> sec) { m_vSec.swap(sec); };
	HKEY AccessRegist(vector<CString> vSecname);

private:
	vector<CString>	m_vSec;
	vector<CString> m_List;
	vector<CHAR> GetKeyList(HKEY hKey);
public:
	afx_msg void OnBnClickedBtnCurdel();
	CListBox m_ListBox;
};
