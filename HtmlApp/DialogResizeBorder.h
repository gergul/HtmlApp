// DialogResizeBorder.h
#ifndef KDIALOG_H_INCLUDED
#define KDIALOG_H_INCLUDED
#include <windows.h>
#include <map>

#define WM_BORDER_RESIZE_START WM_USER + 1000
#define WM_BORDER_RESIZE_END WM_USER + 1001
#define WM_BORDER_RESIZE WM_USER + 1002
#define GAP 10

/*
HTLEFT
HTRIGHT
HTTOP
HTTOPLEFT
HTTOPRIGHT
HTBOTTOM
HTBOTTOMLEFT
HTBOTTOMRIGHT
*/

class CDialogResizeBorder
{
public:
	CDialogResizeBorder(HINSTANCE hinst, HWND hwndOwner, int nHitTestType);

	~CDialogResizeBorder();

	virtual BOOL DoModeless();

	HWND m_hWnd;

protected:
	// API��ע�����Ϣ�������������ǳ�Ա��������Ϊ��Ա������thisָ��
	static INT_PTR CALLBACK DialogProc(HWND hWnd,
		UINT uMsg, WPARAM wParam, LPARAM lParam);

	static BOOL _ModifyStyle(HWND hWnd, int nStyleOffset,
		DWORD dwRemove, DWORD dwAdd, UINT nFlags);

	static BOOL ModifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);

private:
	HWND  m_hOwnerWnd;
	HINSTANCE m_hInst;

	static std::map<HWND, HCURSOR> ms_mpCursors;
	int m_nHitTestType;
	static std::map<HWND, int> ms_mpHitTestType;

	//��͸���ȣ�ӦΪ 1~255��һ��Ϊ1��ֻ�е���ʱ��Ϊ����
	static int ms_opaque;
};

#endif // KDIALOG_H_INCLUDED
