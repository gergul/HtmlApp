// HtmlBrowerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HtmlBrower.h"
#include "HtmlBrowerDlg.h"
#include "afxdialogex.h"
#include "HtmlCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHtmlBrowerDlg �Ի���

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


// CHtmlBrowerDlg ��Ϣ�������

BOOL CHtmlBrowerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHtmlBrowerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		_T("<a href=\"Gergul\">����</a>")
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

		CComVariant vValue = _T("�Ұ���");
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
