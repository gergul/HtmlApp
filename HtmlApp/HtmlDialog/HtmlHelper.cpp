#include "stdafx.h"
#include "HtmlHelper.h"


CHtmlHelper::CHtmlHelper(CHtmlCtrl* pHtmlCtrl)
	: m_pHtmlCtrl(pHtmlCtrl)
{
}


CHtmlHelper::~CHtmlHelper()
{
}

CString CHtmlHelper::GetElementValue(const CString& idElement)
{
	std::vector<CString> vctRes = GetElementAttrib(idElement, _T("value"));
	for (int i = 0; i < vctRes.size(); ++i)
	{
		if (!vctRes[i].IsEmpty())
			return vctRes[i];
	}
	return _T("");
}

void CHtmlHelper::SetElementValue(const CString& idElement, const CString& val)
{
	SetElementAttrib(idElement, _T("value"), val);
}

std::vector<CString> CHtmlHelper::GetElementAttrib(const CString& idElement, const CString& attribName)
{
	std::vector<CString> vctRet;

	std::vector<std::pair<CString, CComVariant> > vctRes;
	CString sHack;
	sHack.Format(_T("document.getElementById('%s')['%s']"), idElement, attribName);
	m_pHtmlCtrl->ExecuteScriptInAllFrames(vctRes, sHack);
	for (int i = 0; i < vctRes.size(); ++i)
	{
		if (vctRes[i].second.vt == VT_BSTR && !CString(vctRes[i].second).IsEmpty())
		{
			vctRet.push_back(CString(vctRes[i].second.bstrVal));
		}
	}

	return vctRet;
}

void CHtmlHelper::SetElementAttrib(const CString& idElement, const CString& attribName, const CString& val)
{
	CString sHack;
	sHack.Format(_T("document.getElementById('%s')['%s']='%s'"), idElement, attribName, val);
	m_pHtmlCtrl->ExecuteScriptInAllFrames(sHack);
}