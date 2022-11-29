#pragma once
#include "CMySQL.h"
#include "MySQLDefinition.h"
#include <vector>
#include <algorithm>

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
	char*						 CStringToChar(CString csting);		//CString -> char* ������Ÿ�� ��ȯ

	BOOL					ConnectToDB(MYSQL* mysql, const char* host);		//DB����
	BOOL					Isinit(CString orgincst, CString findcst);

	VOID						Finish_with_error(MYSQL* con);	//mysql ���� ���н� error
	VOID						FreeSQL(MYSQL_RES* res);			//mysql ���� ����
	

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
	
	/*Column*/
	CString					m_cstCode;				//�÷��� �ڵ�
	CString					m_cstName;				//�÷��� �̸�
	CString					m_cstType;				//�÷��� Ÿ��

	INT						m_nFieldsCnt;				//�ʵ� ����


public:
	virtual MYSQL*		GetConnection() { return m_connection; };
	virtual BOOL			ConnectToDB();
	virtual BOOL			Isinit(CString orgincst, CString findcst);

	/*Setter*/
	void						SetFindVar(CString cstFindvar) { m_cstFindPlaform = cstFindvar; };

	/*Getter*/
	void						GetColumns(MYSQL* connect, vector<CString>* SecureProgram, vector<CString>* Plaformname, vector<CString>* PlatformType);
	void						GetFieldsNum(MYSQL_RES* res);
	
	vector<CString>		GetPfNamebyCode(MYSQL* connect, vector<CString> PfCode);
	
	CString					GetName() { return m_cstName; }
	CString					GetType() { return m_cstType; }
	CString					GetCode() { return m_cstCode; }


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
	
	/*Column*/
	CString					m_cstCode;				//�÷��� �ڵ�
	CString					m_cstName;				//�������α׷� �̸�
	CString					m_cstInstall;				//��ġ �ʼ�/����

	INT						m_nFieldsCnt;				//�ʵ� ����

public:
	virtual MYSQL*		GetConnection() { return m_connection; };
	virtual BOOL			ConnectToDB();
	virtual BOOL			Isinit(CString orgincst, CString findcst);
	
	/*Setter*/
	void						SetFindVar(CString cstFindvar) { m_cstFindPlaform = cstFindvar; };

	/*Getter*/
	void						GetColumns(MYSQL* connect, vector<CString>* SecureProgname, vector<CString> PfCode, vector<CString>* Install);
	void						GetFieldsNum(MYSQL_RES* res);
	void						GetAllSecName(MYSQL* connect, vector<CString>* Secname);
	CString					GetName() { return m_cstName; }
	CString					GetInstall() { return m_cstInstall; }
	CString					GetCode() { return m_cstCode; }
	vector<CString>			GetPlatformbySec(MYSQL* connect, CString cstSecname);
	
};

class CPlatformInformation : public CMySQL
{
public:
	CPlatformInformation();
	virtual ~CPlatformInformation();

protected:
	CString					m_cstTablename;		//���̺� �̸�
	CString					m_cstPfCode;				//�÷��� �ڵ�
	CString					m_cstSite;					//�÷��� ����Ʈ
	CString					m_cstImg;					//�÷��� �̹�����ũ

	INT						m_nFieldsCnt;				//�ʵ� ����

public:
	virtual MYSQL*		GetConnection() { return m_connection; };
	virtual BOOL			ConnectToDB();
	virtual BOOL			Isinit(CString orgincst, CString findcst);

	/*Getter*/
	void						GetColumns(MYSQL* connect, CString PfCode, CString* Site, CString* Image);
};