#include "pch.h"
#include "CMySQL.h"

CMySQL::CMySQL() : CWnd()
, m_cstSchema(_T("secureprogmanagerdb"))
{
}

CMySQL::~CMySQL()
{
}

BOOL CMySQL::ConnectToDB(MYSQL* mysql)
{
	mysql_init(mysql);
	return (BOOL)mysql_real_connect(mysql, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, DB_PORT, NULL, 0);
}

VOID CMySQL::Finish_with_error(MYSQL* con)
{
	AfxMessageBox((CString)mysql_error(con));
	mysql_close(con);
}

VOID CMySQL::FreeSQL(MYSQL_RES* res)
{
	mysql_free_result(res);
	mysql_close(m_connection);
}

char* CMySQL::CStringToChar(CString csting)
{
	wchar_t* wQuery = LPWSTR(LPCWSTR(csting));
	int strSize(WideCharToMultiByte(CP_ACP, 0, wQuery, -1, NULL, 0, NULL, NULL));
	char* cQuery = new char[strSize];
	WideCharToMultiByte(CP_ACP, 0, wQuery, -1, cQuery, strSize, 0, 0);

	return cQuery;
}

//Class for table

CPlatform::CPlatform()
	: CMySQL()
	, m_cstTablename(L"platform")
	, m_nFieldsCnt(0)
{
}

CPlatform::~CPlatform()
{
}

BOOL CPlatform::ConnectToDB()
{
	m_connection = mysql_init(NULL);
	return (BOOL)mysql_real_connect(GetConnection(), DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, DB_PORT, NULL, 0);
}

VOID CPlatform::GetFieldsNum(MYSQL_RES* res)
{
	if (res == NULL)
		Finish_with_error(GetConnection());
	m_nFieldsCnt = mysql_num_fields(res);
}

BOOL CPlatform::Isinit(CString orgincst, CString findcst)
{
	if (orgincst.Find(findcst) == -1)
		return FALSE;
	else
		return TRUE;
}

void CPlatform::GetColumns(MYSQL* connect, vector<CString>* findVar, vector<CString>* Plaformname)
{
	MYSQL_ROW row;
	CString cstName;	//포함되어있는지 확인하기위한 변수
	vector<CString>		vcstPfcode;

	mysql_query(connect, "set names euckr");
	if (mysql_query(connect, "SELECT * FROM platform"))
		Finish_with_error(connect);
	MYSQL_RES* result = mysql_store_result(connect);
	GetFieldsNum(result);


	while (row = mysql_fetch_row(result))
	{
		cstName = row[1];
		if(Isinit(cstName, m_cstFindPlaform))
		{
			m_cstCode = row[0];
			m_cstName = cstName;
			m_cstType = row[2];

			vcstPfcode.push_back(m_cstCode);
			Plaformname->push_back(m_cstName);
		}
	}
	
	vcstPfcode.swap(*findVar);
	FreeSQL(result);
}

//CSecurityProg class

CSecurityProg::CSecurityProg()
	: CMySQL()
	, m_cstTablename(L"securityprog")
	, m_nFieldsCnt(0)
{
}

CSecurityProg::~CSecurityProg()
{
}

BOOL CSecurityProg::ConnectToDB()
{
	m_connection = mysql_init(NULL);
	return (BOOL)mysql_real_connect(GetConnection(), DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, DB_PORT, NULL, 0);
}

VOID CSecurityProg::GetFieldsNum(MYSQL_RES* res)
{
	if (res == NULL)
		Finish_with_error(GetConnection());
	m_nFieldsCnt = mysql_num_fields(res);
}

void CSecurityProg::GetColumns(MYSQL* connect, vector<CString>*name, vector<CString> Findvar)
{
	mysql_query(connect, "set names euckr");
	if (mysql_query(connect, "SELECT * FROM securityprog"))
		Finish_with_error(connect);
	MYSQL_RES* result = mysql_store_result(connect);
	GetFieldsNum(result);

	vector<CString>		vcstSecName;
	MYSQL_ROW			row;
	
	while (row = mysql_fetch_row(result))
	{
		for (CString cst : Findvar)
		{
			if (row[0] == cst)
			{
				m_cstCode = row[0];
				m_cstName = row[1];
				vcstSecName.push_back(m_cstName);
				m_cstInstall = row[2];
			}
		}
	}
	vcstSecName.swap(*name);
	FreeSQL(result);
}