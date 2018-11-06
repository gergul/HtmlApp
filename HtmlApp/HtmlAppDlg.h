
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

	//绑定的同步回调，在这种回调中不支持dom操作
	BOOL js_syncFoo(int, int);
	BOOL js_syncFoo2(const TCHAR* str1, LPCTSTR str2);

	//绑定的异步回调，在这种回调中支持dom操作
	void js_asyncFoo(LPCTSTR str);

	//绑定的链接回调，在这种回调中支持dom操作
	void onClickLink(const CString& sProtocols, const CString& sCmd);

	//绑定的链接回调，在这种回调中不支持dom操作
	//  返回：TRUE - 取消打开；FALSE - 打开网页
	BOOL onClickLink_SYNC(const CString& sProtocols, const CString& sCmd);

	virtual CString GetDefaultUrl() override;

public:
	CDlgDropFilePriview* m_pDlgDropFilePriview;
};
