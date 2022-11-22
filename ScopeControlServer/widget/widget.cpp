#include "headers/widget.h"
#include "ui_widget.h"
#include "config/conf.h"


Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    angle = BASE_ANGLE;
    offset_h = BASE_OFFSET_X;
    offset_v = BASE_OFFSET_Y;

    sending_thread = new QThread;
    sender = new UdpSender(RECEIVER_IP, RECEIVER_PORT);

    sender->moveToThread(sending_thread);

    connect(sending_thread, SIGNAL(started()), sender, SLOT(_init()), Qt::DirectConnection);
    connect(this, &Widget::send, sender, &UdpSender::send, Qt::QueuedConnection);
    connect(this, &Widget::_killSender, sender, &UdpSender::_kill, Qt::DirectConnection);
    connect(sender, &UdpSender::_killThread, sending_thread, &QThread::terminate,  Qt::DirectConnection);

    sending_thread->start();

}

Widget::~Widget() {
    emit _killSender();
    sending_thread->wait();
    delete ui;
}


void Widget::on_pushButton_Send_clicked() {
    QString datagram = (QString::number(angle) + " " + QString::number(offset_h) + " " + QString::number(offset_v));
    emit send(datagram.toUtf8());
}


void Widget::on_horizontalSlider_Angle_valueChanged(int value) {
    angle = qreal(value)/100;
    ui->label_value_Angle->setText(QString::number(angle));
}

void Widget::on_horizontalSlider_OffsetV_valueChanged(int value) {
    offset_v = qreal(value)/100;
    ui->label_value_OffsetV->setText(QString::number(offset_v));
}

void Widget::on_horizontalSlider_OffsetH_valueChanged(int value) {
    offset_h = qreal(value)/100;
    ui->label_value_OffsetH->setText(QString::number(offset_h));
}
