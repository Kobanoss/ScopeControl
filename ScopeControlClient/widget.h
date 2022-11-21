#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <udpreceiver.h>

#define LISTENING_PORT 50000

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
} QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    qreal angle = 2;
    qreal offset_v{};
    qreal offset_h{};

    QThread* rec_thread;
    UdpReceiver* receiver;

    void getDatagram(QByteArray datagram);

    void setLabels();

    Ui::Widget *ui;

signals:
    void _killReceiver();
};

#endif // WIDGET_H
