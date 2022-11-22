#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QObject>
#include <QUdpSocket>

class UdpSender : public QObject
{
    Q_OBJECT

public:
    explicit UdpSender(QHostAddress _to_ip, quint16 _to_port, QObject *parent = nullptr);
    ~UdpSender();


private:
    QUdpSocket* socket;
    QHostAddress ip;
    quint16 port;

public slots:
    void _kill();
    void send(QByteArray datagram);

private slots:
    void _init();


signals:
    void _killThread();
};

#endif // UDPSENDER_H
