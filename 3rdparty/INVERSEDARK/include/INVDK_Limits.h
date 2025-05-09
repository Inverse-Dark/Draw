/**
 * @File: INVDK_Limits.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: 各个类型的极限
 */
#ifndef INVDK_LIMITS_H
#define INVDK_LIMITS_H

#define INVDK_DOUBLE_MIN ((INVDK_DOUBLE)2.22507385850720138309023271733240406e-308L)
#define INVDK_DOUBLE_MAX ((INVDK_DOUBLE)1.79769313486231570814527423731704357e+308L)

#define INVDK_CHAR_Bit (8)	   /* INVDK_CHAR 的位数 */
#define INVDK_CHAR_MIN (-128)  /* INVDK_CHAR 最小值 */
#define INVDK_CHAR_MAX (127)   /* INVDK_CHAR 最大值 */
#define INVDK_UCHAR_MAX (0xff) /* INVDK_UCHAR 最大值 */

#define INVDK_SHORT_MIN (-32767 - 1)				  /* INVDK_SHORT 最小值 */
#define INVDK_SHORT_MAX (32767)						  /* INVDK_SHORT 最大值 */
#define INVDK_USHORT_MAX (0xffff)					  /* INVDK_USHORT 最大值 */
#define INVDK_INT_MIN (-2147483647 - 1)				  /* INVDK_INT 最小值 */
#define INVDK_INT_MAX (2147483647)					  /* INVDK_INT 最大值 */
#define INVDK_UINT_MAX (0xffffffff)					  /* INVDK_UINT 最大值 */
#define INVDK_LONG_MIN (-2147483647L - 1)			  /* INVDK_LONG 最小值 */
#define INVDK_LONG_MAX (2147483647L)				  /* INVDK_LONG 最大值 */
#define INVDK_ULONG_MAX (0xffffffffUL)				  /* INVDK_ULONG 最大值 */
#define INVDK_LLONG_MIN (-9223372036854775807i64 - 1) /* INVDK_LLONG 最小值 */
#define INVDK_LLONG_MAX (9223372036854775807i64)	  /* INVDK_LLONG 最大值 */
#define INVDK_ULLONG_MAX (0xffffffffffffffffui64)	  /* INVDK_ULLONG 最大值 */

#define INVDK_I8_MIN (-127i8 - 1) /* 8位 整数 最小值 */
#define INVDK_I8_MAX (127i8)	  /* 8位 整数 最大值 */
#define INVDK_UI8_MAX (0xffui8)	  /* 8位 无符号整数 最大值 */

#define INVDK_I16_MIN (-32767i16 - 1) /* 16位 整数 最小值 */
#define INVDK_I16_MAX (32767i16)	  /* 16位 整数 最大值 */
#define INVDK_UI16_MAX (0xffffui16)	  /* 16位 无符号整数 最大值 */

#define INVDK_I32_MIN (-2147483647i32 - 1) /* 32位 整数 最小值 */
#define INVDK_I32_MAX (2147483647i32)	   /* 32位 整数 最大值 */
#define INVDK_UI32_MAX (0xffffffffui32)	   /* 32位 无符号整数 最大值 */

#define INVDK_I64_MIN (-9223372036854775807i64 - 1) /* 64位 整数 最小值 */
#define INVDK_I64_MAX (9223372036854775807i64)		/* 64位 整数 最大值 */
#define INVDK_UI64_MAX (0xffffffffffffffffui64)		/* 64位 无符号整数 最大值 */

#endif // !INVDK_LIMITS_H
