#pragma once
#include "HtmlDialog.h"


// CDlgSample 对话框

class CDlgSample 
	: public CHtmlDialog
{
	DECLARE_DYNAMIC(CDlgSample)

public:
	CDlgSample(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSample();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MODAL_SAMPLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

	virtual CString GetDefaultUrl() override;

};
