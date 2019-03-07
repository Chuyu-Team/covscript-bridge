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

#ifndef DISM_HOST
#ifdef __CbsHostStub
#define DISM_HOST
#else
#define DISM_HOST __declspec(dllimport)
#endif //!__CbsHostStub
#endif //!DISM_HOST

////////////////////////////////////////////////////////////////
//                     枚举


enum DismPackageState
{
	DismPackageStateUnknown = 0,
	DismPackageStateNotPresent,
	DismPackageStateUnintallRequested,
	DismPackageStateStaged,              //暂存
	DismPackageStateStaging,             //正在暂存
	DismPackageStateInstalled,           //更新已经安装
	DismPackageStateInstallRequested,    //安装挂起
	DismPackageStateSuperseded,          //该更新已经被取代
	DismPackageStatePartiallInstalled,   //部分安装
	DismPackageStateRemoved,             //已经删除
	DismPackageStatePermanent,           //永久固化更新包
};
enum DismFeatureState
{
	DismFeatureStateUnknown = 0,
	DismFeatureStateNotPresent,
	DismFeatureStateUnintallRequested,   //该功能已经关闭但是未生效
	DismFeatureStateDisable,             //该功能已经关闭
	DismFeatureStateStaging,
	DismFeatureStateEnable,              //该功能被启动
	DismFeatureStateEnableRequested,     //该功能已经启动，但是未生效
	DismFeatureStateSuperseded,          //该功能已经被取代
	DismFeatureStatePartiallInstalled,   //该功能部分安装
	DismFeatureStateRemoved              //该功能已经删除
};

enum DismFullyOfflineInstallableState
{
	DismPackageFullyOfflineUnknow = 0,
	DismPackageFullyOfflineInatallable,
	DismPackageFullyOfflineNotInatallable,
};



enum DismDriverSinStatus
{
	DismDriverSinStatusUnknow = 0,
	DismDriverSinStatusUnsigned,
	DismDriverSinStatusSinged
};


enum DriverShowEnum
{
	DriverShowAll = 0,
	DriverShowInbox = 1,
	DriverShowOutOfBox = 2
};


enum DismMountedImageStatus
{
	DismMountedImageStatusValid = 0,
	DismMountedImageStatusMounting = 1,
	DismMountedImageStatusInvalid = 2,
	DismMountedImageStatusNeedsRemount = 4
};

enum DismImageFileTpye
{
	WimImageFile,
	VhdImageFile
};

//WIM或者esd文件的压缩类型
enum DismCompressTpye
{
	//未知压缩类型
	Compress_Unknown = -1,

	//仅存储，不压缩文件
	Compress_None = 0,

	//此压缩方式支持WIMBOOT启动
	Compress_XpressHuffman = 1,

	//快速压缩，可以节省压缩时间并且可以减少提交占用
	Compress_Xpress = 2,

	//最大压缩，可以节省空间
	Compress_LZX = 3,

	//极限压缩，非常耗费时间，但是体积最小
	Compress_LZMS = 4,
};


enum DismServiceStartType
{
	//启动类型未知，可能是系统启动项，也可能是Dism无法识别的其他启动类型，为了安全性Dism++无法修改启动类型未知的项目
	DismServiceStartTypeUnknown = -1,
	//该服务已经关闭
	DismServiceStartTypeDisable,
	//该服务为手动启动
	DismServiceStartTypeManual,
	//该服务是自动启动
	DismServiceStartTypeAuto,
	//该服务是延迟启动，注意有_不可延迟标记的无法修改为延迟启动，会返回参数错误
	DismServiceStartTypeDelayed
};

enum DismSystemStatus
{
	//状态未知
	DismSystemStatusUnknown = -1,
	//准备就绪
	DismSystemStatusReady,
	//该系统不支持Dism++
	DismSystemStatusNotSupported,
	//找不到系统，目标目录无法访问或者路径不存在
	DismSystemStatusCannotFind,
	//挂载已经失效，需要删除
	DismSystemStatusNeedRemove,
	//请稍等
	DismSystemStatusWait
};


enum DismEnvironmentType
{
	DismEnvironmentDefault = 0, //32位系统获得32位目录，64位系统获取64位路径
	DismEnvironment64Only,    //仅仅获取64位路径，对于32位系统会失败！
	DismEnvironment86Only,    //总是返回32位路径
};


enum DismImageHealthState
{
	DismImageHealthy = 0,      //映像十分健康不需要修复
	DismImageRepairable = 1,   //映像已经受损，但是可以修复
	DismImageNonRepairable = 2 //映像已经收到致命问题，不可修复
};

enum DismServiceType
{
	DismSystemService,    //系统服务
	DismAppService,       //第三方应用程序
	DismDriverService,    //驱动程序
};


enum ProfileStatus
{
	ProfileStatusDisabled = 0,
	ProfileStatusEnabled = 1,
	ProfileStatusApplied = 2,
	ProfileStatusMax
};

enum StartupType
{
	StartupTypeUnknow = -1,

	//HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
	StartupTypeSystemRun,

	//HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Run
	StartupTypeSystemRun32,

	//HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\RunOnce
	StartupTypeSystemRunOnce,

	//HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\RunOnce
	StartupTypeSystemRunOnce32,

	//HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
	StartupTypeUserRun,

	//HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\RunOnce
	StartupTypeUserRunOnce,

	//%SystemDirve%\ProgramData\Microsoft\Windows\Start Menu\Programs\Startup
	StartupTypeAllUsersStartupFolder,

	//%UserProfile%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup
	StartupTypeCurrentUserStartupFolder,

	//HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager
	StartupTypeNativeBootExecute,

	//HKEY_USERS\DEFAULT\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
	StartupTypeDefaultUserRun,

	//HKEY_USERS\DEFAULT\SOFTWARE\Microsoft\Windows\CurrentVersion\RunOnce
	StartupTypeDefaultUserRunOnce,
};

enum StartupState
{
	StartupStateRemove = -1,
	StartupStateDisable,
	StartupStateEnable,
};

////////////////////////////////////////////////////////////////
//                      结构定义

#pragma pack(push, 1)

struct DismSystem
{
	//系统状态
	DismSystemStatus Status;

	/*
	操作系统CPU体系，可能值为：
	PROCESSOR_ARCHITECTURE_AMD64     x64体系
	PROCESSOR_ARCHITECTURE_INTEL     x86体系
	PROCESSOR_ARCHITECTURE_UNKNOWN   未知体系*/
	long Architecture;

	//在线指示
#define _联机映像      0x1     //如果为联机映像那么该标记为1 否则为0

	//存在形式
#define _本地硬盘      0x2  //映像存放于本地
#define _挂载映像      0x4  //映像是来自WIM或者VHD挂载的

	//使用的技术
#define _WIMBOOT       0x8  //映像使用了WIMBOOT技术
#define _VHD装载       0x10  //映像来自VHD装载
#define _CompactOs     0x20  //映像使用了CompactOs技术
#define _WinPE         0x40
	//用户自定义区 24~31  Dism++API可以保证不会使用这块区域，你可以自行添加新的定义
	DWORD Flags;       //Flags拥有以上组合标志
	DWORD ProductType;          //授权类型 WinNT、LanmanNT 或者 ServerNT

	//系统版本号 比如6.3.9600.17041
	UINT16 Version[4];


	wchar_t ProductName[256];    //操作系统名称
	wchar_t EditionID[256];      //系统具体版本

	wchar_t InstallationType[40];      //系统安装类型
	DWORD DefaultLanguage;      //默认显示语言
	DWORD InstallLanguage;      //系统安装语言
	wchar_t InstallLanguageFallback[256];//语言回退列表
	//WIM XML中的Flags
	wchar_t szFlags[256];
	wchar_t RootPath[MAX_PATH];       //系统安装位置
	//映像扩展路径，用于保存WIM路径以及VHD路径 多字符字符串
	wchar_t ExtendPath[1];
};


struct DismPackage
{
	DismPackageState State;
	wchar_t RestartRequired[40];

	wchar_t ReleaseType[40];
	wchar_t Identity[256];
	wchar_t Name[256];
	wchar_t Description[512];
	wchar_t ProductName[256];
	wchar_t ProductVersion[256];
	wchar_t Company[256];
	wchar_t Copyright[256];
	wchar_t SupportInformation[512];
	wchar_t InstallPackageName[256];
	wchar_t InstallLocation[256];
	wchar_t InstallClient[256];
	wchar_t InstallUserName[256];

	//暂无
	FILETIME CreationTime;
	FILETIME LastUpdateTime;
	FILETIME InstallTime;

	wchar_t Keyword[256];
	wchar_t ScavengeSequence[40];
	VARIANT_BOOL IsFullyOfflineInstallable;
	VARIANT_BOOL IsApplicable;
};

struct DismFeature
{
	DismFeatureState State;
	wchar_t RestartRequired[40];
	wchar_t Name[256];
	wchar_t DisplayName[512];
	wchar_t Description[512];
	//DWORD ParentFeatureNameCount;
	wchar_t ParentFeatureName[40];
};

struct DismCapability
{
	DismFeatureState State;
	DWORD DownloadSize;
	DWORD InstallSize;

	wchar_t Name[256];
	wchar_t ID[256];
	wchar_t DisplayName[512];
	wchar_t Description[512];
};


struct DismDriver
{
	wchar_t LocaleName[0x55];
	wchar_t InfProviderName[0x104];
	wchar_t CatalogFile[0x104];
	wchar_t InfPath[0x104];
	wchar_t PublishedInfName[256];
	GUID ClassGuid;
	wchar_t ClassName[0x104];
	wchar_t ClassDescription[256];
	UINT16 Version[4];
	FILETIME Date;
	VARIANT_BOOL InBox;
	VARIANT_BOOL BootCritical;
	VARIANT_BOOL SigStatus;
};


struct DismMountedImage
{
	wchar_t MountDir[MAX_PATH];
	wchar_t ImagePath[MAX_PATH];
	DWORD Index;
	DismMountedImageStatus Status;
	VARIANT_BOOL ReadWritable;
};

struct DismImageInfo
{
	//系统体系
	long Architecture;

	//创建日期
	FILETIME CreationTime;

	//展开空间
	UINT64 Space;

	//系统版本号
	UINT16 Version[4];

	//////////////////////////////////////////////////
	//        你可以修改以下信息 来设置映像信息

	//映像名称
	wchar_t Name[256];

	//映像说明
	wchar_t Description[512];

	//显示名称
	wchar_t DisplayName[256];

	//显示说明
	wchar_t DisplayDescription[512];

	//映像版本标记
	wchar_t Flags[256];
};

struct DismImageFileInfo
{
	//启动下标
	int BootIndex;

	//文件类型
	DismImageFileTpye Type;

	//文件唯一标识
	GUID FileGUID;

	//压缩类型
	DismCompressTpye Compression;

	//映像数量
	DWORD ImageInfoCount;

	//映像
	DismImageInfo ImageInfo[0];
};

struct DismService
{
	DismServiceType Type;
	/*
	服务启动类型,可能值为
	SERVICE_AUTO_START
	SERVICE_BOOT_START
	SERVICE_DEMAND_START
	SERVICE_DISABLED
	SERVICE_SYSTEM_START
	*/
	//延迟启动
#define SERVICE_Delay_START 5
	DWORD dwStartType;

#define _系统保护 0x00000001
#define _不可延迟 0x00000002
#define _系统服务 0x00000004
	//服务Flags 拥有以上状态
	DWORD Flags;

	//服务名称
	wchar_t Name[256];

	//对应服务显示名称
	wchar_t DisplayName[256];

	//对应服务显示描述
	wchar_t Description[512];

	//对应服务路径
	wchar_t ImagePath[MAX_PATH];

	//对应服务的登录状态
	wchar_t ObjectName[256];
};


struct AppxPackage
{
	//当前结构体大小，指向下一个AppxPackage元素
	DWORD cbData;
	wchar_t FullName[256];
	wchar_t InstalledLocation[MAX_PATH];
	wchar_t Users[1];
};



#pragma pack(pop)



typedef class CCbsHostProxy* DismSession;


#define DISM_MSG_PROGRESS   38008     //进度信息wParam为当前完成百分比
#define DISM_MSG_PROCESS    38009     //指示该文件是否应该被捕获wParam = (PWSTR) pszFullPath   lParam = (PBOOL) pfProcessFile
#define DISM_MSG_SCANNING   38010     //扫描的文件数量与文件夹 wParam=(BOOL)IsDirector   lParam=(UINT)Count
#define DISM_MGS_RemoveInfo 37001     //指示该文件或者文件夹需要处理   wParam=(DWORD)Type    lParam=(LPCWSTR)FilePath
#define Dism_MSG_QUERY_ABORT 38030    //是否需要中断该操作？返回-1 则中断当前操作，返回S_OK那么函数正常进行 
#define DISM_MGS_AllowExclusive 39001 //指示此更新是否允请求独占   wParam=(PBOOL)pAllowExclusive

//Dism回掉函数，用于返回进度等信息dwMessageId，有以上几种消息  UserData是你传入的指针 如果函数正常进行，请返回 ERROR_SUCCESS
typedef DWORD(WINAPI *DismCallBack)(DWORD dwMessageId, WPARAM wParam, LPARAM lParam, PVOID UserData);


///////////////////////////////////////////////基础函数支持////////////////////////////////////////////////
//
//

//获取指定的注册表键值,调用后需要使用RegClose关闭
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRegOpenKeyEx(
	_In_   DismSession Session,
	_In_   HKEY        hKey,
	_In_z_ LPCWSTR     lpSubKey,
	_In_   REGSAM      samDesired,
	_Out_  PHKEY       phkResult
	);

//创建键值
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRegCreateKeyEx(
	_In_      DismSession Session,
	_In_      HKEY        hKey,
	_In_z_    LPCWSTR     lpSubKey,
	_In_      REGSAM      samDesired,
	_Out_     PHKEY       phkResult,
	_Out_opt_ LPDWORD     lpdwDisposition
	);

//获取指定的注册表键值,调用后需要使用RegClose关闭
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRegOpenKey(
	_In_   DismSession Session,
	_In_   HKEY        hKey,
	_In_z_ LPCWSTR     lpSubKey,
	_Out_  PHKEY       phkResult
	);

//转换指定的环境变量
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismExpandEnvironmentStrings(
	_In_              DismSession Session,
	_In_z_            LPCWSTR     lpSrc,
	_Outptr_result_z_ LPBSTR      lpDst
	);

#define DismLogLevelSilent      0    //不输出任何信息
#define DismLogLevelFailure     1    //仅错误
#define DismLogLevelWarning     2    //错误和警告
#define DismLogLevelInformation 3    //错误、警告和信息
#define DismLogLevelDebug       4    //以上所有内容和调试输出
//写入日志
_Check_return_ _Success_(return == S_OK)
DISM_HOST HRESULT WINAPI DismWriteLog(
	_In_   DWORD   LogLevel,
	_In_z_ LPCWSTR LogName,
	_In_z_ LPCWSTR LogValue
	);

//释放Dism接口调用后的空间
_Success_(return == S_OK)
DISM_API HRESULT WINAPI DismFreeMemory(
	_In_ void* pStruct
	);

//根据会话获得系统信息
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetSystemInfoBySession(
	_In_     DismSession  Session,
	_Outptr_ DismSystem** Info
	);

//根据路径获得系统信息
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetSystemInfoByPath(
	_In_z_   LPCWSTR      RootPath,
	_Outptr_ DismSystem** Info
	);

//将指定错误代码转换为对应文本。
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismFormatMessage(
	_In_              HRESULT hr,
	_Outptr_result_z_ LPBSTR  ppErrorMessage
	);

//获取临时目录
_Ret_z_
DISM_HOST LPCWSTR WINAPI DismGetScratchDir();

DISM_API BOOL WINAPI DismUnloadRegMount(
	_In_z_ LPCWSTR RootPath
	);

//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////更新包命令///////////////////////////////////////////////
//
//

//添加更新包
_Check_return_ _Success_(return ==S_OK)
DISM_API HRESULT WINAPI DismAddPackage(
	_In_     DismSession  Session,
	_In_z_   LPCWSTR      PackageFilePath,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);

//删除更新包
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRemovePackage(
	_In_     DismSession  Session,
	_In_z_   LPCWSTR      PackageName,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);

//获取更新包信息
//HRESULT WINAPI DismGetPackage(DismSession Session, LPCWSTR PackageIdentity, DismPackage** ppPackageInfo);

//获取所有更新包
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetPackages(
	_In_                            DismSession   Session,
	_Outptr_result_buffer_(*pCount) DismPackage** ppPackages,
	_Out_                           DWORD*        pCount,
	_In_opt_                        DismCallBack  CallBack,
	_In_opt_                        LPVOID        UserData
	);

//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////功能包命令/////////////////////////////////////////////////////
//
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismChangeFeatures(
	_In_       DismSession  Session,
	_In_z_     LPCWSTR      FeatureNames,  //需要关闭的功能名称
#define DismLimitAccess 0x00000001   //NT6.1无效 打开功能时不要从微软服务器中下载文件 PS：如果这样设定可能会应该不能下载到文件而打开失败
	_In_opt_   DWORD        ChangeFlags,   //关闭标志，支持以上状态
	_In_opt_z_ LPCWSTR      SourcePaths,  //NT6.1无效 指定启用源，在启动功能时优先从源复制文件,多个源以NULL分割
	_In_opt_   DismCallBack CallBack,
	_In_opt_   LPVOID       UserData
	);

//获取功能状态
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetFeatures(
	_In_                            DismSession   Session,
	_Outptr_result_buffer_(*pCount) DismFeature** ppFeature,
	_Out_                           LPDWORD       pCount,
	_In_opt_                        DismCallBack  CallBack,
	_In_opt_                        LPVOID        UserData
	);

//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////系统修复命令///////////////////////////////////////////////////////
//
//

//扫描系统是否受损
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismScanHealth(
	_In_     DismSession           Session,
	_Out_    DismImageHealthState* pImageHealthState,
	_In_opt_ DismCallBack          CallBack,
	_In_opt_ PVOID                 UserData
	);

//恢复系统受损
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRestoreHealth(
	_In_         DismSession  Session,
	_In_opt_z_   LPCWSTR      SourcePaths,
	_In_opt_     DismCallBack CallBack,
	_In_opt_     PVOID        UserData
	);

//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////可选功能///////////////////////////////////////////////////////
//
//
//仅从本地获取
#define CapabilityFlagsPackageStore 0x1
//从安装源中获取
#define CapabilityFlagsLocalSouce   0x2
//从云端获取
#define CapabilityFlagsCloud        0x4

//获取所有可选功能状态
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetCapabilities(
	_In_                            DismSession      Session,
	_In_opt_                        DWORD            CapabilityFlags,
	_Outptr_result_buffer_(*pCount) DismCapability** ppCapabilitites,
	_Out_                           DWORD*           pCount
	);

//删除可选功能
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRemoveCapability(
	_In_     DismSession  Session,
	_In_z_   LPCWSTR      CapabilityName,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);

//添加可选功能
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismAddCapability(
	_In_     DismSession  Session,
	_In_z_   LPCWSTR      CapabilityName,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////服务命令支持//////////////////////////////////////////////////////
//
//

//获取所有服务
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetServices(
	_In_                            DismSession   Session,
	_Outptr_result_buffer_(*pCount) DismService** ppService,
	_Out_                           DWORD*        pCount,
	_In_opt_                        DismCallBack  CallBack,
	_In_opt_                        LPVOID        pUserData
	);

//删除服务
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRemoveService(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     Name
	);

//修改服务启动类型
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismSetServiceStart(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     Name,
	_In_   DWORD       StartType
	);

//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////驱动包命令//////////////////////////////////////////////////////
//
//

//添加驱动包
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismAddDriver(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     DriverPath
	);

//删除驱动包
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRemoveDriver(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     DriverName
	);

//获取所有驱动包
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetDrivers(
	_In_                            DismSession    Session,
	_Outptr_result_buffer_(*pCount) DismDriver**   ppDrivers,
	_Out_                           DWORD*         pCount,
	_In_                            DriverShowEnum DriverShow,
	_In_opt_                        DismCallBack   CallBack,
	_In_opt_                        LPVOID         UserData
	);

//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////清理相关////////////////////////////////////////////////////////
//
//

//清理更新时同时移除负载
#define DismComponentCleanupFlagsResetbase 0x00000001

//清理过期不需要的更新
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismComponentCleanup(
	_In_      DismSession  Session,
	_In_opt_  DWORD        Flags,
	_Out_opt_ UINT64*      CleanUpSpace,
	_In_opt_  DismCallBack CallBack,
	_In_opt_  LPVOID       UserData
	);

//清理过期以及不使用的驱动
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismDriverCleanup(
	_In_       DismSession  Session,
	_Reserved_ DWORD        Reserved,
	_Out_opt_  UINT64*      CleanUpSpace,
	_In_opt_   DismCallBack CallBack,
	_In_opt_   LPVOID       UserData
	);

//清理不需要的Metro App
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismAppxsCleanup(
	_In_       DismSession  Session,
	_Reserved_ DWORD        Reserved,
	_Out_opt_  UINT64*      CleanUpSpace,
	_In_opt_   DismCallBack CallBack,
	_In_opt_   LPVOID       UserData
	);

//开启紧凑型系统
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismCompactOs(
	_In_       DismSession  Session,
	_Reserved_ DWORD        Reserved,
	_Out_opt_  UINT64*      CleanUpSpace,
	_In_opt_   DismCallBack CallBack,
	_In_opt_   LPVOID       UserData
	);

//使用NTFS硬链接合并相同文件，缩小系统体积
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismHardLinkMerge(
	_In_       DismSession  Session,
	_Reserved_ DWORD        Reserved,
	_Out_opt_  UINT64*      CleanUpSpace,
	_In_opt_   DismCallBack CallBack,
	_In_opt_   LPVOID       UserData
	);

//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////WIM处理命令//////////////////////////////////////////////////
//
//
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetMountedImages(
	_Outptr_result_buffer_(*pCount) DismMountedImage** ppMountedImages,
	_Out_                           DWORD*             pCount
	);

//获取WIM、esd、VHD的文件信息
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetImageFileInfo(
	_In_z_   LPCWSTR             ImageFilePath,
	_Outptr_ DismImageFileInfo** ppFileInfo
	);

//修改WIM、esd的文件信息
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismSetImageFileInfo(
	_In_z_ LPCWSTR        ImageFilePath,
	_In_   DWORD          ImageIndex,
	_In_   DismImageInfo* pImageInfo
	);




#define _ExportCreate            0x00000001	//覆盖目标文件
/*
导出指定映像，当DesImageFile存在时CompressTpye将忽略
SourceImageFile：需要导出的映像路径
SourceIndex    ：需要导出映像的下标
DesImageFile   ：用于存放目标映像，如果不存在那么会使用CompressTpye指定的压缩等级创建该文件，如果该文件已经存在，那么CompressTpye参数将忽略
CompressTpye   ：压缩等级
ExportFlags    ：导出标记，可以使用以上组合
*/
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismExportImage(
	_In_z_   LPCWSTR          SourceImageFile,
	_In_     DWORD            SourceIndex,
	_In_z_   LPCWSTR          DesImageFile,
	_In_opt_ DWORD            ExportFlags,
	_In_     DismCompressTpye CompressTpye,
	_In_opt_ DismCallBack     CallBack,
	_In_opt_ LPVOID           pUserData
	);

//删除WIM 文件中的映像
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismDeleteImage(
	_In_z_ LPCWSTR FilePath,
	_In_   DWORD   DeleteIndex
	);

//将指定下标的WIM文件设置为可启动，如果indxe为-1 那么清除启动标志
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismSetBootImage(
	_In_z_ LPCWSTR FilePath,
	_In_   DWORD   BootIndex
	);

#define _CommitAppend               0x00000001
#define _CommitVerify               0x00000002
#define _CommitNoDirAcl             0x00000010
#define _CommitNoFileAcl            0x00000020
#define _CommitNoRpFix              0x00000100

//提交挂载映像更改CommitFlags 拥有以上属性
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismCommitImage(
	_In_z_   LPCWSTR      MountPath,
	_In_opt_ DWORD        CommitFlags,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);


#define _MountFlagReadOnly       0x00000200     //如果该标记存在那么为可写挂载，否则为只读挂载
#define _MountFlagOptimize       0x00000400
#define _MountFlagCheckIntegrity 0x00000002
//挂载指定下标映像，其中Flags拥有以上属性
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismMountImage(
	_In_z_   LPCWSTR      ImageFilePath,
	_In_     DWORD        MountIndex,
	_In_opt_ DWORD        MountFlags,
	_In_z_   LPCWSTR      MountPath,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);


#define _ApplyFlags_Verify    0x00000002   //校验数据
#define _ApplyFlags_WIMBoot   0x00002000   //释放WIMBoot 映像
#define _ApplyFlags_Compact   0x00004000   //释放紧凑型映像
#define _ApplyFlags_WinToGo   0x10000000   //为映像启用Windows To Go
#define _ApplyFlags_FixLetter 0x20000000   //修复盘符
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismApplyImage(
	_In_z_   LPCWSTR      ImageFilePath,
	_In_     DWORD        ApplyIndex,
	_In_opt_ DWORD        ApplyFlags,
	_In_z_   LPCWSTR      ApplyPath,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);


//卸载指定目录的挂载映像
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismUnmountImage(
	_In_z_   LPCWSTR      MountPath,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);


//解密加密的WIM文件
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismDecryptWimFile(
	_In_z_     LPCWSTR FilePath,
	_In_opt_z_ LPCWSTR PublicKey,
	_In_       BOOL    TestKey/* 如果为TRUE 那么仅测试Key能否解密此文件*/
	);

#define _CaptureNew                0x80000000	//总是新建文件，删除当前文件。默认情况如果文件已经存在则打开文件。
#define _CaptureSnapshot           0x40000000	//为目标产生快照，使用该标志可以捕获正在使用的文件，一般用于捕获在线系统。
#define _CaptureBootable           0x20000000	//仅WIM文件支持,将Windows PE卷映像标记为能够引导
#define _CaptureReserved           0x00000001	//仅WIM文件支持
#define _CaptureVerify             0x00000002	//仅WIM文件支持
#define _CaptureIndex              0x00000004	//仅WIM文件支持
#define _CaptureNoApply            0x00000008	//仅WIM文件支持
#define _CaptureNoDirAcl           0x00000010	//仅WIM文件支持
#define _CaptureNoFileAcl          0x00000020	//仅WIM文件支持
#define _CaptureShareWrite         0x00000040	//仅WIM文件支持
#define _CaptureFileInfo           0x00000080	//仅WIM文件支持
#define _CaptureNoRpFix            0x00000100	//仅WIM文件支持
#define _CaptureApplyCiEa          0x00001000	//仅WIM文件支持
//#define _CaptureWIMBoot            0x00002000	//仅WIM文件支持，生成的文件允许够使用 WIMBoot 配置。
/*将某个路径捕获为WIM、esd、VHD(X)文件 （esd、VHD(X)暂未支持）
注意DismCompressTpye参数仅仅WIM文件有效 而且仅仅在新建文件中发挥作用*/
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismCaptureImage(
	_In_z_   LPCWSTR          CapturePath,
	_In_z_   LPCWSTR          ImageFilePath,
	_In_     DismCompressTpye CompressTpye,
	_In_opt_ DWORD            CaptureFlags,
	_In_opt_ DismCallBack     CallBack,
	_In_opt_ LPVOID           UserData,
	_In_opt_ DismImageInfo*   pImageInfo
	);

//映像拆分
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismSplitFile(
	_In_z_   LPCWSTR      ImageFilePath,
	_In_z_   LPCWSTR      SplitFilePath,
	_In_     UINT64       SplitSize,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);

//将一个esd文件转换为ISO文件
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismConversionESD2ISO(
	_In_z_   LPCWSTR          szWimFilePath,
	_In_z_   LPCWSTR          szISOPath,
	_In_     DismCompressTpye CompressTpye,
	_In_opt_ DismCallBack     CallBack,
	_In_opt_ LPVOID           UserData
	);

//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////



//Appx支持
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetAllUsersAppx(
	_In_                                     DismSession   Session,
	_Outptr_result_bytebuffer_(*pcbPackages) AppxPackage** ppPackages,
	_Out_                                    DWORD*        pcbPackages
	);

_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRemoveAppx(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     FullName
	);

_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetProvisionedAppxs(
	_In_                                     DismSession   Session,
	_Outptr_result_bytebuffer_(*pcbPackages) AppxPackage** ppPackages,
	_Out_                                    DWORD*        pcbPackages
	);

_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRemoveProvisionedAppx(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     FullName
	);

enum REConfigCode
{
	//仅启动RE
	RunREOnly = -2,

	//仅对RE进行初始化配置
	InitializeRE = -1,

	//在RE中运行自定义工具（仅一次）
	RunCustomToolOnce,

	//执行系统还原（将Windows.bt中的文件移动到当前系统）
	SystemRestore,

	//保留，Dism++中暂未使用此功能。
	Reservation1,

	//在RE中运行自定义工具（持久启动项）
	RunCustomTool,

	MaxREConfigCode,
};

/*RE支持
Code: 任务执行动作

BootID:  Code为 RunCustomToolOnce或者 RunCustomTool时有效。引导菜单，随机输入一个32位值，不要跟其他人冲突，用于产生引导菜单

FilePath：Code为 RunCustomToolOnce或者 RunCustomTool时有效，在RE中需要启动的文件路径

CallBack：可选，回调函数，用于输出处理进度

UserData：可选，此值将传入 回调函数的UserData产生中，供调用者使用
*/
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI WinREConfig2(
	_In_                                                                       REConfigCode Code,
	_In_                                                                       DWORD        BootID,
	_When_(Code== RunCustomToolOnce || Code== RunCustomTool, _In_z_)
		_When_(Code != RunCustomToolOnce && Code == RunCustomTool, _Reserved_) LPCWSTR      FilePath,
	_In_opt_                                                                   DismCallBack CallBack,
	_In_opt_                                                                   LPVOID       UserData
	);


enum DismFirstBootPhase
{
	DismFirstBootPreSysPrep,
	DismFirstBootPostSysPrep,
	DismFirstBootPreOobe,
	DismFirstBootPostOobe,
};

//IBS支持，设置首次启动运行命令
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI IbsSetFirstBootCommandLine(
	_In_   DismSession        Session,
	_In_   DismFirstBootPhase Phase,
	_In_z_ LPCWSTR            CommandLine
	);


/*AssocSupport
用于调整映像文件关联*/

_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismAppAssociationsDefaultExport(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     FilePath
	);

_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismAppAssociationsDefaultImport(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     FilePath
	);

_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismAppAssociationsDefaultRemove(
	_In_ DismSession Session
	);

_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismAppAssociationsExport(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     FilePath
	);

_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismAppAssociationsImport(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     FilePath
	);

_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismAppAssociationsRemove(
	_In_ DismSession Session
	);



#define CopyWithOptimization 0x1
#define CopyWithVSS          0x2

//将一个系统复制到另一个目录
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismCopySystem(
	_In_z_   LPCWSTR      Source,
	_In_z_   LPCWSTR      Target,
	_In_opt_ DWORD        CompactType,
	_In_opt_ DWORD        CopyFlags,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);

/*
用于创建Dism++接口

Session  ： Dism++会话句柄
ID       ： 所需请求接口GUID，值可以是 IPEImageManager、ISuStartupCollection
ppUnknown： Dism++返回的接口
*/
_Check_return_ _Success_(return == S_OK)
HRESULT WINAPI DismCreateInterface(
	_In_         DismSession Session,
	_In_         const GUID& ID, 
	_COM_Outptr_ IUnknown**  ppUnknown
	);



//PE管理
MIDL_INTERFACE("745A9E3A-0DC8-4C44-8AF7-B233576C0B44")
IPEImageManager :public IUnknown
{
public:
	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI get_ScratchSpace(_Out_ unsigned long* pulScratchSpace) = 0;

	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI put_ScratchSpace(_In_ unsigned long ulScratchSpace) = 0;

	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI get_InstallRoot(_Outptr_result_z_ BSTR* pInstallRoot) = 0;

	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT WINAPI put_InstallRoot(_In_z_ BSTR InstallRoot) = 0;
};


MIDL_INTERFACE("B3DB4480-3E38-4C39-BB44-16D47F8B6FFD")
ISuStartup :public IUnknown
{
public:
	virtual StartupType get_StartupType() = 0;

	_Check_return_  _Success_(return !=NULL) _Ret_maybenull_z_
	virtual LPCWSTR get_Name() = 0;

	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT get_Description(_Outptr_result_z_ LPBSTR pDescription) = 0;

	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT get_FilePath(_Outptr_result_z_ LPBSTR pFilePath) = 0;

	_Check_return_  _Success_(return != NULL) _Ret_maybenull_z_
	virtual LPCWSTR get_CommandLine() = 0;

	_Check_return_ _Success_(return == S_OK)
	virtual HRESULT put_State(_In_ StartupState dwState) = 0;

	virtual StartupState get_State() = 0;
};

//用于管理启动项
MIDL_INTERFACE("DCB9FFE1-8E5A-49DE-8CAE-9C9D5C53426F")
ISuStartupCollection : public IUnknown
{
public:
	virtual HRESULT WINAPI get_Count(_Out_ long* pcount) = 0;

	virtual HRESULT WINAPI get_Item(_In_ long Index, _COM_Outptr_ ISuStartup** pvar) = 0;

	virtual HRESULT WINAPI get__NewEnum(_COM_Outptr_ IUnknown** ppUnk) = 0;
};