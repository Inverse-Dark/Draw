#pragma once

#include "INVDKUI_QCustomWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ColorPickerWidget; }
QT_END_NAMESPACE

class ColorPickerWidget : public INVDKUI::QCustomWindow
{
	Q_OBJECT

public:
	/// @brief 单例化对象
	/// @return 单例化对象
	static ColorPickerWidget* Instance(QDialog* parent = nullptr);
	/// @brief 释放内存
	/// @return
	static void destroy();

protected:
	/// @brief 鼠标按下事件
	/// @param event [IN] 事件指针
	/// @return
	virtual void mousePressEvent(QMouseEvent* event) override;
	/// @brief 鼠标释放事件
	/// @param event [IN] 事件指针
	/// @return
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	/// @brief 鼠标移动事件
	/// @param event [IN] 事件指针
	/// @return
	virtual void mouseMoveEvent(QMouseEvent* event) override;

signals:
	/// @brief 提交吸取的颜色
	/// @param r [IN] Red 通道的值
	/// @param g [IN] Green 通道的值
	/// @param b [IN] Blue 通道的值
	/// @param a [IN] Alpha 通道的值
	/// @return
	void ColorPicker(int r, int g, int b, int a);

private slots:
	/// @brief 保存按钮
	/// @return
	void OnSaveClicked();
	/// @brief 取消按钮
	/// @return
	void OnCancelClicked();

private:
	/// @brief 构造函数
	explicit ColorPickerWidget(QWidget* parent = nullptr);
	/// @brief 析构函数
	~ColorPickerWidget();

	/// @brief 初始化窗口
	/// @return
	void initWidget();
	/// @brief 初始化连接的信号
	/// @return
	void initSignals();

private:
	Ui::ColorPickerWidget* ui;

	static ColorPickerWidget* s_pColorPickerWidget; // 单例化对象

	INVDK_INT m_red;    // Red 通道的值
	INVDK_INT m_green;  // Green 通道的值
	INVDK_INT m_blue;   // Blue 通道的值
	INVDK_INT m_alpha;  // Alpha 通道的值
	INVDK_BOOL m_bPickerColor; // 是否取色状态
};