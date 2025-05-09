/**
 * @File: INVDK_IO.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/30
 * @Description: 输入输出流
 */
#ifndef INVDK_IO_H
#define INVDK_IO_H

#include "INVDK_Data.h"

namespace INVDK
{
	/// @brief 格式化字符串并存储到缓冲区
	/// @param _Buffer [IN] 指向缓冲区的指针，用于存储格式化后的字符串
	/// @param _Format [IN] 格式说明符，指定字符串的格式
	/// @param ... [IN] 可变参数列表，根据格式说明符提供相应的值
	/// @return 成功时返回存储到缓冲区的字符数，失败时返回一个负数
	INVDK_SDK_API INVDK_INT sprintf(INVDK_PCHAR const _Buffer, INVDK_CHARPC const _Format, ...);
	/// @brief 从字符串读取格式化输入
	/// @param _Buffer [IN] 指向缓冲区的指针，包含要解析的字符串
	/// @param _Format [IN] 格式说明符，指定字符串的格式
	/// @param ... [IN] 可变参数列表，根据格式符提供相应的变量地址
	/// @return 成功时返回读取的项数，失败时返回一个负数
	INVDK_SDK_API INVDK_INT sscanf(INVDK_PCCHAR _Buffer, INVDK_PCCHAR _Format, ...);
}

#endif // !INVDK_IO_H
