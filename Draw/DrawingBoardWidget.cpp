#include "DrawingBoardWidget.h"
#include "ui_DrawingBoardWidget.h"
#include <QPainter>
#include <QPalette>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDebug>

DrawingBoardWidget::DrawingBoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawingBoardWidget)
{
    ui->setupUi(this);

    // 启用鼠标追踪
    setMouseTracking(true);

    // 创建画家对象
    m_painter = new QPainter();

    drawColor = 0;

    // 设置格子数量
    rows = 32;
    cols = 32;

    // 设置格子的像素
    pixel = 10;
    // 设置比例
    scale = 1.0;

    isMove = false;
    isDraw = false;

    data.resize(cols*rows);
    // 初始化画布
    for(int i =0;i< data.size();i++){
        data[i] = 0x00ffffff;
    }
}

DrawingBoardWidget::~DrawingBoardWidget()
{
    delete ui;
}

void DrawingBoardWidget::paintEvent(QPaintEvent *)
{
    // 计算所需画布的宽度
    int dBWidth = (rows*pixel)*scale;
    // 计算所属画布的高度
    int dBHeight = (cols*pixel)*scale;
    // 记录下画布的大小
    drawBoard.setWidth(dBWidth);
    drawBoard.setHeight(dBHeight);

    // 开始绘画
    m_painter->begin(this);

    // 填充背景
    m_painter->fillRect(0,0,width(),height(), Qt::gray);

    // 填充画布
    m_painter->fillRect(drawBoard,Qt::white);

    // 计算小格子的宽高
    int blockWidth = drawBoard.width()/rows;
    int blockHeight = drawBoard.height()/cols;

    // 画方块
    for(int i =0;i< cols;i++){
        for(int j = 0;j<rows;j++){
            // 获取当前格子开始的地方
            int bX = j*blockWidth;
            int bY = i*blockHeight;
            // 填充上颜色
            m_painter->fillRect(QRect(drawBoard.x()+bX,drawBoard.y()+bY,blockWidth,blockHeight), QColor(qRed(data[i*rows+j]),qGreen(data[i*rows+j]),qBlue(data[i*rows+j]), qAlpha(data[i*rows+j])));
        }
    }
    // 设置画笔
    QPen pen(QColor(0,0,0),1);
    m_painter->setPen(pen);
    // 画线
    for (int i = 0; i < cols+1; i++) {
        for (int j = 0; j < rows+1; j++) {
            // 横线
            QPoint startPoint(drawBoard.x(), drawBoard.y()+i*blockHeight);
            QPoint endPoint(drawBoard.x()+drawBoard.width(),drawBoard.y()+i*blockHeight);
            m_painter->drawLine(startPoint,endPoint);

            // 竖线
            startPoint = QPoint(drawBoard.x()+j*blockWidth, drawBoard.y());
            endPoint = QPoint(drawBoard.x()+j*blockWidth,drawBoard.y()+drawBoard.height());
            m_painter->drawLine(startPoint,endPoint);
        }
    }

    // 结束绘画
    m_painter->end();
}

void DrawingBoardWidget::mousePressEvent(QMouseEvent *event)
{
    // 点击的位置
    lastPos = event->pos();

    if(event->button() == Qt::MouseButton::LeftButton){
        isDraw = true;
        QPoint leftUp = QPoint(drawBoard.x(),drawBoard.y());
        // 判断是否在画布上
        if(drawBoard.contains(lastPos)){
            // 获取格子在画布上的坐标
            QPoint blockPos = lastPos - leftUp;

            // 计算小格子的宽高
            int blockWidth = drawBoard.width()/rows;
            int blockHeight = drawBoard.height()/cols;
            // 获取行数
            int bI = blockPos.y()/blockHeight/* + (blockPos.y()%blockHeight?1:0)*/;
            // 获取列数
            int bJ = blockPos.x()/blockWidth/* + (blockPos.x()%blockWidth?1:0)*/;

            data[bI*rows+bJ] = drawColor;
        }
    }else if(event->button()==Qt::MouseButton::RightButton){
        // 按下右键，开始移动
        isMove = true;
    }
    update();
}

void DrawingBoardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton){
        isDraw = false;
    }else if(event->button()==Qt::MouseButton::RightButton){
        // 松开右键，停止移动
        isMove = false;
    }
    update();
}

void DrawingBoardWidget::mouseMoveEvent(QMouseEvent *event)
{

    // 获取当前鼠标所在坐标
    QPoint pos = event->pos();
    // 获取画布左上角的点
    QPoint leftUp = QPoint(drawBoard.x(),drawBoard.y());
    int bI = -1, bJ = -1;
    // 判断是否在画布上
    if(drawBoard.contains(lastPos)){
        // 获取格子在画布上的坐标
        QPoint blockPos = lastPos - leftUp;

        // 计算小格子的宽高
        int blockWidth = drawBoard.width()/rows;
        int blockHeight = drawBoard.height()/cols;
        // 获取行数
        bI = blockPos.y()/blockHeight/* + (blockPos.y()%blockHeight?1:0)*/;
        // 获取列数
        bJ = blockPos.x()/blockWidth/* + (blockPos.x()%blockWidth?1:0)*/;
    }

    emit boardPoint(QPoint(bJ,bI));

    if(isMove){
        // 获取需要移动的距离
        QPoint moveDist = pos - lastPos;

        drawBoard.setX(drawBoard.x()+moveDist.x());
        drawBoard.setY(drawBoard.y()+moveDist.y());
    }
    if(isDraw){
        if(bI >= 0 && bJ >= 0 &&
            bI < cols && bJ < rows)
        {
            data[bI*rows+bJ] = drawColor;
        }
    }

    // 获取鼠标最后停留的点位
    lastPos = pos;

    update();
}

void DrawingBoardWidget::wheelEvent(QWheelEvent *event)
{
    // 滚轮的滚动量
    QPoint scrollAmount = event->angleDelta();

    // 正值表示滚轮远离使用者放大负值表示朝向使用者缩小
    if(scrollAmount.y() > 0) {
        if(scale<8)
        {
            scale+=0.1;
        }
    }
    else {
        if(scale>0.2)
        {
            scale-=0.1;
        }
    }

    // 计算滚轮事件位置相对于控件的偏移
    QPoint offset = lastPos - drawBoard.center();

    // 计算新的控件位置，使得滚轮事件位置在缩放后仍然位于相同的屏幕位置
    int newX = drawBoard.x() + offset.x() - (offset.x() * scale / (scale + 0.1));
    int newY = drawBoard.y() + offset.y() - (offset.y() * scale / (scale + 0.1));

    // 更新控件的位置
    drawBoard.moveTo(newX, newY);

    // 重新绘制
    update();
}

void DrawingBoardWidget::resizeEvent(QResizeEvent *)
{
    // 计算所需画布的宽度
    int dBWidth = (rows*pixel)*scale;
    // 计算所属画布的高度
    int dBHeight = (cols*pixel)*scale;
    // 记录下画布的大小
    drawBoard.setWidth(dBWidth);
    drawBoard.setHeight(dBHeight);

    // 计算开始绘画的位置
    int dBx = width()/2 - drawBoard.width()/2;
    int dBy = height()/2 - drawBoard.height()/2;
    // 记录下绘画的位置
    drawBoard.setX(dBx);
    drawBoard.setY(dBy);
}

const QRgb &DrawingBoardWidget::getDrawColor() const
{
    return drawColor;
}

void DrawingBoardWidget::setDrawColor(const QRgb &newDrawColor)
{
    drawColor = newDrawColor;
}

const QVector<QRgb> &DrawingBoardWidget::getData() const
{
    return data;
}

void DrawingBoardWidget::setData(const QVector<QRgb> &newData)
{
    data = newData;
}

int DrawingBoardWidget::getRows() const
{
    return rows;
}

void DrawingBoardWidget::setRows(int newRows)
{
    rows = newRows;
}

int DrawingBoardWidget::getCols() const
{
    return cols;
}

void DrawingBoardWidget::setCols(int newCols)
{
    cols = newCols;
}
