#pragma once


// CPCControl dialog

class CPCControl : public CDialogEx
{
	DECLARE_DYNAMIC(CPCControl)

public:
	CPCControl(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPCControl();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SECUREMANAGEMENTPROG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
