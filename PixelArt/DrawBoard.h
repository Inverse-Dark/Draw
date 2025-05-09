#pragma once

#include <QWidget>

#include "INVDK_Vector.hpp"
#include "INVDKUI_Geometry.h"

class DrawBoard  : public QWidget
{
	Q_OBJECT

public:
	/// @brief 构造函数
	DrawBoard(QWidget *parent = NULL);
	/// @brief 析构函数
	~DrawBoard();

    /// @brief 获取画板的行数
    /// @return 行数
    INVDK_INT getRows() const;
    /// @brief 修改画板的行数
    /// @param newRows [IN] 画板的新行数
    /// @return
    INVDK_VOID setRows(INVDK_INT newRows);
    /// @brief 获取画板的列数
    /// @return 列数
    INVDK_INT getCols() const;
    /// @brief 修改画板的列数
    /// @param newCols [IN] 画板的新列数
    /// @return
    INVDK_VOID setCols(INVDK_INT newCols);

    /// @brief 获取绘画数据
    /// @return 绘画数据
    const QImage& getImage() const;
    /// @brief 更新图片
    /// @param newImage [IN] 新的图片
    /// @return
    INVDK_VOID setImage(const QImage& newImage);

    /// @brief 设置绘画的颜色
    /// @param newDrawColor [IN] 新的绘画颜色
    /// @return
    INVDK_VOID setDrawColor(const INVDKUI_RGB& newDrawColor);
    /// @brief 设置绘画模式
    /// @param drawMode [IN] 新的绘画模式
    /// @return
    INVDK_VOID setDrawMode(INVDK_INT drawMode);

    /// @brief 获取当前是否修改了图像
    /// @return 当前状态
    INVDK_BOOL getModify();
    /// @brief 获取当前是否修改了图像
    /// @param state [IN] 新的状态
    /// @return
    INVDK_VOID setModify(INVDK_BOOL state);
signals:
    /// @brief 提交画板的点
    /// @param pos [IN] 画板的坐标
    /// @return
    void boardPoint(INVDK::Point pos);
protected:
	/// @brief 绘制事件
	/// @param event [IN] 事件指针
	/// @return
	virtual INVDK_VOID paintEvent(QPaintEvent* event) override;
	/// @brief 鼠标按下事件
	/// @param event [IN] 事件指针
	/// @return
    virtual INVDK_VOID mousePressEvent(QMouseEvent* event) override;
	/// @brief 鼠标释放事件
	/// @param event [IN] 事件指针
	/// @return
    virtual INVDK_VOID mouseReleaseEvent(QMouseEvent* event) override;
	/// @brief 鼠标移动事件
	/// @param event [IN] 事件指针
	/// @return
    virtual INVDK_VOID mouseMoveEvent(QMouseEvent* event) override;
	/// @brief 滚轮事件
	/// @param event [IN] 事件指针
	/// @return
    virtual INVDK_VOID wheelEvent(QWheelEvent* event) override;
	/// @brief 显示事件
	/// @param event [IN] 事件指针
	/// @return
    virtual INVDK_VOID resizeEvent(QResizeEvent* event) override;
private:
    /// @brief 初始化窗口
    /// @return
    INVDK_VOID initWidget();
    /// @brief 初始化连接的信号
    /// @return
    INVDK_VOID initSignals();

    /// @brief 填充相同颜色的相连区域为当前绘画颜色
    /// @param x [IN] X轴坐标
    /// @param y [IN] Y轴坐标
    /// @param srcRgb [IN] 原颜色
    /// @return
    INVDK_VOID brush(INVDK_INT x, INVDK_INT y, INVDKUI_RGB srcRgb);

	/// @brief 绘制
	/// @param pt [IN] 坐标
	/// @return
    INVDK_VOID drawPixel(INVDK::Point pt);

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
private:
    INVDK_INT m_rows;   // 行
    INVDK_INT m_cols;   // 列

    INVDK_BOOL m_bModify;   // 是否修改了绘制的图像
    INVDK_BOOL m_bDraw; // 左键点击：开始绘画
    INVDK_BOOL m_bMove; // 右键点击：移动画布
    INVDK_INT m_drawMode;   // 绘画模式：1.绘画 2.橡皮擦 3.填充

    INVDK::Point m_ptLBtnDown;	// 左键点击位置
    INVDK::Point m_ptRBtnDown;	// 右键点击位置

    INVDKUI_RGB m_drawColor;   // 当前绘画的颜色

    QImage m_image;	// 显示的图片

	INVDK_FLOAT m_dScale;	// 显示比例

    INVDK::Rect m_rectTarget;	// 绘制的指定区域
    INVDK::Rect m_rectSource;	// 绘制图片的指定区域
};
