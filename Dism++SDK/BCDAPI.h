#pragma once
#include <Windows.h>
#include <comdef.h>

/////////////////////////////////////////////////
//
// 第三方的BcdAPI实现,可以实现类似于BCDEdit的功能
//
/////////////////////////////////////////////////


//当前启动项GUID
const GUID CurrentBoot = { 0xfa926493, 0x6f1c, 0x4193, { 0xa4, 0x14, 0x58, 0xf0, 0xb2, 0x45, 0x6d, 0x1e } };


MIDL_INTERFACE("27a8e78e-3768-456a-8baa-400eb0058abf")
IBcdDevice : public IUnknown
{
	//保存更改
	virtual HRESULT get_DevicePath(BSTR* pDevicePath) = 0;

	virtual HRESULT put_DevicePath(LPCWSTR DevicePath) = 0;

	virtual HRESULT get_FirmwareType(PFIRMWARE_TYPE pFirmwareType) = 0;

	virtual HRESULT get_DeviceSdi(LPGUID pDeviceSdi) = 0;
};

MIDL_INTERFACE("2d49be61-dbf5-49ae-be82-115afd84e524")
IBcdObject : public IUnknown
{
	virtual HRESULT get_ObjectId(GUID* pId) = 0;

	virtual HRESULT get_BootType(DWORD* pBootType) = 0;

	//获得显示名称
	virtual HRESULT get_Descrtption(BSTR* pDescrtption) = 0;

	//设置显示名称
	virtual HRESULT put_Descrtption(LPCWSTR Descrtption) = 0;

	virtual HRESULT get_Device(IBcdDevice** ppDevice) = 0;

	virtual HRESULT put_Device(IBcdDevice* pDevice) = 0;

	virtual HRESULT get_CustomData(LPCWSTR Name, VARIANT* pData) = 0;

	virtual HRESULT put_CustomData(LPCWSTR Name, VARIANT Data) = 0;
};


MIDL_INTERFACE("391b37e6-7bc5-4d1b-973e-2104becfee34")
IBcdBootLoader : public IBcdObject
{
	//删除此条目
	virtual HRESULT Delete(BOOL RemoveDisplayOnly) = 0;

	//添加到显示顺序
	virtual HRESULT Add() = 0;

	virtual HRESULT Copy(const GUID& NewLoaderID, IBcdBootLoader** ppNewBcdBootLoader) = 0;

	virtual HRESULT get_Path(BSTR* pPath) = 0;

	virtual HRESULT put_Path(LPCWSTR Path) = 0;

	//以下疑似Windows专有
	virtual HRESULT get_OSDevice(IBcdDevice** ppOSDevice) = 0;

	virtual HRESULT put_OSDevice(IBcdDevice* pOSDevice) = 0;

	virtual HRESULT get_Recovery(IBcdBootLoader** ppRecoveryBootLoader) = 0;

	virtual HRESULT put_BootSequence() = 0;
};


MIDL_INTERFACE("9dea862c-5cdd-4e70-acc1-f32b344d4795")
IBcdWindowsBootManager :public IBcdObject
{
	virtual HRESULT get_BootLoader(GUID LoaderID, IBcdBootLoader** ppBcdBootLoader) = 0;

	//实模式启动扇区
#define RealModeLoader 0x10400008

	//Windows 启动加载器
#define WindowsLoader  0x10200003
	
	//Windows 旧 OS 加载器
#define WindowsOldLoader 0x10300006
	virtual HRESULT CreateBootLoader(const GUID& LoaderID,DWORD BootTpye, LPCWSTR Descrtption, IBcdBootLoader** ppBcdBootLoader) = 0;
};


MIDL_INTERFACE("9dea862c-5cdd-4e70-acc1-f32b344d4795")
IBcdSession:public IUnknown
{
	virtual HRESULT get_WindowsBootManager(IBcdWindowsBootManager** ppWindowsBootManager) = 0;
};


/*
此函数可以打开Bcd数据库,返回S_OK标识操作完成，其他任何值都表示错误
StoreFilePath为NULL时直接打开当前系统Bcd文件
*/
HRESULT BcdOpenStore(LPCWSTR StoreFilePath, IBcdSession** ppSession);



HRESULT BcdGetCurrentEntryIdentifier(GUID& CurrentEntryIdentifier);


FIRMWARE_TYPE BcdGetFirmwareType();


HRESULT BcdGetSystemPartition(LPBSTR pBootPartition);


//检查是否是WinPE启动
BOOL BcdIsWinPEBoot();

HRESULT BcdGetFirmwareBootDevice(LPBSTR pFirmwareBootDevice);