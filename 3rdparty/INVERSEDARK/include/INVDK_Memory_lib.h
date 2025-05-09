/**
 * @File: INVDK_Memory_lib.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: 内存处理函数
 */
#ifndef INVDK_MEMORY_LIB_H
#define INVDK_MEMORY_LIB_H

#include "INVDK_Data.h"

namespace INVDK
{
	/// @brief 申请内存
	/// @param _Size [IN] 内存大小
	/// @return 申请成功返回申请的内存，申请失败返回空
	INVDK_SDK_API INVDK_PVOID malloc(INVDK_SIZE _Size);
	/// @brief 重新申请内存
	/// @param _Block [IN] 原内存块
	/// @param _Size [IN] 要申请的内存大小
	/// @return 申请成功返回申请的内存，申请失败返回空
	INVDK_SDK_API INVDK_PVOID realloc(INVDK_PVOID _Block, INVDK_SIZE _Size);
	/// @brief 释放内存
	/// @param _Memory [IN] 要释放的内存
	/// @return 
	INVDK_SDK_API INVDK_VOID free(INVDK_PVOID _Memory);

	/// @brief 拷贝内存中指定长度到另一块内存
	/// @param _Dst [OUT] 目标内存
	/// @param _Src [IN] 源内存
	/// @param _Size [IN] 指定的长度
	/// @return 目标内存的首地址
	INVDK_SDK_API INVDK_PVOID memcpy(INVDK_PVOID _Dst, INVDK_PCVOID _Src, INVDK_SIZE _Size);

	/// @brief 将指定内存所有字节设为特定的值
	/// @param _Dst [OUT] 内存
	/// @param _Val [IN] 特定的值
	/// @param _Size [IN] 内存的长度
	/// @return 
	INVDK_SDK_API INVDK_VOID memset(INVDK_PVOID _Dst, INVDK_INT _Val, INVDK_SIZE _Size);
}

#endif	// !INVDK_MEMORY_LIB_H
