#include "headers/udpsender.h"


UdpSender::UdpSender(QHostAddress _to_ip, quint16 _to_port, QObject *parent) : QObject(parent) {
    ip = _to_ip;
    port = _to_port;
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


