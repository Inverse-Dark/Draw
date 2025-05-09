/**
 * @File: INVDK_Data.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: 数据类型
 */
#ifndef INVDK_DATA_H
#define INVDK_DATA_H

#include "INVDK_Data_def.h"
#include "INVDK_Data_type.h"

#ifdef _MSC_VER // 设置编码
#	pragma execution_character_set("utf-8")
#endif // _MSC_VER

using INVDK_VOID = void;
#ifdef __cplusplus
using INVDK_BOOL = bool;
#else 
using INVDK_BOOL = unsigned char;
#endif	// __cplusplus
using INVDK_SHORT = short;
using INVDK_USHORT = unsigned short;
using INVDK_SINT = short int;
using INVDK_INT = int;
using INVDK_UINT = unsigned int;
using INVDK_LUINT = long unsigned int;
using INVDK_CHAR = char;
using INVDK_UCHAR = unsigned char;
using INVDK_LONG = long;
using INVDK_ULONG = unsigned long;
using INVDK_LINT = long int;
using INVDK_ULINT = unsigned long int;
using INVDK_LLONG = long long;
using INVDK_ULLONG = unsigned long long;
using INVDK_FLOAT = float;
using INVDK_DOUBLE = double;
using INVDK_LDOUBLE = long double;

using INVDK_BYTE = unsigned char;	// 8bit
using INVDK_WORD = unsigned short;	// 16bit
using INVDK_DWORD = unsigned long;	// x64 = 64bit	x32 = 32bit
using INVDK_SIZE = unsigned long long;

using INVDK_CCHAR = const INVDK_CHAR;
using INVDK_PCHAR = INVDK_CHAR*;
using INVDK_PCCHAR = INVDK_CCHAR*;
using INVDK_CHARPC = INVDK_CHAR const*;
using INVDK_PUCHAR = INVDK_UCHAR*;
using INVDK_CUCHAR = const INVDK_UCHAR;
using INVDK_PCUCHAR = INVDK_CUCHAR*;

using INVDK_WCHAR = wchar_t;
using INVDK_CWCHAR = const INVDK_WCHAR;
using INVDK_PCWCHAR = INVDK_CWCHAR*;
using INVDK_PWCHAR = INVDK_WCHAR*;

using INVDK_PVOID = INVDK_VOID*;
using INVDK_CVOID = const INVDK_VOID;
using INVDK_PCVOID = INVDK_CVOID*;

#undef NULL
#ifndef NULL
#	ifdef __cplusplus
#		define NULL nullptr
#	else
#		define NULL ((INVDK_PVOID)0)
#	endif
#endif	// !NULL

#undef TRUE
#ifndef TRUE
#	define TRUE		((INVDK_BOOL)(1))
#endif	// !TRUE
#undef FALSE
#ifndef FALSE
#	define FALSE	((INVDK_BOOL)(0))
#endif	// !FALSE

#endif	// !INVDK_DATA_H
