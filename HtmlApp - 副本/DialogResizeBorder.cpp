#include "stdafx.h"
#include "DialogResizeBorder.h"
#include <tchar.h>

CDialogResizeBorder::CDialogResizeBorder(HINSTANCE hinst, HWND hwndOwner)
{
	m_hWnd = NULL;

	m_hInst = hinst;
	m_hOwnerWnd = hwndOwner;
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
		//设置透明度
		//  修改窗口的风格
		ModifyStyleEx(hDlg, 0, WS_EX_LAYERED);
		//  设置透明度，第三个参数，取值从0-255
		::SetLayeredWindowAttributes(hDlg, 0, 100, LWA_ALPHA);
		return TRUE;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	//case WM_SETCURSOR:
	//	::SetCursor(::LoadCursor(NULL, IDC_CROSS));
	//	return TRUE;
	//case WM_LBUTTONDOWN:
	//	//::PostMessage(hDlg, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	//	::ReleaseCapture();
	//	::SendMessage(hDlg, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	//	::SendMessage(hDlg, WM_LBUTTONUP, 0, 0);
	//	return TRUE;
	//case WM_LBUTTONUP:
	//	//MessageBox(hDlg, _T("OK"), _T("unCAP"), MB_OK);
	//	return TRUE;
	case WM_NCHITTEST:
	{
		RECT rcWindow;
		::GetWindowRect(hDlg, &rcWindow);

		//INT nHitTest = (INT)wParam; // hit-test value
		POINTS pt = MAKEPOINTS(lParam); // position of cursor

		LRESULT htRes = HTERROR;

		// 最好将四个角的判断放在前面
		if (pt.x <= rcWindow.left + GAP && pt.y <= rcWindow.top + GAP)
			htRes = (LRESULT)HTTOPLEFT;
		else if (pt.x >= rcWindow.right - GAP && pt.y <= rcWindow.top + GAP)
			htRes = (LRESULT)HTTOPRIGHT;
		else if (pt.x <= rcWindow.left + GAP && pt.y >= rcWindow.bottom - GAP)
			htRes = (LRESULT)HTBOTTOMLEFT;
		else if (pt.x >= rcWindow.right - GAP && pt.y >= rcWindow.bottom - GAP)
			htRes = (LRESULT)HTBOTTOMRIGHT;
		else if (pt.x <= rcWindow.left + GAP)
			htRes = (LRESULT)HTLEFT;
		else if (pt.x >= rcWindow.right - GAP)
			htRes = (LRESULT)HTRIGHT;
		else if (pt.y <= rcWindow.top + GAP)
			htRes = (LRESULT)HTTOP;
		else if (pt.y >= rcWindow.bottom - GAP)
			htRes = (LRESULT)HTBOTTOM;

		if (htRes != HTERROR)
		{
			//在DialogProc中要这样设置返回值
			SetWindowLong(hDlg, DWL_MSGRESULT, htRes);
			return TRUE;
		}
	}
		break;
	case WM_SETCURSOR:
	{
		WORD nHitTest = LOWORD(lParam);

		switch (nHitTest)
		{
		case HTTOP:
		case HTBOTTOM:
			::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));
			return TRUE;
		case HTLEFT:
		case HTRIGHT:
			::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
			return TRUE;
		case HTTOPLEFT:
		case HTBOTTOMRIGHT:
			::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));
			return TRUE;
		case HTTOPRIGHT:
		case HTBOTTOMLEFT:
			::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));
			return TRUE;
		}
	}
		break;
	case WM_NCLBUTTONDOWN:
	{
		INT nHitTest = (INT)wParam; // hit-test value
		POINTS pt = MAKEPOINTS(lParam); // position of cursor

		BOOL bDrilled = FALSE;
		int nHitTestRes = 0;

		switch (nHitTest)
		{
		case HTTOP:
			nHitTestRes = WMSZ_TOP;
			bDrilled = TRUE;
			break;
		case HTBOTTOM:
			nHitTestRes = WMSZ_BOTTOM;
			bDrilled = TRUE;
			break;
		case HTLEFT:
			nHitTestRes = WMSZ_LEFT;
			bDrilled = TRUE;
			break;
		case HTRIGHT:
			nHitTestRes = WMSZ_RIGHT;
			bDrilled = TRUE;
			break;
		case HTTOPLEFT:
			nHitTestRes = WMSZ_TOPLEFT;
			bDrilled = TRUE;
			break;
		case HTTOPRIGHT:
			nHitTestRes = WMSZ_TOPRIGHT;
			bDrilled = TRUE;
			break;
		case HTBOTTOMLEFT:
			nHitTestRes = WMSZ_BOTTOMLEFT;
			bDrilled = TRUE;
			break;
		case HTBOTTOMRIGHT:
			nHitTestRes = WMSZ_BOTTOMRIGHT;
			bDrilled = TRUE;
			break;
		}

		if (bDrilled == TRUE)
		{
			HWND hParent = ::GetParent(hDlg);
			if (NULL != hParent)
			{
				g_bNoticingParentResize = true;

				//通知主窗口开始resize
				::SendMessage(hParent, WM_BORDER_RESIZE_START, 0, 0);				
				//开始拖动
				::SendMessage(hDlg, WM_SYSCOMMAND, SC_SIZE | nHitTestRes, MAKELPARAM(pt.x, pt.y));
				//拖动结束后发一个鼠标弹起的消息，因为在实际中没有触发鼠标弹起事件
				::SendMessage(hDlg, WM_NCLBUTTONUP, 0, 0);
			}
		}
		return bDrilled;
	}
		break;
	case WM_NCLBUTTONUP:
	{
		g_bNoticingParentResize = false;

		//通知主窗口结束resize
		HWND hParent = ::GetParent(hDlg);
		if (NULL != hParent)
		{
			::SendMessage(hParent, WM_BORDER_RESIZE_END, 0, 0);
		}
	}
		break;
	case WM_SIZE:
	{
		if (g_bNoticingParentResize)
		{
			//通知主窗口要改变尺寸
			HWND hParent = ::GetParent(hDlg);
			if (NULL != hParent)
			{
				RECT rcWindow;
				::GetWindowRect(hDlg, &rcWindow);
				::MoveWindow(hParent, rcWindow.left + GAP, rcWindow.top + GAP,
					rcWindow.right - rcWindow.left - 2 * GAP,
					rcWindow.bottom - rcWindow.top - 2 * GAP, TRUE);
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
	return TRUE;
}
