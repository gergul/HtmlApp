
// HtmlApp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHtmlAppApp:
// �йش����ʵ�֣������ HtmlApp.cpp
//

class CHtmlAppApp : public CWinApp
{
public:
	CHtmlAppApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHtmlAppApp theApp;
extern CString g_sHtmlFile;