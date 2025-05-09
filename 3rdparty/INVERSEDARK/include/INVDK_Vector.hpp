/**
 * @File: INVDK_Vector.hpp
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: 模板库：vector 容器类
 */
#ifndef INVDK_VECTOR_HPP
#define INVDK_VECTOR_HPP

#include "INVDK_Data.h"
#include "INVDK_Exception.h"
#include "INVDK_Utility.hpp"
#include "INVDK_String_lib.h"
#include "INVDK_Memory.hpp"
#include "INVDK_Memory_lib.h"

namespace INVDK
{

	/// @brief vector 容器
	template <class _Ty, class _Allocator = INVDK::allocator<_Ty>>
	class Vector
	{
	public:
		/// @brief 默认构造函数
		Vector() : data_(NULL), size_(0), capacity_(0)
		{
			reserve(2);
		}
		/// @brief 构造函数
		/// @param capacity [IN] 容器的容量
		Vector(INVDK_UINT capacity) : data_(NULL), size_(0), capacity_(0)
		{
			reserve(capacity);
		}
		/// @brief 带初始大小和值的构造函数
		/// @param size [IN] 初始大小
		/// @param value [IN] 初始值
		Vector(INVDK_UINT size, const _Ty& value) : data_(NULL), size_(0), capacity_(0)
		{
			reserve(size);
			INVDK::memset(data_, value, size * sizeof(_Ty)); // 初始化内存
			size_ = size; // 设置大小
		}
		/// @brief 复制构造函数
		/// @param other [IN] 被复制的类型
		Vector(const Vector& other) : data_(NULL), size_(0), capacity_(0)
		{
			reserve(other.size_);
			INVDK::memcpy(data_, other.data_, other.size_ * sizeof(_Ty)); // 复制内存
			size_ = other.size_; // 设置大小
		}
		/// @brief 移动构造函数
		/// @param other [IN] 被移动的类型
		Vector(Vector&& other) noexcept
			: data_(other.data_), size_(other.size_), capacity_(other.capacity_)
		{
			other.data_ = NULL;
			other.size_ = 0;
			other.capacity_ = 0;
		}
		/// @brief 析构函数
		~Vector()
		{
			if (data_)
			{
				for (INVDK_UINT i = 0; i < size_; ++i)
				{
					alloc_.destroy(&data_[i]); // 销毁每个元素
				}
				alloc_.deallocate(data_, capacity_); // 释放动态数组的内存
			}
			data_ = NULL;
			size_ = 0;
			capacity_ = 0;
		}
	public:
		/// @brief 获取动态数组的长度
		/// @return 动态数组的长度
		INVDK_UINT size() const
		{
			return size_;
		}

		/// @brief 返回容器分配的内存大小
		/// @return 容器分配的内存大小
		INVDK_UINT capacity() const
		{
			return capacity_;
		}

		/// @brief 判断容器是否为空
		/// @return 如果容器为空，返回TRUE；否则返回FALSE
		INVDK_BOOL empty() const
		{
			return 0 == size_;
		}

		/// @brief 在末尾添加一个元素
		/// @param value [IN] 添加的元素
		/// @return
		INVDK_VOID push_back(const _Ty& value)
		{
			// 如果当前元素数量快超过容器的容量了，那么就扩大一倍
			if (size_ == capacity_)
			{
				reserve(capacity_ == 0 ? 2 : capacity_ * 2);
			}
			data_[size_++] = value;
		}

		/// @brief 清空动态数组
		/// @return
		INVDK_VOID clear()
		{
			if (data_)
			{
				for (INVDK_UINT i = 0; i < size_; ++i)
				{
					alloc_.destroy(&data_[i]); // 销毁每个元素
				}
				alloc_.deallocate(data_, capacity_); // 释放动态数组的内存
			}
			size_ = 0;
		}

		/// @brief 索引运算符，用于访问动态数组中的单个元素
		/// @param index [IN] 下标
		/// @return 对应下标的元素
		_Ty& operator[](INVDK_UINT index)
		{
			if (index >= capacity_)
				throw INVDK::Exception(INVDK_T("Index out of range"));
			return data_[index];
		}
		/// @brief 常量索引运算符，用于访问动态数组中的单个元素（不允许修改）
		/// @param index [IN] 下标
		/// @return 对应下标的元素
		const _Ty& operator[](INVDK_UINT index) const
		{
			if (index >= capacity_)
				throw INVDK::Exception(INVDK_T("Index out of range"));
			return data_[index];
		}
		Vector& operator=(const Vector& other)
		{
			// 防止自我赋值
			if (this != &other)
			{
				// 重新分配内存
				_Ty* newData = alloc_.allocate(other.capacity_);
				for (INVDK_UINT i = 0; i < other.size_; ++i)
				{
					newData[i] = other.data_[i];
				}
				if (data_)
				{
					for (INVDK_UINT i = 0; i < size_; ++i)
					{
						alloc_.destroy(&data_[i]); // 销毁每个元素
					}
					alloc_.deallocate(data_, capacity_); // 释放动态数组的内存
				}
				data_ = newData;	// 指向新的内存
				size_ = other.size_;	// 更新大小
				capacity_ = other.capacity_; // 更新容量
			}
			return *this;
		}
		/// @brief 收缩容量函数
		/// @return 
		INVDK_VOID shrinkToFit()
		{
			if (size_ < capacity_)
			{
				_Ty* newData = alloc_.allocate(size_);
				for (INVDK_UINT i = 0; i < size_; ++i)
				{
					newData[i] = INVDK::move(data_[i]);
				}
				if (data_)
				{
					for (INVDK_UINT i = 0; i < size_; ++i)
					{
						alloc_.destroy(&data_[i]); // 销毁每个元素
					}
					alloc_.deallocate(data_, capacity_); // 释放动态数组的内存
				}
				data_ = newData;
				capacity_ = size_;
			}
		}

		/// @brief 更新动态数组的大小
		/// @param newSize [IN] 新的大小
		/// @return
		INVDK_VOID resize(INVDK_UINT newSize)
		{
			if (newSize > capacity_)
			{
				reserve(newSize);
			}
			// 如果新size更大，用默认值填充新元素
			for (INVDK_UINT i = size_; i < newSize; ++i)
			{
				data_[i] = _Ty();
			}
			size_ = newSize;
		}

		/// @brief 弹出末尾的元素，并删除
		/// @return 末尾的元素
		const _Ty pop_back()
		{
			if (size_ <= 0)
				throw INVDK::Exception(INVDK_T("Empty array, no elements to pop."));
			_Ty temp = data_[size_ - 1];
			size_--;
			return temp;
		}

		/// @brief 获取指定下标的元素
		/// @param index [IN] 下标
		/// @return 对应下标的元素
		_Ty& at(INVDK_UINT index)
		{
			if (index >= capacity_)
				throw INVDK::Exception(INVDK_T("Index out of range"));
			return data_[index];
		}
		/// @brief 获取指定下标的元素（不允许修改）
		/// @param index [IN] 下标
		/// @return 对应下标的元素
		const _Ty& at(INVDK_UINT index) const
		{
			if (index >= capacity_)
				throw INVDK::Exception(INVDK_T("Index out of range"));
			return data_[index];
		}

		/// @brief 获取第一个元素
		/// @return 第一个元素
		const _Ty& front() const
		{
			if (size_ <= 0)
				throw INVDK::Exception(INVDK_T("Index out of range"));
			return data_[0];
		}
		/// @brief 获取最后一个元素
		/// @return 最后一个元素
		const _Ty& back() const
		{
			if (size_ <= 0)
				throw INVDK::Exception(INVDK_T("Index out of range"));
			return data_[size_ - 1];
		}

		/// @brief 正向迭代器
		class iterator
		{
		public:
			/// @brief 构造函数
			/// @param pmove [IN] 当前指向的地址
			iterator(_Ty* pmove = NULL) : pmove_(pmove)
			{}
			/// @brief 重载函数
			/// @param pmove [IN] 被赋予指针的地址
			/// @return
			INVDK_VOID operator=(_Ty* pmove)
			{
				this->pmove_ = pmove;
			}
			/// @brief 重载函数，判断两个迭代器是否相等
			/// @param other [IN] 另一个迭代器
			/// @return 不相等返回TRUE
			INVDK_BOOL operator!=(const iterator& other) const
			{
				return this->pmove_ != other.pmove_;
			}
			/// @brief 重载函数，解引用当前指针
			/// @return 解引用后的值
			_Ty& operator*()
			{
				return *pmove_;
			}
			/// @brief 重载函数，将当前指针移向下一个地址
			/// @return
			INVDK_VOID operator++()
			{
				this->pmove_++;
			}
			/// @brief 重载函数，将当前指针移向下一个地址
			/// @param [IN] 后置++
			/// @return
			INVDK_VOID operator++(INVDK_INT)
			{
				this->pmove_++;
			}
			/// @brief 重载函数，获取另一个地址的距离
			/// @param other [IN] 另一个地址
			/// @return 距离
			INVDK_UINT operator-(const iterator& other) const
			{
				return pmove_ - other.pmove_;
			}

		private:
			_Ty* pmove_; // 当前指针
		};

		/// @brief 获取指向动态数组第一个元素的指针
		/// @return 指向动态数组第一个元素的指针
		iterator begin()
		{
			return iterator(data_);
		}
		/// @brief 获取指向动态数组末尾的指针
		/// @return 指向动态数组末尾的指针
		iterator end()
		{
			return iterator(data_ + size_);
		}

		/// @brief 获取指向动态数组开头的常量迭代器
		/// @return 指向动态数组开头的常量迭代器
		const iterator begin() const
		{
			return iterator(data_);
		}

		/// @brief 获取指向动态数组最后一个元素的常量迭代器
		/// @return 指向动态数组最后一个元素的常量迭代器
		const iterator end() const
		{
			return iterator(data_ + size_);
		}

		/// @brief 反向迭代器
		class reverse_iterator
		{
		public:
			/// @brief 构造函数
			/// @param pmove [IN] 当前指向的地址
			reverse_iterator(_Ty* pmove = NULL) : pmove_(pmove)
			{}
			/// @brief 重载函数
			/// @param pmove [IN] 被赋予指针的地址
			/// @return
			INVDK_VOID operator=(_Ty* pmove)
			{
				this->pmove_ = pmove;
			}
			/// @brief 重载函数，判断两个迭代器是否相等
			/// @param other [IN] 另一个迭代器
			/// @return 不相等返回TRUE
			INVDK_BOOL operator!=(const reverse_iterator& other) const
			{
				return this->pmove_ != other.pmove_;
			}
			/// @brief 重载函数，解引用当前指针
			/// @return 解引用后的值
			_Ty& operator*()
			{
				return *pmove_;
			}
			/// @brief 重载函数，将当前指针移向前一个地址
			/// @return
			INVDK_VOID operator++()
			{
				this->pmove_--;
			}
			/// @brief 重载函数，将当前指针移向前一个地址
			/// @param [IN] 后置++
			/// @return
			INVDK_VOID operator++(INVDK_INT)
			{
				this->pmove_--;
			}
			/// @brief 重载函数，将当前指针移向后一个地址
			/// @return
			INVDK_VOID operator--()
			{
				this->pmove_++;
			}
			/// @brief 重载函数，将当前指针移向后一个地址
			/// @param [IN] 后置--
			/// @return
			INVDK_VOID operator--(INVDK_INT)
			{
				this->pmove_++;
			}
			/// @brief 重载函数，获取另一个地址的距离
			/// @param other [IN] 另一个地址
			/// @return 距离
			INVDK_UINT operator-(const reverse_iterator& other) const
			{
				return other.pmove_ - pmove_;
			}

		private:
			_Ty* pmove_; // 当前指针
		};

		/// @brief 获取指向动态数组最后一个元素的反向迭代器
		/// @return 指向动态数组最后一个元素的反向迭代器
		reverse_iterator rbegin()
		{
			return reverse_iterator(data_ + size_ - 1);
		}

		/// @brief 获取指向动态数组开头的反向迭代器
		/// @return 指向动态数组开头的反向迭代器
		reverse_iterator rend()
		{
			return reverse_iterator(data_ - 1);
		}

		/// @brief 获取指向动态数组最后一个元素的常量反向迭代器
		/// @return 指向动态数组最后一个元素的常量反向迭代器
		const reverse_iterator rbegin() const
		{
			return reverse_iterator(data_ + size_ - 1);
		}

		/// @brief 获取指向动态数组开头的常量反向迭代器
		/// @return 指向动态数组开头的常量反向迭代器
		const reverse_iterator rend() const
		{
			return reverse_iterator(data_ - 1);
		}

		/// @brief 在指定下标插入一个数据
		/// @param index [IN] 下标
		/// @param value [IN] 插入的数据
		/// @return 指向插入数据的迭代器
		iterator inster(INVDK_UINT index, const _Ty& value)
		{
			// 如果下标超过了当前动态数组的总个数，抛出异常
			if (index >= size_)
			{
				throw INVDK::Exception(INVDK_T("Index out of range"));
			}
			// 如果大小已经超过了，先扩容
			if (size_ >= capacity_)
			{
				reserve(capacity_ * 2);
			}
			// 从最后一个元素开始，每个元素往后移一位
			for (INVDK_UINT i = size_; i > index; --i)
			{
				data_[i] = data_[i - 1];
			}
			// 在指定下标插入数据
			data_[index] = value;
			// 动态数组长度加一
			size_++;

			return data_ + index;
		}
		/// @brief 在指定迭代器插入一个数据
		/// @param pos [IN] 迭代器
		/// @param value [IN] 插入的数据
		/// @return 指向插入数据的迭代器
		iterator inster(iterator pos, const _Ty& value)
		{
			// 获取当前要插入的迭代器下标
			INVDK_UINT index = pos - INVDK_iterator(begin());

			// 根据下标插入数据
			return inster(index, value);
		}

		/// @brief 删除指定下标的元素
		/// @param index [IN] 下标
		/// @return 删除后的位置
		iterator erase(INVDK_UINT index)
		{
			// 如果下标超过了当前动态数组的总个数，抛出异常
			if (index >= size_)
			{
				throw INVDK::Exception(INVDK_T("Index out of range"));
			}
			// 将在被删除的元素后面的元素遍历前移
			for (INVDK_UINT i = index; i < size_ - 1; i++)
			{
				data_[i] = data_[i + 1];
			}
			// 动态数组大小减一
			size_--;
			return data_ + index;
		}
		/// @brief 删除指定迭代器
		/// @param pos [IN] 指定的迭代器
		/// @return 删除后的位置
		iterator erase(iterator pos)
		{
			// 获取要删除的迭代器所在位置
			INVDK_UINT index = pos - begin();

			// 根据下标删除
			return erase(index);
		}
		/// @brief 删除2个索引之间的所有元素
		/// @param firstIndex [IN] 开始位置
		/// @param lastIndex [IN] 结束位置
		/// @return 开始位置的迭代器
		iterator erase(INVDK_UINT firstIndex, INVDK_UINT lastIndex)
		{
			// 判断是否越界
			if (firstIndex > lastIndex || lastIndex >= size_)
			{
				throw INVDK::Exception(INVDK_T("Index out of range"));
			}

			// 如果要删除的元素是0个，直接返回
			if (lastIndex - firstIndex <= 0)
				return data_ + firstIndex;

			// 将在结束位置 'last' 之后的元素向前移动，覆盖被删除的元素
			INVDK_UINT idx = firstIndex;
			for (INVDK_UINT i = lastIndex; i < size_; ++i)
			{
				data_[idx++] = data_[i];
			}

			// 调整 size_
			size_ -= (lastIndex - firstIndex);

			return data_ + firstIndex;
		}
		/// @brief 删除2个迭代器之间的所有元素
		/// @param first [IN] 开始位置
		/// @param last [IN] 结束位置
		/// @return 开始位置的迭代器
		iterator erase(iterator first, iterator last)
		{
			// 先获取这2个迭代器在动态数组中的下标
			INVDK_UINT firstIndex = first - begin();
			INVDK_UINT lastIndex = last - begin();

			// 根据2个索引删除之间的所有元素
			return erase(firstIndex, lastIndex);
		}
	private:
		/// @brief 重新分配内存
		/// @param newCapacity [IN] 新的容量
		/// @return 
		INVDK_VOID reserve(INVDK_UINT newCapacity)
		{
			if (newCapacity <= capacity_) return;

			_Ty* newData = NULL;
			try
			{
				newData = alloc_.allocate(newCapacity);
				for (INVDK_UINT i = 0; i < size_; ++i)
				{
					newData[i] = INVDK::move(data_[i]);
				}
			}
			catch (...)
			{
				if (newData)
				{
					alloc_.deallocate(newData, newCapacity);
				}
				throw INVDK::Exception(INVDK_T("Memory allocation failed."));
			}

			if (data_)
			{
				alloc_.deallocate(data_, capacity_); // 释放旧内存
			}
			data_ = newData;
			capacity_ = newCapacity;
		}

	private:
		_Ty* data_;			  // 存储元素的动态数组
		INVDK_UINT size_;	  // 当前元素数量
		INVDK_UINT capacity_; // 容器的容量
		_Allocator alloc_;       // 内存分配器
	};

}

#endif // !INVDK_VECTOR_HPP
