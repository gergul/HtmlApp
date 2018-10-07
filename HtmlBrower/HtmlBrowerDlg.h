
// HtmlBrowerDlg.h : 头文件
//

#pragma once
#include "HtmlCtrl.h"
#include "afxwin.h"

// CHtmlBrowerDlg 对话框
class CHtmlBrowerDlg : public CDialogEx
{
// 构造
public:
	CHtmlBrowerDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CHtmlBrowerDlg();

// 对话框数据
	enum { IDD = IDD_HTMLBROWER_DIALOG };

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
	CHtmlCtrl m_html;
	CEdit m_ctrlEditUrl;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
