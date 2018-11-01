
// HtmlAppDlg.h : 头文件
//

#pragma once
#include "HtmlCtrl.h"
#include "afxwin.h"
#include "HtmlHelper.h"
#include "DlgDropFilePriview.h"
#include "HtmlDialog.h"

// CHtmlAppDlg 对话框
class CHtmlAppDlg : public CHtmlDialog
{
// 构造
public:
	CHtmlAppDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CHtmlAppDlg();

// 对话框数据
	enum { IDD = IDD_HTMLAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
		
// 实现
protected:
	HICON m_hIcon;
	
	// 生成的消息映射函数
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
