#pragma once
#include "afxinet.h"

class CUrlAccess
{
public:
	DWORD			GetUrlFileLength(CString url);//url img ũ��
	DWORD			Download(HINTERNET hInternet, char* pszURL, char* pszFileName, BYTE* pBuffer);	// url�� �̹��� �ٿ�ε�

	BOOL			DownloadforUrl(CString url, CString ImgName);	// url�� �̹��� �ٿ�ε�
	INT				DownloadImageFromHttp(CString pszUrl, CString pszFile);	// url�� �̹��� �ٿ�ε�

	void				AccessSession(CString url);		//��������
	void				SaveImage(INT nWidth, INT nHeight ,CString url, CString Filename);		//�ٿ�ε� �̹��� pc�� ����

	char*				CStringToChar(CString csting);


};

