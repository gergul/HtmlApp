
// HtmlBrower.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "HtmlBrower.h"
#include "HtmlBrowerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHtmlBrowerApp

BEGIN_MESSAGE_MAP(CHtmlBrowerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CHtmlBrowerApp ����

CHtmlBrowerApp::CHtmlBrowerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CHtmlBrowerApp ����

CHtmlBrowerApp theApp;


BOOL RaisePrivileges()
{
	HANDLE TokenHandle;
	TOKEN_PRIVILEGES t_privileges = {0};

	if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &TokenHandle))
	{
		return FALSE;
	}

	if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &t_privileges.Privileges[0].Luid))
	{
		return TRUE;
	}

	t_privileges.PrivilegeCount = 1;
	t_privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if(!AdjustTokenPrivileges(TokenHandle, FALSE, &t_privileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		CloseHandle(TokenHandle);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void SetIECoreVersion()
{
	TCHAR* path = _T("SOFTWARE\\Microsoft\\Internet Explorer\\MAIN\\FeatureControl\\FEATURE_BROWSER_EMULATION");
	CString valueName = AfxGetAppName();
	valueName += _T(".exe");
	long version=9999;
	TCHAR err[1024];
	HKEY hKey;
	DWORD dwDisposition;
	long ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, path, 0,REG_LEGAL_OPTION, &hKey);
	if( ret != ERROR_SUCCESS)
	{
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, ret, NULL,err,sizeof(err),NULL);
		ret = RegCreateKeyEx(HKEY_LOCAL_MACHINE, path,0, NULL, REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL, &hKey, &dwDisposition);
		if( ret != ERROR_SUCCESS)
		{
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, ret, NULL,err,sizeof(err),NULL);
			return;
		}
	}

	ret = RegSetValueEx( hKey, valueName, NULL, REG_DWORD, (BYTE*)&version, sizeof(version));
	if( ret != ERROR_SUCCESS)
		return;
}

// CHtmlBrowerApp ��ʼ��

BOOL CHtmlBrowerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	RaisePrivileges();
	SetIECoreVersion();

	CHtmlBrowerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

