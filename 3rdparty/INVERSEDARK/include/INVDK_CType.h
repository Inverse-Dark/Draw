/**
 * @File: INVDK_CType.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: Char类型判断及简易处理
 */
#ifndef INVDK_CTYPE_H
#define INVDK_CTYPE_H

#include "INVDK_Data.h"

namespace INVDK
{
	/// @brief 将单个字符转换为小写
	/// @param _C [IN] 要转换的字符
	/// @return 对于 ASCII 字符，这些函数将直接返回转换后的字符；对于非 ASCII 字符，这些函数将直接返回原始输入。
	INVDK_SDK_API INVDK_INT tolower(INVDK_INT _C);
	/// @brief 将单个字符转换为大写
	/// @param _C [IN] 要转换的字符
	/// @return 对于 ASCII 字符，这些函数将直接返回转换后的字符；对于非 ASCII 字符，这些函数将直接返回原始输入。
	INVDK_SDK_API INVDK_INT toupper(INVDK_INT _C);

	/// @brief 检查是否是空白字符
	/// @param _C [IN] 要检查的字符
	/// @return 如果是空白字符返回非 0 字符，否则返回 0
	INVDK_SDK_API INVDK_INT isspace(INVDK_INT _C);

	/// @brief 检查是否是数字
	/// @param _C [IN] 要检查的字符
	/// @return 如果是数字返回非 0 字符，否则返回 0
	INVDK_SDK_API INVDK_INT isdigit(INVDK_INT _C);

	/// @brief 检查是否是字母
	/// @param _C [IN] 要检查的字符
	/// @return 如果是字母返回非 0 字符，否则返回 0
	INVDK_SDK_API INVDK_INT isalpha(INVDK_INT _C);

}


#endif // !INVDK_CTYPE_H
