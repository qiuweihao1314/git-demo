#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
    : QObject(parent)
{
    m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
}

bool TcpServer::listen(const QHostAddress &address, quint16 port)
{
    return m_tcpServer->listen(address, port);
}

void TcpServer::onNewConnection()
{
    m_socket = m_tcpServer->nextPendingConnection();
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
}

void TcpServer::onReadyRead()
{
    m_recvBuf.append(m_socket->readAll());

    while(true)
    {
        if(m_waitLen == 0)
        {
            if(m_recvBuf.size() >= 4)
            {
                QByteArray head = m_recvBuf.left(4);
                m_waitLen = *(quint32*)head.data();
                m_recvBuf.remove(0,4);
            }
            else
            {
                break;
            }
        }
        else
        {
            if(m_recvBuf.size() >= m_waitLen)
            {
                QByteArray body = m_recvBuf.left(m_waitLen);
                qDebug() << "收到完整消息：" << body;

                // 收到消息可以回复示例
                // sendMsg("服务端收到你的消息");

                m_recvBuf.remove(0, m_waitLen);
                m_waitLen = 0;
            }
            else
            {
                break;
            }
        }
    }
}

void TcpServer::sendMsg(const QByteArray &data)
{
    QByteArray sendBuf;
    quint32 len = data.size();
    sendBuf.append((char*)&len, 4);
    sendBuf.append(data);
    m_socket->write(sendBuf);
}
