/**
 * @File: INVDK_Math.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: 数学函数
 */
#ifndef INVDK_MATH_H
#define INVDK_MATH_H

#include "INVDK_Data.h"

namespace INVDK
{
#define INVDK_PI				(3.14159265358979323846)	/* pi */
#define INVDK_PI_2				(1.57079632679489661923)	/* pi/2 */
#define INVDK_PI_4				(0.785398163397448309616)	/* pi/4 */
#define INVDK_1_PI				(0.318309886183790671538)	/* 1/pi */
#define INVDK_2_PI				(0.636619772367581343076)	/* 2/pi */

#ifndef INVDK_TINY_VALUE
#	define INVDK_TINY_VALUE	(1e-20)						/* 最小精度 */
#endif
#ifndef INVDK_HUGE_ENUF
#	define INVDK_HUGE_ENUF		1e+300  /* INVDK_HUGE_ENUF*INVDK_HUGE_ENUF 必须溢出 */
#endif
#define INVDK_INFINITY			((INVDK_FLOAT)INVDK_HUGE_ENUF * INVDK_HUGE_ENUF)	/* 无穷 */
#define INVDK_HUGE_VAL			((INVDK_DOUBLE)INVDK_INFINITY)
#define INVDK_HUGE_VALF			((INVDK_FLOAT)INVDK_INFINITY)
#define INVDK_HUGE_VALL			((INVDK_LDOUBLE)INVDK_INFINITY)

#define INVDK_DBL_EPSILON      2.2204460492503131e-016		/* INVDK_DOUBLE 类型能够区分出来的最小差异 */

// 角度 转 弧度
#define INVDK_Angle2Radians(A)	(A * INVDK_PI / 180)
// 弧度 转 角度
#define INVDK_Radians2Angle(R)	(R * 180 / INVDK_PI)

// 获取 A 与 B 中最大的数
#define INVDK_MAX(A, B)			((A) > (B) ? (A) : (B))
// 获取 A 与 B 中最小的数
#define INVDK_MIN(A, B)			((A) < (B) ? (A) : (B))
// 获取 A 的绝对值
#define INVDK_abs(A)			((A) < (0) ? -(A) : (A))

	/// @brief 判断指定值是否无穷大
	/// @param _X [IN] 要判断的值
	/// @return TRUE: 是无穷大	FALSE: 不是无穷大
	INVDK_SDK_API INVDK_BOOL isinf(INVDK_DOUBLE _X);
	/// @brief 判断指定值是否是数字
	/// @param _X [IN] 要判断的值
	/// @return TRUE: 不是数字	FALSE: 是数字
	INVDK_SDK_API INVDK_BOOL isnan(INVDK_DOUBLE _X);

	/// @brief 计算给定数的指数幂
	/// @param _X [IN] 底数，可以是任意实数
	/// @param _Y [IN] 指数，可以是任意实数
	/// @return _X 的 _Y 次幂的结果
	INVDK_SDK_API INVDK_DOUBLE pow(INVDK_DOUBLE _X, INVDK_DOUBLE _Y);

	/// @brief 计算给定数的平方根
	/// @param _X [IN] 需要计算平方根的数，必须大于 0
	/// @return _X 的平方根，如果 _X <= 0，则返回 0
	INVDK_SDK_API INVDK_DOUBLE sqrt(INVDK_DOUBLE _X);

	/// @brief 计算给定弧度的正弦值(对边/斜边)
	/// @param _X [IN] 需要计算正弦的弧度
	/// @return _X 的正弦值
	INVDK_SDK_API INVDK_DOUBLE sin(INVDK_DOUBLE _X);

	/// @brief 计算给定正弦值的角度
	/// @param _X [IN] 需要计算的正弦值
	/// @return 给定正弦值角度
	INVDK_SDK_API INVDK_DOUBLE asin(INVDK_DOUBLE _X);

	/// @brief 计算给定弧度的余弦值(斜边/邻边)
	/// @param _X 需要计算余弦的弧度
	/// @return _X 的余弦值
	INVDK_SDK_API INVDK_DOUBLE cos(INVDK_DOUBLE _X);

	/// @brief 计算给定余弦值的角度
	/// @param _X [IN] 需要计算的余弦值
	/// @return 给定余弦值角度
	INVDK_SDK_API INVDK_DOUBLE acos(INVDK_DOUBLE _X);

	/// @brief 计算给定弧度的正切值(sin(θ)/cos(θ))
	/// @param _X [IN] 需要计算正切的弧度
	/// @return _X 的正切值，或者在余弦值为零时返回 INVDK_HUGE_VAL
	INVDK_SDK_API INVDK_DOUBLE tan(INVDK_DOUBLE _X);

	/// @brief 计算给定弧度的余切值(cos(θ)/sin(θ))
	/// @param _X [IN] 需要计算余切的弧度
	/// @return _X 的余切值，或者在正弦值为零时返回 INVDK_HUGE_VAL
	INVDK_SDK_API INVDK_DOUBLE cot(INVDK_DOUBLE _X);

	/// @brief 计算给定弧度的正割值(1/cos(θ))
	/// @param _X [IN] 需要计算正割的弧度
	/// @return _X 的正割值，或者在余弦值为零时返回 INVDK_HUGE_VAL
	INVDK_SDK_API INVDK_DOUBLE sec(INVDK_DOUBLE _X);

	/// @brief 计算给定弧度的余割值(1/sin(θ))
	/// @param _X [IN] 需要计算余割的角度
	/// @return _X 的余割值，或者在正弦值为零时返回 INVDK_HUGE_VAL
	INVDK_SDK_API INVDK_DOUBLE csc(INVDK_DOUBLE _X);

}

#endif // !INVDK_MATH_H
