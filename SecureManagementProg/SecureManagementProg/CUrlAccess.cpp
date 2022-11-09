#include "pch.h"
#include "CUrlAccess.h"

//void CUrlAccess::AccessSession(CString url)
//{
//	CInternetSession* pSession;
//	CStdioFile* pFile;
//	TCHAR szError[1024];
//	TRY
//	{
//	  pSession = new CInternetSession;
//	  pFile = pSession->OpenURL(url);
//	}
//		CATCH(CInternetException, pEx)
//		pEx->GetErrorMessage(szError, 1024);
//
//
//	//END_CATCH
//	//	if (pFile != NULL)
//	//	{
//	//		CHttpFile* pHttpFile = (CHttpFile*)pFile;
//
//	//		// pHttpFile->ReadString(CString DataType);
//
//	//		delete pHttpFile;
//	//		pHttpFile = NULL;
//	//		pFile = NULL;
//	//	}
//
//	//if (pSession != NULL)
//	//{
//	//	pSession->Close();
//	//	delete pSession;
//	//	pSession = NULL;
//	//}
//}

DWORD CUrlAccess::GetUrlFileLength(CString url)
{
	DWORD filesize;

	TCHAR   szCause[255];
	CString CauseOfError;
	TRY
	{
	 CInternetSession session;
	 CHttpFile* remotefile = (CHttpFile*)session.OpenURL(url,1,INTERNET_FLAG_TRANSFER_BINARY);
	 TCHAR szContentLength[32];
	 DWORD dwInfoSize = 32;
	 DWORD dwFileSize = 0;
	 BOOL bGotFileSize = FALSE;
	 if (remotefile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, szContentLength, &dwInfoSize , NULL))
	 {
	  bGotFileSize = TRUE;
	  dwFileSize = (DWORD)_ttol(szContentLength);
	  filesize = dwFileSize;// Return 값에 할당.
	 }
	 else
	 { // 에러나 나서 파일이 없을경우에
	  filesize = -1;
	 }
	 remotefile->Close();
	 session.Close();
	 delete remotefile;
	 //delete session;
	}

		CATCH_ALL(error)
	{
		AfxMessageBox(L"Error from Server");
		error->GetErrorMessage(szCause, 254, NULL);
		CauseOfError.Format(L"%s", szCause);
		AfxMessageBox(CauseOfError);
	}
	END_CATCH_ALL;

	return filesize;
}

BOOL CUrlAccess::DownloadforUrl(CString url, CString ImgPath)
{
	DWORD dwServiceType = AFX_INET_SERVICE_HTTP;
	CString szServer, szObject, szInfo;

	INTERNET_PORT nPort;
	INTERNET_PROXY_INFO m_proxyinfo;

	CInternetSession m_SessionDownload;
	CHttpConnection* m_pConnection = NULL;
	CHttpFile* m_pHttpFile = NULL;
	CFile FileWrite;

	DWORD d_BytesRead = 0;
	DWORD d_FileSize = 0;

	char szHTTPBuffer[199926];
	
	d_FileSize = GetUrlFileLength(url);
	nPort = 443;
	ZeroMemory(szHTTPBuffer, sizeof(szHTTPBuffer));

	//start Download Routine
	::AfxParseURL(url.GetBuffer(url.GetLength()), dwServiceType, szServer, szObject, nPort);	//url 파싱

	try
	{
		m_pConnection = m_SessionDownload.GetHttpConnection(szServer, INTERNET_FLAG_KEEP_CONNECTION, nPort, NULL, NULL);
		m_pHttpFile = m_pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, szObject, NULL, 0, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION);
	}
	catch (CInternetException* m_pException)
	{
		return FALSE;
	}

	if (m_pHttpFile)
	{
		if (!FileWrite.Open(ImgPath, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone))
			return FALSE;

		try
		{
			m_pHttpFile->SendRequest();
		}
		catch (CInternetException* m_pException)
		{
			return FALSE;
		}

		m_pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, d_FileSize);
		m_pHttpFile->QueryInfo(HTTP_QUERY_MAX, url);

		while (d_BytesRead = m_pHttpFile->Read((void*)szHTTPBuffer, 199926))
		{
			FileWrite.Write((void*)szHTTPBuffer, d_BytesRead);
			memset(szHTTPBuffer, 0, sizeof(szHTTPBuffer));
		}

		szServer.Empty();
		szObject.Empty();

		m_SessionDownload.Close();
		m_pConnection->Close();
		m_pHttpFile->Close();

		//delete m_SessionDownload;
		delete m_pConnection;
		delete m_pHttpFile;

		FileWrite.Close();
	}
	
	return TRUE;
}

DWORD CUrlAccess::Download(HINTERNET hInternet, char* pszURL,
	char* pszFileName, BYTE* pBuffer) 
{
	HINTERNET hURL = InternetOpenUrl(hInternet, (LPCWSTR)pszURL, NULL, 0, 0, 0);
	if (hURL == NULL) {
		InternetCloseHandle(hInternet);
		return -2;
	}

	HANDLE hFile = CreateFile((LPCWSTR)pszFileName, GENERIC_WRITE, 0,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return -3;

	DWORD dwSize = 2048;
	DWORD dwRead, dwWritten, dwTotalSize;

	bool bOK = HttpQueryInfo(hURL, HTTP_QUERY_CONTENT_LENGTH,
		pBuffer, &dwRead, NULL);
	if (!bOK) return -4;
	dwTotalSize = atoi((const char*)pBuffer);

	do {
		InternetQueryDataAvailable(hURL, &dwSize, 0, 0);
		InternetReadFile(hURL, pBuffer, dwSize, &dwRead);
		WriteFile(hFile, pBuffer, dwRead, &dwWritten, NULL);
	} while (dwRead != 0);

	InternetCloseHandle(hURL);
	CloseHandle(hFile);

	return dwTotalSize;
}

void CUrlAccess::SaveImage(INT nWidth, INT nHeight, CString url, CString Filename)
{
	HINTERNET hInternet = InternetOpen(L"MyAGENT", INTERNET_OPEN_TYPE_PRECONFIG,
		NULL, NULL, 0);
	if (hInternet == NULL) return ;

	BYTE* pBuffer = new BYTE[nWidth * nHeight];
	DWORD dwTotalSize;

	dwTotalSize = Download(hInternet, CStringToChar(url), CStringToChar(Filename), pBuffer);
	printf("TotalSize: %d\n", dwTotalSize);

	dwTotalSize = Download(hInternet, CStringToChar(url), CStringToChar(Filename), pBuffer);
	printf("TotalSize: %d\n", dwTotalSize);

	delete[] pBuffer;
	InternetCloseHandle(hInternet);
}

char* CUrlAccess::CStringToChar(CString csting)
{
	wchar_t* wQuery = LPWSTR(LPCWSTR(csting));
	int strSize(WideCharToMultiByte(CP_ACP, 0, wQuery, -1, NULL, 0, NULL, NULL));
	char* cQuery = new char[strSize];
	WideCharToMultiByte(CP_ACP, 0, wQuery, -1, cQuery, strSize, 0, 0);

	return cQuery;
}

#define READ_BUF_SIZE    1024
INT CUrlAccess::DownloadImageFromHttp(CString pszUrl, CString pszFile)
{
	HINTERNET    hInet, hUrl;
	DWORD        dwReadSize = 0;
	CHttpFile		*httpfile;
	// WinINet함수 초기화
	if ((hInet = InternetOpen(L"MyWeb",            // user agent in the HTTP protocol
		/*INTERNET_OPEN_TYPE_DIRECT*/INTERNET_OPEN_TYPE_PRECONFIG,    // AccessType
		NULL,                        // ProxyName
		NULL,                        // ProxyBypass
		0)) != NULL)                // Options
	{
		// 입력된 HTTP주소를 열기
		if ((hUrl = InternetOpenUrl(hInet,        // 인터넷 세션의 핸들
			pszUrl,                        // URL
			NULL,                        // HTTP server에 보내는 해더
			0,                            // 해더 사이즈
			0,                            // Flag
			0)) != NULL)                // Context
		{
			FILE* fp;

			// 다운로드할 파일 만들기
			fopen_s(&fp, CStringToChar(pszFile), "wb");
			

			TCHAR    szBuff[READ_BUF_SIZE];
			DWORD    dwSize;
			DWORD    dwDebug = 10;

			do {
					// 웹상의 파일 읽기
				InternetReadFile(hUrl, szBuff, READ_BUF_SIZE, &dwSize);

					// 웹상의 파일을 만들어진 파일에 써넣기
				fwrite(szBuff, dwSize, 1, fp);

				dwReadSize += dwSize;
			} while ((dwSize != 0) || (--dwDebug != 0));

			fclose(fp);
			
			// 인터넷 핸들 닫기
			InternetCloseHandle(hUrl);
		}
		// 인터넷 핸들 닫기
		InternetCloseHandle(hInet);
	}
	return(dwReadSize);
}