/**
 * @File: String.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: 字符串类型
 */
#ifndef String_H
#define String_H

#include "INVDK_Data.h"

namespace INVDK
{
	class INVDK_SDK_API String
	{
	public:
		/// @brief 默认构造函数
		String();
		/// @brief 构造函数，接受C风格字符串
		/// @param str [IN] C风格字符串
		String(INVDK_PCCHAR str);
		/// @brief 构造函数，接受字符
		/// @param str [IN] 字符
		String(INVDK_CCHAR str);
		/// @brief 构造函数，接受整数
		/// @param num [IN] 整数
		String(INVDK_INT num);
		/// @brief 构造函数，接受无符号整数
		/// @param num [IN] 无符号整数
		String(INVDK_UINT num);
		/// @brief 构造函数，接受单精度浮点数
		/// @param num [IN] 单精度浮点数
		/// @param decit [IN] 最多保留小数位数
		String(INVDK_FLOAT num, INVDK_INT decit = 2);
		/// @brief 构造函数，接受双精度浮点数
		/// @param num [IN] 双精度浮点数
		/// @param decit [IN] 最多保留小数位数
		String(INVDK_DOUBLE num, INVDK_INT decit = 2);

		/// @brief 复制构造函数
		/// @param other [IN] 被复制的类型
		String(const String& other);
		/// @brief 析构函数
		~String();

		/// @brief 赋值运算符
		/// @param other [IN] 字符串
		/// @return 新的字符串
		String& operator=(const String& other);
		/// @brief 加法运算符
		/// @param other [IN] 字符串
		/// @return 新的字符串
		String operator+(const String& other);
		/// @brief 相等运算符
		/// @param other [IN] 字符串
		/// @return 如果2个字符串相等，返回TRUE；否则返回FALSE
		INVDK_BOOL operator==(const String& other);
		/// @brief 相等运算符
		/// @param other [IN] 字符串
		/// @return 如果2个字符串相等，返回TRUE；否则返回FALSE
		INVDK_BOOL operator==(INVDK_PCCHAR other);
		/// @brief 不相等运算符
		/// @param other [IN] 字符串
		/// @return 如果2个字符串不相等，返回TRUE；否则返回FALSE
		INVDK_BOOL operator!=(const String& other);
		/// @brief 不相等运算符
		/// @param other [IN] 字符串
		/// @return 如果2个字符串不相等，返回TRUE；否则返回FALSE
		INVDK_BOOL operator!=(INVDK_PCCHAR other);
		/// @brief 加等于运算符
		/// @param other [IN] 字符串
		/// @return 新的字符串
		String& operator+=(const String& other);
		/// @brief 索引运算符，用于访问字符串中的单个字符
		/// @param index [IN] 下标
		/// @return 对应下标的字符
		INVDK_CHAR& operator[](INVDK_UINT index);
		/// @brief 常量索引运算符，用于访问字符串中的单个字符（不允许修改）
		/// @param index [IN] 下标
		/// @return 对应下标的字符
		INVDK_CCHAR& operator[](INVDK_UINT index) const;

		/// @brief 隐式转换为 INVDK_PCHAR 类型
		operator INVDK_PCHAR();

		/// @brief 获取字符串长度
		/// @return 字符串的长度
		INVDK_SIZE size() const;
		/// @brief 转换为C风格字符串
		/// @return C风格字符串
		INVDK_PCCHAR c_str() const;
		/// @brief 弹出最后一个字符
		/// @return 弹出的字符
		INVDK_CCHAR pop_back();
		/// @brief 判断是否空的
		/// @return 如果是空返回非 0 字符，否则返回 0
		INVDK_BOOL isEmpty() const;
		/// @brief 清空字符串
		/// @return 
		INVDK_VOID clear();

		/// @brief 将字符串转为整数
		/// @param base [IN] 进制
		/// @return 整数
		INVDK_INT toInt(INVDK_INT base = 10) const;
		/// @brief 将字符串转为无符号整数
		/// @param base [IN] 进制
		/// @return 无符号整数
		INVDK_UINT toUInt(INVDK_INT base = 10) const;
		/// @brief 将字符串转为双精度浮点数
		/// @return 双精度浮点数
		INVDK_DOUBLE toDouble() const;
	private:
		INVDK_PCHAR data_;	  // 存储字符串数据的指针
		INVDK_SIZE size_;	  // 字符串的长度（不包括'\0'）
		INVDK_SIZE capacity_; // 分配的内存大小（包括'\0'）

	};
}

#endif	// !String_H


