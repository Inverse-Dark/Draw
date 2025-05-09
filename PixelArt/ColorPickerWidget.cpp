#include "ColorPickerWidget.h"
#include "ui_ColorPickerWidget.h"
#include "INVDKUI_Geometry.h"
#include "INVDKUI_RGB.h"

#include <QMouseEvent>
#include <QScreen>

ColorPickerWidget* ColorPickerWidget::s_pColorPickerWidget = NULL;

ColorPickerWidget* ColorPickerWidget::Instance(QDialog* parent)
{
	if (NULL == s_pColorPickerWidget)
		s_pColorPickerWidget = new ColorPickerWidget(parent);
	return s_pColorPickerWidget;
}

void ColorPickerWidget::destroy()
{
	if (NULL != s_pColorPickerWidget)
	{
		delete s_pColorPickerWidget;
		s_pColorPickerWidget = NULL;
	}
}

ColorPickerWidget::ColorPickerWidget(QWidget* parent)
	: QCustomWindow(parent)
	, ui(new Ui::ColorPickerWidget)
{
	initWidget();	// 初始化界面
	initSignals();	// 初始化信号
}

ColorPickerWidget::~ColorPickerWidget()
{}

void ColorPickerWidget::initWidget()
{
	m_pWidgetMain = new QWidget(this);
	ui->setupUi(static_cast<QWidget*>(m_pWidgetMain));

	m_red = m_green = m_blue = m_alpha = 255;
	m_bPickerColor = FALSE;

	this->setWindowFlags(INVDKUI::WindowMinMaxButtonsHint | INVDKUI::WindowStaysOnTopHint);
	this->setTitle("Color Picker");
	this->initialization();
}

void ColorPickerWidget::initSignals()
{
	// 保存按钮
	connect(ui->pushButtonSave, &QPushButton::clicked, this, &ColorPickerWidget::OnSaveClicked);
	// 取消按钮
	connect(ui->pushButtonCancel, &QPushButton::clicked, this, &ColorPickerWidget::OnCancelClicked);
}

void ColorPickerWidget::OnSaveClicked()
{
	emit ColorPicker(m_red, m_green, m_blue, m_alpha);
	this->hide();
}

void ColorPickerWidget::OnCancelClicked()
{
	this->hide();
}

void ColorPickerWidget::mousePressEvent(QMouseEvent* event)
{
	// 获取吸取颜色的控件的外接矩形
	INVDK::Rect labelColorRect(ui->labelColor->geometry().x(), ui->labelColor->geometry().y() + m_pWidgetTitle->height(),
		ui->labelColor->geometry().width(), ui->labelColor->geometry().height());
	// 判断是否开始吸取颜色
	if (labelColorRect.contains(INVDKUI::qpoint_to_invdkPoint(event->pos())))
		m_bPickerColor = true;

	QCustomWindow::mousePressEvent(event);
}

void ColorPickerWidget::mouseReleaseEvent(QMouseEvent * event)
{
	if (m_bPickerColor)
		m_bPickerColor = false;

	QCustomWindow::mouseReleaseEvent(event);
}

void ColorPickerWidget::mouseMoveEvent(QMouseEvent * event)
{
	QCustomWindow::mouseMoveEvent(event);

	if (!m_bPickerColor)
		return;

	INVDK_INT x = QCursor::pos().x() + 1;
	INVDK_INT y = QCursor::pos().y() + 1;

	QScreen* screen = qApp->primaryScreen();
	QPixmap pixmap = screen->grabWindow(0, x, y, 1, 1);

	if (pixmap.isNull())
		return;

	QImage image = pixmap.toImage();
	if (image.valid(0, 0))
	{
		INVDKUI_RGB color = image.pixel(0, 0);
		m_red = INVDKUI::red(color);
		m_green = INVDKUI::green(color);
		m_blue = INVDKUI::blue(color);
		m_alpha = INVDKUI::alpha(color);
	}

	//根据背景色自动计算合适的前景色
	INVDKUI_RGB color = INVDKUI::rgb(m_red, m_green, m_blue);
	INVDK_DOUBLE gray = (0.299 * INVDKUI::red(color) + 0.587 * INVDKUI::green(color) + 0.114 * INVDKUI::blue(color)) / 255;
	QColor textColor = gray > 0.5 ? Qt::black : Qt::white;

	QString str = tr("background:rgba(%1, %2, %3, %4);color:%5").arg(m_red).arg(m_green).arg(m_blue).arg(m_alpha).arg(textColor.name());
	ui->labelColor->setStyleSheet(str);

	QString text;
	text = tr(" R:") + QString::number(m_red) +
		tr(" G:") + QString::number(m_green) +
		tr(" B:") + QString::number(m_blue) +
		tr(" A:") + QString::number(m_alpha);
	ui->labelPosColor->setText(tr("X:") + QString::number(x) + tr(" Y:") + QString::number(y) + "<br><br>" + text);

}