// DlgDropFilePriview.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HtmlApp.h"
#include "DlgDropFilePriview.h"
#include "afxdialogex.h"
#include "HtmlAppDlg.h"

// CDlgDropFilePriview �Ի���

IMPLEMENT_DYNAMIC(CDlgDropFilePriview, CDialogEx)

CDlgDropFilePriview::CDlgDropFilePriview(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_DROP_FILE, pParent)
{

}

CDlgDropFilePriview::~CDlgDropFilePriview()
{
}

CHtmlAppDlg* CDlgDropFilePriview::GetAppDlg()
{
	return dynamic_cast<CHtmlAppDlg*>(this->GetParent());
}

void CDlgDropFilePriview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HTML, m_ctrlHtmlText);
}


BOOL CDlgDropFilePriview::OnInitDialog()
{
	BOOL bRet = CDialogEx::OnInitDialog();
	
	CString sText =
		_T("<html>\r\n")
		_T("  <body>\r\n")
		_T("    <a href=\"Gergul\">���</a>\r\n")
		_T("  </body>\r\n")
		_T("</html>");

	m_ctrlHtmlText.SetWindowText(sText);

	return bRet;
}

BEGIN_MESSAGE_MAP(CDlgDropFilePriview, CDialogEx)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgDropFilePriview::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgDropFilePriview ��Ϣ�������


void CDlgDropFilePriview::OnDropFiles(HDROP hDropInfo)
{
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//ȡ�ñ��϶��ļ�����Ŀ
	CString sDropFile;
	for (int i = 0; i < DropCount; i++)
	{
		TCHAR wcStr[MAX_PATH];
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ���
		sDropFile = wcStr;
	}
	DragFinish(hDropInfo);  //�ϷŽ�����,�ͷ��ڴ�

	CDialogEx::OnDropFiles(hDropInfo);

	if (sDropFile.IsEmpty())
		return;

	CHtmlAppDlg* pHtmlDlg = GetAppDlg();
	if (pHtmlDlg == NULL)
		return;
	pHtmlDlg->GetHtmlCtrl()->Navigate2(sDropFile);
}


void CDlgDropFilePriview::OnBnClickedButton1()
{
	CHtmlAppDlg* pHtmlDlg = GetAppDlg();
	if (pHtmlDlg == NULL)
		return;
	
	CString sHtml;
	m_ctrlHtmlText.GetWindowText(sHtml);

	CString sText = sHtml;
	sText.Trim();
	if (sText.Left(4).MakeUpper() == _T("HTTP") || sText.Left(4).MakeUpper() == _T("FILE") || sText.GetAt(1) == ':')
		pHtmlDlg->GetHtmlCtrl()->Navigate2(sText);
	else
		pHtmlDlg->GetHtmlCtrl()->SetHtml(sHtml);
}
