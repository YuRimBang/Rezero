#pragma once
#include "afxinet.h"

class CUrlAccess
{
public:
	DWORD			GetUrlFileLength(CString url);//url img 크기
	DWORD			Download(HINTERNET hInternet, char* pszURL, char* pszFileName, BYTE* pBuffer);


	BOOL			DownloadUrlFileBuffer(CString url, CString ImgName);	//이미지 다운로드
	void				AccessSession(CString url);		//접속
	void				SaveImage(INT nWidth, INT nHeight ,CString url, CString Filename);

	char*				CStringToChar(CString csting);

	INT				getFileFromHttp(CString pszUrl, CString pszFile);
};

