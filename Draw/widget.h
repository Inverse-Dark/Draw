#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class DrawingBoardWidget;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonSave_clicked();

    void on_horizontalSliderR_valueChanged(int value);

    void on_horizontalSliderG_valueChanged(int value);

    void on_horizontalSliderB_valueChanged(int value);

    void on_pushButtonSaveFile_clicked();

    void on_horizontalSliderA_valueChanged(int value);

    void on_pushButtonOpenFile_clicked();

    void on_pushButtonClean_clicked();

    // QWidget interface
    void on_pushButtonColorPicker_clicked();

    void on_pushButtonBrush_clicked();

    void on_pushButtonPen_clicked();

    void on_pushButtonEraser_clicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::Widget *ui;

    int r,g,b,a;
    QRgb color;

};
#endif // WIDGET_H
