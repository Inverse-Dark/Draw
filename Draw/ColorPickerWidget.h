#ifndef COLORPICKERWIDGET_H
#define COLORPICKERWIDGET_H

#include <QWidget>

namespace Ui {
class ColorPickerWidget;
}

class QGridLayout;
class QVBoxLayout;
class QLabel;
class QLineEdit;
class ColorPickerWidget : public QWidget
{
    Q_OBJECT

public:
    static ColorPickerWidget *Instance();

signals:
    void ColorPicker(int r, int g, int b, int a);

private slots:
    // QWidget interface
    void on_pushButtonSave_clicked();

    void on_pushButtonClose_clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    explicit ColorPickerWidget(QWidget *parent = nullptr);
    ~ColorPickerWidget();

private:
    Ui::ColorPickerWidget *ui;

    int r,g,b,a;
    bool pressed;

    static ColorPickerWidget* instance;
};

#endif // COLORPICKERWIDGET_H
