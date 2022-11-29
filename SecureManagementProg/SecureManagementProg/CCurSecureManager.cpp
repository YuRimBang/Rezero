// CCurSecureManager.cpp : implementation file
//

#include "pch.h"
#include "SecureManagementProg.h"
#include "CCurSecureManager.h"
#include "afxdialogex.h"


// CCurSecureManager dialog

IMPLEMENT_DYNAMIC(CCurSecureManager, CDialogEx)

CCurSecureManager::CCurSecureManager(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CCurSecureManager::~CCurSecureManager()
{
}

void CCurSecureManager::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_CURSECURE, m_ListBox);
}

HKEY CCurSecureManager::AccessRegist(vector<CString> vSecname)
{
    HKEY hKey;
    TCHAR szDefaultPath[_MAX_PATH] = { 0 };
    DWORD dwBufLen = MAX_PATH;
    DWORD dwBytes = 0;
    LSTATUS	RegOpen = ERROR_SUCCESS;
    CString cstRegistPath;

    cstRegistPath.Format(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
    RegOpen = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        cstRegistPath, 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hKey);
    if(RegOpen == ERROR_SUCCESS)
        AfxMessageBox(_T("Success to Access Regist"));
    else
        AfxMessageBox(_T("Fail to Access Regist"));

    for (CString Secname : vSecname)
    {
        RegOpen = ::RegQueryValueEx(hKey, Secname, NULL, NULL, NULL, &dwBytes);
        if (RegOpen == ERROR_SUCCESS)
        {
            LONG lResult = RegQueryValueEx(hKey, Secname, NULL, NULL, (LPBYTE)szDefaultPath, &dwBytes);
            m_ListBox.AddString(Secname);
        }
    }
    RegCloseKey(hKey);

    return hKey;
}

BOOL CCurSecureManager::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    if (!m_List.empty())
        m_List.clear();
    AccessRegist(m_vSec);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_MESSAGE_MAP(CCurSecureManager, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_CURDEL, &CCurSecureManager::OnBnClickedBtnCurdel)
END_MESSAGE_MAP()

vector< CHAR > CCurSecureManager::GetKeyList(HKEY hKey)
{
    vector< CHAR > retval_;
    CHAR     achKey[MAX_PATH];    // buffer for subkey name
    DWORD   cbName;                     // size of name string 
    CHAR     achClass[MAX_PATH] = "";   // buffer for class name 
    DWORD   cchClassName = MAX_PATH;    // size of class string 
    DWORD   cSubKeys = 0;                 // number of subkeys 
    DWORD   cbMaxSubKey;                // longest subkey size 
    DWORD   cchMaxClass;                // longest class string 
    DWORD   cValues;                    // number of values for key 
    DWORD   cchMaxValue;                // longest value name 
    DWORD   cbMaxValueData;             // longest value data 
    DWORD   cbSecurityDescriptor;       // size of security descriptor 
    FILETIME ftLastWriteTime;           // last write time 

    DWORD i, lretval_;

    DWORD cchValue = MAX_PATH;

    // Get the class name and the value count. 
    lretval_ = RegQueryInfoKey(
        hKey,   // key handle 
        (LPWSTR)achClass,               // buffer for class name 
        &cchClassName,          // size of class string 
        NULL,                   // reserved 
        &cSubKeys,              // number of subkeys 
        &cbMaxSubKey,           // longest subkey size 
        &cchMaxClass,           // longest class string 
        &cValues,               // number of values for this key 
        &cchMaxValue,           // longest value name 
        &cbMaxValueData,        // longest value data 
        &cbSecurityDescriptor,  // security descriptor 
        &ftLastWriteTime);      // last write time 

    // Enumerate the subkeys, until RegEnumKeyEx fails.

    if (cSubKeys)
    {
        //      printf( "Number of subkeys: %d\n", cSubKeys);
        for (i = 0; i< cSubKeys;i++)
            {
                cbName = MAX_PATH;
                lretval_ = RegEnumKeyEx(hKey,
                                        i,
                                        (LPWSTR)achKey,
                                        &cbName,
                                        NULL,
                                        NULL,
                                        NULL,
                                        &ftLastWriteTime);
                if (lretval_ == ERROR_SUCCESS)
                {
                    retval_.push_back(*achKey);
                }
            }
    }
    return retval_;
}


void CCurSecureManager::OnBnClickedBtnCurdel()
{
    // TODO: Add your control notification handler code here
}
