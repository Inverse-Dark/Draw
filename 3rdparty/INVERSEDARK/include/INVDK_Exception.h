/**
 * @File: INVDK_Exception.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: 异常类型
 */
#ifndef INVDK_EXCEPTION_H
#define INVDK_EXCEPTION_H

#include "INVDK_String.h"

namespace INVDK
{

	class INVDK_SDK_API Exception
	{
	public:
		/// @brief 默认构造函数
		Exception();
		/// @brief 构造函数，接受错误信息
		/// @param msg [IN] 错误信息
		Exception(const String& msg);
		/// @brief 复制构造函数
		/// @param other [IN] 被复制的类型
		Exception(const Exception& other);
		/// @brief 析构函数
		~Exception();

		/// @brief 赋值运算符
		/// @param other [IN] 异常
		/// @return 新的异常
		Exception& operator=(const Exception& other);

		/// @brief 获取错误信息
		/// @return 错误信息
		String what() const;
	
	private:
		String msg_;	// 错误信息
	};

}

#endif	// !INVDK_EXCEPTION_H
