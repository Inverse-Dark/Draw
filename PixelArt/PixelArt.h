#pragma once

#include "INVDKUI_QCustomWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PixelArt; };
QT_END_NAMESPACE

class PixelArt : public INVDKUI::QCustomWindow
{
	Q_OBJECT

public:
	/// @brief 构造函数
	/// @param parent [IN] 父窗体的指针
	PixelArt(QWidget* parent = nullptr);
	/// @brief 析构函数
	~PixelArt();

private:
	/// @brief 初始化窗口
	/// @return
	virtual INVDK_VOID initWidget();
	/// @brief 初始化连接的信号
	/// @return
	virtual INVDK_VOID initSignals();
	/// @brief 初始化
	/// @return
	virtual INVDK_VOID initialization() override;

private slots:
	/// @brief 保存按钮
	/// @return
	void OnSaveClicked();
	/// @brief 打开文件按钮
	/// @return
	void OnOpenFileClicked();
	/// @brief 保存文件按钮
	/// @return
	void OnSaveFileClicked();

	/// @brief 改变 Red 通道的值
	/// @param value [IN] 新的 Red 通道值
	/// @return
	void OnRedValueChanged(int value);
	/// @brief 改变 Greed 通道的值
	/// @param value [IN] 新的 Greed 通道值
	/// @return
	void OnGreedValueChanged(int value);
	/// @brief 改变 Blue 通道的值
	/// @param value [IN] 新的 Blue 通道值
	/// @return
	void OnBlueValueChanged(int value);
	/// @brief 改变 Alpha 通道的值
	/// @param value [IN] 新的 Alpha 通道值
	/// @return
	void OnAlphaValueChanged(int value);

	/// @brief 清空画板
	/// @return
	void OnCleanClicked();
	/// @brief 打开取色器
	/// @return
	void OnColorPickerClicked();
	/// @brief 更换画画模式为 填充
	/// @return
	void OnBrushClicked();
	/// @brief 更换画画模式为 铅笔
	/// @return
	void OnPenClicked();
	/// @brief 更换画画模式为 橡皮擦
	/// @return
	void OnEraserClicked();

	/// @brief 获取画板中鼠标所在的坐标
	/// @param pos [IN] 当前鼠标所在的坐标
	/// @return
	void OnBoardPoint(INVDK::Point pos);
	/// @brief 获取吸取的颜色
	/// @param r [IN] Red 通道的值
	/// @param g [IN] Green 通道的值
	/// @param b [IN] Blue 通道的值
	/// @param a [IN] Alpha 通道的值
	/// @return
	void OnColorPicker(int r, int g, int b, int a);

protected:
	/// @brief 显示事件
	/// @param event [IN] 事件指针
	/// @return
	virtual INVDK_VOID showEvent(QShowEvent* event) override;
	/// @brief 大小改变事件
	/// @param event [IN] 事件指针
	/// @return
	virtual INVDK_VOID resizeEvent(QResizeEvent* event) override;
	/// @brief 关闭事件
	/// @param event [IN] 事件指针
	/// @return
	virtual INVDK_VOID closeEvent(QCloseEvent* event) override;

private:
	Ui::PixelArt* ui;

	INVDK_INT m_red;    // Red 通道的值
	INVDK_INT m_green;  // Green 通道的值
	INVDK_INT m_blue;   // Blue 通道的值
	INVDK_INT m_alpha;  // Alpha 通道的值
	INVDKUI_RGB m_color;   // 上面4个通道合成的颜色 ARGB
};
