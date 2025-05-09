/**
 * @File: INVDK_Utility.hpp
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: 工具函数
 */
#ifndef INVDK_UTILITY_HPP
#define INVDK_UTILITY_HPP

#include "INVDK_Data.h"

namespace INVDK
{

	/// @brief 交换两个值
	/// @tparam _Ty 值 的类型
	/// @param _Val1 [IN] 值1
	/// @param _Val2 [IN] 值2
	/// @return
	template <class _Ty>
	INVDK_VOID swap(_Ty& _Val1, _Ty& _Val2)
	{
		_Ty temp = _Val1;
		_Val1 = _Val2;
		_Val2 = temp;
	}

	/// @brief 交换两个指针
	/// @tparam _Ty 指针 的类型
	/// @param _Val1 [IN] 指针1
	/// @param _Val2 [IN] 指针2
	/// @return
	template <class _Ty>
	INVDK_VOID swap(_Ty*& _Val1, _Ty*& _Val2)
	{
		_Ty* temp = _Val1;
		_Val1 = _Val2;
		_Val2 = temp;
	}

	/// @brief 移除引用类型
	/// @tparam _Ty [IN] 模板类型参数
	template <class _Ty>
	struct remove_reference
	{
		using type = _Ty; // 默认类型
		using const_ref_type = const _Ty; // 常量引用类型
	};
	/// @brief 左值引用类型
	/// @tparam _Ty [IN] 模板类型参数
	template <class _Ty>
	struct remove_reference<_Ty&>
	{
		using type = _Ty; // 默认类型
		using const_ref_type = const _Ty&; // 常量引用类型
	};
	/// @brief 右值引用类型
	/// @tparam _Ty [IN] 模板类型参数
	template <class _Ty>
	struct remove_reference<_Ty&&>
	{
		using type = _Ty; // 默认类型
		using const_ref_type = const _Ty&&; // 常量引用类型
	};

	/// @brief 移除引用类型
	/// @tparam _Ty [IN] 模板类型参数
	template <class _Ty>
	using remove_reference_t = typename remove_reference<_Ty>::type; // 移除引用类型

	/// @brief 移除引用类型
	/// @tparam _Ty [IN] 模板类型参数
	template <class _Ty>
	using remove_reference_ref = typename remove_reference<_Ty>::const_ref_type; // 移除引用类型

	/// @brief 完美转发
	/// @tparam _Ty [IN] 模板类型参数
	/// @param _Arg [IN] 需要转发的参数
	/// @return 转发的参数
	template <class _Ty>
	_Ty&& forward(remove_reference_t<_Ty>& _Arg) noexcept
	{
		return static_cast<_Ty&&>(_Arg);
	}
	/// @brief 完美转发
	/// @tparam _Ty [IN] 模板类型参数
	/// @param _Arg [IN] 需要转发的参数
	/// @return 转发的参数
	template <class _Ty>
	_Ty&& forward(remove_reference_t<_Ty>&& _Arg) noexcept
	{
		return static_cast<_Ty&&>(_Arg);
	}

	/// @brief 将左值转换为右值引用
	/// @tparam _Ty [IN] 模板类型参数
	/// @param _Arg [IN] 需要转换的值
	/// @return 右值引用类型
	template <class _Ty>
	remove_reference_t<_Ty>&& move(_Ty&& _Arg) noexcept
	{
		return static_cast<remove_reference_t<_Ty>&&>(_Arg);
	}


	template <class _Ty1, class _Ty2>
	class pair
	{
	public:
		/// @brief 默认构造函数
		pair() : first(), second()
		{}

		/// @brief 构造函数
		/// @param _Val1 [IN] 值1
		/// @param _Val2 [IN] 值2
		pair(const _Ty1& _Val1, const _Ty2& _Val2) : first(_Val1), second(_Val2)
		{}

		/// @brief 重载函数
		/// @param other [IN] pair 类型
		/// @return 新的 pair 类型
		pair operator=(const pair& other)
		{
			first = other.first;
			second = other.second;
			return *this;
		}

		/// @brief 交换两个 pair 类型
		/// @param other [IN] pair 类型
		/// @return
		INVDK_VOID swap(pair& other)
		{
			INVDK::swap<_Ty1>(first, other.first);
			INVDK::swap<_Ty2>(second, other.second);
		}

		_Ty1 first;  // 值1
		_Ty2 second; // 值2
	};

	/// @brief 制作 pair 类型
	/// @tparam _Ty1 值1 的类型
	/// @tparam _Ty2 值2 的类型
	/// @param _Val1 [IN] 值1
	/// @param _Val2 [IN] 值2
	/// @return pair 类型
	template <class _Ty1, class _Ty2>
	pair<_Ty1, _Ty2> make_pair(const _Ty1& _Val1, const _Ty2& _Val2)
	{
		return pair<_Ty1, _Ty2>(_Val1, _Val2);
	}


}


#endif // !INVDK_UTILITY_HPP
