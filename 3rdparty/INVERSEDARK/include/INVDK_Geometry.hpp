/**
 * @File: INVDK_Geometry.hpp
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/30
 * @Description: 几何数据类型定义
 */
#ifndef INVDK_GEOMETRY_HPP
#define INVDK_GEOMETRY_HPP

#include "INVDK_Data.h"
#include "INVDK_Math.h"
#include "INVDK_Exception.h"
#include "INVDK_String_lib.h"

namespace INVDK
{
	/// @brief 记载 2D 点坐标
	/// @tparam _Ty X,Y 坐标类型
	template <class _Ty>
	class Point_;
	/// @brief 记载 3D 点坐标
	/// @tparam _Ty X,Y,Z 坐标类型
	template <class _Ty>
	class Point3_;
	/// @brief 大小
	/// @tparam _Ty 宽高的类型
	template <class _Ty>
	class Size_;
	/// @brief 矩形
	/// @tparam _Ty 坐标，大小的类型
	template <class _Ty>
	class Rect_;

	template <class _Ty>
	class Point_
	{
	public:
		/// @brief 构造函数
		Point_();
		/// @brief 构造函数
		/// @param x [IN] X 坐标
		/// @param y [IN] Y 坐标
		Point_(_Ty x, _Ty y);
		Point_(const Size_<_Ty> size);
		/// @brief 构造函数
		/// @param point [IN] 另一个点
		Point_(const Point_& point);

		/// @brief 赋值运算符重载
		/// @param other [IN] 另一个点
		/// @return 另一个点所在位置
		Point_& operator=(const Point_& other);
		/// @brief 赋值运算符重载
		/// @param other [IN] 另一个点
		/// @return 两个点 X,Y 坐标相加过后的位置
		Point_& operator+=(const Point_& other);
		/// @brief 赋值运算符重载
		/// @param other [IN] 相减的点
		/// @return 两个点 X,Y 坐标相减过后的位置
		Point_& operator-=(const Point_& other);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相乘过后的位置
		Point_& operator*=(const INVDK_INT& scalar);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相乘过后的位置
		Point_& operator*=(const INVDK_FLOAT& scalar);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相乘过后的位置
		Point_& operator*=(const INVDK_DOUBLE& scalar);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相除过后的位置
		Point_& operator/=(const INVDK_INT& scalar);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相除过后的位置
		Point_& operator/=(const INVDK_FLOAT& scalar);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相除过后的位置
		Point_& operator/=(const INVDK_DOUBLE& scalar);

		/// @brief 加法运算符重载
		/// @param other [IN] 相加的点
		/// @return 两个点 X,Y 坐标相加过后的位置
		Point_ operator+(const Point_& other) const;
		/// @brief 减法运算符重载
		/// @param other [IN] 相减的点
		/// @return 两个点 X,Y 坐标相减过后的位置
		Point_ operator-(const Point_& other) const;
		/// @brief 乘法运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相乘过后的位置
		Point_ operator*(const INVDK_INT& scalar) const;
		/// @brief 乘法运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相乘过后的位置
		Point_ operator*(const INVDK_FLOAT& scalar) const;
		/// @brief 乘法运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相乘过后的位置
		Point_ operator*(const INVDK_DOUBLE& scalar) const;
		/// @brief 除法运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相除过后的位置
		Point_ operator/(const INVDK_INT& scalar) const;
		/// @brief 除法运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相除过后的位置
		Point_ operator/(const INVDK_FLOAT& scalar) const;
		/// @brief 除法运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相除过后的位置
		Point_ operator/(const INVDK_DOUBLE& scalar) const;

		/// @brief 逻辑运算符重载
		/// @param other [IN] 另一个点
		/// @return 是否相等
		INVDK_BOOL operator==(const Point_& other) const;
		/// @brief 逻辑运算符重载
		/// @param other [IN] 另一个点
		/// @return 是否不相等
		INVDK_BOOL operator!=(const Point_& other) const;

		/// @brief 两个点之间的点乘运算
		/// @param other [IN] 另一个点
		/// @return 点乘的结果，即两个点的点积
		INVDK_DOUBLE dot(const Point_& other) const;
		/// @brief 两个点之间的叉乘运算
		/// @param other [IN] 另一个点
		/// @return 叉乘的结果，即两个点的叉积
		INVDK_DOUBLE cross(const Point_& other) const;
		/// @brief 检查点是否在给定的矩形内
		/// @param rect [IN] 给定的矩形
		/// @return TRUE: 在	FALSE: 不在
		INVDK_BOOL inside(const Rect_<_Ty>& rect) const;

		_Ty x; // X 坐标
		_Ty y; // Y 坐标
	};
	typedef Point_<INVDK_INT> Point2i;
	typedef Point_<INVDK_LLONG> Point2l;
	typedef Point_<INVDK_FLOAT> Point2f;
	typedef Point_<INVDK_DOUBLE> Point2d;
	typedef Point2i Point;

	template <class _Ty>
	class Point3_
	{
	public:
		/// @brief 构造函数
		Point3_();
		/// @brief 构造函数
		/// @param x [IN] X 坐标
		/// @param y [IN] Y 坐标
		/// @param z [IN] Z 坐标
		Point3_(_Ty x, _Ty y, _Ty z);
		/// @brief 构造函数
		/// @param point [IN] 另一个点
		Point3_(const Point3_& point);

		/// @brief 赋值运算符重载
		/// @param other [IN] 另一个点
		/// @return 另一个点所在位置
		Point3_& operator=(const Point3_& other);
		/// @brief 赋值运算符重载
		/// @param other [IN] 另一个点
		/// @return 两个点 X,Y 坐标相加过后的位置
		Point3_& operator+=(const Point3_& other);
		/// @brief 赋值运算符重载
		/// @param other [IN] 相减的点
		/// @return 两个点 X,Y 坐标相减过后的位置
		Point3_& operator-=(const Point3_& other);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相乘过后的位置
		Point3_& operator*=(const INVDK_INT& scalar);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相乘过后的位置
		Point3_& operator*=(const INVDK_FLOAT& scalar);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相乘过后的位置
		Point3_& operator*=(const INVDK_DOUBLE& scalar);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相除过后的位置
		Point3_& operator/=(const INVDK_INT& scalar);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相除过后的位置
		Point3_& operator/=(const INVDK_FLOAT& scalar);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相除过后的位置
		Point3_& operator/=(const INVDK_DOUBLE& scalar);

		/// @brief 加法运算符重载
		/// @param other [IN] 相加的点
		/// @return 两个点 X,Y 坐标相加过后的位置
		Point3_ operator+(const Point3_& other) const;
		/// @brief 减法运算符重载
		/// @param other [IN] 相减的点
		/// @return 两个点 X,Y 坐标相减过后的位置
		Point3_ operator-(const Point3_& other) const;
		/// @brief 乘法运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相乘过后的位置
		Point3_ operator*(const INVDK_INT& scalar) const;
		/// @brief 乘法运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相乘过后的位置
		Point3_ operator*(const INVDK_FLOAT& scalar) const;
		/// @brief 乘法运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相乘过后的位置
		Point3_ operator*(const INVDK_DOUBLE& scalar) const;
		/// @brief 除法运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相除过后的位置
		Point3_ operator/(const INVDK_INT& scalar) const;
		/// @brief 除法运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相除过后的位置
		Point3_ operator/(const INVDK_FLOAT& scalar) const;
		/// @brief 除法运算符重载
		/// @param scalar [IN] 标量
		/// @return X,Y 坐标与标量相除过后的位置
		Point3_ operator/(const INVDK_DOUBLE& scalar) const;

		/// @brief 逻辑运算符重载
		/// @param other [IN] 另一个点
		/// @return 是否相等
		INVDK_BOOL operator==(const Point3_& other) const;
		/// @brief 逻辑运算符重载
		/// @param other [IN] 另一个点
		/// @return 是否不相等
		INVDK_BOOL operator!=(const Point3_& other) const;

		/// @brief 两个点之间的点乘运算
		/// @param other [IN] 另一个点
		/// @return 点乘的结果，即两个点的点积
		INVDK_DOUBLE dot(const Point3_& other) const;
		/// @brief 两个点之间的叉乘运算
		/// @param other [IN] 另一个点
		/// @return 叉乘的结果，即两个点的叉积
		Point3_ cross(const Point3_& other) const;

		_Ty x; // X 坐标
		_Ty y; // Y 坐标
		_Ty z; // Z 坐标
	};
	typedef Point3_<INVDK_INT> Point3i;
	typedef Point3_<INVDK_FLOAT> Point3f;
	typedef Point3_<INVDK_DOUBLE> Point3d;

	template <class _Ty>
	class Size_
	{
	public:
		/// @brief 构造函数
		Size_();
		/// @brief 构造函数
		/// @param width [IN] 宽
		/// @param height [IN] 高
		Size_(_Ty width, _Ty height);
		/// @brief 构造函数
		/// @param size [IN] 大小
		Size_(const Size_& size);

		/// @brief 赋值运算符重载
		/// @param other [IN] 另一个大小的宽与高
		/// @return 另一个大小的宽与高
		Size_& operator=(const Size_& other);
		/// @brief 赋值运算符重载
		/// @param other [IN] 另一个大小
		/// @return 两个大小的宽与高相加过后的宽高
		Size_& operator+=(const Size_& other);
		/// @brief 赋值运算符重载
		/// @param other [IN] 相减的大小
		/// @return 两个大小的宽与高相减过后的宽高
		Size_& operator-=(const Size_& other);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return 大小与标量相乘过后的宽高
		Size_& operator*=(const _Ty& scalar);
		/// @brief 赋值运算符重载
		/// @param scalar [IN] 标量
		/// @return 大小与标量相除过后的宽高
		Size_& operator/=(const _Ty& scalar);

		/// @brief 加法运算符重载
		/// @param other [IN] 另一个大小
		/// @return 两个大小的宽与高相加过后的宽高
		Size_ operator+(const Size_& other) const;
		/// @brief 减法运算符重载
		/// @param other [IN] 相减的大小
		/// @return 两个大小的宽与高相减过后的宽高
		Size_ operator-(const Size_& other) const;
		/// @brief 乘法运算符重载
		/// @param scalar [IN] 标量
		/// @return 大小与标量相乘过后的宽高
		Size_ operator*(const _Ty& scalar) const;
		/// @brief 除法运算符重载
		/// @param scalar [IN] 标量
		/// @return 大小与标量相除过后的宽高
		Size_ operator/(const _Ty& scalar) const;

		/// @brief 逻辑运算符重载
		/// @param other [IN] 另一个大小
		/// @return 是否相等
		INVDK_BOOL operator==(const Size_& other) const;
		/// @brief 逻辑运算符重载
		/// @param other [IN] 另一个大小
		/// @return 是否不相等
		INVDK_BOOL operator!=(const Size_& other) const;

		/// @brief 获取面积
		/// @return 面积
		_Ty area() const;
		/// @brief 获取纵横比
		/// @return 纵横比
		INVDK_DOUBLE aspectRatio() const;
		/// @brief 判断是否为空
		/// @return TRUE: 空	FALSE: 不为空
		INVDK_BOOL empty() const;

		_Ty width;	 // 宽
		_Ty height; // 高
	};
	typedef Size_<INVDK_INT> Size2i;
	typedef Size_<INVDK_LLONG> Size2l;
	typedef Size_<INVDK_FLOAT> Size2f;
	typedef Size_<INVDK_DOUBLE> Size2d;
	typedef Size2i Size;

	template <class _Ty>
	class Rect_
	{
	public:
		/// @brief 构造函数
		Rect_();
		/// @brief 构造函数
		/// @param x [IN] X 坐标
		/// @param y [IN] Y 坐标
		/// @param width [IN] 宽
		/// @param height [IN] 高
		Rect_(_Ty x, _Ty y, _Ty width, _Ty height);
		/// @brief 构造函数
		/// @param rect [IN] 矩形
		Rect_(const Rect_& rect);
		/// @brief 构造函数
		/// @param point [IN] 开始坐标
		/// @param size [IN] 矩形的宽高
		Rect_(const Point_<_Ty> point, const Size_<_Ty> size);
		/// @brief 构造函数
		/// @param point1 [IN] 开始坐标
		/// @param point2 [IN] 结束坐标
		Rect_(const Point_<_Ty> point1, const Point_<_Ty> point2);

		/// @brief 赋值运算符重载
		/// @param other [IN] 另一个矩形
		/// @return 另一个矩形
		Rect_& operator=(const Rect_& other);
		/// @brief 赋值运算符
		/// @param point [IN] 给定坐标
		/// @return 矩形的原坐标加上给定坐标的新矩形
		Rect_& operator+=(const Point_<_Ty>& point);
		/// @brief 赋值运算符重载
		/// @param size [IN] 给定大小
		/// @return 矩形的原大小加上给定大小的新矩形
		Rect_& operator+=(const Size_<_Ty>& size);
		/// @brief 赋值运算符重载
		/// @param point [IN] 给定坐标
		/// @return 矩形的原坐标减去给定坐标的新矩形
		Rect_& operator-=(const Point_<_Ty>& point);
		/// @brief 赋值运算符重载
		/// @param size [IN] 给定大小
		/// @return 矩形的原大小减去给定大小的新矩形
		Rect_& operator-=(const Size_<_Ty>& size);
		/// @brief 赋值运算符重载
		/// @param other [IN] 另一个矩形
		/// @return 两个矩形重叠的地方，不重叠返回空的矩形
		Rect_& operator&=(const Rect_& other);
		/// @brief 赋值运算符重载
		/// @param other [IN] 另一个矩形
		/// @return 生成一个能覆盖两个矩形的最小矩形
		Rect_& operator|=(const Rect_& other);

		/// @brief 加法运算符重载
		/// @param point [IN] 给定坐标
		/// @return 矩形的原坐标加上给定坐标的新矩形
		Rect_ operator+(const Point_<_Ty>& point) const;
		/// @brief 加法运算符重载
		/// @param size [IN] 给定大小
		/// @return 矩形的原大小加上给定大小的新矩形
		Rect_ operator+(const Size_<_Ty>& size) const;
		/// @brief 减法运算符重载
		/// @param point [IN] 给定坐标
		/// @return 矩形的原坐标减去给定坐标的新矩形
		Rect_ operator-(const Point_<_Ty>& point) const;
		/// @brief 减法运算符重载
		/// @param size [IN] 给定大小
		/// @return 矩形的原大小减去给定大小的新矩形
		Rect_ operator-(const Size_<_Ty>& size) const;
		/// @brief 与运算符重载
		/// @param other [IN] 另一个矩形
		/// @return 两个矩形重叠的地方，不重叠返回空的矩形
		Rect_ operator&(const Rect_& other) const;
		/// @brief 或运算符重载
		/// @param other [IN] 另一个矩形
		/// @return 生成一个能覆盖两个矩形的最小矩形
		Rect_ operator|(const Rect_& other) const;

		/// @brief 逻辑运算符重载
		/// @param other [IN] 另一个矩形
		/// @return 是否相等
		INVDK_BOOL operator==(const Rect_& other) const;
		/// @brief 逻辑运算符重载
		/// @param other [IN] 另一个矩形
		/// @return 是否不相等
		INVDK_BOOL operator!=(const Rect_& other) const;

		/// @brief 获取矩形左上角的坐标
		/// @return 左上角的坐标
		Point_<_Ty> tl() const;
		/// @brief 获取矩形右下角的坐标
		/// @return 右下角的坐标
		Point_<_Ty> br() const;
		/// @brief 获取矩形的大小
		/// @return 矩形的大小
		Size_<_Ty> size() const;
		/// @brief 获取面积
		/// @return 面积
		_Ty area() const;
		/// @brief 判断是否为空
		/// @return TRUE: 空	FALSE: 不为空
		INVDK_BOOL empty() const;
		/// @brief 检查给定点的位置是否包含在矩形内
		/// @param point [IN] 给定点
		/// @return TRUE: 包含	FALSE: 不包含
		INVDK_BOOL contains(const Point_<_Ty>& point) const;

		/// @brief 获取矩形的中心点
		/// @return 矩形的中心点
		Point_<_Ty> center() const;

		_Ty x;		 // X 坐标
		_Ty y;		 // Y 坐标
		_Ty width;	 // 宽
		_Ty height; // 高
	};
	typedef Rect_<INVDK_INT> Rect2i;
	typedef Rect_<INVDK_FLOAT> Rect2f;
	typedef Rect_<INVDK_DOUBLE> Rect2d;
	typedef Rect2i Rect;


	///////////////////////// 2D Point /////////////////////////
	template <class _Ty>
	inline Point_<_Ty>::Point_()
		: x(0), y(0)
	{}
	template <class _Ty>
	inline Point_<_Ty>::Point_(_Ty x, _Ty y)
		: x(x), y(y)
	{}
	template <class _Ty>
	inline Point_<_Ty>::Point_(const Size_<_Ty> size)
		: x(size.width), y(size.height)
	{}
	template <class _Ty>
	inline Point_<_Ty>::Point_(const Point_& point)
		: x(point.x), y(point.y)
	{}

	template <class _Ty>
	inline Point_<_Ty>& Point_<_Ty>::operator=(const Point_& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	template <class _Ty>
	inline Point_<_Ty>& Point_<_Ty>::operator+=(const Point_& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	template <class _Ty>
	inline Point_<_Ty>& Point_<_Ty>::operator-=(const Point_& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	template <class _Ty>
	inline Point_<_Ty>& Point_<_Ty>::operator*=(const INVDK_INT& scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	template <class _Ty>
	inline Point_<_Ty>& Point_<_Ty>::operator*=(const INVDK_FLOAT& scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	template <class _Ty>
	inline Point_<_Ty>& Point_<_Ty>::operator*=(const INVDK_DOUBLE& scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	template <class _Ty>
	inline Point_<_Ty>& Point_<_Ty>::operator/=(const INVDK_INT& scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}
	template <class _Ty>
	inline Point_<_Ty>& Point_<_Ty>::operator/=(const INVDK_FLOAT& scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}
	template <class _Ty>
	inline Point_<_Ty>& Point_<_Ty>::operator/=(const INVDK_DOUBLE& scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	template <class _Ty>
	inline Point_<_Ty> Point_<_Ty>::operator+(const Point_& other) const
	{
		return Point_(x + other.x, y + other.y);
	}
	template <class _Ty>
	inline Point_<_Ty> Point_<_Ty>::operator-(const Point_& other) const
	{
		return Point_(x - other.x, y - other.y);
	}
	template <class _Ty>
	inline Point_<_Ty> Point_<_Ty>::operator*(const INVDK_INT& scalar) const
	{
		return Point_(x * scalar, y * scalar);
	}
	template <class _Ty>
	inline Point_<_Ty> Point_<_Ty>::operator*(const INVDK_FLOAT& scalar) const
	{
		return Point_(x * scalar, y * scalar);
	}
	template <class _Ty>
	inline Point_<_Ty> Point_<_Ty>::operator*(const INVDK_DOUBLE& scalar) const
	{
		return Point_(x * scalar, y * scalar);
	}
	template <class _Ty>
	inline Point_<_Ty> Point_<_Ty>::operator/(const INVDK_INT& scalar) const
	{
		return Point_(x / scalar, y / scalar);
	}
	template <class _Ty>
	inline Point_<_Ty> Point_<_Ty>::operator/(const INVDK_FLOAT& scalar) const
	{
		return Point_(x / scalar, y / scalar);
	}
	template <class _Ty>
	inline Point_<_Ty> Point_<_Ty>::operator/(const INVDK_DOUBLE& scalar) const
	{
		return Point_(x / scalar, y / scalar);
	}

	template <class _Ty>
	inline INVDK_BOOL Point_<_Ty>::operator==(const Point_& other) const
	{
		return (x == other.x && y == other.y);
	}
	template <class _Ty>
	inline INVDK_BOOL Point_<_Ty>::operator!=(const Point_& other) const
	{
		return (x != other.x || y != other.y);
	}

	template <class _Ty>
	inline INVDK_DOUBLE Point_<_Ty>::dot(const Point_& other) const
	{
		return INVDK_DOUBLE(x * other.x + y * other.y);
	}
	template <class _Ty>
	inline INVDK_DOUBLE Point_<_Ty>::cross(const Point_& other) const
	{
		return INVDK_DOUBLE(x * other.y - y * other.x);
	}
	template <class _Ty>
	inline INVDK_BOOL Point_<_Ty>::inside(const Rect_<_Ty>& rect) const
	{
		return rect.contains(*this);
	}

	///////////////////////// 3D Point /////////////////////////
	template <class _Ty>
	inline Point3_<_Ty>::Point3_()
		: x(0), y(0), z(0)
	{}
	template <class _Ty>
	inline Point3_<_Ty>::Point3_(_Ty x, _Ty y, _Ty z)
		: x(x), y(y), z(z)
	{}
	template <class _Ty>
	inline Point3_<_Ty>::Point3_(const Point3_& point)
		: x(point.x), y(point.y), z(point.z)
	{}

	template <class _Ty>
	inline Point3_<_Ty>& Point3_<_Ty>::operator=(const Point3_& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	template <class _Ty>
	inline Point3_<_Ty>& Point3_<_Ty>::operator+=(const Point3_& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	template <class _Ty>
	inline Point3_<_Ty>& Point3_<_Ty>::operator-=(const Point3_& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	template <class _Ty>
	inline Point3_<_Ty>& Point3_<_Ty>::operator*=(const INVDK_INT& scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	template <class _Ty>
	inline Point3_<_Ty>& Point3_<_Ty>::operator*=(const INVDK_FLOAT& scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	template <class _Ty>
	inline Point3_<_Ty>& Point3_<_Ty>::operator*=(const INVDK_DOUBLE& scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	template <class _Ty>
	inline Point3_<_Ty>& Point3_<_Ty>::operator/=(const INVDK_INT& scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	template <class _Ty>
	inline Point3_<_Ty>& Point3_<_Ty>::operator/=(const INVDK_FLOAT& scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	template <class _Ty>
	inline Point3_<_Ty>& Point3_<_Ty>::operator/=(const INVDK_DOUBLE& scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	template <class _Ty>
	inline Point3_<_Ty> Point3_<_Ty>::operator+(const Point3_& other) const
	{
		return Point_(x + other.x, y + other.y, z + other.z);
	}
	template <class _Ty>
	inline Point3_<_Ty> Point3_<_Ty>::operator-(const Point3_& other) const
	{
		return Point_(x - other.x, y - other.y, z - other.z);
	}
	template <class _Ty>
	inline Point3_<_Ty> Point3_<_Ty>::operator*(const INVDK_INT& scalar) const
	{
		return Point_(x * scalar, y * scalar, z * scalar);
	}
	template <class _Ty>
	inline Point3_<_Ty> Point3_<_Ty>::operator*(const INVDK_FLOAT& scalar) const
	{
		return Point_(x * scalar, y * scalar, z * scalar);
	}
	template <class _Ty>
	inline Point3_<_Ty> Point3_<_Ty>::operator*(const INVDK_DOUBLE& scalar) const
	{
		return Point_(x * scalar, y * scalar, z * scalar);
	}
	template <class _Ty>
	inline Point3_<_Ty> Point3_<_Ty>::operator/(const INVDK_INT& scalar) const
	{
		return Point_(x / scalar, y / scalar, z / scalar);
	}
	template <class _Ty>
	inline Point3_<_Ty> Point3_<_Ty>::operator/(const INVDK_FLOAT& scalar) const
	{
		return Point_(x / scalar, y / scalar, z / scalar);
	}
	template <class _Ty>
	inline Point3_<_Ty> Point3_<_Ty>::operator/(const INVDK_DOUBLE& scalar) const
	{
		return Point_(x / scalar, y / scalar, z / scalar);
	}

	template <class _Ty>
	inline INVDK_BOOL Point3_<_Ty>::operator==(const Point3_& other) const
	{
		return (x == other.x && y == other.y && z == other.z);
	}
	template <class _Ty>
	inline INVDK_BOOL Point3_<_Ty>::operator!=(const Point3_& other) const
	{
		return (x != other.x || y != other.y || z != other.z);
	}

	template <class _Ty>
	inline INVDK_DOUBLE Point3_<_Ty>::dot(const Point3_& other) const
	{
		return INVDK_DOUBLE(x * other.x + y * other.y + z * other.z);
	}
	template <class _Ty>
	inline Point3_<_Ty> Point3_<_Ty>::cross(const Point3_& other) const
	{
		return Point3_(y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
	}

	///////////////////////// Size /////////////////////////
	template <class _Ty>
	inline Size_<_Ty>::Size_()
		: width(0), height(0)
	{}
	template <class _Ty>
	inline Size_<_Ty>::Size_(_Ty width, _Ty height)
		: width(width), height(height)
	{}
	template <class _Ty>
	inline Size_<_Ty>::Size_(const Size_& size)
		: width(size.width), height(size.height)
	{}

	template <class _Ty>
	inline Size_<_Ty>& Size_<_Ty>::operator=(const Size_& other)
	{
		width = other.width;
		height = other.height;
		return *this;
	}
	template <class _Ty>
	inline Size_<_Ty>& Size_<_Ty>::operator+=(const Size_& other)
	{
		width += other.width;
		height += other.height;
		return *this;
	}
	template <class _Ty>
	inline Size_<_Ty>& Size_<_Ty>::operator-=(const Size_& other)
	{
		width -= other.width;
		height -= other.height;
		return *this;
	}
	template <class _Ty>
	inline Size_<_Ty>& Size_<_Ty>::operator*=(const _Ty& scalar)
	{
		width *= scalar;
		height *= scalar;
		return *this;
	}
	template <class _Ty>
	inline Size_<_Ty>& Size_<_Ty>::operator/=(const _Ty& scalar)
	{
		width /= scalar;
		height /= scalar;
		return *this;
	}

	template <class _Ty>
	inline Size_<_Ty> Size_<_Ty>::operator+(const Size_& other) const
	{
		return Size_(width + other.width, height + other.height);
	}
	template <class _Ty>
	inline Size_<_Ty> Size_<_Ty>::operator-(const Size_& other) const
	{
		return Size_(width - other.width, height - other.height);
	}
	template <class _Ty>
	inline Size_<_Ty> Size_<_Ty>::operator*(const _Ty& scalar) const
	{
		return Size_(width * scalar, height * scalar);
	}
	template <class _Ty>
	inline Size_<_Ty> Size_<_Ty>::operator/(const _Ty& scalar) const
	{
		return Size_(width / scalar, height / scalar);
	}

	template <class _Ty>
	inline INVDK_BOOL Size_<_Ty>::operator==(const Size_& other) const
	{
		return (width == other.width && height == other.height);
	}
	template <class _Ty>
	inline INVDK_BOOL Size_<_Ty>::operator!=(const Size_& other) const
	{
		return (width != other.width || height != other.height);
	}

	template <class _Ty>
	inline _Ty Size_<_Ty>::area() const
	{
		return width * height;
	}
	template <class _Ty>
	inline INVDK_DOUBLE Size_<_Ty>::aspectRatio() const
	{
		return width / height;
	}
	template <class _Ty>
	inline INVDK_BOOL Size_<_Ty>::empty() const
	{
		return width <= 0 || height <= 0;
	}

	///////////////////////// Rect /////////////////////////
	template <class _Ty>
	inline Rect_<_Ty>::Rect_()
		: x(0), y(0), width(0), height(0)
	{}
	template <class _Ty>
	inline Rect_<_Ty>::Rect_(_Ty x, _Ty y, _Ty width, _Ty height)
		: x(x), y(y), width(width), height(height)
	{}
	template <class _Ty>
	inline Rect_<_Ty>::Rect_(const Rect_& rect)
		: x(rect.x), y(rect.y), width(rect.width), height(rect.height)
	{}
	template <class _Ty>
	inline Rect_<_Ty>::Rect_(const Point_<_Ty> point, const Size_<_Ty> size)
		: x(point.x), y(point.y), width(size.width), height(size.height)
	{}
	template <class _Ty>
	inline Rect_<_Ty>::Rect_(const Point_<_Ty> point1, const Point_<_Ty> point2)
	{
		x = INVDK_MIN(point1.x, point2.x);
		y = INVDK_MIN(point1.y, point2.y);
		width = INVDK_MAX(point1.x, point2.x) - x;
		height = INVDK_MAX(point1.y, point2.y) - y;
	}

	template <class _Ty>
	inline Rect_<_Ty>& Rect_<_Ty>::operator=(const Rect_& other)
	{
		x = other.x;
		y = other.y;
		width = other.width;
		height = other.height;
		return *this;
	}
	template <class _Ty>
	inline Rect_<_Ty>& Rect_<_Ty>::operator+=(const Point_<_Ty>& point)
	{
		x += point.x;
		y += point.y;
		return *this;
	}
	template <class _Ty>
	inline Rect_<_Ty>& Rect_<_Ty>::operator+=(const Size_<_Ty>& size)
	{
		width += size.width;
		height += size.height;
		return *this;
	}
	template <class _Ty>
	inline Rect_<_Ty>& Rect_<_Ty>::operator-=(const Point_<_Ty>& point)
	{
		x -= point.x;
		y -= point.y;
		return *this;
	}
	template <class _Ty>
	inline Rect_<_Ty>& Rect_<_Ty>::operator-=(const Size_<_Ty>& size)
	{
		width -= size.width;
		height -= size.height;
		return *this;
	}
	template <class _Ty>
	inline Rect_<_Ty>& Rect_<_Ty>::operator&=(const Rect_& other)
	{
		_Ty x = INVDK_MAX(x, other.x);
		_Ty y = INVDK_MAX(y, other.y);
		width = INVDK_MIN(x + width, other.x + other.width) - x;
		height = INVDK_MIN(y + height, other.y + other.height) - y;
		x = x;
		y = y;
		if (width <= 0 || height <= 0)
			*this = Rect_();
		return *this;
	}
	template <class _Ty>
	inline Rect_<_Ty>& Rect_<_Ty>::operator|=(const Rect_& other)
	{
		if (empty())
		{
			*this = other;
		}
		else if (!other.empty())
		{
			_Ty x = INVDK_MIN(x, other.x);
			_Ty y = INVDK_MIN(y, other.y);
			width = INVDK_MAX(x + width, other.x + other.width) - x;
			height = INVDK_MAX(y + height, other.y + other.height) - y;
			x = x;
			y = y;
		}
		return *this;
	}

	template <class _Ty>
	inline Rect_<_Ty> Rect_<_Ty>::operator+(const Point_<_Ty>& point) const
	{
		return Rect_(x + point.x, y + point.y, width, height);
	}
	template <class _Ty>
	inline Rect_<_Ty> Rect_<_Ty>::operator+(const Size_<_Ty>& size) const
	{
		return Rect_(x, y, width + size.width, height + size.height);
	}
	template <class _Ty>
	inline Rect_<_Ty> Rect_<_Ty>::operator-(const Point_<_Ty>& point) const
	{
		return Rect_(x - point.x, y - point.y, width, height);
	}
	template <class _Ty>
	inline Rect_<_Ty> Rect_<_Ty>::operator-(const Size_<_Ty>& size) const
	{
		return Rect_(x, y, width - size.width, height - size.height);
	}
	template <class _Ty>
	inline Rect_<_Ty> Rect_<_Ty>::operator&(const Rect_& other) const
	{
		Rect_<_Ty> newRect = *this;
		return newRect &= other;
	}
	template <class _Ty>
	inline Rect_<_Ty> Rect_<_Ty>::operator|(const Rect_& other) const
	{
		Rect_<_Ty> newRect = *this;
		return newRect |= other;
	}

	template <class _Ty>
	inline INVDK_BOOL Rect_<_Ty>::operator==(const Rect_& other) const
	{
		return (x == other.x && y == other.y && width == other.width && height == other.height);
	}
	template <class _Ty>
	inline INVDK_BOOL Rect_<_Ty>::operator!=(const Rect_& other) const
	{
		return (x != other.x || y != other.y || width != other.width || height != other.height);
	}

	template <class _Ty>
	inline Point_<_Ty> Rect_<_Ty>::tl() const
	{
		return Point_<_Ty>(x, y);
	}
	template <class _Ty>
	inline Point_<_Ty> Rect_<_Ty>::br() const
	{
		return Point_<_Ty>(x + width, y + height);
	}
	template <class _Ty>
	inline Size_<_Ty> Rect_<_Ty>::size() const
	{
		return Size_<_Ty>(width, height);
	}
	template <class _Ty>
	inline _Ty Rect_<_Ty>::area() const
	{
		return width * height;
	}
	template <class _Ty>
	inline INVDK_BOOL Rect_<_Ty>::empty() const
	{
		return (width <= 0 || height <= 0);
	}
	template <class _Ty>
	inline INVDK_BOOL Rect_<_Ty>::contains(const Point_<_Ty>& point) const
	{
		return (x <= point.x && point.x <= x + width && y <= point.y && point.y <= y + height);
	}
	template<class _Ty>
	inline Point_<_Ty> Rect_<_Ty>::center() const
	{
		return Point_<_Ty>(x + width / 2, y + height / 2);
	}


	/// @brief 将二维坐标转换为一维下标
	/// @param point [IN] 点
	/// @param width [IN] 一行的宽度
	/// @return 一维下标
	inline INVDK_UINT point2D_to_index(const INVDK::Point2i& point, const INVDK_UINT& width)
	{
		return (width * point.y + point.x);
	}
	/// @brief 将一维下标转换为二位坐标
	/// @param index [IN] 下标
	/// @param width [IN] 一行的宽度
	/// @return 二维坐标
	inline INVDK::Point index_to_point2D(const INVDK_UINT& index, const INVDK_UINT& width)
	{
		return INVDK::Point(index % width, index / width);
	}
	/// @brief 将三维坐标转换为一维下标
	/// @param point [IN] 点
	/// @param width [IN] 一行的宽度
	/// @param height [IN] 一层的高度
	/// @return 一维下标
	inline INVDK_UINT point3D_to_index(const INVDK::Point3i& point, const INVDK_UINT& width, const INVDK_UINT& height)
	{
		return (width * height * point.z) + (width * point.y) + point.x;
	}
	/// @brief 将一维下标转换为三维坐标
	/// @param index [IN] 下标
	/// @param width [IN] 一行的宽度
	/// @param height [IN] 一层的高度
	/// @return 三维坐标
	inline INVDK::Point3i index_to_point3D(const INVDK_UINT& index, const INVDK_UINT& width, const INVDK_UINT& height)
	{
		INVDK_UINT z = index / (width * height);
		INVDK_UINT temp = index % (width * height);
		INVDK_UINT y = temp / width;
		INVDK_UINT x = temp % width;

		return INVDK::Point3i(x, y, z);
	}

	/// @brief 计算两点之间的欧几里得距离
	/// @param x1 [IN] 点1 的 X
	/// @param y1 [IN] 点1 的 Y
	/// @param x2 [IN] 点2 的 X
	/// @param y2 [IN] 点2 的 Y
	/// @return 两点之间的欧几里得距离
	inline INVDK_DOUBLE distance(const INVDK_DOUBLE& x1, const INVDK_DOUBLE& y1, const INVDK_DOUBLE& x2, const INVDK_DOUBLE& y2)
	{
		return INVDK::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	}

	/// @brief 计算两点之间的欧几里得距离
	/// @tparam _Ty 点 的类型
	/// @param point1 [IN] 点1
	/// @param point2 [IN] 点2
	/// @return 两点之间的欧几里得距离
	template <class _Ty>
	inline INVDK_DOUBLE distance(const INVDK::Point_<_Ty>& point1, const INVDK::Point_<_Ty>& point2)
	{
		return distance(point1.x, point1.y, point2.x, point2.y);
	}

	/// @brief 2D 图形旋转指定角度
	/// @tparam _Ty 点的类型
	/// @param point [IN] 要旋转的点
	/// @param angle [IN] 指定弧度
	/// @return 旋转后点的位置
	template <class _Ty>
	inline INVDK::Point_<_Ty> getRotatePoint2D(const INVDK::Point_<_Ty>& point, const INVDK_DOUBLE& angle)
	{
		INVDK::Point_<_Ty> rotatePoint;
		rotatePoint.x = point.x * INVDK::cos(angle) - point.y * INVDK::sin(angle);
		rotatePoint.y = point.x * INVDK::sin(angle) + point.y * INVDK::cos(angle);
		return rotatePoint;
	}

	/// @brief 3D 图形围绕指定轴进行旋转指定角度
	/// @tparam _Ty 点的类型
	/// @param point [IN] 要旋转的点
	/// @param angle [IN] 指定弧度
	/// @param mode [IN] 0: X轴	1: Y轴	2: Z轴
	/// @return 旋转后点的位置
	template <class _Ty>
	inline INVDK::Point3_<_Ty> getRotatePoint3D(const INVDK::Point3_<_Ty>& point, const INVDK_DOUBLE& angle, const INVDK_UINT mode = 0)
	{
		INVDK::Point3_<_Ty> rotatePoint;
		switch (mode)
		{
		case 0:
			rotatePoint.x = point.x;
			rotatePoint.y = point.y * INVDK::cos(angle) - point.z * INVDK::sin(angle);
			rotatePoint.z = point.y * INVDK::sin(angle) + point.z * INVDK::cos(angle);
			break;
		case 1:
			rotatePoint.x = point.z * INVDK::sin(angle) + point.x * INVDK::cos(angle);
			rotatePoint.y = point.y;
			rotatePoint.z = point.z * INVDK::cos(angle) - point.x * INVDK::sin(angle);
			break;
		case 2:
			rotatePoint.x = point.x * INVDK::cos(angle) - point.y * INVDK::sin(angle);
			rotatePoint.y = point.x * INVDK::sin(angle) + point.y * INVDK::cos(angle);
			rotatePoint.z = point.z;
			break;
		default:
			throw INVDK::Exception(INVDK_T("Rotation mode input error"));
			break;
		}
		return rotatePoint;
	}

}

#endif // !INVDK_GEOMETRY_HPP
