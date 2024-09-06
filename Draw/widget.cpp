#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QFileDialog>
#include "ColorPickerWidget.h"
#include <QSvgGenerator>
#include <QPainter>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    setWindowState(Qt::WindowMaximized);
    // 设置标题
    setWindowTitle(tr("Draw"));

    connect(ui->widgetDrawingBoard,&DrawingBoardWidget::boardPoint,this,[&](QPoint pos){
        float x = pos.x();
        float y = pos.y();
        QRgb rgb;
        if(x < 0 || y < 0 || x > ui->widgetDrawingBoard->getRows() || y > ui->widgetDrawingBoard->getCols())
            rgb = 0;
        else
            rgb = ui->widgetDrawingBoard->getData()[y * ui->widgetDrawingBoard->getRows() + x];

        QString text;
        text = tr(" R:") + QString::number(qRed(rgb)) +
               tr(" G:") + QString::number(qGreen(rgb)) +
               tr(" B:") + QString::number(qBlue(rgb)) +
               tr(" A:") + QString::number(qAlpha(rgb));
        ui->label_mousePos->setText(tr("X:") + QString::number(x) + tr(" ,Y:") + QString::number(y) + "<br>" + text);
    });
    connect(ColorPickerWidget::Instance(),&ColorPickerWidget::ColorPicker,this,[&](int r, int g, int b, int a){
        ui->horizontalSliderR->setValue(r);
        ui->horizontalSliderG->setValue(g);
        ui->horizontalSliderB->setValue(b);
        ui->horizontalSliderA->setValue(a);

        // 设置 QLabel 的样式
        ui->labelColor->setStyleSheet("border: 1px solid black;");
        QImage img(ui->labelColor->width(),ui->labelColor->height(),QImage::Format_ARGB32);
        img.fill(color);
        ui->labelColor->setPixmap(QPixmap::fromImage(img));

        // 获取颜色
        color = a << 24 | r << 16 | g << 8 | b;
        // 设置画笔颜色
        ui->widgetDrawingBoard->setDrawColor(color);
    });

    ui->spinBoxRows->setValue(ui->widgetDrawingBoard->getRows());
    ui->spinBoxCols->setValue(ui->widgetDrawingBoard->getCols());

    r = ui->horizontalSliderR->value();
    g = ui->horizontalSliderG->value();
    b = ui->horizontalSliderB->value();
    a = ui->horizontalSliderA->value();

    // 获取颜色
    color = a << 24 | r << 16 | g << 8 | b;
    // 设置画笔颜色
    ui->widgetDrawingBoard->setDrawColor(color);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent*)
{
    // 设置 QLabel 的样式
    ui->labelColor->setStyleSheet("border: 1px solid black;");
    QImage img(ui->labelColor->width(),ui->labelColor->height(),QImage::Format_ARGB32);
    img.fill(color);
    ui->labelColor->setPixmap(QPixmap::fromImage(img));
}

void Widget::on_pushButtonSave_clicked()
{
    int cols = ui->spinBoxCols->text().toInt();
    int rows = ui->spinBoxRows->text().toInt();

    // 获取旧的绘画数据
    QVector<QRgb> oldData = ui->widgetDrawingBoard->getData();
    // 用来保存新的数据
    QVector<QRgb> newData(cols*rows);
    // 先初始化新的数据
    for(int i =0;i< newData.size();i++){
        newData[i] = 0x00ffffff;
    }

    // 获取最小的行列，免得越界
    int col = qMin(ui->widgetDrawingBoard->getCols(), ui->spinBoxCols->text().toInt());
    int row = qMin(ui->widgetDrawingBoard->getRows(), ui->spinBoxRows->text().toInt());

    // 保存至新的
    for (int i = 0; i<col; i++) {
        for (int j =0; j<row; j++) {
            // 将旧的数据保存至新的数据
            newData[i*ui->spinBoxRows->text().toInt()+j] = oldData[i*ui->widgetDrawingBoard->getRows()+j];
        }
    }

    // 保存新的行列至画布界面
    ui->widgetDrawingBoard->setRows(ui->spinBoxRows->text().toInt());
    ui->widgetDrawingBoard->setCols(ui->spinBoxCols->text().toInt());
    // 保存新的绘画数据
    ui->widgetDrawingBoard->setData(newData);

    // 更新画布
    ui->widgetDrawingBoard->update();
}

void Widget::on_horizontalSliderR_valueChanged(int value)
{
    // 保存值
    r = value;
    // 获取颜色
    color = a << 24 | r << 16 | g << 8 | b;
    // 更新画笔的颜色
    ui->widgetDrawingBoard->setDrawColor(color);
    // 用来预览画笔颜色
    QImage img(ui->labelColor->width(),ui->labelColor->height(),QImage::Format_ARGB32);
    img.fill(color);
    // 设置 QLabel 的样式
    ui->labelColor->setStyleSheet("border: 1px solid black;");
    ui->labelColor->setPixmap(QPixmap::fromImage(img));
    // 设置显示文本
    ui->labelR->setText(QString(tr("R: %1")).arg(r));
}

void Widget::on_horizontalSliderG_valueChanged(int value)
{
    // 保存值
    g = value;
    // 获取颜色
    color = a << 24 | r << 16 | g << 8 | b;
    // 更新画笔的颜色
    ui->widgetDrawingBoard->setDrawColor(color);
    // 用来预览画笔颜色
    QImage img(ui->labelColor->width(),ui->labelColor->height(),QImage::Format_ARGB32);
    img.fill(color);
    // 设置 QLabel 的样式
    ui->labelColor->setStyleSheet("border: 1px solid black;");
    ui->labelColor->setPixmap(QPixmap::fromImage(img));
    // 设置显示文本
    ui->labelG->setText(QString(tr("G: %1")).arg(g));
}

void Widget::on_horizontalSliderB_valueChanged(int value)
{
    // 保存值
    b = value;
    // 获取颜色
    color = a << 24 | r << 16 | g << 8 | b;
    // 更新画笔的颜色
    ui->widgetDrawingBoard->setDrawColor(color);
    // 用来预览画笔颜色
    QImage img(ui->labelColor->width(),ui->labelColor->height(),QImage::Format_ARGB32);
    img.fill(color);
    // 设置 QLabel 的样式
    ui->labelColor->setStyleSheet("border: 1px solid black;");
    ui->labelColor->setPixmap(QPixmap::fromImage(img));
    // 设置显示文本
    ui->labelB->setText(QString(tr("B: %1")).arg(b));
}

void Widget::on_horizontalSliderA_valueChanged(int value)
{
    // 保存值
    a = value;
    // 获取颜色
    color = a << 24 | r << 16 | g << 8 | b;
    // 更新画笔的颜色
    ui->widgetDrawingBoard->setDrawColor(color);
    // 用来预览画笔颜色
    QImage img(ui->labelColor->width(),ui->labelColor->height(),QImage::Format_ARGB32);
    img.fill(color);
    // 设置 QLabel 的样式
    ui->labelColor->setStyleSheet("border: 1px solid black;");
    ui->labelColor->setPixmap(QPixmap::fromImage(img));
    // 设置显示文本
    ui->labelA->setText(QString(tr("A: %1")).arg(a));
}

// 保存图片
void Widget::on_pushButtonSaveFile_clicked()
{
    int height = ui->widgetDrawingBoard->getCols();
    int width = ui->widgetDrawingBoard->getRows();

    QImage img(width,height,QImage::Format_RGBA8888);

    QVector<QRgb> data = ui->widgetDrawingBoard->getData();
    for(int i =0;i<height;i++){
        for(int j =0;j<width;j++){
            img.setPixel(j,i,data[i*width+j]);
        }
    }

    // 创建一个QFileDialog对象
    QFileDialog dialog;
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(QObject::tr("Image Files (*.png *.jpg *.jpeg *.bmp *.ico);;Svg Files (*.svg)"));
    dialog.selectFile("Draw.png");

    QString selectedFilter;
    QString filePath;

    // 弹出保存文件对话框
    if (dialog.exec()) {
        QStringList files = dialog.selectedFiles();
        if (!files.isEmpty()) {
            filePath = files.first();
        }
        selectedFilter = dialog.selectedNameFilter();
    }

    if(!filePath.isEmpty())
    {
        // 检查用户选择的过滤器
        if (selectedFilter == "Image Files (*.png *.jpg *.jpeg *.bmp *.ico)") {
            // 用户选择了图片文件类型
            img.save(filePath);
        } else if (selectedFilter == "Svg Files (*.svg)") {
            // 用户选择了SVG文件类型
            QSvgGenerator generator;
            generator.setFileName(filePath);
            generator.setSize(img.size());
            generator.setViewBox(QRect(0, 0, img.width(), img.height()));
            generator.setTitle("SVG");
            generator.setDescription("SVG File");
            QPainter painter(&generator);
            painter.drawImage(QPoint(0, 0), img);
            painter.end();
        }
    }
}

// 打开图片
void Widget::on_pushButtonOpenFile_clicked()
{
    // 创建一个QFileDialog对象
    QFileDialog dialog;
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(QObject::tr("Image Files (*.png *.jpg *.jpeg *.bmp *.ico)"));

    QString selectedFilter;
    QString filePath;

    if (dialog.exec()) {
        QStringList files = dialog.selectedFiles();
        if (!files.isEmpty()) {
            filePath = files.first();
        }
        selectedFilter = dialog.selectedNameFilter();
    }

    if (!filePath.isEmpty()) {
        if (selectedFilter == "Image Files (*.png *.jpg *.jpeg *.bmp *.ico)") {
            QImage img(filePath);
            if(!img.isNull())
            {
                int width = img.width();
                int height = img.height();
                if(width > 1024 || height > 1024)
                {
                    QMessageBox::information(this, tr("Info"), tr("This image is of an unsupported size."));
                    return;
                }

                QVector<QRgb> map = ui->widgetDrawingBoard->getData();

                map.resize(width*height);

                for(int i = 0; i < height; i++)
                {
                    for(int j = 0; j < width; j++)
                    {
                        map[i*width+j] = img.pixel(j,i);
                    }
                }
                ui->widgetDrawingBoard->setData(map);

                ui->widgetDrawingBoard->setRows(width);
                ui->widgetDrawingBoard->setCols(height);
                ui->spinBoxRows->setValue(ui->widgetDrawingBoard->getRows());
                ui->spinBoxCols->setValue(ui->widgetDrawingBoard->getCols());
            }
        }
    }
}

// 清空画板
void Widget::on_pushButtonClean_clicked()
{
    int cols = ui->spinBoxCols->text().toInt();
    int rows = ui->spinBoxRows->text().toInt();

    // 创建新的画板
    QVector<QRgb> newData(cols*rows);
    // 初始化新的画板
    for(int i =0;i< newData.size();i++){
        newData[i] = 0x00ffffff;
    }
    // 替换掉旧的画板
    ui->widgetDrawingBoard->setData(newData);
    // 刷新画板
    ui->widgetDrawingBoard->update();
}

// 显示取色器
void Widget::on_pushButtonColorPicker_clicked()
{
    ColorPickerWidget* colorPickerWidget = ColorPickerWidget::Instance();
    colorPickerWidget->show();
}

void Widget::on_pushButtonPen_clicked()
{
    ui->widgetDrawingBoard->setDrawMode(1);
}

void Widget::on_pushButtonEraser_clicked()
{
    ui->widgetDrawingBoard->setDrawMode(2);
}

void Widget::on_pushButtonBrush_clicked()
{
    ui->widgetDrawingBoard->setDrawMode(3);
}


