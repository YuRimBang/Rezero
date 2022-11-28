#include "pch.h"
#include "OperationStatus.h"

BOOL COperationStatus::m_bSearching = FALSE;
BOOL COperationStatus::m_bDelete = FALSE;
BOOL COperationStatus::m_bRefresh = FALSE;
HWND COperationStatus::m_hMsgHwnd;

void COperationStatus::SetHwnd(HWND hwnd)
{
    m_hMsgHwnd = hwnd;
}

BOOL COperationStatus::SetSearching(BOOL bStatus)
{
    if (bStatus == TRUE && CheckOperationStatus() == S_FALSE)
        return FALSE;

    m_bSearching = bStatus;

    if (bStatus == TRUE)
        ::SendMessage(m_hMsgHwnd, MSG_PROGRESS_UPDATE, MSG_PROGRESS_SEARCH, MSG_START);
    if (bStatus == FALSE)
        ::SendMessage(m_hMsgHwnd, MSG_PROGRESS_UPDATE, MSG_PROGRESS_SEARCH, MSG_END);

    return TRUE;
}

BOOL COperationStatus::SetDelete(BOOL bStatus)
{
    if (bStatus == TRUE && CheckOperationStatus() == S_FALSE)
        return FALSE;

    m_bSearching = bStatus;

    if (bStatus == TRUE)
        ::SendMessage(m_hMsgHwnd, MSG_PROGRESS_UPDATE, MSG_PROGRESS_DELETE, MSG_START);
    if (bStatus == FALSE)
        ::SendMessage(m_hMsgHwnd, MSG_PROGRESS_UPDATE, MSG_PROGRESS_DELETE, MSG_END);

    return TRUE;
}

BOOL COperationStatus::SetRefresh(BOOL bStatus)
{
    if (bStatus == TRUE && CheckOperationStatus() == S_FALSE)
        return FALSE;

    m_bSearching = bStatus;

    if (bStatus == TRUE)
        ::SendMessage(m_hMsgHwnd, MSG_PROGRESS_UPDATE, MSG_PROGRESS_REFRESH, MSG_START);
    if (bStatus == FALSE)
        ::SendMessage(m_hMsgHwnd, MSG_PROGRESS_UPDATE, MSG_PROGRESS_REFRESH, MSG_END);

    return TRUE;
}

BOOL COperationStatus::SetAccess(BOOL bStatus)
{
    if (bStatus == TRUE && CheckOperationStatus() == S_FALSE)
        return FALSE;

    m_bSearching = bStatus;

    if (bStatus == TRUE)
        ::SendMessage(m_hMsgHwnd, MSG_PROGRESS_UPDATE, MSG_PROGRESS_ACCESS, MSG_START);
    if (bStatus == FALSE)
        ::SendMessage(m_hMsgHwnd, MSG_PROGRESS_UPDATE, MSG_PROGRESS_ACCESS, MSG_END);

    return TRUE;
}

HRESULT COperationStatus::CheckOperationStatus()
{
    if (m_bSearching == TRUE || m_bDelete == TRUE || m_bRefresh == TRUE )
    {
        AfxMessageBox(_T("operation for previous data did not complete.\n (Please try again when the operation is complete)"));
        return S_FALSE;
    }
    else
        return S_OK;
}