#pragma once
#include "HtmlDialog.h"


// CDlgSample �Ի���

class CDlgSample 
	: public CHtmlDialog
{
	DECLARE_DYNAMIC(CDlgSample)

public:
	CDlgSample(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSample();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MODAL_SAMPLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

	virtual CString GetDefaultUrl() override;

};
