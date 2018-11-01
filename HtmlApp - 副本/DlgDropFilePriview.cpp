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

void CDlgDropFilePriview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BOOL CDlgDropFilePriview::OnInitDialog()
{
	BOOL bRet = CDialogEx::OnInitDialog();
		
	return bRet;
}

BEGIN_MESSAGE_MAP(CDlgDropFilePriview, CDialogEx)
	ON_WM_DROPFILES()
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

	CHtmlAppDlg* pHtmlDlg = dynamic_cast<CHtmlAppDlg*>(this->GetParent());
	if (pHtmlDlg == NULL)
		return;
	pHtmlDlg->GetHtmlCtrl()->Navigate2(sDropFile);
}
