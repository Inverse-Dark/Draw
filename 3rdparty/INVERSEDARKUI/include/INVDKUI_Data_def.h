/**
 * @File: INVDKUI_Data_def.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/4/10
 * @Description: 编译参数的宏定义
 */
#ifndef INVDKUI_DATA_DEF_H
#define INVDKUI_DATA_DEF_H

#if defined(__GNUC__) || defined(__GNUG__)
#	ifdef INVDKUI_SDK_EXPORT
#		define INVDKUI_SDK_API __attribute__ ((visibility("default")))
#	else
#		define INVDKUI_SDK_API
#	endif	// INVDKUI_SDK_EXPORT
#elif _MSC_VER
#	ifdef INVDKUI_SDK_EXPORT
#		define INVDKUI_SDK_API __declspec(dllexport)
#	else
#		define INVDKUI_SDK_API __declspec(dllimport)
#	endif	// INVDKUI_SDK_EXPORT
#else
#	define INVDKUI_SDK_API
#endif

#endif	// !INVDKUI_DATA_DEF_H


