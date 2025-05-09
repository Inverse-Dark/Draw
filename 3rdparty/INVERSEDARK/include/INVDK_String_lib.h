/**
 * @File: INVDK_String_lib.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: 字符串处理函数
 */
#ifndef INVDK_STRING_LIB_H
#define INVDK_STRING_LIB_H

#include "INVDK_Data.h"

namespace INVDK
{
	#define INVDK_T(T)  (T) /* 处理字符串，字符串都用这个包裹一下，方便后续替换 */

	/// @brief 获取字符串的长度
	/// @param _Str [IN] 字符串
	/// @return 字符串的长度
	INVDK_SDK_API INVDK_SIZE strlen(INVDK_PCCHAR _Str);
	/// @brief 复制一个字符串
	/// @param _Str [IN] 要复制的字符串
	/// @return 新的字符串指针
	INVDK_SDK_API INVDK_PCHAR strdup(INVDK_PCCHAR _Str);
	/// @brief 将第二个字符串拷贝到第一个字符串
	/// @param _Dst [OUT] 第一个字符串
	/// @param _Src [IN] 第二个字符串
	/// @return 
	INVDK_SDK_API INVDK_VOID strcpy(INVDK_PCHAR _Dst, INVDK_PCCHAR _Src);
	/// @brief 拼接两个字符串
	/// @param _Dst [OUT] 第一个字符串
	/// @param _Src [IN] 第二个字符串
	/// @return 拼接后的字符串首地址
	INVDK_SDK_API INVDK_PVOID strcat(INVDK_PVOID _Dst, INVDK_PCVOID _Src);
	/// @brief 比较两个字符串，直到遇到字符串结尾的空字符 '\0' 或者发现两个字符不相等
	/// @param _Str1 [IN] 字符串1
	/// @param _Str2 [IN] 字符串2
	/// @return 如果 _Str1 小于 _Size 返回负数，如果 _Str1 等于 _Str2 返回 0，如果 _Str1 大于 _Str2 返回正数。
	INVDK_SDK_API INVDK_INT strcmp(INVDK_PCCHAR _Str1, INVDK_PCCHAR _Str2);
	/// @brief 用于比较两个字符串的前 n 个字符。
	/// @param _Str1 [IN] 字符串1
	/// @param _Str2 [IN] 字符串2
	/// @param _Size [IN] 要比较的最大字符数
	/// @return 如果 _Str1 小于 _Size 返回负数，如果 _Str1 等于 _Str2 返回 0，如果 _Str1 大于 _Str2 返回正数。
	INVDK_SDK_API INVDK_INT strncmp(INVDK_PCCHAR _Str1, INVDK_PCCHAR _Str2, INVDK_SIZE _Size);

	/// @brief 字符串转长整型
	/// @param _Str [IN] 字符串
	/// @param _EndChar [OUT] 如果不为空的话，将会指向字符串中数字的最后一位
	/// @param _Base [IN] 进制
	/// @return 一个长整型的数字
	INVDK_SDK_API INVDK_LINT strtol(INVDK_PCCHAR _Str, INVDK_PCHAR* _EndChar, INVDK_INT _Base);
	/// @brief 字符串转无符号长整型
	/// @param _Str [IN] 字符串
	/// @param _EndChar [OUT] 如果不为空的话，将会指向字符串中数字的最后一位
	/// @param _Base [IN] 进制
	/// @return 一个长整型的数字
	INVDK_SDK_API INVDK_ULINT strtoul(INVDK_PCCHAR _Str, INVDK_PCHAR* _EndChar, INVDK_INT _Base);
	/// @brief 字符串转双精度浮点数
	/// @param _Str [IN] 字符串
	/// @param _EndChar [OUT] 如果不为空的话，将会指向字符串中数字的最后一位
	/// @return 一个双精度浮点数
	INVDK_SDK_API INVDK_DOUBLE strtod(INVDK_PCCHAR _Str, INVDK_PCHAR* _EndChar);
}

#endif	// !INVDK_STRING_LIB_H
