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
#error "��֧�ִ���ϵ"
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


//������������Dism++��Ҫ�ĳ���
DISM_API int WINAPI DismApplyDPI(int Size);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                               ��Ҫʵ�����½ӿڣ��Ա���������Dism++
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MIDL_INTERFACE("4d420a2e-ea11-450a-b8a0-ab8ca7772043")
IDismPluginInfo: public IUnknown
{
	//��ò����GUID��ÿ�������ֵӦ�ú㶨
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetGUID(
		_Out_ GUID* pPluginGUID
		) = 0;

	//��ò���İ汾��
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetVersion(
		_Out_writes_(4) UINT16 Version[4]
		) = 0;

	//��ò����ͼ�꣬����ýӿ�δʵ����ô��ʹ��ϵͳ�Դ��ĳ���ͼ��
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetIcon(
		_Out_ HICON* pIcon) = 0;

	//��ò��������
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetAuthor(
		_Outptr_result_z_ BSTR* pAuthor
		) = 0;

	//��ò������
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetName(
		_Outptr_result_z_ BSTR* pPluginName
		) = 0;

	//��ò������
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetDescription(
		_Outptr_result_z_ BSTR* pDescription
		) = 0;

	//��ò���ٷ���վ
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetWebSite(
		_Outptr_result_z_ BSTR* pWebSite
		) = 0;

	//����������°汾,����ø���˵��
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI CheckUpdate(
		_Out_writes_(4)   UINT16 LatestVersion[4],
		_Outptr_result_z_ BSTR*  pUpdateDescription
		) = 0;

	//�������°汾��ָ��Ŀ¼
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI DownloadUpdate(
		_In_z_   LPCWSTR      NewFileRootPath,
		_In_opt_ DismCallBack CallBack,
		_In_opt_ LPVOID       UserData
		) = 0;
};

//ӳ���������ò����ʾ��ӳ����Ĳ����չ�Ի�����
MIDL_INTERFACE("836f8013-9fd3-40eb-b5f4-62d09d54dff2")
IDismImagePlugin: public IUnknown
{
	//��ʾ�Ի���
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI DoModal(
		_In_opt_ HWND Parent
		) = 0;

	//�ڴ����ϲ����ʾ������
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetName(
		_Outptr_result_z_ BSTR* pPluginName
		) = 0;

	//�ڴ����ϣ��ò����ʾ��˵��
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetDescription(
		_Outptr_result_z_ BSTR* pDescription
		) = 0;

	//��ò����ͼ�꣬����ýӿ�δʵ����ô��ʹ��ϵͳ�Դ��ĳ���ͼ��
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI GetIcon(
		_Out_ HICON* pIcon
		) = 0;
};

//�����ϣ��һ��DLLͬʱ֧�ֶ�����������ʵ�ִ˽ӿ�
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


//Dism++���������֧��
MIDL_INTERFACE("E9C1A683-7D97-4415-B5E9-18E228FB47DD")
IDismImagePluginCommandLine : public IUnknown
{
	//ppszArglist�����������������NULL��ֹ
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI put_CommandLine(
		_In_ LPCWSTR* ppszArglist
		) = 0;
};

//��������Ľӿ�,�õ��Ľӿڶ���ͨ��Reaease ɾ���������ǰϵͳ��֧�ָò�����벻Ҫ����S_OK
_Check_return_ _Success_(return == S_OK)
HRESULT WINAPI DismCreateInstance2(
	_In_         DismSession Session,
	_In_         const GUID& InstanceIID,
	_COM_Outptr_ void**      ppInstance
	);

/*��������ַ���ת��
��XML�У���������#��ͷ���ַ�����Dism++������ô˽ӿ����������������ʾ���������ҪΪ��Ĳ��ʵ�ֶ������֧�֣���ô��ʵ�ִ˽ӿ�*/
_Check_return_ _Success_(return !=NULL )
LPCWSTR WINAPI DismLoadString(
	_In_z_ LPCWSTR Str
	);