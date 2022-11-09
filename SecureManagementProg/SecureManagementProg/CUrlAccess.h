#pragma once
#include "afxinet.h"

class CUrlAccess
{
public:
	DWORD			GetUrlFileLength(CString url);//url img 크기
	DWORD			Download(HINTERNET hInternet, char* pszURL, char* pszFileName, BYTE* pBuffer);	// url로 이미지 다운로드

	BOOL			DownloadforUrl(CString url, CString ImgName);	// url로 이미지 다운로드
	INT				DownloadImageFromHttp(CString pszUrl, CString pszFile);	// url로 이미지 다운로드

	void				AccessSession(CString url);		//세션접속
	void				SaveImage(INT nWidth, INT nHeight ,CString url, CString Filename);		//다운로드 이미지 pc내 저장

	char*				CStringToChar(CString csting);


};

