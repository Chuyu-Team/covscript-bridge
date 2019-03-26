// stdafx.h: 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>

// Dism++ SDK

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
// Dism++为了实现二进制一致所造成的警告
#pragma warning(disable:4200) // 结构/联合中的零大小数组(等级 2 和等级 4)
#endif

#include "CBS++API.h"
#include "BCDAPI.h"
#include "Plugin.h"
#pragma comment(lib, _DismExe)

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

// 在此处引用程序需要的其他标头
