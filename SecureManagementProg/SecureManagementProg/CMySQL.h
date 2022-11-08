#pragma once
#include "CMySQL.h"
#include "MySQLDefinition.h"
#include <vector>

using namespace std;

class CMySQL : public CWnd
{
public:
	CMySQL();
	virtual ~CMySQL();

protected:
	MYSQL*					m_connection;
	CString					m_cstSchema;

public:
	/*Getter*/
	MYSQL*					GetConnection() { return m_connection; };	//DB Connect

public:
	BOOL					ConnectToDB(MYSQL* mysql);		//DB연결
	
	VOID						Finish_with_error(MYSQL* con);	//mysql 연결 실패시 error
	VOID						FreeSQL(MYSQL_RES* res);			//mysql 연결 해제
	
	char*						CStringToChar(CString csting);		//CString -> char* 데이터타입 변환
};

class CPlatform : public CMySQL
{
public:
	CPlatform();
	virtual ~CPlatform();

protected:
	//MYSQL*					m_connection;
	
	CString					m_cstFindPlaform;		//사용자가 찾는 이름
	CString					m_cstTablename;		//테이블 이름
	CString					m_cstCode;				//플랫폼 코드
	CString					m_cstName;				//플랫폼 이름
	CString					m_cstType;				//플랫폼 타입

	INT						m_nFieldsCnt;				//필드 갯수


public:
	virtual BOOL			ConnectToDB();

	/*Setter*/
	void						SetFindVar(CString cstFindvar) { m_cstFindPlaform = cstFindvar; };

	/*Getter*/
	void						GetColumns(MYSQL* connect, vector<CString>* SecureProgram, vector<CString>* Plaformname, vector<CString>* PlatformType);
	void						GetFieldsNum(MYSQL_RES* res);
	
	MYSQL*					GetConnection() { return m_connection; };
	
	CString					GetName() { return m_cstName; }
	CString					GetType() { return m_cstType; }
	CString					GetCode() { return m_cstCode; }

	BOOL					Isinit(CString orgincst, CString findcst);
};

class CSecurityProg : public CMySQL
{
public:
	CSecurityProg();
	virtual ~CSecurityProg();

protected:
	//MYSQL*					m_connection;

	CString					m_cstFindPlaform;		//사용자가 찾는 이름
	CString					m_cstTablename;		//테이블 이름
	CString					m_cstCode;				//플랫폼 코드
	CString					m_cstName;				//보안프로그램 이름
	CString					m_cstInstall;				//설치 필수/선택

	INT						m_nFieldsCnt;				//필드 갯수
public:
	virtual BOOL			ConnectToDB();
	BOOL					Isinit(CString orgincst, CString findcst);
	/*Setter*/
	void						SetFindVar(CString cstFindvar) { m_cstFindPlaform = cstFindvar; };

	/*Getter*/
	void						GetColumns(MYSQL* connect, vector<CString>* SecureProgname, vector<CString> PfCode, vector<CString>* Install);
	void						GetFieldsNum(MYSQL_RES* res);

	MYSQL* GetConnection() { return m_connection; };

	CString					GetName() { return m_cstName; }
	CString					GetInstall() { return m_cstInstall; }
	CString					GetCode() { return m_cstCode; }

};