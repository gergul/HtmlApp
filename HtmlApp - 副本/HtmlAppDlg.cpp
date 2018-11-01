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
	DDX_Control(pDX, IDC_EDIT1, m_ctrlEditUrl);
}

BEGIN_MESSAGE_MAP(CHtmlAppDlg, CHtmlDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHtmlAppDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHtmlAppDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CHtmlAppDlg ��Ϣ�������

BOOL CHtmlAppDlg::OnInitDialog()
{
	CHtmlDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
		
	ADD_EXTERNAL_CALL(&m_html, _T("onClickButton"), &CHtmlAppDlg::onClickedHtmlButton, this);
	ADD_ON_CLICK_LINK(&m_html, _T("toolbar"), _T("console"), &CHtmlAppDlg::onClickLink, this);
	ADD_ON_CLICK_LINK(&m_html, _T(""), _T("Gergul"), &CHtmlAppDlg::onClickLink, this);

	CHtmlCtrl::AppendFunction(_T("foo"), (AFX_PMSG)&CHtmlAppDlg::foo, VT_EMPTY, VTS_I4 VTS_I4);
	CHtmlCtrl::AppendFunction(_T("foo1"), (AFX_PMSG)&CHtmlAppDlg::foo1, VT_EMPTY, VTS_BSTR VTS_BSTR);
	
	TCHAR szBasePath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szBasePath);
	m_ctrlEditUrl.SetWindowText(CString(szBasePath) + _T("\\data\\layui-v2.4.3\\dlg.html"));

	OnBnClickedButton1();
		
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
		//CRect rect;
		//CPaintDC dc(this);
		//GetClientRect(rect);
		//dc.FillSolidRect(rect, RGB(255, 0, 0));

		__super::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHtmlAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHtmlAppDlg::OnBnClickedButton1()
{	
#if 1
	if (g_sHtmlFile.IsEmpty())
		return;
	m_ctrlEditUrl.SetWindowText(g_sHtmlFile);

	CString sUrl;
	m_ctrlEditUrl.GetWindowText(sUrl);
	m_html.Navigate2(sUrl);
#else
 	CString m_Text = _T("<html>")
 		_T("<body>")
		_T("<a href=\"Gergul\">����</a>")
 		_T("</body>")
 		_T("</html>");
  	m_html.SetHtml(m_Text );
#endif
}

BOOL CHtmlAppDlg::PreTranslateMessage(MSG* pMsg)
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

	return __super::PreTranslateMessage(pMsg);
}

BOOL CHtmlAppDlg::foo(int n1, int n2)
{
	CString s;
	s.Format(_T("foo(%d, %d)"), n1, n2);
	AfxMessageBox(s);
	return TRUE;
}

BOOL CHtmlAppDlg::foo1(const TCHAR* str1, LPCTSTR str2)
{
	CString s;
	s.Format(_T("foo1(%s, %s)"), str1, str2);
	AfxMessageBox(s);
	return TRUE;
}

void CHtmlAppDlg::OnBnClickedButton2()
{
	CComVariant res;
	m_html.ExecuteScript(res, _T("function itemclick(item)        {            alert(item.text);        }        $(function ()        {            window['g'] =            $(\"#maingrid\").ligerGrid({                height:'100%',                columns: [                { display: '�˿�', name: 'CustomerID', align: 'left', width: 100, minWidth: 60 },                { display: '��˾��', name: 'CompanyName', minWidth: 120 },                { display: '��ϵ��', name: 'ContactName', minWidth: 140 },                { display: '����', name: 'City' }                ], data:CustomersData,  pageSize:30 ,rownumbers:true,                toolbar: { items: [                { text: '����', click: itemclick, icon: 'add' },                { line: true },                { text: '�޸�', click: itemclick, icon: 'modify' },                { line: true },                { text: 'ɾ��', click: itemclick, img: '../../../lib/ligerUI/skins/icons/delete.gif' }                ]                }            });                         $(\"#pageloading\").hide();        });        function deleteRow()        {            g.deleteSelectedRow();        }"));

	std::vector<std::pair<CString, CComVariant> > vctRes;
	m_html.ExecuteScriptInAllFrames(vctRes, _T("document.getElementById('text123').value"));
	
	CString sText = GetHtmlHelper()->GetElementValue(_T("text123"));
	AfxMessageBox(sText);
	GetHtmlHelper()->SetElementValue(_T("text123"), _T("gergul123123123"));

	m_html.ExecuteScript(_T("willError()"));

	m_html.ErgodicElementsInAllFrames([&](CComDispatchDriver& element) {
		CComVariant vValue = _T("�Ұ���");
		element.PutPropertyByName(L"value", &vValue);
	});
}

void CHtmlAppDlg::onClickedHtmlButton(LPCTSTR pJsonStr)
{
	GetHtmlHelper()->SetElementValue(_T("text123"), pJsonStr);
	m_html.ExecuteScript(_T("document.getElementById('tianqi').src = 'https://www.baidu.com';"));
}

void CHtmlAppDlg::onClickLink(const CString& sProtocols, const CString& sCmd)
{
	GetHtmlHelper()->SetElementValue(_T("text123"), sProtocols + _T("-") + sCmd);
}
