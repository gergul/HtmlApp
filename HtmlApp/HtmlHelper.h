#pragma once
#include "HtmlCtrl.h"

class CHtmlHelper
{
public:
	CHtmlHelper(CHtmlCtrl* pHtmlCtrl);
	~CHtmlHelper();

public:
	//全frame获取属性值
	std::vector<CString> GetElementAttrib(const CString& idElement, const CString& attribName);
	//全frame设置属性值
	void SetElementAttrib(const CString& idElement, const CString& attribName, const CString& val);
	CString GetElementValue(const CString& idElement);
	void SetElementValue(const CString& idElement, const CString& val);



private:
	CHtmlCtrl* m_pHtmlCtrl;
};

