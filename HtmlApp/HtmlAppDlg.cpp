// HtmlAppDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HtmlApp.h"
#include "HtmlAppDlg.h"
#include "DlgSample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHtmlAppDlg �Ի���

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


// CHtmlAppDlg ��Ϣ�������

BOOL CHtmlAppDlg::OnInitDialog()
{
	CHtmlDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	//ע���첽�ص�����
	ADD_EXTERNAL_CALL(&m_html, _T("asyncFoo"), &CHtmlAppDlg::js_asyncFoo, this);
	ADD_EXTERNAL_CALL0(&m_html, _T("asyncFoo2"), &CHtmlAppDlg::js_asyncFoo2, this);
	//ע�����ӻص�
	ADD_ON_CLICK_LINK(&m_html, _T("toolbar"), _T("console"), &CHtmlAppDlg::onClickLink, this);
	ADD_ON_CLICK_LINK(&m_html, _T("app"), _T("Gergul"), &CHtmlAppDlg::onClickLink, this);
	ADD_ON_CLICK_LINK(&m_html, _T(""), _T("Gergul"), &CHtmlAppDlg::onClickLink, this);
	//ע�����ӻص�
	ADD_ON_CLICK_LINK_SYNC(&m_html, _T("https"), _T("//www.baidu.com/"), &CHtmlAppDlg::onClickLink_SYNC, this);
	ADD_ON_CLICK_LINK_SYNC(&m_html, _T("https"), _T("//www.google.com/"), &CHtmlAppDlg::onClickLink_SYNC, this);
	//ע��ͬ���ص�����
	CHtmlCtrl::AppendFunction_SYNC(_T("js_syncFoo"), (AFX_PMSG)&CHtmlAppDlg::js_syncFoo, VT_EMPTY, VTS_I4 VTS_I4);
	CHtmlCtrl::AppendFunction_SYNC(_T("js_syncFoo2"), (AFX_PMSG)&CHtmlAppDlg::js_syncFoo2, VT_EMPTY, VTS_BSTR VTS_BSTR);
		
	m_pDlgDropFilePriview = new CDlgDropFilePriview(this);
	m_pDlgDropFilePriview->Create(CDlgDropFilePriview::IDD, this);
	m_pDlgDropFilePriview->ShowWindow(SW_SHOW);
	
	//CDlgSample* dlg = new CDlgSample(this);
	//dlg->Create(CDlgSample::IDD, this);
	//dlg->ShowWindow(SW_SHOW);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHtmlAppDlg::OnPaint()
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
		__super::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	//���ﲻ�ܽ���dom����


	CString s;
	s.Format(_T("js_syncFoo(%d, %d)"), n1, n2);
	AfxMessageBox(s);
	return TRUE;
}

BOOL CHtmlAppDlg::js_syncFoo2(const TCHAR* str1, LPCTSTR str2)
{
	//���ﲻ�ܽ���dom����


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

	//����frameִ��
	CComVariant res;
	m_html.ExecuteScript(res, _T("(function(){return 123;})();"));
	int i = res.intVal;
		
	//�������е�Ԫ�ص�valueֵ
	m_html.ErgodicElementsInAllFrames([&](CComDispatchDriver& element) {
		CComVariant vValue = _T("�Ұ���");
		element.PutPropertyByName(L"value", &vValue);
	});

	//HtmlHelper��Ӧ��
	CString sText = GetHtmlHelper()->GetElementValue(_T("text123"));
	AfxMessageBox(sText);
	GetHtmlHelper()->SetElementValue(_T("text123"), _T("gergul"));

	//����frame��ִ��
	std::vector<std::pair<CString, CComVariant> > vctRes;
	m_html.ExecuteScriptInAllFrames(vctRes, _T("document.getElementById('text123').value"));
	if (vctRes.size() > 0)
	{
		CString sVal = (LPTSTR)vctRes[0].second.bstrVal;
	}

	//������һ��js����
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
		AfxMessageBox(_T("׼���򿪣�"));
		return FALSE;
	}
	if (sProtocols == _T("https") && sCmd == _T("//www.google.com/"))
	{
		AfxMessageBox(_T("��ֹ�򿪣�"));
		return TRUE;
	}

	return FALSE;
}

CString CHtmlAppDlg::GetDefaultUrl()
{
	return g_sHtmlFile;
}
