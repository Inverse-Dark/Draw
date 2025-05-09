/**
 * @File: INVDK_Errno.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: 错误码
 */
#ifndef INVDK_ERRNO_H
#define INVDK_ERRNO_H

#include "INVDK_Data.h"

INVDK_SDK_API INVDK_INT INVDK_errno; // 错误码

#define INVDK_NORMAL	(0)	/* 正常 */
#define	INVDK_INVALID	(1)	/* 无效 */
#define INVDK_ERANGE	(2)	/* 溢出 */

#endif	// !INVDK_ERRNO_H
