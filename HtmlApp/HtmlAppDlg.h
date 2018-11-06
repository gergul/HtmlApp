
// HtmlAppDlg.h : ͷ�ļ�
//

#pragma once
#include "HtmlCtrl.h"
#include "afxwin.h"
#include "HtmlHelper.h"
#include "DlgDropFilePriview.h"
#include "HtmlDialog.h"

// CHtmlAppDlg �Ի���
class CHtmlAppDlg : public CHtmlDialog
{
// ����
public:
	CHtmlAppDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CHtmlAppDlg();

// �Ի�������
	enum { IDD = IDD_HTMLAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
		
// ʵ��
protected:
	HICON m_hIcon;
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK() {}
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

	//�󶨵�ͬ���ص��������ֻص��в�֧��dom����
	BOOL js_syncFoo(int, int);
	BOOL js_syncFoo2(const TCHAR* str1, LPCTSTR str2);

	//�󶨵��첽�ص��������ֻص���֧��dom����
	void js_asyncFoo(LPCTSTR str);

	//�󶨵����ӻص��������ֻص���֧��dom����
	void onClickLink(const CString& sProtocols, const CString& sCmd);

	//�󶨵����ӻص��������ֻص��в�֧��dom����
	//  ���أ�TRUE - ȡ���򿪣�FALSE - ����ҳ
	BOOL onClickLink_SYNC(const CString& sProtocols, const CString& sCmd);

	virtual CString GetDefaultUrl() override;

public:
	CDlgDropFilePriview* m_pDlgDropFilePriview;
};
