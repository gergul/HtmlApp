//定义文件
//
#pragma once

#include <afxhtml.h>
#include <atlsafe.h>
#include <functional>
#include <vector>
#include <map>

// macro to declare a typedef for ATL smart poitners; eg SPIHTMLDocument2
#define DECLARE_SMARTPTR(ifacename) typedef CComQIPtr<ifacename> SP##ifacename;
// smart pointer to IHTMLDocument2
DECLARE_SMARTPTR(IHTMLDocument2)

typedef std::function<void(LPCTSTR pJsonStr)> FN_ON_EXTERNAL_CALL;
//ADD_EXTERNAL_CALL 注册在js中调用的C++函数(异步)
//  pHtmlCtrl - Html控件指针
//  jsFuncName - 在js中调用的名称
//  memberFun - 回调函数
//  memberFunClassObjPtr - 回调函数所在类的对象指针
//js调用c++的方法见AppendFunction的说明
#define ADD_EXTERNAL_CALL(pHtmlCtrl, jsFuncName, memberFun, memberFunClassObjPtr) \
	(pHtmlCtrl)->AppendFunction((jsFuncName), \
	(FN_ON_EXTERNAL_CALL)std::bind(memberFun, (memberFunClassObjPtr), std::placeholders::_1));


typedef std::function<void(const CString& sProtocol, const CString& sCmd)> FN_ON_CLICK_LINK;
//ADD_ON_CLICK_LINK 注册点击链接的回调(异步)
//  pHtmlCtrl - Html控件指针
//  protocol - 链接协议，如“http”,“app”等，命名要求见AppendOnClickLink的说明
//  cmd - 命令
//  memberFun - 回调函数
//  memberFunClassObjPtr - 回调函数所在类的对象指针
#define ADD_ON_CLICK_LINK(pHtmlCtrl, protocol, cmd, memberFun, memberFunClassObjPtr) \
	(pHtmlCtrl)->AppendOnClickLink((protocol), (cmd), \
	(FN_ON_CLICK_LINK)std::bind(memberFun, (memberFunClassObjPtr), std::placeholders::_1, std::placeholders::_2));

//注册点击链接的回调原型
//  返回：TRUE - 只点击不进行打开网页；FALSE - 打开网页，如果一个命令没有在这个注册，则默认是打开网页的。
typedef std::function<BOOL(const CString& sProtocol, const CString& sCmd)> FN_ON_CLICK_LINK_SYNC;
//ADD_ON_CLICK_LINK_SYNC 注册点击链接的回调(同步)
//  pHtmlCtrl - Html控件指针
//  protocol - 链接协议，如“http”,“app”等，命名要求见AppendOnClickLink的说明
//  cmd - 命令
//  memberFun - 回调函数
//  memberFunClassObjPtr - 回调函数所在类的对象指针
#define ADD_ON_CLICK_LINK_SYNC(pHtmlCtrl, protocol, cmd, memberFun, memberFunClassObjPtr) \
	(pHtmlCtrl)->AppendOnClickLink_SYNC((protocol), (cmd), \
	(FN_ON_CLICK_LINK_SYNC)std::bind(memberFun, (memberFunClassObjPtr), std::placeholders::_1, std::placeholders::_2));

//这个类将 CHtmlView 转换为普通的能在对话框和框架中使用的控制
class CHtmlCtrl
	: public CHtmlView
{
	DECLARE_DYNCREATE(CHtmlCtrl)

public:
	CHtmlCtrl(); // protected constructor used by dynamic creation
	virtual ~CHtmlCtrl() {};

public:
	// create control in same place as static control
	BOOL CreateFromStatic(UINT nID, CWnd* pParent, DWORD dwStyle = WS_CHILD | WS_VISIBLE, CCreateContext* pContext = NULL);
	// get/set HideContextMenu property
	BOOL GetIsHideContextMenu() { return m_bHideMenu; }
	void SetIsHideContextMenu(BOOL val) { m_bHideMenu = val; }
	// Set doc contents from string
	BOOL SetHtml(LPCTSTR strHTML);
	// create control from scratch
	BOOL Create(const RECT& rc, CWnd* pParent, UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE, CCreateContext* pContext = NULL);
	//获得网页
	SPIHTMLDocument2 GetSafeHtmlDocument() const;

	//脚本交互
public:
	//绑定c++函数到脚本（同步，不能在这种回调中进行DOM操作）
	//脚本中调用window.external.pszFuncName(...)即可调用相应的C++函数
	//  pFuncAddr必须是CCmdTarget类或其继承类的成员函数
	//  wRetType 见VARENUM
	//  pszParamType 见 afxdisp.h VTS_XXX 每个参数类型使用空格分开
	static BOOL AppendFunction_SYNC(LPCTSTR pszFuncName, AFX_PMSG pFuncAddr, WORD wRetType, LPCSTR pszParamType);
	//绑定C++函数到超链接（同步，不能在这种回调中进行DOM操作）
	//  sProtocol - 协议。必需为以下字符“0~9 a~z + - .”才合法（不含引号），并且字母不能是大写
	//  sCmd - 命令
	BOOL AppendOnClickLink_SYNC(const CString& sProtocol, const CString& sCmd, FN_ON_CLICK_LINK_SYNC fn);

public:
	//绑定C++函数到脚本（异步）
	//脚本中调用window.external.call('pszFuncName', 'json string')即可调用相应的C++函数
	BOOL AppendFunction(LPCTSTR pszFuncName, FN_ON_EXTERNAL_CALL pfn);
	//绑定C++函数到超链接（异步）
	//  sProtocol - 协议。必需为以下字符“0~9 a~z + - .”才合法（不含引号），并且字母不能是大写
	//  sCmd - 命令
	BOOL AppendOnClickLink(const CString& sProtocol, const CString& sCmd, FN_ON_CLICK_LINK fn);

public:
	static BOOL CallScriptFunction(CComPtr<IHTMLDocument2> &doc, LPCTSTR pStrFuncName,
		CStringArray* pArrFuncArgs = NULL, CComVariant* pOutVarRes = NULL);
	static BOOL ExecuteScript(CComPtr<IHTMLDocument2> &doc, const CString &sScript,
		const CString &sLanguage = _T("JavaScript"));
	static BOOL ExecuteScript(CComPtr<IHTMLDocument2> &doc, CComVariant& res,
		const CString &sScript, const CString &sLanguage = _T("JavaScript"));

public:
	//执行脚本
	BOOL ExecuteScript(const CString &sScript, const CString &sLanguage = _T("JavaScript"));
	//全frame执行脚本
	void ExecuteScriptInAllFrames(const CString &sScript, const CString &sLanguage = _T("JavaScript"));
	//执行脚本的函数
	BOOL CallScriptFunction(LPCTSTR pStrFuncName, CStringArray* pArrFuncArgs, CComVariant* pOutVarRes);
	//执行脚本（有返回值）
	BOOL ExecuteScript(CComVariant& res, const CString &sScript, const CString &sLanguage = _T("JavaScript"));
	//全frame执行脚本（有返回值）<<frameUrl, res>>
	void ExecuteScriptInAllFrames(std::vector<std::pair<CString, CComVariant> >& vctRes, const CString &sScript,
		const CString &sLanguage = _T("JavaScript"));
	
public://遍历element
	static void ErgodicElements(const SPIHTMLDocument2& doc, std::function<void(CComDispatchDriver& element)> funcErgodic);
	static void ErgodicElementsInAllFrames(const SPIHTMLDocument2& doc, std::function<void(CComDispatchDriver& element)> funcErgodic);
	void ErgodicElements(std::function<void(CComDispatchDriver& element)> funcErgodic);
	void ErgodicElementsInAllFrames(std::function<void(CComDispatchDriver& element)> funcErgodic);

protected:
	//把url分割出协议和命令
	static bool SplitProtocol(const CString& src, CString& sProtocol, CString& sCmd);
	//协议名是否有效。0~9 a~z + - . 才合法（大写也不行）
	static bool IsProtocolLegal(const CString& sProtocol);

protected:
	// 重写该函数可以截获子窗口消息，从而禁用上下文菜单。
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// 通常，CHtmlView 自己是在 PostNcDestroy 销毁的，但对于一个界面控制来说
	// 我们不想那样做，因为控制一般都是作为另一个窗口对象的成员实现的。
	virtual void PostNcDestroy() {}
	// 重写以便旁路掉对 MFC doc/view 框架的依赖，CHtmView 仅仅在这里依附于框架。
	afx_msg void OnDestroy();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT msg);
	// 点击链接时触发
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName,
		CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	// 打开URL时触发
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	// 打开URL出错时触发
	virtual void OnNavigateError(LPCTSTR lpszURL, LPCTSTR lpszFrame, DWORD dwError, BOOL *pbCancel);
	// 滚动条显隐相关
	virtual HRESULT OnGetHostInfo(DOCHOSTUIINFO *pInfo);
	// 为了与脚本交互
	virtual HRESULT OnGetExternal(LPDISPATCH *lppDispatch);
	// 需要打开窗口时触发
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);

	//右键菜单相关
	// return HRESULT(S_OK);则不弹出系统默认菜单；return HRESULT(S_FALSE);则弹出系统默认菜单
	virtual HRESULT OnShowContextMenu(DWORD dwID, LPPOINT ppt, LPUNKNOWN pcmdtReserved, LPDISPATCH pdispReserved) override;

	DECLARE_MESSAGE_MAP();

protected:
	static const AFX_DISPMAP dispatchMap;
	static const AFX_DISPMAP* PASCAL GetThisDispatchMap();
	virtual const AFX_DISPMAP* GetDispatchMap() const;
private:
#define MAX_FUNCS 256
	static AFX_DISPMAP_ENTRY _dispatchEntries[MAX_FUNCS];
	static UINT _dispatchEntryCount;
	static DWORD _dwStockPropMask;

protected:
	//点击链接与js运行c++方法的消息转接
	afx_msg LRESULT OnClickLink(WPARAM pProtocol, LPARAM pCmd);
	afx_msg LRESULT OnExternalCall(WPARAM pFuncName, LPARAM pJsonStr);
	void OnScriptExternalCall(LPCTSTR pFunName, LPCTSTR pJsonStr);
		
private:
	BOOL m_bHideMenu;// hide context menu
	std::map<CString, FN_ON_EXTERNAL_CALL> m_mpExternalCall;
	std::map<CString, std::map<CString, FN_ON_CLICK_LINK> > m_mpOnClickLink;//<protocol, <cmd, function>>
	std::map<CString, std::map<CString, FN_ON_CLICK_LINK_SYNC> > m_mpOnClickLink_SYNC;//<protocol, <cmd, function>>
};



//////////////////////////////////////遍历器//////////////////////////////////////
//遍历所有frame
class CErgodicFrameHandler
{
public:
	CErgodicFrameHandler();
	virtual ~CErgodicFrameHandler();

	void Run(CComPtr<IHTMLDocument2> &parentDoc);

protected:
	virtual void OnFrame(CComPtr<IHTMLDocument2> &doc) = 0;
};

//class Script Error Handler
class CScriptErrorHandler
	: public CErgodicFrameHandler
{
public:
	CScriptErrorHandler();
	virtual ~CScriptErrorHandler();

protected:
	virtual void OnFrame(CComPtr<IHTMLDocument2> &doc);

private:
	CString m_sScript;
};

//class run script on each frame
class CScriptRunner
	: public CErgodicFrameHandler
{
public:
	CScriptRunner(const CString& sScript, const CString& sScriptType = _T("JavaScript"));
	virtual ~CScriptRunner();

protected:
	virtual void OnFrame(CComPtr<IHTMLDocument2> &doc);

private:
	CString m_sScript;
	CString m_sScriptType;
};

//class run script on each frame (this class will return values)
class CScriptRunnerEx
	: public CErgodicFrameHandler
{
public:
	CScriptRunnerEx(const CString& sScript, const CString& sScriptType = _T("JavaScript"));
	virtual ~CScriptRunnerEx();

	std::vector<std::pair<CString, CComVariant> > m_vctResults;//<<frameUrl, res>>

protected:
	virtual void OnFrame(CComPtr<IHTMLDocument2> &doc);

private:
	CString m_sScript;
	CString m_sScriptType;
};
