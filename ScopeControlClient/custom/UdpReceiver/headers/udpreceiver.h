#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>


class UdpReceiver : public QObject {
    Q_OBJECT
public:
    explicit UdpReceiver(quint16 _listening_port, QObject *parent = nullptr);
    ~UdpReceiver();

private:
    QUdpSocket* socket;
    quint16 port;
    QByteArray datagram;

    void readPendingDatagrams();

public slots:
    void _kill();

private slots:
    void _init();

signals:
    void _killThread();
    void received(QByteArray datagram);
};

#endif // UDPRECEIVER_H
