// DlgTemplate.cpp : 实现文件
//

#include "stdafx.h"
#include "HtmlDialog.h"
#include "afxdialogex.h"

// HtmlDialog 对话框

IMPLEMENT_DYNAMIC(CHtmlDialog, CDialogEx)

CHtmlDialog::CHtmlDialog(UINT id, CWnd* pParent /*=NULL*/)
	: CDialogEx(id, pParent)
	, m_htmlHelper(&m_html)
	, m_bEnableResize(true)
	, m_bWinChangeByBorder(false)
{

}

CHtmlDialog::~CHtmlDialog()
{
	for (std::map<int, CDialogResizeBorder*>::iterator it = m_mpBorders.begin();
		it != m_mpBorders.end(); ++it)
	{
		if (it->second)
			delete (it->second);
	}
	m_mpBorders.clear();
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

	ADD_EXTERNAL_CALL(&m_html, _T("setTransparentColor"), &CHtmlDialog::js_setTransparentColor, this);
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

void CHtmlDialog::SetTransparentColor(COLORREF color)
{
	//窗口透明
	ModifyStyleEx(0, WS_EX_LAYERED);
	SetLayeredWindowAttributes(color, 0, LWA_COLORKEY);//
}

void CHtmlDialog::SyncBorder(bool bCheckShowed/* = true*/)
{
	for (std::map<int, CDialogResizeBorder*>::iterator it = m_mpBorders.begin();
		it != m_mpBorders.end(); ++it)
	{
		int nHitTest = it->first;
		CDialogResizeBorder* pBorder = it->second;
				
		if (m_bEnableResize && 
			!IsZoomed() && !IsIconic() && 
			(!bCheckShowed || (bCheckShowed && TRUE == ::IsWindowVisible(m_hWnd)))
			)
		{
			HWND hBorderWnd = pBorder->m_hWnd;
			::ShowWindow(hBorderWnd, SW_SHOW);

			CRect rectWin;
			this->GetWindowRect(&rectWin);
			switch (nHitTest)
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
			
			::SetFocus(m_html.m_hWnd);
		}
		else
		{
			::ShowWindow(pBorder->m_hWnd, SW_HIDE);
		}
	}
}

std::vector<CString> CHtmlDialog::SplitCString(const CString& strSource, TCHAR* ch)
{
	std::vector<CString> vecString;

	CString strTmp = _tcstok((LPTSTR)(LPCTSTR)strSource, ch);
	if (strTmp == _T(""))
		return vecString;
	vecString.push_back(strTmp);

	while (1)
	{
		strTmp = _tcstok(NULL, ch);
		if (strTmp == _T(""))
			break;
		vecString.push_back(strTmp);
	}

	return vecString;
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

	::PostMessage(m_hWnd, WM_SYNCBORDER, true, 0);
}

void CHtmlDialog::js_enableResize(LPCTSTR str)
{
	CString sVal = str;
	sVal.MakeUpper();
	if (sVal == _T("TRUE") || sVal == _T("1"))
		m_bEnableResize = true;
	else if (sVal == _T("FALSE") || sVal == _T("0"))
		m_bEnableResize = false;

	::PostMessage(m_hWnd, WM_SYNCBORDER, true, 0);
}

void CHtmlDialog::js_setTransparentColor(LPCTSTR str)
{
	CString sVal = str;
	sVal.Trim();
	std::vector<CString> vctRGB = SplitCString(sVal, _T(", "));
	if (vctRGB.size() != 3)
		return;

	WORD r = _ttoi(vctRGB[0].GetString());
	WORD g = _ttoi(vctRGB[1].GetString());
	WORD b = _ttoi(vctRGB[2].GetString());

	SetTransparentColor(RGB(r, g, b));
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
		::PostMessage(m_hWnd, WM_SYNCBORDER, true, 0);
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

		//if (IsZoomed())
		//{
		//	ShowWindow(SW_RESTORE);
		//}
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
		rectHtml.top = 0;
		rectHtml.left = 0;
		rectHtml.bottom = cy;
		rectHtml.right = cx;

		m_html.MoveWindow(&rectHtml);
	}
}

void CHtmlDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	__super::OnGetMinMaxInfo(lpMMI);

	if (!m_bWinChangeByBorder)
		::PostMessage(m_hWnd, WM_SYNCBORDER, true, 0);
}

LRESULT CHtmlDialog::OnBorderResizeStart(WPARAM wParam, LPARAM lParam)
{
	m_bWinChangeByBorder = true;
	return 0;
}

LRESULT CHtmlDialog::OnBorderResizeEnd(WPARAM wParam, LPARAM lParam)
{
	m_bWinChangeByBorder = false;
	::PostMessage(m_hWnd, WM_SYNCBORDER, true, 0);
	return 0;
}

LRESULT CHtmlDialog::OnBorderResize(WPARAM wParam, LPARAM lParam)
{
	HWND hBorder = (HWND)wParam;
	int nHitTest = (int)lParam;

	RECT rectBorder;
	::GetWindowRect(hBorder, &rectBorder);
	
	CRect rectWin;
	this->GetWindowRect(rectWin);
	switch (nHitTest)
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
	this->MoveWindow(&rectWin);

	return 0;
}

LRESULT CHtmlDialog::OnSyncBorder(WPARAM wParam, LPARAM lParam)
{
	SyncBorder((bool)wParam);
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

	CString sDefaultUrl = GetDefaultUrl();
	if (!sDefaultUrl.IsEmpty())
		m_html.Navigate2(sDefaultUrl);

	//新建Resize Border dialog
	m_mpBorders[HTLEFT] = new CDialogResizeBorder(NULL, m_hWnd, HTLEFT);
	m_mpBorders[HTLEFT]->DoModeless();
	m_mpBorders[HTRIGHT] = new CDialogResizeBorder(NULL, m_hWnd, HTRIGHT);
	m_mpBorders[HTRIGHT]->DoModeless();
	m_mpBorders[HTTOP] = new CDialogResizeBorder(NULL, m_hWnd, HTTOP);
	m_mpBorders[HTTOP]->DoModeless();
	m_mpBorders[HTBOTTOM] = new CDialogResizeBorder(NULL, m_hWnd, HTBOTTOM);
	m_mpBorders[HTBOTTOM]->DoModeless();
	m_mpBorders[HTTOPLEFT] = new CDialogResizeBorder(NULL, m_hWnd, HTTOPLEFT);
	m_mpBorders[HTTOPLEFT]->DoModeless();
	m_mpBorders[HTTOPRIGHT] = new CDialogResizeBorder(NULL, m_hWnd, HTTOPRIGHT);
	m_mpBorders[HTTOPRIGHT]->DoModeless();
	m_mpBorders[HTBOTTOMLEFT] = new CDialogResizeBorder(NULL, m_hWnd, HTBOTTOMLEFT);
	m_mpBorders[HTBOTTOMLEFT]->DoModeless();
	m_mpBorders[HTBOTTOMRIGHT] = new CDialogResizeBorder(NULL, m_hWnd, HTBOTTOMRIGHT);
	m_mpBorders[HTBOTTOMRIGHT]->DoModeless();
	::PostMessage(m_hWnd, WM_SYNCBORDER, false, 0);

	return bRet;
}

BEGIN_MESSAGE_MAP(CHtmlDialog, CDialogEx)
	ON_WM_TIMER()
	ON_WM_SIZE()
	//ON_WM_CTLCOLOR()
	ON_WM_GETMINMAXINFO()
	ON_MESSAGE(WM_BORDER_RESIZE_START, &CHtmlDialog::OnBorderResizeStart)
	ON_MESSAGE(WM_BORDER_RESIZE_END, &CHtmlDialog::OnBorderResizeEnd)
	ON_MESSAGE(WM_BORDER_RESIZE, &CHtmlDialog::OnBorderResize)
	ON_MESSAGE(WM_SYNCBORDER, &CHtmlDialog::OnSyncBorder)
END_MESSAGE_MAP()


// HtmlDialog 消息处理程序
