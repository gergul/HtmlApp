#pragma once
#include <vector>
#include <afxdialogex.h>
#include "HtmlCtrl.h"
#include "HtmlHelper.h"
#include "DialogResizeBorder.h"

#define TIMER_WIN_POS WM_USER + 10000
#define WM_SYNCBORDER WM_USER + 2000

// HtmlDialog 对话框

class CHtmlDialog 
	: public CDialogEx
{
	DECLARE_DYNAMIC(CHtmlDialog)

public:
	CHtmlDialog(UINT id, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHtmlDialog();

public:
	void InitJsEvents();
	void RemoveBorder();

	CHtmlCtrl* GetHtmlCtrl() { return &m_html; }
	CHtmlHelper* GetHtmlHelper() { return &m_htmlHelper; }

	virtual CString GetDefaultUrl() { return _T(""); }

	void SyncBorder(bool bCheckShowed = true);

protected:
	void js_onClickedClose(LPCTSTR str);
	void js_onClickedMax(LPCTSTR str);
	void js_onClickedRestore(LPCTSTR str);
	void js_onClickedMin(LPCTSTR str);
	void js_onMouseDownCaption(LPCTSTR str);
	void js_onDbClickCaption(LPCTSTR str);

	void js_moveTo(LPCTSTR str);
	void js_setWindowSize(LPCTSTR str);
	void js_showWindow(LPCTSTR str);

	void js_enableResize(LPCTSTR str);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg LRESULT OnBorderResizeStart(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBorderResizeEnd(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBorderResize(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSyncBorder(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	CHtmlCtrl m_html;
	CHtmlHelper m_htmlHelper;	
	POINT m_ptLast;
	//CBrush m_bkBrush;
	bool m_bEnableResize;

	bool m_bWinChangeByBorder;
	std::map<int, CDialogResizeBorder*> m_mpBorders;
};
