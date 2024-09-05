#include "ColorPickerWidget.h"
#include "ui_ColorPickerWidget.h"
#include <QMouseEvent>

ColorPickerWidget *ColorPickerWidget::instance = 0;

ColorPickerWidget::ColorPickerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ColorPickerWidget)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Color Picker"));

    r = g = b = a = 255;

    pressed = false;
}

ColorPickerWidget::~ColorPickerWidget()
{
}

ColorPickerWidget* ColorPickerWidget::Instance()
{
    if (!instance) {
        instance = new ColorPickerWidget;
    }
    return instance;
}

void ColorPickerWidget::mousePressEvent(QMouseEvent *e)
{

    if (ui->labelColor->rect().contains(e->pos())) {
        pressed = true;
    }
}

void ColorPickerWidget::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
}

void ColorPickerWidget::mouseMoveEvent(QMouseEvent *)
{
    if(!pressed){
        return;
    }

    int x = QCursor::pos().x() + 1;
    int y = QCursor::pos().y() + 1;

    QScreen *screen = qApp->primaryScreen();
    QPixmap pixmap = screen->grabWindow(0, x, y, 2, 2);

    if (pixmap.isNull()) {
        return;
    }

    QImage image = pixmap.toImage();
    if (image.valid(0, 0)) {
        QColor color = image.pixel(0, 0);
        r = color.red();
        g = color.green();
        b = color.blue();
        a = color.alpha();
    }

    //根据背景色自动计算合适的前景色
    QColor color(r, g, b);
    double gray = (0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue()) / 255;
    QColor textColor = gray > 0.5 ? Qt::black : Qt::white;

    QString str = tr("background:rgba(%1, %2, %3, %4);color:%5").arg(r).arg(g).arg(b).arg(a).arg(textColor.name());
    ui->labelColor->setStyleSheet(str);

    QString text;
    text = tr(" R:") + QString::number(r) +
           tr(" G:") + QString::number(g) +
           tr(" B:") + QString::number(b) +
           tr(" A:") + QString::number(a);
    ui->labelPosColor->setText(tr("X:") + QString::number(x) + tr(" Y:") + QString::number(y) + "<br><br>" + text);
}

void ColorPickerWidget::on_pushButtonSave_clicked()
{
    emit ColorPicker(r,g,b,a);
    this->hide();
}

void ColorPickerWidget::on_pushButtonClose_clicked()
{
    this->hide();
}

