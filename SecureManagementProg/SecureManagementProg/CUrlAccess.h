#pragma once
#include "afxinet.h"

class CUrlAccess
{
public:
	DWORD			GetUrlFileLength(CString url);//url img ũ��
	DWORD			Download(HINTERNET hInternet, char* pszURL, char* pszFileName, BYTE* pBuffer);


	BOOL			DownloadUrlFileBuffer(CString url, CString ImgName);	//�̹��� �ٿ�ε�
	void				AccessSession(CString url);		//����
	void				SaveImage(INT nWidth, INT nHeight ,CString url, CString Filename);

	char*				CStringToChar(CString csting);

	INT				getFileFromHttp(CString pszUrl, CString pszFile);
};

