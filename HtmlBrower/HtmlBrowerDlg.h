
// HtmlBrowerDlg.h : ͷ�ļ�
//

#pragma once
#include "HtmlCtrl.h"
#include "afxwin.h"

// CHtmlBrowerDlg �Ի���
class CHtmlBrowerDlg : public CDialogEx
{
// ����
public:
	CHtmlBrowerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CHtmlBrowerDlg();

// �Ի�������
	enum { IDD = IDD_HTMLBROWER_DIALOG };

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
	DECLARE_MESSAGE_MAP()

	BOOL foo(int, int);
	BOOL foo1(const TCHAR* str1, LPCTSTR str2);

	void onClickedHtmlButton(LPCTSTR pJsonStr);
	void onClickLink(const CString& sProtocols, const CString& sCmd);

public:
	CHtmlCtrl m_html;
	CEdit m_ctrlEditUrl;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
