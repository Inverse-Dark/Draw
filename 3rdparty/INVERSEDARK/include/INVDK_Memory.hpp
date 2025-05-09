/**
 * @File: INVDK_Memory.hpp
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/30
 * @Description: 内存模板类
 */
#ifndef INVDK_MEMORY_HPP
#define INVDK_MEMORY_HPP

#include "INVDK_Data.h"
#include "INVDK_Utility.hpp"
#include "INVDK_Exception.h"
#include "INVDK_String_lib.h"

namespace INVDK
{
	template <class _Ty>
	class allocator
	{
	public:
        using value_type = _Ty;

		/// @brief 默认构造函数
		allocator() = default;
		/// @brief 默认析构函数
		~allocator() = default;

		/// @brief 申请指定大小的内存
		/// @param _Count [IN] 指定大小
		/// @return 申请成功，返回申请的内存首地址，失败则抛出异常
		value_type* allocate(const INVDK_SIZE _Count)
		{
			if (_Count > max_size())	// 判断申请的内存是否超过最大可分配数量
				throw INVDK::Exception(INVDK_T("Memory allocation failed"));
			if (value_type* p = static_cast<value_type*>(::operator new(_Count * sizeof(value_type))))
				return p;	// 分配内存成功就返回，否则抛出异常
			throw INVDK::Exception(INVDK_T("Memory allocation failed"));
		}

		/// @brief 申请指定大小的内存
		/// @param _Count [IN] 指定大小
		/// @param [IN] 内存块(无用)
		/// @return 申请成功，返回申请的内存首地址，失败则抛出异常
		value_type* allocate(const INVDK_SIZE _Count, INVDK_PCVOID)
		{
			return allocate(_Count);
		}

		/// @brief 释放指定数量的内存
		/// @param _Ptr [IN] 要释放的内存块
		/// @param _Bytes [IN] 要释放的内存数量
		/// @return 
		INVDK_VOID deallocate(value_type* _Ptr, INVDK_SIZE _Bytes)
		{
			::operator delete(_Ptr, _Bytes);
		}

		/// @brief 释放内存
		/// @param _Ptr [IN] 要释放的内存块
		/// @return 
		template<typename _Ty>
		void destroy(_Ty* _Ptr)
		{
			_Ptr->~_Ty();
		}

		/// @brief 构造对象
		/// @param _Ptr [IN] 要构造的对象
		/// @param _Arg [IN] 构造函数参数
		/// @return
		template<typename _Ty, typename... _Args>
		void construct(_Ty* _Ptr, _Args&&... _Arg)
		{
			::new (_Ptr) _Ty(INVDK::forward<_Args>(_Arg)...);
		}

		/// @brief 获取最大可分配内存数量
		/// @return 最大可分配内存数量
		INVDK_SIZE max_size() const
		{
			return static_cast<INVDK_SIZE>(-1) / sizeof(value_type);
		}
	};


}

#endif // !INVDK_MEMORY_HPP
