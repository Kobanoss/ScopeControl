#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    rec_thread = new QThread;
    receiver = new UdpReceiver(LISTENING_PORT);

    receiver->moveToThread(rec_thread);

    connect(rec_thread, SIGNAL(started()), receiver, SLOT(_init()), Qt::DirectConnection);
    connect(receiver, &UdpReceiver::received, this, &Widget::getDatagram, Qt::QueuedConnection);
    connect(this, &Widget::_killReceiver, receiver, &UdpReceiver::_kill, Qt::DirectConnection);
    connect(receiver, &UdpReceiver::_killThread, rec_thread, &QThread::terminate,  Qt::DirectConnection);

    rec_thread->start();
}

Widget::~Widget() {
    emit _killReceiver();
    QTimer::singleShot(1000, this, [this] () {
        delete ui;
    });;
}

void Widget::getDatagram(QByteArray datagram) {
    QString data = QString(datagram);
    QStringList data_list = data.split(' ');
    angle = data_list.at(0).toDouble();
    offset_h = data_list.at(1).toDouble();
    offset_v = data_list.at(2).toDouble();
    setLabels();
}


void Widget::setLabels() {
    ui->label_value_Angle->setText(QString::number(angle));
    ui->label_value_OffsetH->setText(QString::number(offset_h));
    ui->label_value_OffsetV->setText(QString::number(offset_v));
}
