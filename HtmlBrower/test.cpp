#define WM_NVTO (WM_USER+1000) 
class NvToParam
{
public:
	CString URL;
	DWORD Flags;
	CString TargetFrameName;
	CByteArray PostedData;
	CString Headers;
};

void CDemoView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName,
	CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel)
{
	CString strHeaders(lpszHeaders);
	if (strHeaders.Find("User-Agent:LHPBrowser 1.0") < 0)// ���ͷ����û���Զ����User-Agent�� 
	{
		*pbCancel = TRUE;// û�У�ȡ����ε��� 
		if (!strHeaders.IsEmpty())
			strHeaders += "\r\n";
		strHeaders += "User-Agent:LHPBrowser 1.0";// �����Զ����User-Agent�� 
		NvToParam* pNvTo = new NvToParam;
		pNvTo->URL = lpszURL;
		pNvTo->Flags = nFlags;
		pNvTo->TargetFrameName = lpszTargetFrameName;
		baPostedData.Copy(pNvTo->PostedData);
		pNvTo->Headers = strHeaders; // ����һ���Զ���ĵ�����Ϣ�����Ѳ�������ȥ 
		PostMessage(WM_NVTO, (WPARAM)pNvTo);
		return;
	}

	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);

}

LRESULT CDemoView::OnNvTo(WPARAM wParam, LPARAM lParam)
{
	NvToParam* pNvTo = (NvToParam*)wParam;
	Navigate2((LPCTSTR)pNvTo->URL, pNvTo->Flags, pNvTo->PostedData, (LPCTSTR)pNvTo->TargetFrameName, (LPCTSTR)pNvTo->Headers);

	delete pNvTo;
	return 1;
}