#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent)
    : QTcpSocket(parent)
{
    connect(this, &QTcpSocket::readyRead, this, [=](){
        QByteArray data = this->readAll();
        qDebug() << "客户端收到服务器回复：" << data;
    });

    connect(this, &QTcpSocket::connected, this, [=](){
        qDebug() << "客户端成功连上服务器";
        this->write("Hello Server!");
    });

    connect(this, &QTcpSocket::errorOccurred, this, [=](QAbstractSocket::SocketError err){
        qDebug() << "客户端连接错误：" << this->errorString();
    });
}

void TcpClient::connectToServer(const QString &ip, quint16 port)
{
    this->connectToHost(ip, port);
}
