#pragma once
#include "HtmlCtrl.h"

class CHtmlHelper
{
public:
	CHtmlHelper(CHtmlCtrl* pHtmlCtrl);
	~CHtmlHelper();

public:
	//ȫframe��ȡ����ֵ
	std::vector<CString> GetElementAttrib(const CString& idElement, const CString& attribName);
	//ȫframe��������ֵ
	void SetElementAttrib(const CString& idElement, const CString& attribName, const CString& val);
	CString GetElementValue(const CString& idElement);
	void SetElementValue(const CString& idElement, const CString& val);



private:
	CHtmlCtrl* m_pHtmlCtrl;
};

