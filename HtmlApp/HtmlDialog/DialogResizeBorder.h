// DialogResizeBorder.h
#ifndef DIALOG_RESIZE_BORDER
#define DIALOG_RESIZE_BORDER
#include <windows.h>
#include <map>

#define WM_BORDER_RESIZE_START WM_USER + 1000//WPARAM:BorderDialog, LPARAM:HitTestType  ���أ�S_OK��Ч
#define WM_BORDER_RESIZE_END WM_USER + 1001//WPARAM:BorderDialog, LPARAM:HitTestType  ���أ�S_OK��Ч
#define WM_BORDER_RESIZE WM_USER + 1002 //WPARAM:BorderDialog, LPARAM:HitTestType  ���أ�S_OK��Ч

#define WM_SYNCBORDER WM_USER + 2000//ͬ������������Ϣ


class CDialogResizeBorder
{
public:
	/*nHitTestType:
	HTLEFT
	HTRIGHT
	HTTOP
	HTTOPLEFT
	HTTOPRIGHT
	HTBOTTOM
	HTBOTTOMLEFT
	HTBOTTOMRIGHT
	*/
	CDialogResizeBorder(HINSTANCE hinst, HWND hwndOwner, int nHitTestType);

	~CDialogResizeBorder();

	virtual BOOL DoModeless();

	virtual void SyncBorder(bool bCheckShowed = true);

	inline LONG GetWidth();
	inline LONG GetHornDepth();
		
public:
	HWND m_hWnd;

	//��͸���ȣ�ӦΪ 1~255��һ��Ϊ1������Ϊ0�������ܽ�������¼�����ֻ�е���ʱ��Ϊ����
	static int ms_opaque;

	static int ms_width;//�߿���
	static int ms_hornDepth;//�ǵ���ȣ����Ҫ��Բ�Ǵ���������ڿ��Ե���
	static int ms_minOwerWidth;//������С�ɵ�����С
	static int ms_minOwerHeight;//������С�ɵ�����С

protected:
	// API��ע�����Ϣ�������������ǳ�Ա��������Ϊ��Ա������thisָ��
	static INT_PTR CALLBACK DialogProc(HWND hWnd,
		UINT uMsg, WPARAM wParam, LPARAM lParam);

	static BOOL _ModifyStyle(HWND hWnd, int nStyleOffset,
		DWORD dwRemove, DWORD dwAdd, UINT nFlags);

	static BOOL ModifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);

protected:
	void syncBorder(bool bCheckShowed = true);
	void resizeWindow();

private:
	HWND  m_hOwnerWnd;
	HINSTANCE m_hInst;

	static std::map<HWND, HCURSOR> ms_mpCursors;
	int m_nHitTestType;
	static std::map<HWND, int> ms_mpHitTestType;
	static std::map<HWND, CDialogResizeBorder*> ms_wndClass;
		
};

#endif // DIALOG_RESIZE_BORDER
