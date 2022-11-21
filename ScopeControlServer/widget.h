#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include <QUdpSocket>
#include <QTimer>
#include <udpsender.h>

#define RECEIVER_IP QHostAddress::LocalHost
#define RECEIVER_PORT 50000

QT_BEGIN_NAMESPACE
namespace Ui {
    class Widget;
} QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_Send_clicked();
    void on_horizontalSlider_Angle_valueChanged(int value);
    void on_horizontalSlider_OffsetV_valueChanged(int value);
    void on_horizontalSlider_OffsetH_valueChanged(int value);

private:
    qreal angle = 2;
    qreal offset_v{};
    qreal offset_h{};

    QThread* sending_thread;
    UdpSender* sender;

    Ui::Widget *ui;

signals:
    void _killSender();
    void send(QByteArray datagram);
};

#endif // WIDGET_H
