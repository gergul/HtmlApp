#pragma once

#define AFX_DESIGN_TIME

// CDlgDropFilePriview �Ի���

class CDlgDropFilePriview : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDropFilePriview)

public:
	CDlgDropFilePriview(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDropFilePriview();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_DROP_FILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
