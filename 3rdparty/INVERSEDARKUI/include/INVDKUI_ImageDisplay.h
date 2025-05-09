/**
 * @File: INVDKUI_ImageDisplay.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/4/29
 * @Description: 图像显示界面
 */
#ifndef INVDKUI_IMAGEDISPLAY_H
#define INVDKUI_IMAGEDISPLAY_H

#include "INVDKUI_QCustomWindow.h"

namespace INVDKUI
{
    class INVDKUI_SDK_API ImageDisplay :
        public QCustomWindow
    {
        Q_OBJECT
	public:
		/// @brief 构造函数
		/// @param parent [IN] 父窗体的指针
		explicit ImageDisplay(QWidget* parent = NULL);
		/// @brief 析构函数
		virtual ~ImageDisplay() override;

		/// @brief 从文件中加载图片显示
		/// @param imgPath [IN] 图片的文件路径
		/// @return
		INVDK_VOID showImage(const INVDK::String& imgPath);
		/// @brief 显示图片
		/// @param image [IN] 要显示的图片
		/// @return
		INVDK_VOID showImage(const QImage& image);
	private:
		/// @brief 计算缩放图片后的位置
		/// @return
		INVDK_VOID rescaleImg();

		/// @brief 计算放大后图片显示的位置
		/// @param zoomCenter [IN] 放大中心点
		/// @return
		INVDK_VOID zoomOut(const INVDK::Point& zoomCenter);
		/// @brief 计算缩小后图片显示的位置
		/// @param zoomCenter [IN] 缩小中心点
		/// @return
		INVDK_VOID zoomIn(const INVDK::Point& zoomCenter);

		/// @brief 控件坐标转换为图像坐标
		/// @param pt [IN] 要转换的坐标
		/// @return 转换后的坐标
		INVDK::Point widget2Image(const INVDK::Point& pt);

		/// @brief 绘制图像
		/// @return
		INVDK_VOID paintImage();
	protected:
		/// @brief 事件过滤器
		/// @param obj [IN] 事件对象
		/// @param event [IN] 事件指针
		/// @return TRUE: 事件被处理	FALSE: 事件未被处理
		INVDK_BOOL eventFilter(QObject* obj, QEvent* event) override;
    private:
		QImage m_image;	// 显示的图片

		INVDK_FLOAT m_dScale;	// 显示比例

		INVDK::Rect m_rectTarget;	// 绘制的指定区域
		INVDK::Rect m_rectSource;	// 绘制图片的指定区域

		INVDK::Point m_ptLBtnDown;	// 左键点击位置
		INVDK::Point m_ptRBtnDown;	// 右键点击位置
    };
}

#endif // !INVDKUI_IMAGEDISPLAY_H
