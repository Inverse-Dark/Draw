#include "DrawBoard.h"
#include "INVDKUI_RGB.h"
#include "INVDK_Math.h"

#include <QPainter>
#include <QMouseEvent>

DrawBoard::DrawBoard(QWidget* parent)
	: QWidget(parent)
{
	initWidget();	// 初始化界面
	initSignals();	// 初始化信号
}

DrawBoard::~DrawBoard()
{}

INVDK_VOID DrawBoard::initWidget()
{
	// 启用鼠标追踪
	this->setMouseTracking(TRUE);

	m_rows = 16;	// 行数
	m_cols = 16;	// 列数

	m_bModify = FALSE;	// 是否修改
	m_bDraw = FALSE;	// 是否绘制
	m_bMove = FALSE;	// 是否移动

	m_drawMode = 1;	// 绘制模式：1.绘制 2.橡皮擦 3.填充

	m_ptLBtnDown = INVDK::Point(-1, -1);	// 左键点击位置
	m_ptRBtnDown = INVDK::Point(-1, -1);	// 左键点击位置

	m_drawColor = INVDKUI::rgb(0xFF, 0xFF, 0xFF);	// 当前绘制的颜色

	m_image = QImage(m_cols, m_rows, QImage::Format_ARGB32);	// 显示的图片
	m_image.fill(Qt::white);

	m_dScale = 1.0f;	// 显示比例

	m_rectTarget = INVDK::Rect(0, 0, 0, 0);	// 绘制的指定区域
	m_rectSource = INVDK::Rect(0, 0, 0, 0);	// 绘制图片的指定区域
}

INVDK_VOID DrawBoard::initSignals()
{}

INVDK_VOID DrawBoard::brush(INVDK_INT x, INVDK_INT y, INVDKUI_RGB srcRgb)
{
	// 检查坐标是否在绘图板的边界内
	if (x < 0 || x >= m_cols || y < 0 || y >= m_rows)
		return;

	// 点击的坐标所在的颜色
	INVDKUI_RGB curRgb = m_image.pixel(x, y);
	// 如果当前坐标的颜色与填充的颜色一致，那么返回
	if (curRgb == m_drawColor) return;
	// 如果当前坐标的颜色与被填充的颜色不一致，那么返回
	if (curRgb != srcRgb) return;

	// 更换新的颜色
	m_image.setPixel(x, y, m_drawColor);
	
	// 循环递归4个方向
	brush(x + 1, y, srcRgb);
	brush(x - 1, y, srcRgb);
	brush(x, y + 1, srcRgb);
	brush(x, y - 1, srcRgb);
}

INVDK_VOID DrawBoard::drawPixel(INVDK::Point pt)
{
	switch (m_drawMode)
	{
	case 1: // 笔
		m_image.setPixel(pt.x, pt.y, m_drawColor);
		break;
	case 2: // 橡皮擦
		// 擦成白色，并非透明色
		m_image.setPixel(pt.x, pt.y, 0xffffffff);
		break;
	case 3: // 填充
		brush(pt.x, pt.y, m_image.pixel(INVDKUI::invdkPoint_to_qpoint(pt)));
		break;
	}
}

INVDK_VOID DrawBoard::rescaleImg()
{
	INVDK_FLOAT hRatio = height() * 1.0 / m_image.height();
	INVDK_FLOAT wRatio = width() * 1.0 / m_image.width();
	m_dScale = INVDK_MAX(m_dScale, INVDK_MIN(hRatio, wRatio));

	INVDK_FLOAT targetLeft = INVDK_INT((width() - m_dScale * m_image.width()) / 2 + 0.5);
	INVDK_FLOAT targetTop = INVDK_INT((height() - m_dScale * m_image.height()) / 2 + 0.5);
	targetLeft = std::max(0.0f, targetLeft);
	targetTop = std::max(0.0f, targetTop);
	INVDK_FLOAT targetWidth = width() - 2 * targetLeft;
	INVDK_FLOAT targetHeight = height() - 2 * targetTop;
	m_rectTarget = INVDK::Rect(targetLeft, targetTop, targetWidth, targetHeight);

	INVDK_FLOAT sourceWidth = INVDK_INT(targetWidth / m_dScale + 0.5);
	INVDK_FLOAT sourceHeight = INVDK_INT(targetHeight / m_dScale + 0.5);
	INVDK_FLOAT sourceLeft = INVDK_MAX(0.0f, INVDK_FLOAT(m_rectSource.x));
	INVDK_FLOAT sourceTop = INVDK_MAX(0.0f, INVDK_FLOAT(m_rectSource.y));
	m_rectSource = INVDK::Rect(sourceLeft, sourceTop, sourceWidth, sourceHeight);
}

INVDK_VOID DrawBoard::zoomOut(const INVDK::Point& zoomCenter)
{
	INVDK_INT x = m_rectSource.x + INVDK_INT((zoomCenter.x - m_rectTarget.x) / m_dScale + 0.5) - m_rectTarget.x / m_dScale;
	INVDK_INT y = m_rectSource.y + INVDK_INT((zoomCenter.y - m_rectTarget.y) / m_dScale + 0.5) - m_rectTarget.y / m_dScale;
	m_dScale *= 1.1f;
	INVDK_INT x1 = x - INVDK_INT((zoomCenter.x - m_rectTarget.x) / m_dScale + 0.5);
	INVDK_INT y1 = y - INVDK_INT((zoomCenter.y - m_rectTarget.y) / m_dScale + 0.5);
	m_rectSource.x = x1;
	m_rectSource.y = y1;
	rescaleImg();
	update();
}

INVDK_VOID DrawBoard::zoomIn(const INVDK::Point& zoomCenter)
{
	INVDK_INT x = m_rectSource.x + INVDK_INT((zoomCenter.x - m_rectTarget.x) / m_dScale + 0.5) - m_rectTarget.x / m_dScale;
	INVDK_INT y = m_rectSource.y + INVDK_INT((zoomCenter.y - m_rectTarget.y) / m_dScale + 0.5) - m_rectTarget.y / m_dScale;
	m_dScale /= 1.1f;
	INVDK_INT x1 = x - INVDK_INT((zoomCenter.x - m_rectTarget.x) / m_dScale + 0.5);
	INVDK_INT y1 = y - INVDK_INT((zoomCenter.y - m_rectTarget.y) / m_dScale + 0.5);
	m_rectSource.x = x1;
	m_rectSource.y = y1;
	rescaleImg();
	update();
}

INVDK::Point DrawBoard::widget2Image(const INVDK::Point& pt)
{
	INVDK_FLOAT x_img = (pt.x - m_rectTarget.x) / m_dScale + m_rectSource.x;	// 计算图片坐标系下的x坐标
	INVDK_FLOAT y_img = (pt.y - m_rectTarget.y) / m_dScale + m_rectSource.y;	// 计算图片坐标系下的y坐标
	return INVDK::Point(INVDK_INT(x_img), INVDK_INT(y_img));	// 返回图片坐标系下的坐标
}

INVDK_INT DrawBoard::getRows() const
{
	return m_rows;
}

INVDK_VOID DrawBoard::setRows(INVDK_INT newRows)
{
	this->m_rows = newRows;
}

INVDK_INT DrawBoard::getCols() const
{
	return m_cols;
}

INVDK_VOID DrawBoard::setCols(INVDK_INT newCols)
{
	this->m_cols = newCols;
}

const QImage& DrawBoard::getImage() const
{
	return m_image;
}

INVDK_VOID DrawBoard::setImage(const QImage& newImage)
{
	m_image = newImage;	// 显示的图片
}

INVDK_VOID DrawBoard::setDrawColor(const INVDKUI_RGB& newDrawColor)
{
	this->m_drawColor = newDrawColor;
}

INVDK_VOID DrawBoard::setDrawMode(INVDK_INT drawMode)
{
	this->m_drawMode = drawMode;
}

INVDK_BOOL DrawBoard::getModify()
{
	return m_bModify;
}

INVDK_VOID DrawBoard::setModify(INVDK_BOOL state)
{
	m_bModify = state;
}

INVDK_VOID DrawBoard::paintEvent(QPaintEvent* event)
{
	QPainter painter;	// 创建画家对象
	painter.begin(this);	// 开始绘画
	painter.fillRect(rect(), 0xFF7F7F7F);	// 绘制背景

	// 图片为空就返回
	if (m_image.isNull())
	{
		painter.end();
		return;
	}

	// 绘制 m_image 的 m_rectSource 区域到界面的 m_rectTarget 区域
	painter.drawImage(INVDKUI::invdkRect_to_qrect(m_rectTarget), m_image, INVDKUI::invdkRect_to_qrect(m_rectSource));

	painter.end();	// 结束绘画
}

INVDK_VOID DrawBoard::mousePressEvent(QMouseEvent* event)
{
	if (Qt::LeftButton == event->button())	// 判断是否是左键按下
	{
		m_ptLBtnDown = INVDKUI::qpoint_to_invdkPoint(event->pos());	// 获取鼠标按下位置
		if (m_rectTarget.contains(m_ptLBtnDown))
		{
			m_bDraw = TRUE;	// 鼠标按下时，绘制状态置为TRUE

			if (!m_bModify)	// 修改了图像
				m_bModify = TRUE;

			INVDK::Point pt = widget2Image(m_ptLBtnDown);	// 将鼠标位置转换为图片坐标系下的坐标
			drawPixel(pt);	// 绘制
		}
	}
	else if (Qt::RightButton == event->button())	// 判断是否是右键按下
	{
		m_ptRBtnDown = INVDKUI::qpoint_to_invdkPoint(event->pos());	// 获取鼠标按下位置
		if (m_rectTarget.contains(m_ptRBtnDown))
			m_bMove = TRUE;	// 鼠标按下时，移动状态置为TRUE
	}
	update();
}

INVDK_VOID DrawBoard::mouseReleaseEvent(QMouseEvent* event)
{
	if (Qt::LeftButton == event->button())	// 判断是否是左键释放
	{
		m_bDraw = FALSE;	// 释放鼠标时，绘制状态置为FALSE
		m_ptLBtnDown = INVDK::Point(-1, -1);	// 释放时将鼠标按下位置置为无效值
	}
	else if (Qt::RightButton == event->button())	// 判断是否是右键释放
	{
		m_bMove = FALSE;	// 释放鼠标时，移动状态置为FALSE
		m_ptRBtnDown = INVDK::Point(-1, -1);	// 释放时将鼠标按下位置置为无效值
	}
}

INVDK_VOID DrawBoard::mouseMoveEvent(QMouseEvent* event)
{
	if (m_image.isNull())	// 如果图片为空，直接返回
		return;

	INVDK::Point pt(-1, -1);
	INVDK::Point mousePos = INVDKUI::qpoint_to_invdkPoint(event->pos());	// 获取鼠标位置
	if (m_rectTarget.contains(mousePos))	// 如果鼠标不在目标区域内，直接返回
	{
		pt = widget2Image(mousePos);	// 将鼠标位置转换为图片坐标系下的坐标

		if (m_bDraw)	// 如果绘制状态为TRUE
		{
			drawPixel(pt);	// 绘制
		}
		else if (m_bMove)
		{
			INVDK_INT x0 = m_rectSource.x + INVDK_INT((m_ptRBtnDown.x - m_rectTarget.x) / m_dScale + 0.5);
			INVDK_INT y0 = m_rectSource.y + INVDK_INT((m_ptRBtnDown.y - m_rectTarget.y) / m_dScale + 0.5);
			INVDK_INT x1 = m_rectSource.x + INVDK_INT((mousePos.x - m_rectTarget.x) / m_dScale + 0.5);
			INVDK_INT y1 = m_rectSource.y + INVDK_INT((mousePos.y - m_rectTarget.y) / m_dScale + 0.5);
			// 如果图片宽度大于等于目标区域宽度加上源区域x坐标加上鼠标按下位置x坐标减去鼠标移动位置x坐标
			if (m_image.width() >= m_rectSource.width + m_rectSource.x + x0 - x1)
			{
				INVDK_INT x = m_rectSource.x + x0 - x1;	// 计算新的x坐标
				m_rectSource.x = INVDK_MAX(0, x);	// 更新源区域x坐标
			}
			// 如果图片高度大于等于目标区域高度加上源区域y坐标加上鼠标按下位置y坐标减去鼠标移动位置y坐标
			if (m_image.height() >= m_rectSource.height + m_rectSource.y + y0 - y1)
			{
				INVDK_INT y = m_rectSource.y + y0 - y1;	// 计算新的y坐标
				m_rectSource.y = INVDK_MAX(0, y);	// 更新源区域y坐标
			}

			m_ptRBtnDown = mousePos;	// 更新鼠标按下位置
		}

		update();
	}

	emit boardPoint(pt);	// 发送鼠标所在坐标
}

INVDK_VOID DrawBoard::wheelEvent(QWheelEvent* event)
{
	if (m_image.isNull())	// 如果图片为空，直接返回
		return;

	INVDK::Point mousePos = INVDKUI::qpoint_to_invdkPoint(event->pos());	// 获取鼠标位置

	if (!m_rectTarget.contains(mousePos))	// 如果鼠标不在目标区域内，直接返回
		return;

	if (event->delta() > 0)	// 如果滚轮向上滚动
		zoomOut(mousePos);	// 放大图片
	else
		zoomIn(mousePos);	// 缩小图片
}

INVDK_VOID DrawBoard::resizeEvent(QResizeEvent* event)
{
	rescaleImg();
}
