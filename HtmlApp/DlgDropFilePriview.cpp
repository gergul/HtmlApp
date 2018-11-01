// DlgDropFilePriview.cpp : 实现文件
//

#include "stdafx.h"
#include "HtmlApp.h"
#include "DlgDropFilePriview.h"
#include "afxdialogex.h"
#include "HtmlAppDlg.h"


// CDlgDropFilePriview 对话框

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


// CDlgDropFilePriview 消息处理程序


void CDlgDropFilePriview::OnDropFiles(HDROP hDropInfo)
{
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//取得被拖动文件的数目
	CString sDropFile;
	for (int i = 0; i < DropCount; i++)
	{
		TCHAR wcStr[MAX_PATH];
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名
		sDropFile = wcStr;
	}
	DragFinish(hDropInfo);  //拖放结束后,释放内存

	CDialogEx::OnDropFiles(hDropInfo);

	if (sDropFile.IsEmpty())
		return;

	CHtmlAppDlg* pHtmlDlg = dynamic_cast<CHtmlAppDlg*>(this->GetParent());
	if (pHtmlDlg == NULL)
		return;
	pHtmlDlg->GetHtmlCtrl()->Navigate2(sDropFile);
}
