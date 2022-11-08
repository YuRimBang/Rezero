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
	BOOL					ConnectToDB(MYSQL* mysql);		//DB����
	
	VOID						Finish_with_error(MYSQL* con);	//mysql ���� ���н� error
	VOID						FreeSQL(MYSQL_RES* res);			//mysql ���� ����
	
	char*						CStringToChar(CString csting);		//CString -> char* ������Ÿ�� ��ȯ
};

class CPlatform : public CMySQL
{
public:
	CPlatform();
	virtual ~CPlatform();

protected:
	//MYSQL*					m_connection;
	
	CString					m_cstFindPlaform;		//����ڰ� ã�� �̸�
	CString					m_cstTablename;		//���̺� �̸�
	CString					m_cstCode;				//�÷��� �ڵ�
	CString					m_cstName;				//�÷��� �̸�
	CString					m_cstType;				//�÷��� Ÿ��

	INT						m_nFieldsCnt;				//�ʵ� ����


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

	CString					m_cstFindPlaform;		//����ڰ� ã�� �̸�
	CString					m_cstTablename;		//���̺� �̸�
	CString					m_cstCode;				//�÷��� �ڵ�
	CString					m_cstName;				//�������α׷� �̸�
	CString					m_cstInstall;				//��ġ �ʼ�/����

	INT						m_nFieldsCnt;				//�ʵ� ����
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