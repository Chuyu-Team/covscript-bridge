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
//                     ö��


enum DismPackageState
{
	DismPackageStateUnknown = 0,
	DismPackageStateNotPresent,
	DismPackageStateUnintallRequested,
	DismPackageStateStaged,              //�ݴ�
	DismPackageStateStaging,             //�����ݴ�
	DismPackageStateInstalled,           //�����Ѿ���װ
	DismPackageStateInstallRequested,    //��װ����
	DismPackageStateSuperseded,          //�ø����Ѿ���ȡ��
	DismPackageStatePartiallInstalled,   //���ְ�װ
	DismPackageStateRemoved,             //�Ѿ�ɾ��
	DismPackageStatePermanent,           //���ù̻����°�
};
enum DismFeatureState
{
	DismFeatureStateUnknown = 0,
	DismFeatureStateNotPresent,
	DismFeatureStateUnintallRequested,   //�ù����Ѿ��رյ���δ��Ч
	DismFeatureStateDisable,             //�ù����Ѿ��ر�
	DismFeatureStateStaging,
	DismFeatureStateEnable,              //�ù��ܱ�����
	DismFeatureStateEnableRequested,     //�ù����Ѿ�����������δ��Ч
	DismFeatureStateSuperseded,          //�ù����Ѿ���ȡ��
	DismFeatureStatePartiallInstalled,   //�ù��ܲ��ְ�װ
	DismFeatureStateRemoved              //�ù����Ѿ�ɾ��
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

//WIM����esd�ļ���ѹ������
enum DismCompressTpye
{
	//δ֪ѹ������
	Compress_Unknown = -1,

	//���洢����ѹ���ļ�
	Compress_None = 0,

	//��ѹ����ʽ֧��WIMBOOT����
	Compress_XpressHuffman = 1,

	//����ѹ�������Խ�ʡѹ��ʱ�䲢�ҿ��Լ����ύռ��
	Compress_Xpress = 2,

	//���ѹ�������Խ�ʡ�ռ�
	Compress_LZX = 3,

	//����ѹ�����ǳ��ķ�ʱ�䣬���������С
	Compress_LZMS = 4,
};


enum DismServiceStartType
{
	//��������δ֪��������ϵͳ�����Ҳ������Dism�޷�ʶ��������������ͣ�Ϊ�˰�ȫ��Dism++�޷��޸���������δ֪����Ŀ
	DismServiceStartTypeUnknown = -1,
	//�÷����Ѿ��ر�
	DismServiceStartTypeDisable,
	//�÷���Ϊ�ֶ�����
	DismServiceStartTypeManual,
	//�÷������Զ�����
	DismServiceStartTypeAuto,
	//�÷������ӳ�������ע����_�����ӳٱ�ǵ��޷��޸�Ϊ�ӳ��������᷵�ز�������
	DismServiceStartTypeDelayed
};

enum DismSystemStatus
{
	//״̬δ֪
	DismSystemStatusUnknown = -1,
	//׼������
	DismSystemStatusReady,
	//��ϵͳ��֧��Dism++
	DismSystemStatusNotSupported,
	//�Ҳ���ϵͳ��Ŀ��Ŀ¼�޷����ʻ���·��������
	DismSystemStatusCannotFind,
	//�����Ѿ�ʧЧ����Ҫɾ��
	DismSystemStatusNeedRemove,
	//���Ե�
	DismSystemStatusWait
};


enum DismEnvironmentType
{
	DismEnvironmentDefault = 0, //32λϵͳ���32λĿ¼��64λϵͳ��ȡ64λ·��
	DismEnvironment64Only,    //������ȡ64λ·��������32λϵͳ��ʧ�ܣ�
	DismEnvironment86Only,    //���Ƿ���32λ·��
};


enum DismImageHealthState
{
	DismImageHealthy = 0,      //ӳ��ʮ�ֽ�������Ҫ�޸�
	DismImageRepairable = 1,   //ӳ���Ѿ����𣬵��ǿ����޸�
	DismImageNonRepairable = 2 //ӳ���Ѿ��յ��������⣬�����޸�
};

enum DismServiceType
{
	DismSystemService,    //ϵͳ����
	DismAppService,       //������Ӧ�ó���
	DismDriverService,    //��������
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
//                      �ṹ����

#pragma pack(push, 1)

struct DismSystem
{
	//ϵͳ״̬
	DismSystemStatus Status;

	/*
	����ϵͳCPU��ϵ������ֵΪ��
	PROCESSOR_ARCHITECTURE_AMD64     x64��ϵ
	PROCESSOR_ARCHITECTURE_INTEL     x86��ϵ
	PROCESSOR_ARCHITECTURE_UNKNOWN   δ֪��ϵ*/
	long Architecture;

	//����ָʾ
#define _����ӳ��      0x1     //���Ϊ����ӳ����ô�ñ��Ϊ1 ����Ϊ0

	//������ʽ
#define _����Ӳ��      0x2  //ӳ�����ڱ���
#define _����ӳ��      0x4  //ӳ��������WIM����VHD���ص�

	//ʹ�õļ���
#define _WIMBOOT       0x8  //ӳ��ʹ����WIMBOOT����
#define _VHDװ��       0x10  //ӳ������VHDװ��
#define _CompactOs     0x20  //ӳ��ʹ����CompactOs����
#define _WinPE         0x40
	//�û��Զ����� 24~31  Dism++API���Ա�֤����ʹ����������������������µĶ���
	DWORD Flags;       //Flagsӵ��������ϱ�־
	DWORD ProductType;          //��Ȩ���� WinNT��LanmanNT ���� ServerNT

	//ϵͳ�汾�� ����6.3.9600.17041
	UINT16 Version[4];


	wchar_t ProductName[256];    //����ϵͳ����
	wchar_t EditionID[256];      //ϵͳ����汾

	wchar_t InstallationType[40];      //ϵͳ��װ����
	DWORD DefaultLanguage;      //Ĭ����ʾ����
	DWORD InstallLanguage;      //ϵͳ��װ����
	wchar_t InstallLanguageFallback[256];//���Ի����б�
	//WIM XML�е�Flags
	wchar_t szFlags[256];
	wchar_t RootPath[MAX_PATH];       //ϵͳ��װλ��
	//ӳ����չ·�������ڱ���WIM·���Լ�VHD·�� ���ַ��ַ���
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

	//����
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
	//ϵͳ��ϵ
	long Architecture;

	//��������
	FILETIME CreationTime;

	//չ���ռ�
	UINT64 Space;

	//ϵͳ�汾��
	UINT16 Version[4];

	//////////////////////////////////////////////////
	//        ������޸�������Ϣ ������ӳ����Ϣ

	//ӳ������
	wchar_t Name[256];

	//ӳ��˵��
	wchar_t Description[512];

	//��ʾ����
	wchar_t DisplayName[256];

	//��ʾ˵��
	wchar_t DisplayDescription[512];

	//ӳ��汾���
	wchar_t Flags[256];
};

struct DismImageFileInfo
{
	//�����±�
	int BootIndex;

	//�ļ�����
	DismImageFileTpye Type;

	//�ļ�Ψһ��ʶ
	GUID FileGUID;

	//ѹ������
	DismCompressTpye Compression;

	//ӳ������
	DWORD ImageInfoCount;

	//ӳ��
	DismImageInfo ImageInfo[0];
};

struct DismService
{
	DismServiceType Type;
	/*
	������������,����ֵΪ
	SERVICE_AUTO_START
	SERVICE_BOOT_START
	SERVICE_DEMAND_START
	SERVICE_DISABLED
	SERVICE_SYSTEM_START
	*/
	//�ӳ�����
#define SERVICE_Delay_START 5
	DWORD dwStartType;

#define _ϵͳ���� 0x00000001
#define _�����ӳ� 0x00000002
#define _ϵͳ���� 0x00000004
	//����Flags ӵ������״̬
	DWORD Flags;

	//��������
	wchar_t Name[256];

	//��Ӧ������ʾ����
	wchar_t DisplayName[256];

	//��Ӧ������ʾ����
	wchar_t Description[512];

	//��Ӧ����·��
	wchar_t ImagePath[MAX_PATH];

	//��Ӧ����ĵ�¼״̬
	wchar_t ObjectName[256];
};


struct AppxPackage
{
	//��ǰ�ṹ���С��ָ����һ��AppxPackageԪ��
	DWORD cbData;
	wchar_t FullName[256];
	wchar_t InstalledLocation[MAX_PATH];
	wchar_t Users[1];
};



#pragma pack(pop)



typedef class CCbsHostProxy* DismSession;


#define DISM_MSG_PROGRESS   38008     //������ϢwParamΪ��ǰ��ɰٷֱ�
#define DISM_MSG_PROCESS    38009     //ָʾ���ļ��Ƿ�Ӧ�ñ�����wParam = (PWSTR) pszFullPath   lParam = (PBOOL) pfProcessFile
#define DISM_MSG_SCANNING   38010     //ɨ����ļ��������ļ��� wParam=(BOOL)IsDirector   lParam=(UINT)Count
#define DISM_MGS_RemoveInfo 37001     //ָʾ���ļ������ļ�����Ҫ����   wParam=(DWORD)Type    lParam=(LPCWSTR)FilePath
#define Dism_MSG_QUERY_ABORT 38030    //�Ƿ���Ҫ�жϸò���������-1 ���жϵ�ǰ����������S_OK��ô������������ 
#define DISM_MGS_AllowExclusive 39001 //ָʾ�˸����Ƿ��������ռ   wParam=(PBOOL)pAllowExclusive

//Dism�ص����������ڷ��ؽ��ȵ���ϢdwMessageId�������ϼ�����Ϣ  UserData���㴫���ָ�� ��������������У��뷵�� ERROR_SUCCESS
typedef DWORD(WINAPI *DismCallBack)(DWORD dwMessageId, WPARAM wParam, LPARAM lParam, PVOID UserData);


///////////////////////////////////////////////��������֧��////////////////////////////////////////////////
//
//

//��ȡָ����ע����ֵ,���ú���Ҫʹ��RegClose�ر�
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRegOpenKeyEx(
	_In_   DismSession Session,
	_In_   HKEY        hKey,
	_In_z_ LPCWSTR     lpSubKey,
	_In_   REGSAM      samDesired,
	_Out_  PHKEY       phkResult
	);

//������ֵ
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRegCreateKeyEx(
	_In_      DismSession Session,
	_In_      HKEY        hKey,
	_In_z_    LPCWSTR     lpSubKey,
	_In_      REGSAM      samDesired,
	_Out_     PHKEY       phkResult,
	_Out_opt_ LPDWORD     lpdwDisposition
	);

//��ȡָ����ע����ֵ,���ú���Ҫʹ��RegClose�ر�
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRegOpenKey(
	_In_   DismSession Session,
	_In_   HKEY        hKey,
	_In_z_ LPCWSTR     lpSubKey,
	_Out_  PHKEY       phkResult
	);

//ת��ָ���Ļ�������
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismExpandEnvironmentStrings(
	_In_              DismSession Session,
	_In_z_            LPCWSTR     lpSrc,
	_Outptr_result_z_ LPBSTR      lpDst
	);

#define DismLogLevelSilent      0    //������κ���Ϣ
#define DismLogLevelFailure     1    //������
#define DismLogLevelWarning     2    //����;���
#define DismLogLevelInformation 3    //���󡢾������Ϣ
#define DismLogLevelDebug       4    //�����������ݺ͵������
//д����־
_Check_return_ _Success_(return == S_OK)
DISM_HOST HRESULT WINAPI DismWriteLog(
	_In_   DWORD   LogLevel,
	_In_z_ LPCWSTR LogName,
	_In_z_ LPCWSTR LogValue
	);

//�ͷ�Dism�ӿڵ��ú�Ŀռ�
_Success_(return == S_OK)
DISM_API HRESULT WINAPI DismFreeMemory(
	_In_ void* pStruct
	);

//���ݻỰ���ϵͳ��Ϣ
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetSystemInfoBySession(
	_In_     DismSession  Session,
	_Outptr_ DismSystem** Info
	);

//����·�����ϵͳ��Ϣ
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetSystemInfoByPath(
	_In_z_   LPCWSTR      RootPath,
	_Outptr_ DismSystem** Info
	);

//��ָ���������ת��Ϊ��Ӧ�ı���
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismFormatMessage(
	_In_              HRESULT hr,
	_Outptr_result_z_ LPBSTR  ppErrorMessage
	);

//��ȡ��ʱĿ¼
_Ret_z_
DISM_HOST LPCWSTR WINAPI DismGetScratchDir();

DISM_API BOOL WINAPI DismUnloadRegMount(
	_In_z_ LPCWSTR RootPath
	);

//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////���°�����///////////////////////////////////////////////
//
//

//��Ӹ��°�
_Check_return_ _Success_(return ==S_OK)
DISM_API HRESULT WINAPI DismAddPackage(
	_In_     DismSession  Session,
	_In_z_   LPCWSTR      PackageFilePath,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);

//ɾ�����°�
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRemovePackage(
	_In_     DismSession  Session,
	_In_z_   LPCWSTR      PackageName,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);

//��ȡ���°���Ϣ
//HRESULT WINAPI DismGetPackage(DismSession Session, LPCWSTR PackageIdentity, DismPackage** ppPackageInfo);

//��ȡ���и��°�
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





//////////////////////////////////////////////////���ܰ�����/////////////////////////////////////////////////////
//
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismChangeFeatures(
	_In_       DismSession  Session,
	_In_z_     LPCWSTR      FeatureNames,  //��Ҫ�رյĹ�������
#define DismLimitAccess 0x00000001   //NT6.1��Ч �򿪹���ʱ��Ҫ��΢��������������ļ� PS����������趨���ܻ�Ӧ�ò������ص��ļ�����ʧ��
	_In_opt_   DWORD        ChangeFlags,   //�رձ�־��֧������״̬
	_In_opt_z_ LPCWSTR      SourcePaths,  //NT6.1��Ч ָ������Դ������������ʱ���ȴ�Դ�����ļ�,���Դ��NULL�ָ�
	_In_opt_   DismCallBack CallBack,
	_In_opt_   LPVOID       UserData
	);

//��ȡ����״̬
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




//////////////////////////////////////////////////ϵͳ�޸�����///////////////////////////////////////////////////////
//
//

//ɨ��ϵͳ�Ƿ�����
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismScanHealth(
	_In_     DismSession           Session,
	_Out_    DismImageHealthState* pImageHealthState,
	_In_opt_ DismCallBack          CallBack,
	_In_opt_ PVOID                 UserData
	);

//�ָ�ϵͳ����
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



//////////////////////////////////////////////////��ѡ����///////////////////////////////////////////////////////
//
//
//���ӱ��ػ�ȡ
#define CapabilityFlagsPackageStore 0x1
//�Ӱ�װԴ�л�ȡ
#define CapabilityFlagsLocalSouce   0x2
//���ƶ˻�ȡ
#define CapabilityFlagsCloud        0x4

//��ȡ���п�ѡ����״̬
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetCapabilities(
	_In_                            DismSession      Session,
	_In_opt_                        DWORD            CapabilityFlags,
	_Outptr_result_buffer_(*pCount) DismCapability** ppCapabilitites,
	_Out_                           DWORD*           pCount
	);

//ɾ����ѡ����
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRemoveCapability(
	_In_     DismSession  Session,
	_In_z_   LPCWSTR      CapabilityName,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);

//��ӿ�ѡ����
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



/////////////////////////////////////////////////��������֧��//////////////////////////////////////////////////////
//
//

//��ȡ���з���
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetServices(
	_In_                            DismSession   Session,
	_Outptr_result_buffer_(*pCount) DismService** ppService,
	_Out_                           DWORD*        pCount,
	_In_opt_                        DismCallBack  CallBack,
	_In_opt_                        LPVOID        pUserData
	);

//ɾ������
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRemoveService(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     Name
	);

//�޸ķ�����������
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismSetServiceStart(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     Name,
	_In_   DWORD       StartType
	);

//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////����������//////////////////////////////////////////////////////
//
//

//���������
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismAddDriver(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     DriverPath
	);

//ɾ��������
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismRemoveDriver(
	_In_   DismSession Session,
	_In_z_ LPCWSTR     DriverName
	);

//��ȡ����������
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



/////////////////////////////////////////////�������////////////////////////////////////////////////////////
//
//

//�������ʱͬʱ�Ƴ�����
#define DismComponentCleanupFlagsResetbase 0x00000001

//������ڲ���Ҫ�ĸ���
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismComponentCleanup(
	_In_      DismSession  Session,
	_In_opt_  DWORD        Flags,
	_Out_opt_ UINT64*      CleanUpSpace,
	_In_opt_  DismCallBack CallBack,
	_In_opt_  LPVOID       UserData
	);

//��������Լ���ʹ�õ�����
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismDriverCleanup(
	_In_       DismSession  Session,
	_Reserved_ DWORD        Reserved,
	_Out_opt_  UINT64*      CleanUpSpace,
	_In_opt_   DismCallBack CallBack,
	_In_opt_   LPVOID       UserData
	);

//������Ҫ��Metro App
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismAppxsCleanup(
	_In_       DismSession  Session,
	_Reserved_ DWORD        Reserved,
	_Out_opt_  UINT64*      CleanUpSpace,
	_In_opt_   DismCallBack CallBack,
	_In_opt_   LPVOID       UserData
	);

//����������ϵͳ
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismCompactOs(
	_In_       DismSession  Session,
	_Reserved_ DWORD        Reserved,
	_Out_opt_  UINT64*      CleanUpSpace,
	_In_opt_   DismCallBack CallBack,
	_In_opt_   LPVOID       UserData
	);

//ʹ��NTFSӲ���Ӻϲ���ͬ�ļ�����Сϵͳ���
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



///////////////////////////////////////////////WIM��������//////////////////////////////////////////////////
//
//
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetMountedImages(
	_Outptr_result_buffer_(*pCount) DismMountedImage** ppMountedImages,
	_Out_                           DWORD*             pCount
	);

//��ȡWIM��esd��VHD���ļ���Ϣ
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismGetImageFileInfo(
	_In_z_   LPCWSTR             ImageFilePath,
	_Outptr_ DismImageFileInfo** ppFileInfo
	);

//�޸�WIM��esd���ļ���Ϣ
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismSetImageFileInfo(
	_In_z_ LPCWSTR        ImageFilePath,
	_In_   DWORD          ImageIndex,
	_In_   DismImageInfo* pImageInfo
	);




#define _ExportCreate            0x00000001	//����Ŀ���ļ�
/*
����ָ��ӳ�񣬵�DesImageFile����ʱCompressTpye������
SourceImageFile����Ҫ������ӳ��·��
SourceIndex    ����Ҫ����ӳ����±�
DesImageFile   �����ڴ��Ŀ��ӳ�������������ô��ʹ��CompressTpyeָ����ѹ���ȼ��������ļ���������ļ��Ѿ����ڣ���ôCompressTpye����������
CompressTpye   ��ѹ���ȼ�
ExportFlags    ��������ǣ�����ʹ���������
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

//ɾ��WIM �ļ��е�ӳ��
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismDeleteImage(
	_In_z_ LPCWSTR FilePath,
	_In_   DWORD   DeleteIndex
	);

//��ָ���±��WIM�ļ�����Ϊ�����������indxeΪ-1 ��ô���������־
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

//�ύ����ӳ�����CommitFlags ӵ����������
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismCommitImage(
	_In_z_   LPCWSTR      MountPath,
	_In_opt_ DWORD        CommitFlags,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);


#define _MountFlagReadOnly       0x00000200     //����ñ�Ǵ�����ôΪ��д���أ�����Ϊֻ������
#define _MountFlagOptimize       0x00000400
#define _MountFlagCheckIntegrity 0x00000002
//����ָ���±�ӳ������Flagsӵ����������
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismMountImage(
	_In_z_   LPCWSTR      ImageFilePath,
	_In_     DWORD        MountIndex,
	_In_opt_ DWORD        MountFlags,
	_In_z_   LPCWSTR      MountPath,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);


#define _ApplyFlags_Verify    0x00000002   //У������
#define _ApplyFlags_WIMBoot   0x00002000   //�ͷ�WIMBoot ӳ��
#define _ApplyFlags_Compact   0x00004000   //�ͷŽ�����ӳ��
#define _ApplyFlags_WinToGo   0x10000000   //Ϊӳ������Windows To Go
#define _ApplyFlags_FixLetter 0x20000000   //�޸��̷�
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismApplyImage(
	_In_z_   LPCWSTR      ImageFilePath,
	_In_     DWORD        ApplyIndex,
	_In_opt_ DWORD        ApplyFlags,
	_In_z_   LPCWSTR      ApplyPath,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);


//ж��ָ��Ŀ¼�Ĺ���ӳ��
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismUnmountImage(
	_In_z_   LPCWSTR      MountPath,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);


//���ܼ��ܵ�WIM�ļ�
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismDecryptWimFile(
	_In_z_     LPCWSTR FilePath,
	_In_opt_z_ LPCWSTR PublicKey,
	_In_       BOOL    TestKey/* ���ΪTRUE ��ô������Key�ܷ���ܴ��ļ�*/
	);

#define _CaptureNew                0x80000000	//�����½��ļ���ɾ����ǰ�ļ���Ĭ���������ļ��Ѿ���������ļ���
#define _CaptureSnapshot           0x40000000	//ΪĿ��������գ�ʹ�øñ�־���Բ�������ʹ�õ��ļ���һ�����ڲ�������ϵͳ��
#define _CaptureBootable           0x20000000	//��WIM�ļ�֧��,��Windows PE��ӳ����Ϊ�ܹ�����
#define _CaptureReserved           0x00000001	//��WIM�ļ�֧��
#define _CaptureVerify             0x00000002	//��WIM�ļ�֧��
#define _CaptureIndex              0x00000004	//��WIM�ļ�֧��
#define _CaptureNoApply            0x00000008	//��WIM�ļ�֧��
#define _CaptureNoDirAcl           0x00000010	//��WIM�ļ�֧��
#define _CaptureNoFileAcl          0x00000020	//��WIM�ļ�֧��
#define _CaptureShareWrite         0x00000040	//��WIM�ļ�֧��
#define _CaptureFileInfo           0x00000080	//��WIM�ļ�֧��
#define _CaptureNoRpFix            0x00000100	//��WIM�ļ�֧��
#define _CaptureApplyCiEa          0x00001000	//��WIM�ļ�֧��
//#define _CaptureWIMBoot            0x00002000	//��WIM�ļ�֧�֣����ɵ��ļ�����ʹ�� WIMBoot ���á�
/*��ĳ��·������ΪWIM��esd��VHD(X)�ļ� ��esd��VHD(X)��δ֧�֣�
ע��DismCompressTpye��������WIM�ļ���Ч ���ҽ������½��ļ��з�������*/
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

//ӳ����
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI DismSplitFile(
	_In_z_   LPCWSTR      ImageFilePath,
	_In_z_   LPCWSTR      SplitFilePath,
	_In_     UINT64       SplitSize,
	_In_opt_ DismCallBack CallBack,
	_In_opt_ LPVOID       UserData
	);

//��һ��esd�ļ�ת��ΪISO�ļ�
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



//Appx֧��
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
	//������RE
	RunREOnly = -2,

	//����RE���г�ʼ������
	InitializeRE = -1,

	//��RE�������Զ��幤�ߣ���һ�Σ�
	RunCustomToolOnce,

	//ִ��ϵͳ��ԭ����Windows.bt�е��ļ��ƶ�����ǰϵͳ��
	SystemRestore,

	//������Dism++����δʹ�ô˹��ܡ�
	Reservation1,

	//��RE�������Զ��幤�ߣ��־������
	RunCustomTool,

	MaxREConfigCode,
};

/*RE֧��
Code: ����ִ�ж���

BootID:  CodeΪ RunCustomToolOnce���� RunCustomToolʱ��Ч�������˵����������һ��32λֵ����Ҫ�������˳�ͻ�����ڲ��������˵�

FilePath��CodeΪ RunCustomToolOnce���� RunCustomToolʱ��Ч����RE����Ҫ�������ļ�·��

CallBack����ѡ���ص���������������������

UserData����ѡ����ֵ������ �ص�������UserData�����У���������ʹ��
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

//IBS֧�֣������״�������������
_Check_return_ _Success_(return == S_OK)
DISM_API HRESULT WINAPI IbsSetFirstBootCommandLine(
	_In_   DismSession        Session,
	_In_   DismFirstBootPhase Phase,
	_In_z_ LPCWSTR            CommandLine
	);


/*AssocSupport
���ڵ���ӳ���ļ�����*/

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

//��һ��ϵͳ���Ƶ���һ��Ŀ¼
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
���ڴ���Dism++�ӿ�

Session  �� Dism++�Ự���
ID       �� ��������ӿ�GUID��ֵ������ IPEImageManager��ISuStartupCollection
ppUnknown�� Dism++���صĽӿ�
*/
_Check_return_ _Success_(return == S_OK)
HRESULT WINAPI DismCreateInterface(
	_In_         DismSession Session,
	_In_         const GUID& ID, 
	_COM_Outptr_ IUnknown**  ppUnknown
	);



//PE����
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

//���ڹ���������
MIDL_INTERFACE("DCB9FFE1-8E5A-49DE-8CAE-9C9D5C53426F")
ISuStartupCollection : public IUnknown
{
public:
	virtual HRESULT WINAPI get_Count(_Out_ long* pcount) = 0;

	virtual HRESULT WINAPI get_Item(_In_ long Index, _COM_Outptr_ ISuStartup** pvar) = 0;

	virtual HRESULT WINAPI get__NewEnum(_COM_Outptr_ IUnknown** ppUnk) = 0;
};