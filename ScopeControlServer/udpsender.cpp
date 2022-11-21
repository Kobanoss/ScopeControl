#include "udpsender.h"

UdpSender::UdpSender(QHostAddress to_ip, quint16 to_port, QObject *parent) : QObject(parent) {
    ip = to_ip;
    port = to_port;
}

UdpSender::~UdpSender() {
    ip.clear();
    socket->close();
    delete socket;

}

void UdpSender::_init() {
    socket = new QUdpSocket;
}

void UdpSender::_kill() {
    emit _killThread();
    this->~UdpSender();
}

void UdpSender::send(QByteArray datagram) {
    socket->writeDatagram(datagram, ip, port);
}


