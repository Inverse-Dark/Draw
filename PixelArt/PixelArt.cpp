#include "PixelArt.h"
#include "ui_PixelArt.h"
#include "ColorPickerWidget.h"
#include "INVDKUI_RGB.h"
#include "INVDKUI_MessageBox.h"
#include "INVDK_Math.h"

#include <QFileDialog>
#include <QSvgGenerator>
#include <QPainter>
#include <QCloseEvent>

PixelArt::PixelArt(QWidget *parent)
    : INVDKUI::QCustomWindow(parent)
    , ui(new Ui::PixelArt)
{
    initWidget();   // 初始化界面
    initSignals();  // 初始化信号
    initialization();   // 初始化
}

PixelArt::~PixelArt()
{
    delete ui;
}

INVDK_VOID PixelArt::initWidget()
{
    m_pWidgetMain = new QWidget(this);
    ui->setupUi(static_cast<QWidget*>(m_pWidgetMain));

    QCustomWindow::setTitle("Pixel Art");
}

INVDK_VOID PixelArt::initSignals()
{
    // 保存画板行列按钮
    connect(ui->pushButtonSave, &QPushButton::clicked, this, &PixelArt::OnSaveClicked);
    // 打开图片按钮
    connect(ui->pushButtonOpenFile, &QPushButton::clicked, this, &PixelArt::OnOpenFileClicked);
    // 保存图片按钮
    connect(ui->pushButtonSaveFile, &QPushButton::clicked, this, &PixelArt::OnSaveFileClicked);

    // 改变 Red 通道的值
    connect(ui->horizontalSliderR, &QSlider::valueChanged, this, &PixelArt::OnRedValueChanged);
    // 改变 Red 通道的值
    connect(ui->horizontalSliderG, &QSlider::valueChanged, this, &PixelArt::OnGreedValueChanged);
    // 改变 Red 通道的值
    connect(ui->horizontalSliderB, &QSlider::valueChanged, this, &PixelArt::OnBlueValueChanged);
    // 改变 Red 通道的值
    connect(ui->horizontalSliderA, &QSlider::valueChanged, this, &PixelArt::OnAlphaValueChanged);

    // 清空画板按钮
    connect(ui->pushButtonClean, &QPushButton::clicked, this, &PixelArt::OnCleanClicked);
    // 打开取色器按钮
    connect(ui->pushButtonColorPicker, &QPushButton::clicked, this, &PixelArt::OnColorPickerClicked);
    // 填充按钮
    connect(ui->pushButtonBrush, &QPushButton::clicked, this, &PixelArt::OnBrushClicked);
    // 铅笔按钮
    connect(ui->pushButtonPen, &QPushButton::clicked, this, &PixelArt::OnPenClicked);
    // 橡皮擦按钮
    connect(ui->pushButtonEraser, &QPushButton::clicked, this, &PixelArt::OnEraserClicked);

    // 画板中鼠标所在的坐标颜色
    connect(ui->widgetDrawBoard, &DrawBoard::boardPoint, this, &PixelArt::OnBoardPoint);
    // 拾色器中拾取的颜色
    connect(ColorPickerWidget::Instance(), &ColorPickerWidget::ColorPicker, this, &PixelArt::OnColorPicker);
}

INVDK_VOID PixelArt::initialization()
{
    QCustomWindow::initialization();

    // 初始化值
    m_red = ui->horizontalSliderR->value();
    m_green = ui->horizontalSliderG->value();
    m_blue = ui->horizontalSliderB->value();
    m_alpha = ui->horizontalSliderA->value();
    // ARGB
    m_color = INVDKUI::rgba(m_red, m_green, m_blue, m_alpha);
    // 设置画笔颜色
    ui->widgetDrawBoard->setDrawColor(m_color);
}

void PixelArt::OnSaveClicked()
{
    INVDK_INT cols = ui->spinBoxCols->text().toInt();
    INVDK_INT rows = ui->spinBoxRows->text().toInt();

    // 获取旧的绘画数据
    QImage oldImage = ui->widgetDrawBoard->getImage();
    // 用来保存新的数据
    QImage newImage(cols, rows, QImage::Format_ARGB32);
    newImage.fill(Qt::white);

    // 获取最小的行列，免得越界
    INVDK_INT col = INVDK_MIN(ui->widgetDrawBoard->getCols(), ui->spinBoxCols->value());
    INVDK_INT row = INVDK_MIN(ui->widgetDrawBoard->getRows(), ui->spinBoxRows->value());

    // 保存至新的
    for (INVDK_INT i = 0; i < col; i++)
    {
        for (INVDK_INT j = 0; j < row; j++)
        {
            // 将旧的数据保存至新的数据
            //newData[i * ui->spinBoxRows->text().toInt() + j] = oldData[i * ui->widgetDrawBoard->getRows() + j];
            newImage.setPixel(j, i, oldImage.pixel(j, i));
        }
    }

    // 保存新的行列至画布界面
    ui->widgetDrawBoard->setRows(ui->spinBoxRows->text().toInt());
    ui->widgetDrawBoard->setCols(ui->spinBoxCols->text().toInt());
    // 保存新的绘画数据
    ui->widgetDrawBoard->setImage(newImage);

    // 更新画布
    ui->widgetDrawBoard->update();
}

void PixelArt::OnOpenFileClicked()
{
    if (ui->widgetDrawBoard->getModify())
    {
        switch (INVDKUI::MessageBox::showMessageBoxQuestion(
            "Draw",
            "The current image has been modified but not saved. Are you sure you want to open a new picture?"))
        {
        case INVDKUI::MessageBox::Yes:
            break;
        case INVDKUI::MessageBox::No:
            break;
        }
    }

    // 创建一个QFileDialog对象
    QFileDialog dialog;
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(QObject::tr("Image Files (*.png *.jpg *.jpeg *.bmp *.ico)"));

    QString selectedFilter;
    QString filePath;

    if (dialog.exec())
    {
        QStringList files = dialog.selectedFiles();
        if (!files.isEmpty())
        {
            filePath = files.first();
        }
        selectedFilter = dialog.selectedNameFilter();
    }

    if (!filePath.isEmpty())
    {
        if (selectedFilter == "Image Files (*.png *.jpg *.jpeg *.bmp *.ico)")
        {
            QImage img(filePath);
            if (!img.isNull())
            {
                int width = img.width();
                int height = img.height();
                if (width > 1024 || height > 1024)
                {
                    INVDKUI::MessageBox::showMessageBoxInfo("Info",
                        "This image is of an unsupported size.");
                    return;
                }

                ui->widgetDrawBoard->setRows(height);
                ui->widgetDrawBoard->setCols(width);
                ui->spinBoxRows->setValue(ui->widgetDrawBoard->getRows());
                ui->spinBoxCols->setValue(ui->widgetDrawBoard->getCols());
                ui->widgetDrawBoard->setImage(img);
            }
        }
    }

    // 新打开的文件，当然没有修改啦
    ui->widgetDrawBoard->setModify(false);
}

void PixelArt::OnSaveFileClicked()
{
    int height = ui->widgetDrawBoard->getCols();
    int width = ui->widgetDrawBoard->getRows();

    QImage img = ui->widgetDrawBoard->getImage();

    // 创建一个QFileDialog对象
    QFileDialog dialog;
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(QObject::tr("Image Files (*.png *.jpg *.jpeg *.bmp *.ico);;Svg Files (*.svg)"));
    dialog.selectFile("Draw.png");

    QString selectedFilter;
    QString filePath;

    // 弹出保存文件对话框
    if (dialog.exec())
    {
        QStringList files = dialog.selectedFiles();
        if (!files.isEmpty())
        {
            filePath = files.first();
        }
        selectedFilter = dialog.selectedNameFilter();
    }

    if (!filePath.isEmpty())
    {
        // 检查用户选择的过滤器
        if (selectedFilter == "Image Files (*.png *.jpg *.jpeg *.bmp *.ico)")
        {
            // 用户选择了图片文件类型
            img.save(filePath);
        }
        else if (selectedFilter == "Svg Files (*.svg)")
        {
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
        // 保存后，自然要换成未修改
        ui->widgetDrawBoard->setModify(false);
    }
}

void PixelArt::OnRedValueChanged(int value)
{
    // 保存值
    m_red = value;
    // 获取颜色
	m_color = INVDKUI::rgba(m_red, m_green, m_blue, m_alpha);
    // 更新画笔的颜色
    ui->widgetDrawBoard->setDrawColor(m_color);
    // 用来预览画笔颜色
    QImage img(ui->labelColor->width(), ui->labelColor->height(), QImage::Format_ARGB32);
    img.fill(m_color);
    // 设置 QLabel 的样式
    ui->labelColor->setStyleSheet("border: 1px solid black;");
    ui->labelColor->setPixmap(QPixmap::fromImage(img));
    // 设置显示文本
    ui->labelR->setText(QString(tr("R: %1")).arg(m_red));
}

void PixelArt::OnGreedValueChanged(int value)
{
    // 保存值
    m_green = value;
    // 获取颜色
    m_color = INVDKUI::rgba(m_red, m_green, m_blue, m_alpha);
    // 更新画笔的颜色
    ui->widgetDrawBoard->setDrawColor(m_color);
    // 用来预览画笔颜色
    QImage img(ui->labelColor->width(), ui->labelColor->height(), QImage::Format_ARGB32);
    img.fill(m_color);
    // 设置 QLabel 的样式
    ui->labelColor->setStyleSheet("border: 1px solid black;");
    ui->labelColor->setPixmap(QPixmap::fromImage(img));
    // 设置显示文本
    ui->labelG->setText(QString(tr("G: %1")).arg(m_green));
}

void PixelArt::OnBlueValueChanged(int value)
{
    // 保存值
    m_blue = value;
    // 获取颜色
    m_color = INVDKUI::rgba(m_red, m_green, m_blue, m_alpha);
    // 更新画笔的颜色
    ui->widgetDrawBoard->setDrawColor(m_color);
    // 用来预览画笔颜色
    QImage img(ui->labelColor->width(), ui->labelColor->height(), QImage::Format_ARGB32);
    img.fill(m_color);
    // 设置 QLabel 的样式
    ui->labelColor->setStyleSheet("border: 1px solid black;");
    ui->labelColor->setPixmap(QPixmap::fromImage(img));
    // 设置显示文本
    ui->labelB->setText(QString(tr("B: %1")).arg(m_blue));
}

void PixelArt::OnAlphaValueChanged(int value)
{
    // 保存值
    m_alpha = value;
    // 获取颜色
    m_color = INVDKUI::rgba(m_red, m_green, m_blue, m_alpha);
    // 更新画笔的颜色
    ui->widgetDrawBoard->setDrawColor(m_color);
    // 用来预览画笔颜色
    QImage img(ui->labelColor->width(), ui->labelColor->height(), QImage::Format_ARGB32);
    img.fill(m_color);
    // 设置 QLabel 的样式
    ui->labelColor->setStyleSheet("border: 1px solid black;");
    ui->labelColor->setPixmap(QPixmap::fromImage(img));
    // 设置显示文本
    ui->labelA->setText(QString(tr("A: %1")).arg(m_alpha));
}

void PixelArt::OnCleanClicked()
{
    INVDK_INT cols = ui->widgetDrawBoard->getCols();
    INVDK_INT rows = ui->widgetDrawBoard->getRows();
    // 创建新的画板
    QImage newImage(cols, rows, QImage::Format_ARGB32);
    newImage.fill(Qt::white);
    // 替换掉旧的画板
    ui->widgetDrawBoard->setImage(newImage);
    // 刷新画板
    ui->widgetDrawBoard->update();
}

void PixelArt::OnColorPickerClicked()
{
    ColorPickerWidget::Instance()->show();
}

void PixelArt::OnBrushClicked()
{
    ui->widgetDrawBoard->setDrawMode(3);
}

void PixelArt::OnPenClicked()
{
    ui->widgetDrawBoard->setDrawMode(1);
}

void PixelArt::OnEraserClicked()
{
    ui->widgetDrawBoard->setDrawMode(2);
}

void PixelArt::OnBoardPoint(INVDK::Point pos)
{
    INVDK_INT x = pos.x;
    INVDK_INT y = pos.y;
    INVDKUI_RGB rgb;
    if (x < 0 || y < 0 ||
        x >= ui->widgetDrawBoard->getCols() ||
        y >= ui->widgetDrawBoard->getRows())
    {
        rgb = 0;
    }
    else
    {
		QImage img = ui->widgetDrawBoard->getImage();
        rgb = img.pixel(x, y);
    }

    QString text;
    text = tr(" R:") + QString::number(INVDKUI::red(rgb)) +
        tr(" G:") + QString::number(INVDKUI::green(rgb)) +
        tr(" B:") + QString::number(INVDKUI::blue(rgb)) +
        tr(" A:") + QString::number(INVDKUI::alpha(rgb));
    ui->label_mousePos->setText(tr("X:") + QString::number(x) + tr(" ,Y:") + QString::number(y) + "<br>" + text);
}

void PixelArt::OnColorPicker(int r, int g, int b, int a)
{
    ui->horizontalSliderR->setValue(r);
    ui->horizontalSliderG->setValue(g);
    ui->horizontalSliderB->setValue(b);
    ui->horizontalSliderA->setValue(a);

    // 设置 QLabel 的样式
    ui->labelColor->setStyleSheet("border: 1px solid black;");
    QImage img(ui->labelColor->width(), ui->labelColor->height(), QImage::Format_ARGB32);
    img.fill(m_color);
    ui->labelColor->setPixmap(QPixmap::fromImage(img));

    // 获取颜色
    m_color = INVDKUI::rgba(r, g, b, a);
    // 设置画笔颜色
    ui->widgetDrawBoard->setDrawColor(m_color);
}

INVDK_VOID PixelArt::showEvent(QShowEvent* event)
{
    // 用来预览画笔颜色
    QImage img(ui->labelColor->width(), ui->labelColor->height(), QImage::Format_ARGB32);
    img.fill(m_color);
    // 设置 QLabel 的样式
    ui->labelColor->setStyleSheet("border: 1px solid black;");
    ui->labelColor->setPixmap(QPixmap::fromImage(img));

    QCustomWindow::showEvent(event);
}

INVDK_VOID PixelArt::resizeEvent(QResizeEvent* event)
{
    // 用来预览画笔颜色
    QImage img(ui->labelColor->width(), ui->labelColor->height(), QImage::Format_ARGB32);
    img.fill(m_color);
    // 设置 QLabel 的样式
    ui->labelColor->setStyleSheet("border: 1px solid black;");
    ui->labelColor->setPixmap(QPixmap::fromImage(img));

    QCustomWindow::resizeEvent(event);
}

INVDK_VOID PixelArt::closeEvent(QCloseEvent* event)
{
    if (ui->widgetDrawBoard->getModify())
    {
        switch (INVDKUI::MessageBox::showMessageBoxQuestion(
            "Draw",
            "The current image has been modified but not saved. Are you sure you want to exit?"))
        {
        case INVDKUI::MessageBox::Yes:
            qApp->exit();
            break;
        case INVDKUI::MessageBox::No:
        default:
            event->ignore();
            break;
        }
    }
	QCustomWindow::closeEvent(event);
}
