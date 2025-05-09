/**
 * @File: INVDKUI_RGB.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/5/7
 * @Description: 颜色类型
 */
#ifndef INVDKUI_RGB_H
#define INVDKUI_RGB_H

#include "INVDKUI_Data.h"

namespace INVDKUI
{
	/// @brief 颜色掩码
	const INVDKUI_RGB RGB_MASK = 0x00FFFFFF;

	/// @brief 获取颜色的红色分量
	/// @param rgb [IN] 颜色值
	/// @return 红色分量
	INVDKUI_SDK_API INVDK_INT red(INVDKUI_RGB rgb);
	/// @brief 获取颜色的绿色分量
	/// @param rgb [IN] 颜色值
	/// @return 绿色分量
	INVDKUI_SDK_API INVDK_INT green(INVDKUI_RGB rgb);
	/// @brief 获取颜色的蓝色分量
	/// @param rgb [IN] 颜色值
	/// @return 蓝色分量
	INVDKUI_SDK_API INVDK_INT blue(INVDKUI_RGB rgb);
	/// @brief 获取颜色的透明度分量
	/// @param rgb [IN] 颜色值
	/// @return 透明度分量
	INVDKUI_SDK_API INVDK_INT alpha(INVDKUI_RGB rgb);

	/// @brief 设置颜色值
	/// @param r [IN] 红色分量
	/// @param g [IN] 绿色分量
	/// @param b [IN] 蓝色分量
	/// @return 颜色值
	INVDKUI_SDK_API INVDKUI_RGB rgb(INVDK_INT r, INVDK_INT g, INVDK_INT b);
	/// @brief 设置颜色值
	/// @param r [IN] 红色分量
	/// @param g [IN] 绿色分量
	/// @param b [IN] 蓝色分量
	/// @param a [IN] 透明度分量
	/// @return 颜色值
	INVDKUI_SDK_API INVDKUI_RGB rgba(INVDK_INT r, INVDK_INT g, INVDK_INT b, INVDK_INT a);

	/// @brief 将RGB颜色转换为灰度值
	/// @param r [IN] 红色分量
	/// @param g [IN] 绿色分量
	/// @param b [IN] 蓝色分量
	/// @return 灰度值
	INVDKUI_SDK_API INVDK_INT gray(INVDK_INT r, INVDK_INT g, INVDK_INT b);
	/// @brief 将RGB颜色转换为灰度值
	/// @param rgb [IN] 颜色值
	/// @return 灰度值
	INVDKUI_SDK_API INVDK_INT gray(INVDKUI_RGB rgb);

	/// @brief 判断颜色是否为灰色
	/// @param rgb [IN] 颜色值
	/// @return TRUE: 灰色	FALSE: 非灰色
	INVDKUI_SDK_API INVDK_BOOL isGray(INVDKUI_RGB rgb);
}

#endif // !INVDKUI_RGB_H
