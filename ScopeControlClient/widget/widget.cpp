#include "headers/widget.h"
#include "ui_widget.h"
#include "config/conf.h"


Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    angle = BASE_ANGLE;
    offset_h = BASE_OFFSET_X;
    offset_v = BASE_OFFSET_Y;

    stylesheet_map = {{0, "grey"},
                      {1, "white"},
                      {2, "black"}};\

    scope_path_map = {{0, ":/crosshair/crosshair red.svg"},
                      {1, ":/crosshair/crosshair black.svg"}};

    rec_thread = new QThread;
    receiver = new UdpReceiver(LISTENING_PORT);

    receiver->moveToThread(rec_thread);

    connect(rec_thread, SIGNAL(started()), receiver, SLOT(_init()), Qt::DirectConnection);
    connect(receiver, &UdpReceiver::received, this, &Widget::getDatagram, Qt::QueuedConnection);
    connect(this, &Widget::_killReceiver, receiver, &UdpReceiver::_kill, Qt::DirectConnection);
    connect(receiver, &UdpReceiver::_killThread, rec_thread, &QThread::terminate,  Qt::DirectConnection);

    rec_thread->start();

    painter_widget = new PainterWidget(scope_path_map.value(0), ui->widget_image);
    connect(this, &Widget::changeScopeColor, painter_widget, &PainterWidget::updateScopeColor);
    connect(this, &Widget::changeScopeGeometry, painter_widget, &PainterWidget::updateScopeGeometry);
    ui->gridLayout_image->addWidget(painter_widget);

    painter_widget->repaint();
}

Widget::~Widget() {
    delete painter_widget;
    emit _killReceiver();
    rec_thread->wait();
    delete ui;
}


void Widget::getDatagram(QByteArray datagram) {
    QString data = QString(datagram);
    QStringList data_list = data.split(' ');
    angle = data_list.at(0).toDouble();
    offset_h = data_list.at(1).toDouble();
    offset_v = data_list.at(2).toDouble();
    setLabels();
    calculateScopeGeometry();
}

void Widget::calculateScopeGeometry() {
    emit changeScopeGeometry(offset_h, offset_v, angle);
}

void Widget::setLabels() {
    ui->label_value_Angle->setText(QString::number(angle));
    ui->label_value_OffsetH->setText(QString::number(offset_h));
    ui->label_value_OffsetV->setText(QString::number(offset_v));
}


void Widget::resizeEvent(QResizeEvent*) {
    QSize block_size = ui->gridLayout_Main->geometry().size();
    qreal aspect_ratio = (qreal)block_size.height() / block_size.width();
    qreal widget_stretch, spacesers_stretch{};

    if (aspect_ratio == FIXED_AR) {
        ui->widget_image->resize(block_size);

        ui->gridLayout_Main->setColumnStretch(0, spacesers_stretch);
        ui->gridLayout_Main->setColumnStretch(2, spacesers_stretch);
        ui->gridLayout_Main->setRowStretch(0, spacesers_stretch);
        ui->gridLayout_Main->setRowStretch(2, spacesers_stretch);
        return;
    }

    if (aspect_ratio < (FIXED_AR)) {
        widget_stretch = block_size.height() * (1/FIXED_AR);

        ui->gridLayout_Main->setColumnStretch(0, (block_size.width() - widget_stretch)/2 + 0.5);
        ui->gridLayout_Main->setColumnStretch(1, widget_stretch);
        ui->gridLayout_Main->setColumnStretch(2, (block_size.width() - widget_stretch)/2 + 0.5);
        return;
    }
    widget_stretch = block_size.width() * FIXED_AR;

    ui->gridLayout_Main->setRowStretch(0, (block_size.height() - widget_stretch)/2 + 0.5);
    ui->gridLayout_Main->setRowStretch(1, widget_stretch);
    ui->gridLayout_Main->setRowStretch(2, (block_size.height() - widget_stretch)/2 + 0.5);
    return;
}


void Widget::on_comboBox_background_activated(int index) {
    ui->widget_image->setStyleSheet("background-color:"+stylesheet_map.value(index));
}


void Widget::on_comboBox_crosshair_color_activated(int index){
    emit changeScopeColor(scope_path_map.value(index));
}
