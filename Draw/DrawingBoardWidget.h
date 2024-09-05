#ifndef DRAWINGBOARDWIDGET_H
#define DRAWINGBOARDWIDGET_H

#include <QWidget>

class QPainter;
namespace Ui {
class DrawingBoardWidget;
}

class DrawingBoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingBoardWidget(QWidget *parent = nullptr);
    ~DrawingBoardWidget();

    int getRows() const;
    void setRows(int newRows);
    int getCols() const;
    void setCols(int newCols);

    const QVector<QRgb> &getData() const;
    void setData(const QVector<QRgb> &newData);

    const QRgb &getDrawColor() const;
    void setDrawColor(const QRgb &newDrawColor);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:
    void boardPoint(QPoint pos);

private:
    Ui::DrawingBoardWidget *ui;

    QPainter* m_painter;    // 画家
   // QPen* m_pen;            // 画笔
   // QBrush m_brush;           // 画刷

    //QPalette m_pal; // 调色板

    QRect drawBoard;   // 画布大小
    double scale;  // 画布显示比例
    int pixel;  // 每格所占像素，格子是正方形

    int rows;   // 行
    int cols;   // 列

    bool isDraw;            // 左键点击，绘画
    bool isMove;            // 右键点击，移动画布
    QPoint lastPos;      // 按下的坐标

    QVector<QRgb> data;   // 绘画的数据
    QRgb      drawColor;      // 当前颜色
};

#endif // DRAWINGBOARDWIDGET_H
