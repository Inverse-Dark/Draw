/**
 * @File: INVDK_Functional.hpp
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/30
 * @Description: 函数模板
 */
#ifndef INVDK_FUNCTIONAL_HPP
#define INVDK_FUNCTIONAL_HPP

#include "INVDK_Data.h"

namespace INVDK
{
	template<class _Ty>
	struct less
	{
		/// @brief 比较2个元素的大小
		/// @param _Left [IN] 元素1
		/// @param _Right [IN] 元素2
		/// @return TRUE:元素1 小于 元素2	FALSE:元素1 大于 元素2
		constexpr INVDK_BOOL operator()(const _Ty& _Left, const _Ty& _Right) const
		{
			return _Left < _Right;
		}
	};


}

#endif // !INVDK_FUNCTIONAL_HPP
