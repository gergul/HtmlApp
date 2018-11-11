// HtmlAppDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HtmlApp.h"
#include "HtmlAppDlg.h"
#include "DlgSample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHtmlAppDlg 对话框

CHtmlAppDlg::CHtmlAppDlg(CWnd* pParent /*=NULL*/)
	: CHtmlDialog(CHtmlAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


CHtmlAppDlg::~CHtmlAppDlg()
{
}


void CHtmlAppDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHtmlAppDlg, CHtmlDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CHtmlAppDlg 消息处理程序

BOOL CHtmlAppDlg::OnInitDialog()
{
	CHtmlDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	//注册异步回调函数
	ADD_EXTERNAL_CALL(&m_html, _T("asyncFoo"), &CHtmlAppDlg::js_asyncFoo, this);
	ADD_EXTERNAL_CALL0(&m_html, _T("asyncFoo2"), &CHtmlAppDlg::js_asyncFoo2, this);
	//注册链接回调
	ADD_ON_CLICK_LINK(&m_html, _T("toolbar"), _T("console"), &CHtmlAppDlg::onClickLink, this);
	ADD_ON_CLICK_LINK(&m_html, _T("app"), _T("Gergul"), &CHtmlAppDlg::onClickLink, this);
	ADD_ON_CLICK_LINK(&m_html, _T(""), _T("Gergul"), &CHtmlAppDlg::onClickLink, this);
	//注册链接回调
	ADD_ON_CLICK_LINK_SYNC(&m_html, _T("https"), _T("//www.baidu.com/"), &CHtmlAppDlg::onClickLink_SYNC, this);
	ADD_ON_CLICK_LINK_SYNC(&m_html, _T("https"), _T("//www.google.com/"), &CHtmlAppDlg::onClickLink_SYNC, this);
	//注册同步回调函数
	CHtmlCtrl::AppendFunction_SYNC(_T("js_syncFoo"), (AFX_PMSG)&CHtmlAppDlg::js_syncFoo, VT_EMPTY, VTS_I4 VTS_I4);
	CHtmlCtrl::AppendFunction_SYNC(_T("js_syncFoo2"), (AFX_PMSG)&CHtmlAppDlg::js_syncFoo2, VT_EMPTY, VTS_BSTR VTS_BSTR);
		
	m_pDlgDropFilePriview = new CDlgDropFilePriview(this);
	m_pDlgDropFilePriview->Create(CDlgDropFilePriview::IDD, this);
	m_pDlgDropFilePriview->ShowWindow(SW_SHOW);
	
	//CDlgSample* dlg = new CDlgSample(this);
	//dlg->Create(CDlgSample::IDD, this);
	//dlg->ShowWindow(SW_SHOW);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHtmlAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		__super::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHtmlAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CHtmlAppDlg::PreTranslateMessage(MSG* pMsg)
{
	return __super::PreTranslateMessage(pMsg);
}

BOOL CHtmlAppDlg::js_syncFoo(int n1, int n2)
{
	//这里不能进行dom操作


	CString s;
	s.Format(_T("js_syncFoo(%d, %d)"), n1, n2);
	AfxMessageBox(s);
	return TRUE;
}

BOOL CHtmlAppDlg::js_syncFoo2(const TCHAR* str1, LPCTSTR str2)
{
	//这里不能进行dom操作


	CString s;
	s.Format(_T("js_syncFoo2(%s, %s)"), str1, str2);
	AfxMessageBox(s);
	return TRUE;
}

void CHtmlAppDlg::js_asyncFoo(LPCTSTR str)
{
	CString s;
	s.Format(_T("js_asyncFoo(%s)"), str);
	AfxMessageBox(s);

	//顶层frame执行
	CComVariant res;
	m_html.ExecuteScript(res, _T("(function(){return 123;})();"));
	int i = res.intVal;
		
	//设置所有的元素的value值
	m_html.ErgodicElementsInAllFrames([&](CComDispatchDriver& element) {
		CComVariant vValue = _T("我爱你");
		element.PutPropertyByName(L"value", &vValue);
	});

	//HtmlHelper的应用
	CString sText = GetHtmlHelper()->GetElementValue(_T("text123"));
	AfxMessageBox(sText);
	GetHtmlHelper()->SetElementValue(_T("text123"), _T("gergul"));

	//所有frame都执行
	std::vector<std::pair<CString, CComVariant> > vctRes;
	m_html.ExecuteScriptInAllFrames(vctRes, _T("document.getElementById('text123').value"));
	if (vctRes.size() > 0)
	{
		CString sVal = (LPTSTR)vctRes[0].second.bstrVal;
	}

	//将导致一个js错误
	m_html.ExecuteScript(_T("willError()"));
}

void CHtmlAppDlg::js_asyncFoo2()
{
	CString s;
	s.Format(_T("js_asyncFoo2()"));
	AfxMessageBox(s);
}

void CHtmlAppDlg::onClickLink(const CString& sProtocols, const CString& sCmd)
{
	if (sProtocols == _T("toolbar") && sCmd == _T("console"))
	{
		GetHtmlHelper()->SetElementValue(_T("text123"), sProtocols + _T("-") + sCmd);
	}
	else if (sProtocols == _T("app") && sCmd == _T("Gergul"))
	{
		GetHtmlHelper()->SetElementValue(_T("text123"), _T("Hello Gergul"));
	}
	else if (sProtocols == _T("") && sCmd == _T("Gergul"))
	{
		AfxMessageBox(_T("Hello Gergul"));
	}
}

BOOL CHtmlAppDlg::onClickLink_SYNC(const CString& sProtocols, const CString& sCmd)
{
	if (sProtocols == _T("https") && sCmd == _T("//www.baidu.com/"))
	{
		AfxMessageBox(_T("准备打开！"));
		return FALSE;
	}
	if (sProtocols == _T("https") && sCmd == _T("//www.google.com/"))
	{
		AfxMessageBox(_T("阻止打开！"));
		return TRUE;
	}

	return FALSE;
}

CString CHtmlAppDlg::GetDefaultUrl()
{
	return g_sHtmlFile;
}
