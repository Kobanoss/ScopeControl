#include "udpreceiver.h"

UdpReceiver::UdpReceiver(quint16 _listening_port, QObject *parent) : QObject(parent) {
    port = _listening_port;
    datagram = nullptr;
}

UdpReceiver::~UdpReceiver() {
    datagram.clear();
    socket->close();
    delete socket;
}


void UdpReceiver::_init() {
    socket = new QUdpSocket;
    socket->bind(port,QUdpSocket::ShareAddress);
    socket->connect(socket, &QUdpSocket::readyRead, this, &UdpReceiver::readPendingDatagrams);
}

void UdpReceiver::_kill() {
    emit _killThread();
    this->~UdpReceiver();
}


void UdpReceiver::readPendingDatagrams() {
    if (!socket->hasPendingDatagrams()) {
        return;
    }

    QHostAddress sender_ip;
    quint16 sender_port;

    datagram.resize(socket->pendingDatagramSize());
    socket->readDatagram(datagram.data(), datagram.size(), &sender_ip, &sender_port);
    emit received(datagram);
}
