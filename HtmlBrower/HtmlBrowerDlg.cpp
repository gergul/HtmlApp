// HtmlBrowerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HtmlBrower.h"
#include "HtmlBrowerDlg.h"
#include "afxdialogex.h"
#include "HtmlCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHtmlBrowerDlg 对话框

#define WM_CLICK_CONSOLE WM_USER + 1

CHtmlBrowerDlg::CHtmlBrowerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHtmlBrowerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


CHtmlBrowerDlg::~CHtmlBrowerDlg()
{

}


void CHtmlBrowerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlEditUrl);
}

BEGIN_MESSAGE_MAP(CHtmlBrowerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHtmlBrowerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHtmlBrowerDlg::OnBnClickedButton2)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CHtmlBrowerDlg 消息处理程序

BOOL CHtmlBrowerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// TODO: 在此添加控件通知处理程序代码
	
	m_html.SetIsHideContextMenu(TRUE);
	m_html.CreateFromStatic(IDC_STATIC_HELP, this);

	ADD_EXTERNAL_CALL(&m_html, _T("onClickButton"), &CHtmlBrowerDlg::onClickedHtmlButton, this);
	ADD_ON_CLICK_LINK(&m_html, _T("toolbar"), _T("console"), &CHtmlBrowerDlg::onClickLink, this);
	ADD_ON_CLICK_LINK(&m_html, _T(""), _T("Gergul"), &CHtmlBrowerDlg::onClickLink, this);

	CHtmlCtrl::AppendFunction(_T("foo"), (AFX_PMSG)&CHtmlBrowerDlg::foo, VT_EMPTY, VTS_I4 VTS_I4);
	CHtmlCtrl::AppendFunction(_T("foo1"), (AFX_PMSG)&CHtmlBrowerDlg::foo1, VT_EMPTY, VTS_BSTR VTS_BSTR);


	TCHAR szBasePath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szBasePath);
	m_ctrlEditUrl.SetWindowText(CString(szBasePath) + _T("\\data\\layui-v2.4.3\\dlg.html"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHtmlBrowerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHtmlBrowerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHtmlBrowerDlg::OnBnClickedButton1()
{	
#if 1
	CString sUrl;
	m_ctrlEditUrl.GetWindowText(sUrl);
	m_html.Navigate2(sUrl, NULL, NULL, _T("User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.81 Safari/537.36 OPR/45.0.2552.812"));
#else
 	CString m_Text = _T("<html>")
 		_T("<body>")
		_T("<a href=\"Gergul\">哈哈</a>")
 		_T("</body>")
 		_T("</html>");
  	m_html.SetHtml(m_Text );
#endif
}

BOOL CHtmlBrowerDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN &&
		pMsg->wParam == VK_RETURN)
	{
		if (pMsg->hwnd == m_ctrlEditUrl.GetSafeHwnd())
		{
			OnBnClickedButton1();
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CHtmlBrowerDlg::foo(int n1, int n2)
{
	CString s;
	s.Format(_T("foo(%d, %d)"), n1, n2);
	AfxMessageBox(s);
	return TRUE;
}

BOOL CHtmlBrowerDlg::foo1(const TCHAR* str1, LPCTSTR str2)
{
	CString s;
	s.Format(_T("foo1(%s, %s)"), str1, str2);
	AfxMessageBox(s);
	return TRUE;
}

void CHtmlBrowerDlg::OnBnClickedButton2()
{
	CComVariant res;
	m_html.ExecuteScript(res, _T("\"123\""));

	std::vector<std::pair<CString, CComVariant> > vctRes;
	m_html.ExecuteScriptInAllFrames(vctRes, _T("document.getElementById('text123').value"));
	
	CString sText = m_html.GetElementValue(_T("text123"));
	AfxMessageBox(sText);
	m_html.SetElementValue(_T("text123"), _T("gergul123123123"));

	m_html.ExecuteScript(_T("willError()"));

	SPIHTMLDocument2 doc = m_html.GetSafeHtmlDocument();
	if (NULL == doc)
		return;
	//IHTMLElement *pHtml = NULL;
	//doc->get_body(&pHtml);
	//CComBSTR bs = _T("123");

	CComQIPtr< IHTMLElementCollection > spElementCollection;
	doc->get_all(&spElementCollection);
	long lLen = 0;
	spElementCollection->get_length(&lLen);
	for (int i=0; i<lLen; ++i)
	{
		CComDispatchDriver spDisp;
		HRESULT hr = spElementCollection->item(CComVariant(i),CComVariant(),&spDisp);
		if(FAILED(hr))
			continue;

		CComVariant vValue = _T("我爱你");
		spDisp.PutPropertyByName(L"value", &vValue);
	}
	
	doc->close();
}

void CHtmlBrowerDlg::onClickedHtmlButton(LPCTSTR pJsonStr)
{
	m_html.SetElementValue(_T("text123"), pJsonStr);
	m_html.ExecuteScript(_T("document.getElementById('tianqi').src = 'https://www.baidu.com';"));
}

void CHtmlBrowerDlg::onClickLink(const CString& sProtocols, const CString& sCmd)
{
	m_html.SetElementValue(_T("text123"), sProtocols + _T("-") + sCmd);
}

void CHtmlBrowerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (IsWindow(m_html.GetSafeHwnd()))
	{
		CRect rectHtml;
		m_html.GetWindowRect(&rectHtml);
		ScreenToClient(&rectHtml);
		rectHtml.bottom = cy;
		rectHtml.right = cx;

		m_html.MoveWindow(&rectHtml);
	}
}
