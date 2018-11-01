
// HtmlAppDlg.h : ͷ�ļ�
//

#pragma once
#include "HtmlCtrl.h"
#include "afxwin.h"
#include "HtmlHelper.h"
#include "DlgDropFilePriview.h"
#include "HtmlDialog.h"

// CHtmlAppDlg �Ի���
class CHtmlAppDlg : public CHtmlDialog
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
	DECLARE_MESSAGE_MAP()

	BOOL foo(int, int);
	BOOL foo1(const TCHAR* str1, LPCTSTR str2);

	void onClickedHtmlButton(LPCTSTR pJsonStr);
	void onClickLink(const CString& sProtocols, const CString& sCmd);

public:
	//HtmlDialogHelper* m_pDlgHelper;
	CEdit m_ctrlEditUrl;
	CDlgDropFilePriview* m_pDlgDropFilePriview;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
