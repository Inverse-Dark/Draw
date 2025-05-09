/**
 * @File: INVDKUI_Geometry.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/4/17
 * @Description: INVDK的几何类与Qt的几何类的转换
 */
#ifndef INVDKUI_GEOMETRY_H
#define INVDKUI_GEOMETRY_H

#include <QMetaType>

#include "INVDKUI_Data.h"
#include "INVDK_Geometry.hpp"

namespace INVDKUI
{
	/// @brief 将INVDK::Point注册为QMetaType
	/// @return 
	INVDKUI_SDK_API INVDK_VOID registerInvdkPointMetaType();
	/// @brief 将INVDK::Size注册为QMetaType
	/// @return 
	INVDKUI_SDK_API INVDK_VOID registerInvdkSizeMetaType();
	/// @brief 将INVDK::Rect注册为QMetaType
	/// @return 
	INVDKUI_SDK_API INVDK_VOID registerInvdkRectMetaType();

	/// @brief 将QPoint转换为INVDK::Point
	/// @param point [IN] QPoint对象
	/// @return INVDK::Point对象
    INVDKUI_SDK_API INVDK::Point qpoint_to_invdkPoint(const QPoint& point);
	/// @brief 将INVDK::Point转换为QPoint
	/// @param point [IN] INVDK::Point对象
	/// @return QPoint对象
	INVDKUI_SDK_API QPoint invdkPoint_to_qpoint(const INVDK::Point& point);

	/// @brief 将QSize转换为INVDK::Size
	/// @param size [IN] QSize对象
	/// @return INVDK::Size对象
	INVDKUI_SDK_API INVDK::Size qsize_to_invdkSize(const QSize& size);
	/// @brief 将INVDK::Size转换为QSize
	/// @param size [IN] INVDK::Size对象
	/// @return QSize对象
	INVDKUI_SDK_API QSize invdkSize_to_qsize(const INVDK::Size& size);

	/// @brief 将QRect转换为INVDK::Rect
	/// @param rect [IN] QRect对象
	/// @return INVDK::Rect对象
	INVDKUI_SDK_API INVDK::Rect qrect_to_invdkRect(const QRect& rect);
	/// @brief 将INVDK::Rect转换为QRect
	/// @param rect [IN] INVDK::Rect对象
	/// @return QRect对象
	INVDKUI_SDK_API QRect invdkRect_to_qrect(const INVDK::Rect& rect);
}

#endif // !INVDKUI_GEOMETRY_H
