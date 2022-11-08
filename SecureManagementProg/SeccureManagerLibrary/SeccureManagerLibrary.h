// SeccureManagerLibrary.h : main header file for the SeccureManagerLibrary DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSeccureManagerLibraryApp
// See SeccureManagerLibrary.cpp for the implementation of this class
//

class CSeccureManagerLibraryApp : public CWinApp
{
public:
	CSeccureManagerLibraryApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
