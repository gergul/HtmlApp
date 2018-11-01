// DlgTemplate.cpp : 实现文件
//

#include "stdafx.h"
#include "HtmlDialog.h"
#include "afxdialogex.h"

#define TRANS_COLOR RGB(255, 255, 255)

// HtmlDialog 对话框

IMPLEMENT_DYNAMIC(CHtmlDialog, CDialogEx)

CHtmlDialog::CHtmlDialog(UINT id, CWnd* pParent /*=NULL*/)
	: CDialogEx(id, pParent)
	, m_htmlHelper(&m_html)
	, m_bEnableResize(true)
	, m_pBorder(NULL)
	, m_bWinChangeByBorder(false)
{

}

CHtmlDialog::~CHtmlDialog()
{
	if (m_pBorder)
	{
		delete m_pBorder;
		m_pBorder = NULL;
	}
}

void CHtmlDialog::InitJsEvents()
{
	ADD_EXTERNAL_CALL(&m_html, _T("onMouseDownCaption"), &CHtmlDialog::js_onMouseDownCaption, this);
	ADD_EXTERNAL_CALL(&m_html, _T("onDbClickHtmlCaption"), &CHtmlDialog::js_onDbClickCaption, this);

	ADD_EXTERNAL_CALL(&m_html, _T("onClickClose"), &CHtmlDialog::js_onClickedClose, this);
	ADD_EXTERNAL_CALL(&m_html, _T("onClickMax"), &CHtmlDialog::js_onClickedMax, this);
	ADD_EXTERNAL_CALL(&m_html, _T("onClickRestore"), &CHtmlDialog::js_onClickedRestore, this);
	ADD_EXTERNAL_CALL(&m_html, _T("onClickMin"), &CHtmlDialog::js_onClickedMin, this);

	ADD_EXTERNAL_CALL(&m_html, _T("moveTo"), &CHtmlDialog::js_moveTo, this);
	ADD_EXTERNAL_CALL(&m_html, _T("setWindowSize"), &CHtmlDialog::js_setWindowSize, this);
	ADD_EXTERNAL_CALL(&m_html, _T("showWindow"), &CHtmlDialog::js_showWindow, this);
	ADD_EXTERNAL_CALL(&m_html, _T("enableResize"), &CHtmlDialog::js_enableResize, this);
}

void CHtmlDialog::RemoveBorder()
{
	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);//获取旧样式
	WORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	dwNewStyle &= dwStyle;//按位与将旧样式去掉
	::SetWindowLong(m_hWnd, GWL_STYLE, dwNewStyle);//设置成新的样式
	DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);//获取旧扩展样式
	DWORD dwNewExStyle = WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR;
	dwNewExStyle &= dwExStyle;//按位与将旧扩展样式去掉
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewExStyle);//设置新的扩展样式
	//告诉windows：我的样式改变了，窗口位置和大小保持原来不变！
	::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
}

void CHtmlDialog::SyncBorder()
{
	if (TRUE == ::IsWindowVisible(m_hWnd))
	{
		HWND hBorderWnd = m_pBorder->m_hWnd;

		::ShowWindow(hBorderWnd, SW_SHOW);

		CRect rectWin;
		this->GetWindowRect(&rectWin);
		::MoveWindow(hBorderWnd, rectWin.left - GAP, rectWin.top - GAP, rectWin.Width() + GAP*2, rectWin.Height() + GAP*2, TRUE);

		::SetWindowPos(hBorderWnd, m_hWnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
		::SetWindowPos(m_hWnd, hBorderWnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
		::SetFocus(m_html.m_hWnd);
	}
	else
	{
		::ShowWindow(m_pBorder->m_hWnd, SW_HIDE);
	}
}

void CHtmlDialog::js_onClickedClose(LPCTSTR str)
{
	::PostMessage(this->GetSafeHwnd(), WM_CLOSE, 0, 0);
}

void CHtmlDialog::js_onClickedMax(LPCTSTR str)
{
	ShowWindow(SW_SHOWMAXIMIZED);
}

void CHtmlDialog::js_onClickedRestore(LPCTSTR str)
{
	ShowWindow(SW_RESTORE);
}

void CHtmlDialog::js_onClickedMin(LPCTSTR str)
{
	ShowWindow(SW_SHOWMINIMIZED);
}

void CHtmlDialog::js_onMouseDownCaption(LPCTSTR str)
{
	::GetCursorPos(&m_ptLast);
	SetTimer(TIMER_WIN_POS, 10, NULL);

	//::SendMessage(GetSafeHwnd(), WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
}

void CHtmlDialog::js_onDbClickCaption(LPCTSTR str)
{
	if (IsZoomed() == TRUE)
	{
		ShowWindow(SW_RESTORE);
	}
	else
	{
		ShowWindow(SW_SHOWMAXIMIZED);
	}
}

void CHtmlDialog::js_moveTo(LPCTSTR str)
{
	CString s = str;
	s.Trim();
	int nIdx = s.Find(',', 0);
	if (nIdx < 0)
		nIdx = s.Find('x', 0);
	if (nIdx < 0)
		nIdx = s.Find('X', 0);
	if (nIdx < 0)
		nIdx = s.Find('*', 0);
	if (nIdx < 0)
		nIdx = s.Find(' ', 0);
	if (nIdx < 0)
		return;

	int nX = _ttoi(s.Left(nIdx).GetString());
	int nY = _ttoi(s.Mid(nIdx + 1, s.GetLength() - nIdx - 1).GetString());

	CRect rectWin;
	GetWindowRect(&rectWin);
	int nWidth = rectWin.Width();
	int nHeight = rectWin.Height();
	rectWin.left = nX;
	rectWin.top = nY;
	rectWin.right = rectWin.left + nWidth;
	rectWin.bottom = rectWin.top + nHeight;
	MoveWindow(&rectWin);
}

void CHtmlDialog::js_setWindowSize(LPCTSTR str)
{
	CString s = str;
	s.Trim();
	int nIdx = s.Find(',', 0);
	if (nIdx < 0)
		nIdx = s.Find('x', 0);
	if (nIdx < 0)
		nIdx = s.Find('X', 0);
	if (nIdx < 0)
		nIdx = s.Find('*', 0);
	if (nIdx < 0)
		nIdx = s.Find(' ', 0);
	if (nIdx < 0)
		return;

	int nWidth = _ttoi(s.Left(nIdx).GetString());
	int nHeight = _ttoi(s.Mid(nIdx + 1, s.GetLength() - nIdx - 1).GetString());
	if (nWidth == 0 || nHeight == 0)
		return;

	CRect rectWin;
	GetWindowRect(&rectWin);
	rectWin.right = rectWin.left + nWidth;
	rectWin.bottom = rectWin.top + nHeight;
	MoveWindow(&rectWin);
}

void CHtmlDialog::js_showWindow(LPCTSTR str)
{
	CString sVal = str;
	sVal.MakeUpper();
	if (sVal == _T("TRUE") || sVal == _T("1"))
		ShowWindow(SW_SHOW);
	else if (sVal == _T("FALSE") || sVal == _T("0"))
		ShowWindow(SW_HIDE);
}

void CHtmlDialog::js_enableResize(LPCTSTR str)
{
	CString sVal = str;
	sVal.MakeUpper();
	if (sVal == _T("TRUE") || sVal == _T("1"))
		m_bEnableResize = true;
	else if (sVal == _T("FALSE") || sVal == _T("0"))
		m_bEnableResize = false;
}

void CHtmlDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
}


BOOL CHtmlDialog::PreTranslateMessage(MSG* pMsg)
{
	//For: 拖动窗口
	if (pMsg->message == WM_LBUTTONUP)
	{
		KillTimer(TIMER_WIN_POS);
	}

	return __super::PreTranslateMessage(pMsg);
}

void CHtmlDialog::OnTimer(UINT_PTR nIDEvent)
{
	//For: 拖动窗口
	if (nIDEvent == TIMER_WIN_POS)
	{
		POINT ptCur;
		GetCursorPos(&ptCur);
		CRect rectWin;
		GetWindowRect(&rectWin);
		int nWidth = rectWin.Width();
		int nHeight = rectWin.Height();
		rectWin.left += ptCur.x - m_ptLast.x;
		rectWin.top += ptCur.y - m_ptLast.y;
		rectWin.right = rectWin.left + nWidth;
		rectWin.bottom = rectWin.top + nHeight;
		MoveWindow(&rectWin);
		m_ptLast = ptCur;
	}
}

LRESULT CHtmlDialog::OnNcHitTest(CPoint pt)
{
	if (!m_bEnableResize)
		return __super::OnNcHitTest(pt);

	RECT rcWindow;
	::GetWindowRect(m_hWnd, &rcWindow);

	// 最好将四个角的判断放在前面
	if (pt.x <= rcWindow.left + GAP && pt.y <= rcWindow.top + GAP)
		return HTTOPLEFT;
	else if (pt.x >= rcWindow.right - GAP && pt.y <= rcWindow.top + GAP)
		return HTTOPRIGHT;
	else if (pt.x <= rcWindow.left + GAP && pt.y >= rcWindow.bottom - GAP)
		return HTBOTTOMLEFT;
	else if (pt.x >= rcWindow.right - GAP && pt.y >= rcWindow.bottom - GAP)
		return HTBOTTOMRIGHT;
	else if (pt.x <= rcWindow.left + GAP)
		return HTLEFT;
	else if (pt.x >= rcWindow.right - GAP)
		return HTRIGHT;
	else if (pt.y <= rcWindow.top + GAP)
		return HTTOP;
	else if (pt.y >= rcWindow.bottom - GAP)
		return HTBOTTOM;

	//return HTCAPTION; // 为了实现“鼠标按下客户区时也能移动主窗口”
	return __super::OnNcHitTest(pt);
}

BOOL CHtmlDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (!m_bEnableResize)
		return __super::OnSetCursor(pWnd, nHitTest, message);

	switch (nHitTest)
	{
	case HTTOP:
	case HTBOTTOM:
		SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));
		return TRUE;

	case HTLEFT:
	case HTRIGHT:
		SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
		return TRUE;

	case HTTOPLEFT:
	case HTBOTTOMRIGHT:
		SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));
		return TRUE;

	case HTTOPRIGHT:
	case HTBOTTOMLEFT:
		SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));
		return TRUE;

	default:
		return __super::OnSetCursor(pWnd, nHitTest, message);
	}
}

void CHtmlDialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (!m_bEnableResize)
		__super::OnNcLButtonDown(nHitTest, point);

	switch (nHitTest)
	{
	case HTTOP:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
		break;
	case HTBOTTOM:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
		break;
	case HTLEFT:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
		break;
	case HTRIGHT:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
		break;
	case HTTOPLEFT:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
		break;
	case HTTOPRIGHT:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
		break;
	case HTBOTTOMLEFT:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
		break;
	case HTBOTTOMRIGHT:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
		break;
	default:
		__super::OnNcLButtonDown(nHitTest, point);
	}
}

void CHtmlDialog::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	if (IsWindow(m_html.GetSafeHwnd()))
	{
		CRect rectHtml;
		m_html.GetWindowRect(&rectHtml);
		ScreenToClient(&rectHtml);
		rectHtml.top = GAP;
		rectHtml.left = GAP;
		rectHtml.bottom = cy - GAP;
		rectHtml.right = cx - GAP;

		m_html.MoveWindow(&rectHtml);
	}
}

void CHtmlDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	__super::OnGetMinMaxInfo(lpMMI);

	if (!m_bWinChangeByBorder)
		SyncBorder();
}

LRESULT CHtmlDialog::OnBorderResizeStart(WPARAM wParam, LPARAM lParam)
{
	m_bWinChangeByBorder = true;
	return 0;
}

LRESULT CHtmlDialog::OnBorderResizeEnd(WPARAM wParam, LPARAM lParam)
{
	m_bWinChangeByBorder = false;
	return 0;
}

//HBRUSH CHtmlDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	if (nCtlColor == CTLCOLOR_DLG)
//		return m_bkBrush;
//
//	return __super::OnCtlColor(pDC, pWnd, nCtlColor);
//}

BOOL CHtmlDialog::OnInitDialog()
{
	BOOL bRet = __super::OnInitDialog();

	CRect rectWin;
	this->GetWindowRect(&rectWin);
	CRect rectHtml;
	rectHtml.top = GAP;
	rectHtml.left = GAP;
	rectHtml.bottom = rectWin.Height() - GAP;
	rectHtml.right = rectWin.Width() - GAP;
	m_html.Create(rectHtml, this, GetDlgCtrlID() + 10000);

	m_html.SetIsHideContextMenu(TRUE);

	InitJsEvents();
	RemoveBorder();
	
	//m_bkBrush.CreateSolidBrush(TRANS_COLOR);

	////窗口透明
	//ModifyStyleEx(0, WS_EX_LAYERED);
	//SetLayeredWindowAttributes(TRANS_COLOR, 0, LWA_COLORKEY);//

	CString sDefaultUrl = GetDefaultUrl();
	if (!sDefaultUrl.IsEmpty())
		m_html.Navigate2(sDefaultUrl);

	m_pBorder = new CDialogResizeBorder(NULL, m_hWnd);
	m_pBorder->DoModeless();

	return bRet;
}

BEGIN_MESSAGE_MAP(CHtmlDialog, CDialogEx)
	ON_WM_TIMER()
	//ON_WM_NCHITTEST()		//For: 调整窗口尺寸
	//ON_WM_SETCURSOR()		//For: 调整窗口尺寸
	//ON_WM_NCLBUTTONDOWN()	//For: 调整窗口尺寸
	ON_WM_SIZE()
	//ON_WM_CTLCOLOR()
	ON_WM_GETMINMAXINFO()
	ON_MESSAGE(WM_BORDER_RESIZE_START, &CHtmlDialog::OnBorderResizeStart)
	ON_MESSAGE(WM_BORDER_RESIZE_END, &CHtmlDialog::OnBorderResizeEnd)
END_MESSAGE_MAP()


// HtmlDialog 消息处理程序
