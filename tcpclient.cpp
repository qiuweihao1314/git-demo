#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent)
    : QObject(parent)
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
}

void TcpClient::connectToServer(const QString &ip, quint16 port)
{
    m_socket->connectToHost(ip, port);
}

void TcpClient::onReadyRead()
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
                qDebug() << "客户端收到完整消息：" << body;

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

void TcpClient::sendMsg(const QByteArray &data)
{
    QByteArray sendBuf;
    quint32 len = data.size();
    sendBuf.append((char*)&len, 4);
    sendBuf.append(data);
    m_socket->write(sendBuf);
}
