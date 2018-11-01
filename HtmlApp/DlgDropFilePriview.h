#pragma once

#define AFX_DESIGN_TIME

// CDlgDropFilePriview 对话框

class CDlgDropFilePriview : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDropFilePriview)

public:
	CDlgDropFilePriview(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDropFilePriview();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_DROP_FILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
