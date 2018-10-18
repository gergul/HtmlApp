
// HtmlAppDlg.h : ͷ�ļ�
//

#pragma once
#include "HtmlCtrl.h"
#include "afxwin.h"

#define TIMER_WIN_POS 1

// CHtmlAppDlg �Ի���
class CHtmlAppDlg : public CDialogEx
{
// ����
public:
	CHtmlAppDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CHtmlAppDlg();

// �Ի�������
	enum { IDD = IDD_HTMLAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK() {}
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

	BOOL foo(int, int);
	BOOL foo1(const TCHAR* str1, LPCTSTR str2);

	void onClickedHtmlButton(LPCTSTR pJsonStr);
	void onClickLink(const CString& sProtocols, const CString& sCmd);

	void onClickedHtmlTitle(LPCTSTR pJsonStr);
	void onClickedHtmlClose(LPCTSTR pJsonStr);
	void onClickedHtmlMax(LPCTSTR pJsonStr);
	void onClickedHtmlRestore(LPCTSTR pJsonStr);
	void onClickedHtmlMin(LPCTSTR pJsonStr);

public:
	CHtmlCtrl m_html;
	CEdit m_ctrlEditUrl;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	POINT m_ptLast;
};
