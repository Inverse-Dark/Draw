#ifndef INVDKUI_NAMESPACE_H
#define INVDKUI_NAMESPACE_H

#include "INVDKUI_Data.h"

namespace INVDKUI
{
	enum BaseColor
	{
		Black = 0x00000000,	// 黑色
		Navy = 0xFF000080,	// 海军蓝
		Green = 0xFF008000,	// 绿色
		Maroon = 0xFF800000,	// 褐色
		Teal = 0xFF008080,	// 蓝绿
		Purple = 0xFF800080,	// 紫色
		Olive = 0xFF808000,	// 橄榄色
		Gray = 0xFF808080,	// 灰色
		Silver = 0xFFC0C0C0,	// 银色
		Red = 0xFFFF0000,	// 红色
		Lime = 0xFF00FF00,	// 鲜绿色
		Blue = 0xFF0000FF,	// 蓝色
		Fuchsia = 0xFFFF00FF,	// 紫红色
		Yellow = 0xFFFFFF00,	// 黄色
		Aqua = 0xFF00FFFF,	// 水绿色
		White = 0xFFFFFFFF,	// 白色
	};

	enum WindowType
	{
		WindowTitleHint = 0b00000001,		// 隐藏标题栏

		WindowMinimizeButtonHint = 0b00000010,	// 隐藏最小化按钮
		WindowMaximizeButtonHint = 0b00000100,	// 隐藏最大化按钮
		WindowMinMaxButtonsHint = WindowMinimizeButtonHint | WindowMaximizeButtonHint,	// 隐藏最小化和最大化按钮

		WindowStaysOnTopHint = 0b10000000,	// 窗口置顶
	};

}


#endif // !INVDKUI_NAMESPACE_H
