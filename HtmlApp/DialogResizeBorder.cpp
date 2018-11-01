#include "stdafx.h"
#include "DialogResizeBorder.h"
#include <tchar.h>

std::map<HWND, HCURSOR> CDialogResizeBorder::ms_mpCursors;
std::map<HWND, int> CDialogResizeBorder::ms_mpHitTestType;
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
		//设置透明度
		//  修改窗口的风格
		ModifyStyleEx(hDlg, 0, WS_EX_LAYERED);
		//  设置透明度，第三个参数
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
		//设置鼠标
		::SetCursor(ms_mpCursors[hDlg]);
		return TRUE;
	}
	break;
	case WM_LBUTTONDOWN:
	{
		//::PostMessage(hDlg, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
		//鼠标左键按下时拖动窗口并联动主窗口
		HWND hParent = ::GetParent(hDlg);
		if (NULL != hParent)
		{
			g_bNoticingParentResize = true;

			::ReleaseCapture();
			::SendMessage(hParent, WM_BORDER_RESIZE_START, 0, 0);
			::SendMessage(hDlg, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
			::SendMessage(hDlg, WM_LBUTTONUP, 0, 0);
			return TRUE;
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		g_bNoticingParentResize = false;

		//结束拖动窗口
		HWND hParent = ::GetParent(hDlg);
		if (NULL != hParent)
		{
			::SendMessage(hParent, WM_BORDER_RESIZE_END, 0, 0);
			return TRUE;
		}
	}
	break;
	case WM_MOVE:
	{
		//拖动的过程
		if (g_bNoticingParentResize)
		{
			HWND hParent = ::GetParent(hDlg);
			if (NULL != hParent)
			{
				::SendMessage(hParent, WM_BORDER_RESIZE, (WPARAM)hDlg, (LPARAM)ms_mpHitTestType[hDlg]);
			}
		}
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
	nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "内存对话框", -1,
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


	return TRUE;
}
