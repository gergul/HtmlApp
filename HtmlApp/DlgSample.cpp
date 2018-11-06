// DlgSample.cpp : 实现文件
//

#include "stdafx.h"
#include "HtmlApp.h"
#include "DlgSample.h"
#include "afxdialogex.h"

// CDlgSample 对话框

IMPLEMENT_DYNAMIC(CDlgSample, CHtmlDialog)

CDlgSample::CDlgSample(CWnd* pParent /*=NULL*/)
	: CHtmlDialog(IDD_DLG_MODAL_SAMPLE, pParent)
{

}

CDlgSample::~CDlgSample()
{
}

void CDlgSample::DoDataExchange(CDataExchange* pDX)
{
	CHtmlDialog::DoDataExchange(pDX);
}

CString CDlgSample::GetDefaultUrl()
{
	//设置主页
	return _T("https://www.baidu.com");
}

BEGIN_MESSAGE_MAP(CDlgSample, CHtmlDialog)
END_MESSAGE_MAP()


// CDlgSample 消息处理程序
