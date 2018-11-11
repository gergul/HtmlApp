#include "stdafx.h"
#include "DialogResizeBorder.h"
#include <tchar.h>

std::map<HWND, HCURSOR> CDialogResizeBorder::ms_mpCursors;
std::map<HWND, int> CDialogResizeBorder::ms_mpHitTestType;
std::map<HWND, CDialogResizeBorder*> CDialogResizeBorder::ms_wndClass;

int CDialogResizeBorder::ms_opaque = 1;

CDialogResizeBorder::CDialogResizeBorder(HINSTANCE hinst, HWND hwndOwner, int nHitTestType)
{
	m_hWnd = NULL;

	m_hInst = hinst;
	m_hOwnerWnd = hwndOwner;

	m_nHitTestType = nHitTestType;
}

CDialogResizeBorder::~CDialogResizeBorder()
{

}

bool g_bNoticingParentResize = false;

INT_PTR CALLBACK CDialogResizeBorder::DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//����͸����
		//  �޸Ĵ��ڵķ��
		ModifyStyleEx(hDlg, 0, WS_EX_LAYERED);
		//  ����͸���ȣ�����������
		::SetLayeredWindowAttributes(hDlg, 0, ms_opaque, LWA_ALPHA);
		return TRUE;
	}
	break;
	case WM_CLOSE:
	{
		EndDialog(hDlg, 0);
		return TRUE;
	}
	break;
	case WM_SETCURSOR:
	{
		//�������
		::SetCursor(ms_mpCursors[hDlg]);
		return TRUE;
	}
	break;
	case WM_LBUTTONDOWN:
	{
		//::PostMessage(hDlg, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
		//����������ʱ�϶����ڲ�����������
		HWND hOwer = ms_wndClass[hDlg]->m_hOwnerWnd;
		if (NULL != hOwer)
		{
			::ReleaseCapture();
			LRESULT res = ::SendMessage(hOwer, WM_BORDER_RESIZE_START, (WPARAM)hDlg, (LPARAM)ms_mpHitTestType[hDlg]);
			if (res == S_OK)
			{
				g_bNoticingParentResize = true;
				::SendMessage(hDlg, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
			}
			::SendMessage(hDlg, WM_LBUTTONUP, 0, 0);
			return TRUE;
		}
	}
	break;
	case WM_MOVE:
	{
		//�϶��Ĺ���
		if (g_bNoticingParentResize)
		{
			CDialogResizeBorder* pDlg = ms_wndClass[hDlg];
			if (NULL != pDlg)
			{
				LRESULT res = ::SendMessage(pDlg->m_hOwnerWnd, WM_BORDER_RESIZE, (WPARAM)hDlg, (LPARAM)ms_mpHitTestType[hDlg]);
				if (res == S_OK)
				{
					pDlg->resizeWindow();
				}
				return TRUE;
			}			
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		g_bNoticingParentResize = false;

		//�����϶�����
		CDialogResizeBorder* pDlg = ms_wndClass[hDlg];
		if (NULL != pDlg)
		{
			LRESULT res = ::SendMessage(pDlg->m_hOwnerWnd, WM_BORDER_RESIZE_END, (WPARAM)hDlg, (LPARAM)ms_mpHitTestType[hDlg]);
			if (res == S_OK)
			{
				pDlg->resizeWindow();
			}
			return TRUE;
		}
	}
	break;
	case WM_SYNCBORDER:
	{
		std::map<HWND, CDialogResizeBorder*>::iterator it = ms_wndClass.find(hDlg);
		if (it != ms_wndClass.end())
			it->second->syncBorder((bool)wParam);
		return TRUE;
	}
	break;
	default:
		break;
	}
	return FALSE;
}

BOOL CDialogResizeBorder::_ModifyStyle(HWND hWnd, int nStyleOffset, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	DWORD dwStyle = ::GetWindowLong(hWnd, nStyleOffset);
	DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
	if (dwStyle == dwNewStyle)
		return FALSE;

	::SetWindowLong(hWnd, nStyleOffset, dwNewStyle);
	if (nFlags != 0)
	{
		::SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
	}
	return TRUE;
}

BOOL CDialogResizeBorder::ModifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	return _ModifyStyle(hWnd, (int)GWL_EXSTYLE, dwRemove, dwAdd, nFlags);
}

void CDialogResizeBorder::syncBorder(bool bCheckShowed /*= true*/)
{
	if (!::IsZoomed(m_hWnd) && !::IsIconic(m_hWnd) &&
		(!bCheckShowed || (bCheckShowed && TRUE == ::IsWindowVisible(m_hWnd)))
		)
	{
		HWND hBorderWnd = m_hWnd;
		::ShowWindow(hBorderWnd, SW_SHOW);

		CRect rectWin;
		::GetWindowRect(m_hOwnerWnd, &rectWin);

		switch (m_nHitTestType)
		{
		case HTLEFT:
			::MoveWindow(hBorderWnd, rectWin.left - GAP, rectWin.top + GAP, GAP, rectWin.Height() - GAP * 2, TRUE);
			break;
		case HTRIGHT:
			::MoveWindow(hBorderWnd, rectWin.right, rectWin.top + GAP, GAP, rectWin.Height() - GAP * 2, TRUE);
			break;
		case HTTOP:
			::MoveWindow(hBorderWnd, rectWin.left + GAP, rectWin.top - GAP, rectWin.Width() - GAP * 2, GAP, TRUE);
			break;
		case HTBOTTOM:
			::MoveWindow(hBorderWnd, rectWin.left + GAP, rectWin.bottom, rectWin.Width() - GAP * 2, GAP, TRUE);
			break;
		case HTTOPLEFT:
			::MoveWindow(hBorderWnd, rectWin.left - GAP / 2, rectWin.top - GAP / 2, GAP, GAP, TRUE);
			break;
		case HTTOPRIGHT:
			::MoveWindow(hBorderWnd, rectWin.right - GAP / 2, rectWin.top - GAP / 2, GAP, GAP, TRUE);
			break;
		case HTBOTTOMLEFT:
			::MoveWindow(hBorderWnd, rectWin.left - GAP / 2, rectWin.bottom - GAP / 2, GAP, GAP, TRUE);
			break;
		case HTBOTTOMRIGHT:
			::MoveWindow(hBorderWnd, rectWin.right - GAP / 2, rectWin.bottom - GAP / 2, GAP, GAP, TRUE);
			break;
		default:
			break;
		}

		::SetFocus(m_hOwnerWnd);
	}
	else
	{
		::ShowWindow(m_hWnd, SW_HIDE);
	}
}

void CDialogResizeBorder::resizeWindow()
{
	RECT rectBorder;
	::GetWindowRect(m_hWnd, &rectBorder);

	CRect rectWin;
	::GetWindowRect(m_hOwnerWnd, rectWin);

	switch (m_nHitTestType)
	{
	case HTLEFT:
		rectWin.left = rectBorder.right;
		break;
	case HTRIGHT:
		rectWin.right = rectBorder.left;
		break;
	case HTTOP:
		rectWin.top = rectBorder.bottom;
		break;
	case HTBOTTOM:
		rectWin.bottom = rectBorder.top;
		break;
	case HTTOPLEFT:
		rectWin.left = rectBorder.right - GAP / 2;
		rectWin.top = rectBorder.bottom - GAP / 2;
		break;
	case HTTOPRIGHT:
		rectWin.right = rectBorder.left + GAP / 2;
		rectWin.top = rectBorder.bottom - GAP / 2;
		break;
	case HTBOTTOMLEFT:
		rectWin.left = rectBorder.right - GAP / 2;
		rectWin.bottom = rectBorder.top + GAP / 2;
		break;
	case HTBOTTOMRIGHT:
		rectWin.right = rectBorder.left + GAP / 2;
		rectWin.bottom = rectBorder.top + GAP / 2;
		break;
	default:
		break;
	}
	::MoveWindow(m_hOwnerWnd, rectWin.left, rectWin.top, rectWin.Width(), rectWin.Height(), TRUE);
}

BOOL CDialogResizeBorder::DoModeless()
{
	HGLOBAL hgbl;
	LPDLGTEMPLATE lpdt;
	LPWORD lpw;
	LPWSTR lpwsz;
	int nchar;

	hgbl = GlobalAlloc(GMEM_ZEROINIT, 1024);
	if (!hgbl)
		return FALSE;

	lpdt = (LPDLGTEMPLATE)GlobalLock(hgbl);

	// Define a dialog box.
	lpdt->style = WS_POPUP/* | WS_BORDER | WS_SYSMENU | DS_MODALFRAME | WS_CAPTION*/;
	lpdt->cdit = 0;//3  // number of controls
	lpdt->x = 10;
	lpdt->y = 10;
	lpdt->cx = 100;
	lpdt->cy = 70;

	lpw = (LPWORD)(lpdt + 1);
	*lpw++ = 0;   // no menu
	*lpw++ = 0;   // predefined dialog box class (by default)

	lpwsz = (LPWSTR)lpw;
	nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "BORDER", -1,
		lpwsz, 50);
	lpw += nchar;
	
	GlobalUnlock(hgbl);

	m_hWnd = CreateDialogIndirect(m_hInst,
		(LPDLGTEMPLATE)hgbl,
		m_hOwnerWnd,
		(DLGPROC)DialogProc);
	if (NULL == m_hWnd)
		return FALSE;

	::ShowWindow(m_hWnd, SW_SHOW);

	GlobalFree(hgbl);


	switch (m_nHitTestType)
	{
	case HTLEFT:
	case HTRIGHT:
	{
		ms_mpCursors[m_hWnd] = ::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE));
	}
	break;
	case HTTOP:
	case HTBOTTOM:
	{
		ms_mpCursors[m_hWnd] = ::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS));
	}
	break;
	case HTTOPLEFT:
	case HTBOTTOMRIGHT:
	{
		ms_mpCursors[m_hWnd] = ::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE));
	}
	break;
	case HTTOPRIGHT:
	case HTBOTTOMLEFT:
	{
		ms_mpCursors[m_hWnd] = ::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW));
	}
	break;
	default:
	{
		ms_mpCursors[m_hWnd] = NULL;
	}
	break;
	}

	ms_mpHitTestType[m_hWnd] = m_nHitTestType;
	ms_wndClass[m_hWnd] = this;


	return TRUE;
}

void CDialogResizeBorder::SyncBorder(bool bCheckShowed /*= true*/)
{
	::PostMessage(m_hWnd, WM_SYNCBORDER, (WPARAM)bCheckShowed, 0);
}
