#pragma once
#include <Windows.h>
#include <comdef.h>

#ifndef DISM_API
#ifdef Dism_Exe
#define DISM_API
#else
#define DISM_API __declspec(dllimport)
#endif //!Dism_Exe
#endif //!DISM_API


#define _DismExeIA32 "Dism++x86"
#define _DismExeAMD64 "Dism++x64"
#define _DismExeARM64 "Dism++ARM64"




#if defined _AMD64_
#define _DismExe _DismExeAMD64
#define IsNative TRUE
#define DismExeNative _CRT_WIDE(_DismExeAMD64) L".exe"
#elif defined _X86_
#define _DismExe _DismExeIA32
__forceinline bool __IsNative()
{
	USHORT ProcessMachine = IMAGE_FILE_MACHINE_UNKNOWN;
	//USHORT NativeMachine;
	IsWow64Process2(/*NtGetCurrentProcess()*/(HANDLE)-1, &ProcessMachine, NULL);

	return ProcessMachine == IMAGE_FILE_MACHINE_UNKNOWN;
}
#define IsNative __IsNative()

__forceinline LPCWSTR __DismExeNative()
{
	USHORT ProcessMachine = IMAGE_FILE_MACHINE_UNKNOWN;
	USHORT NativeMachine = IMAGE_FILE_MACHINE_UNKNOWN;
	IsWow64Process2(/*NtGetCurrentProcess()*/(HANDLE)-1, &ProcessMachine, &NativeMachine);

	switch (NativeMachine)
	{
	case IMAGE_FILE_MACHINE_I386:
		return _CRT_WIDE(_DismExeIA32) L".exe";
		break;
	case IMAGE_FILE_MACHINE_AMD64:
		return _CRT_WIDE(_DismExeAMD64) L".exe";
		break;
	case IMAGE_FILE_MACHINE_ARM64:
		return _CRT_WIDE(_DismExeARM64) L".exe";
		break;
	default:
		return NULL;
		break;
	}
}
#define DismExeNative __DismExeNative()
#elif defined _ARM64_
#define _DismExe _DismExeARM64
#define IsNative TRUE
#define DismExeNative _CRT_WIDE(_DismExeARM64) L".exe"
#else
#error "不支持此体系"
#endif

#define DismExe _CRT_WIDE(_DismExe) L".exe"


DISM_API BOOL WINAPI DismIsNoviceMode();

DISM_API HRESULT WINAPI DismGetFileFilter(
	_COM_Outptr_ LPBSTR pFileFilter
	);

_Ret_z_
DISM_API LPCWSTR WINAPI DismMultiLanguage(
		_In_z_ LPCWSTR Str
	);


//将长度缩放至Dism++需要的长度
DISM_API int WINAPI DismApplyDPI(int Size);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                               需要实现以下接口，以便于整合至Dism++
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MIDL_INTERFACE("4d420a2e-ea11-450a-b8a0-ab8ca7772043")
IDismPluginInfo: public IUnknown
{
	//获得插件的GUID，每个插件该值应该恒定
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetGUID(
		_Out_ GUID* pPluginGUID
		) = 0;

	//获得插件的版本号
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetVersion(
		_Out_writes_(4) UINT16 Version[4]
		) = 0;

	//获得插件的图标，如果该接口未实现那么将使用系统自带的程序图标
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetIcon(
		_Out_ HICON* pIcon) = 0;

	//获得插件的作者
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetAuthor(
		_Outptr_result_z_ BSTR* pAuthor
		) = 0;

	//获得插件名称
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetName(
		_Outptr_result_z_ BSTR* pPluginName
		) = 0;

	//获得插件名称
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetDescription(
		_Outptr_result_z_ BSTR* pDescription
		) = 0;

	//获得插件官方网站
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetWebSite(
		_Outptr_result_z_ BSTR* pWebSite
		) = 0;

	//检查插件的最新版本,并获得更新说明
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI CheckUpdate(
		_Out_writes_(4)   UINT16 LatestVersion[4],
		_Outptr_result_z_ BSTR*  pUpdateDescription
		) = 0;

	//下载最新版本到指定目录
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI DownloadUpdate(
		_In_z_   LPCWSTR      NewFileRootPath,
		_In_opt_ DismCallBack CallBack,
		_In_opt_ LPVOID       UserData
		) = 0;
};

//映像处理插件，该插件显示在映像处理的插件扩展对话框中
MIDL_INTERFACE("836f8013-9fd3-40eb-b5f4-62d09d54dff2")
IDismImagePlugin: public IUnknown
{
	//显示对话框
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI DoModal(
		_In_opt_ HWND Parent
		) = 0;

	//在窗口上插件显示的名称
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetName(
		_Outptr_result_z_ BSTR* pPluginName
		) = 0;

	//在窗口上，该插件显示的说明
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetDescription(
		_Outptr_result_z_ BSTR* pDescription
		) = 0;

	//获得插件的图标，如果该接口未实现那么将使用系统自带的程序图标
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetIcon(
		_Out_ HICON* pIcon
		) = 0;
};

//如果你希望一个DLL同时支持多个插件，可以实现此接口
MIDL_INTERFACE("83302884-00ad-43e5-a5f8-57880563463b")
IDismImagePluginCollection: public IUnknown
{
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI get_Count(
		_Out_ long* pcount
		) = 0;

	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI get_Item(
		_In_         long               Index,
		_COM_Outptr_ IDismImagePlugin** pDismImagePlugin
		) = 0;

	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI get__NewEnum(
		_COM_Outptr_ IUnknown** ppUnk
		) = 0;
};


//Dism++插件命令行支持
MIDL_INTERFACE("E9C1A683-7D97-4415-B5E9-18E228FB47DD")
IDismImagePluginCommandLine : public IUnknown
{
	//ppszArglist将传递命令参数，以NULL终止
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI put_CommandLine(
		_In_ LPCWSTR* ppszArglist
		) = 0;
};

//创建插件的接口,得到的接口都会通过Reaease 删除，如果当前系统不支持该插件，请不要返回S_OK
_Check_return_ _Success_(return == S_OK)
HRESULT WINAPI DismCreateInstance2(
	_In_         DismSession Session,
	_In_         const GUID& InstanceIID,
	_COM_Outptr_ void**      ppInstance
	);

/*多国语言字符串转换
在XML中，凡事遇到#开头的字符串，Dism++都会调用此接口来调整多国语言显示，如果你需要为你的插件实现多国语言支持，那么请实现此接口*/
_Check_return_ _Success_(return !=NULL )
LPCWSTR WINAPI DismLoadString(
	_In_z_ LPCWSTR Str
	);