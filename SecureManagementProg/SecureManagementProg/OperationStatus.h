#pragma once
#include "ProgressManager.h"
class COperationStatus
{
public:
	static BOOL m_bSearching;
	static BOOL m_bDelete;
	static BOOL m_bRefresh;

	static HWND	m_hMsgHwnd;

	static BOOL SetSearching(BOOL Isstatus);
	static BOOL SetDelete(BOOL Isstatus);
	static BOOL SetRefresh(BOOL Isstatus);

	static void SetHwnd(HWND hwnd);

	static HRESULT CheckOperationStatus();
};

