/**
 * @File: INVDKUI_MessageBox.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/4/29
 * @Description: 弹窗类
 */
#ifndef INVDKUI_MESSAGEBOX_H
#define INVDKUI_MESSAGEBOX_H

#include "INVDKUI_QCustomWindow.h"

class QTimer;
class QFrame;
class QSpacerItem;
namespace INVDKUI
{
	/// @brief 弹窗类
	/// @note 该类继承自QCustomWindow，提供了一个弹窗类。
	class INVDKUI_SDK_API MessageBox :
		public QCustomWindow
	{
		Q_OBJECT
	public:
		enum ButtonInfo
		{
			No = 0,
			Yes = 1
		};
	public:
		/// @brief 单例化对象
		/// @param parent [IN] 父窗口
		/// @return
		static MessageBox* Instance(QWidget* parent = NULL);
		/// @brief 释放内存
		/// @return
		static INVDK_VOID destroy();

		/// @brief 设置确认图标
		/// @param iconPath [IN] 图标路径
		/// @return
		INVDK_VOID setConfirmIcon(INVDK::String iconPath);
		/// @brief 设置取消图标
		/// @param iconPath [IN] 图标路径
		/// @return
		INVDK_VOID setCancelIcon(INVDK::String iconPath);

		/// @brief 弹出消息框
		/// @param title [IN] 标题
		/// @param info [IN] 弹窗信息
		/// @param closeSecond [IN] 关闭秒数
		/// @return
		static INVDK_VOID showMessageBoxInfo(const INVDK::String& title, const INVDK::String& info, int closeSecond = 0);
		/// @brief 弹出错误框
		/// @param title [IN] 标题
		/// @param info [IN] 弹窗信息
		/// @param closeSecond [IN] 关闭秒数
		/// @return
		static INVDK_VOID showMessageBoxError(const INVDK::String& title, const INVDK::String& info, int closeSecond = 0);
		/// @brief 弹出询问框
		/// @param title [IN] 标题
		/// @param info [IN] 弹窗信息
		/// @return 点击确认返回Yes，点击取消返回No
		static ButtonInfo showMessageBoxQuestion(const INVDK::String& title, const INVDK::String& info);
	private:
		/// @brief 构造函数
		/// @param parent [IN] 父窗体的指针
		explicit MessageBox(QWidget* parent = NULL);
		/// @brief 析构函数
		virtual ~MessageBox() override;
		/// @brief 初始化窗口
		/// @return
		INVDK_VOID initWidget();
		/// @brief 初始化连接的信号
		/// @return
		INVDK_VOID initSignals();
		/// @brief 检测显示时间是否结束
		/// @return
		INVDK_VOID checkSecond();
	protected:
		/// @brief 显示事件
		/// @param event [IN] 事件指针
		/// @return
		virtual INVDK_VOID showEvent(QShowEvent* event) override;
		/// @brief 隐藏事件
		/// @param event [IN] 事件指针
		/// @return
		virtual INVDK_VOID hideEvent(QHideEvent* event) override;
	private slots:
		/// @brief 设置弹窗属性
		/// @param title [IN] 标题
		/// @param msg [IN] 弹窗信息
		/// @param type [IN] 弹窗类型
		/// @param closeSecond [IN] 关闭秒数
		/// @return
		void setMessage(const INVDK::String& title, const INVDK::String& msg, int type = 0, int closeSecond = 0);
		/// @brief 确认按钮
		/// @return
		void OnOKClicked();
		/// @brief 关闭按钮
		/// @return
		void OnCloseClicked();
	private:
		static MessageBox* s_pMessageBox;	// 单例化对象

		INVDK_INT m_closeSecond;	// 总共显示的时间
		INVDK_INT m_currentSecond;	// 当前已经显示的时间

		QTimer* m_pTimer;	// 定时器
	private:	// 界面
		QVBoxLayout* m_pVerticalLayoutMain;	// 包含整个主窗体的垂直布局
		QFrame* m_pFrame;	// 主界面
		QVBoxLayout* m_pVerticalLayoutInfo;	// 包含信息图标与信息及按钮的垂直布局
		QHBoxLayout* m_pHorizontalLayoutInfo;	// 包含信息图标与信息的水平布局
		QLabel* m_pLabelIcoMain;	// 信息图标
		QSpacerItem* m_pHorizontalSpacerInfo;	// 水平间距
		QLabel* m_pLabelInfo;	// 信息
		QHBoxLayout* m_pHorizontalLayoutButton;	// 包含按钮的水平布局
		QSpacerItem* m_pHorizontalSpacerButton;	// 水平间距
		QPushButton* m_pPushButtonConfirm;	// 确认按钮
		QPushButton* m_pPushButtonCancel;	// 取消按钮
	};

}

#endif // !INVDKUI_MESSAGEBOX_H