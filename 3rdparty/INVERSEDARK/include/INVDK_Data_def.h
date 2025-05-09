/**
 * @File: INVDK_Data_def.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: 编译参数的宏定义
 */
#ifndef INVDK_DATA_DEF_H
#define INVDK_DATA_DEF_H

#if defined(__GNUC__) || defined(__GNUG__)
#	ifdef INVDK_SDK_EXPORT
#		define INVDK_SDK_API __attribute__ ((visibility("default")))
#	else
#		define INVDK_SDK_API
#	endif	// INVDK_SDK_EXPORT
#elif _MSC_VER
#	ifdef INVDK_SDK_EXPORT
#		define INVDK_SDK_API __declspec(dllexport)
#	else
#		define INVDK_SDK_API __declspec(dllimport)
#	endif	// INVDK_SDK_EXPORT
#else
#	define INVDK_SDK_API
#endif

#endif	// !INVDK_DATA_DEF_H


