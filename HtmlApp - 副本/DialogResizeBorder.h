// DialogResizeBorder.h
#ifndef KDIALOG_H_INCLUDED
#define KDIALOG_H_INCLUDED
#include <windows.h>

#define WM_BORDER_RESIZE_START WM_USER + 1000
#define WM_BORDER_RESIZE_END WM_USER + 1001
#define GAP 10

class CDialogResizeBorder
{
public:
	CDialogResizeBorder(HINSTANCE hinst, HWND hwndOwner);

	~CDialogResizeBorder();

	virtual BOOL DoModeless();

	HWND m_hWnd;

protected:
	// API中注册的消息处理函数，不能是成员函数，因为成员函数有this指针
	static INT_PTR CALLBACK DialogProc(HWND hWnd,
		UINT uMsg, WPARAM wParam, LPARAM lParam);

	static BOOL _ModifyStyle(HWND hWnd, int nStyleOffset,
		DWORD dwRemove, DWORD dwAdd, UINT nFlags);

	static BOOL ModifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);

private:
	HWND  m_hOwnerWnd;
	HINSTANCE m_hInst;
};

#endif // KDIALOG_H_INCLUDED
