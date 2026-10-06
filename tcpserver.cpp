#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
    : QTcpServer(parent)
{
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    m_clientSocket = new QTcpSocket(this);
    m_clientSocket->setSocketDescriptor(socketDescriptor);

    qDebug() << "客户端连接成功";

    connect(m_clientSocket, &QTcpSocket::readyRead, this, [=](){
        QByteArray data = m_clientSocket->readAll();
        qDebug() << "收到客户端数据：" << data;
        m_clientSocket->write("Server received your message!");

    });

    connect(m_clientSocket, &QTcpSocket::disconnected, this, [=](){
        qDebug() << "客户端断开";
        m_clientSocket->deleteLater();
    });
}
