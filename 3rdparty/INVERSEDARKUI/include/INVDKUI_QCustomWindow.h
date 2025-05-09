/**
 * @File: INVDKUI_QCustomWindow.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/4/10
 * @Description: 自定义窗口
 */
#ifndef INVDKUI_QCUSTOMWINDOW_H
#define INVDKUI_QCUSTOMWINDOW_H

#include <QDialog>

#include "INVDKUI_Data.h"
#include "INVDKUI_NameSpace.h"
#include "INVDKUI_Geometry.h"
#include "INVDK_String.h"

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
namespace INVDKUI
{
	
	/// @brief 自定义窗口类
	/// @note 该类继承自QDialog，提供了一个自定义的窗口类，可以在此基础上进行扩展和定制。
	class INVDKUI_SDK_API QCustomWindow :
		public QDialog
	{
		Q_OBJECT
	public:
		/// @brief 构造函数
		/// @param parent [IN] 父窗体的指针
		explicit QCustomWindow(QWidget* parent = NULL);
		/// @brief 析构函数
		virtual ~QCustomWindow() override;

		/// @brief 最大化窗口
		/// @return
		INVDK_VOID showMaximized();
		/// @brief 恢复窗口
		/// @return
		INVDK_VOID showNormal();
		/// @brief 设置标题
		/// @param title [IN] 标题文本
		/// @return
		INVDK_VOID setTitle(INVDK::String title);
		/// @brief 设置样式
		/// @param styleFilePath [IN] 样式文件路径
		/// @return
		INVDK_VOID setStyleFilePath(INVDK::String styleFilePath);
		/// @brief 设置软件图标
		/// @param iconPath [IN] 图标路径
		/// @return
		INVDK_VOID setApplicationIcon(INVDK::String iconPath);
		/// @brief 设置窗体图标
		/// @param iconPath [IN] 图标路径
		/// @return
		INVDK_VOID setWindowIcon(INVDK::String iconPath);
		/// @brief 设置最小化按钮图标
		/// @param iconPath [IN] 图标路径
		/// @return
		INVDK_VOID setMinButtonIcon(INVDK::String iconPath);
		/// @brief 设置最大化按钮图标
		/// @param iconPath [IN] 图标路径
		/// @return
		INVDK_VOID setMaxButtonIcon(INVDK::String iconPath);
		/// @brief 设置关闭按钮图标
		/// @param iconPath [IN] 图标路径
		/// @return
		INVDK_VOID setCloseButtonIcon(INVDK::String iconPath);

		/// @brief 设置窗体标志
		/// @param flags [IN] 窗体标志
		/// @return
		INVDK_VOID setWindowFlags(INVDK_UINT flags);
	private:
		/// @brief 初始化窗口
		/// @return
		virtual INVDK_VOID initWidget();
		/// @brief 初始化连接的信号
		/// @return
		virtual INVDK_VOID initSignals();

		/// @brief 更新标题栏的可见性
		/// @return
		INVDK_VOID updateTitleBarVisibility();
	protected:
		/// @brief 初始化
		/// @return
		virtual INVDK_VOID initialization();

		/// @brief 关闭事件
		/// @param event [IN] 事件指针
		/// @return
		virtual INVDK_VOID closeEvent(QCloseEvent* event) override;
		/// @brief 鼠标点击事件
		/// @param event [IN] 事件指针
		/// @return
		virtual INVDK_VOID mousePressEvent(QMouseEvent* event) override;
		/// @brief 鼠标松开事件
		/// @param event [IN] 事件指针
		/// @return
		virtual INVDK_VOID mouseReleaseEvent(QMouseEvent* event) override;
		/// @brief 鼠标移动事件
		/// @param event [IN] 事件指针
		/// @return
		virtual INVDK_VOID mouseMoveEvent(QMouseEvent* event) override;
		/// @brief 显示事件
		/// @param event [IN] 事件指针
		/// @return
		virtual INVDK_VOID showEvent(QShowEvent* event) override;
		/// @brief 隐藏事件
		/// @param event [IN] 事件指针
		/// @return
		virtual INVDK_VOID hideEvent(QHideEvent* event) override;
		/// @brief 改变事件
		/// @param event [IN] 事件指针
		/// @return
		virtual INVDK_VOID changeEvent(QEvent* event) override;
	protected slots:
		/// @brief 最小化按钮
		/// @return
		virtual void OnMinClicked();
		/// @brief 最大化按钮
		/// @return
		virtual void OnMaxClicked();
		/// @brief 关闭按钮
		/// @return
		virtual void OnCloseClicked();

	protected:    // 界面标题栏
		QVBoxLayout* m_pVerticalLayoutFrame;	// 包含整个界面的垂直布局

		QWidget* m_pWidgetTitle;	// 标题
		QHBoxLayout* m_pHorizontalLayoutTitle;	// 包含整个标题的水平布局
		QLabel* m_pLabelIco;	// 标题图标
		QLabel* m_pLabelTitle;	// 标题文本
		QLabel* m_pLabelTime;	// 剩余时间
		QWidget* m_pWidgetMenu;	// 菜单按钮
		QHBoxLayout* m_pHorizontalLayoutMenu;	// 包含菜单按钮的水平布局
		QPushButton* m_pPushButtonMin;	// 最小化按钮
		QPushButton* m_pPushButtonMax;	// 最大化按钮
		QPushButton* m_pPushButtonClose;	// 关闭按钮

		QWidget* m_pWidgetMain;	// 主窗体
	private:
		INVDK_BOOL m_bMax;  // 是否最大化
		INVDK_BOOL m_bPressed;    // 是否点击标题栏
		INVDK::Point m_lastPos;   // 鼠标最后点击的坐标与当前坐标的差值
		INVDK::String m_title;	// 标题文本
	};

}

#endif // !INVDKUI_QCUSTOMWINDOW_H



