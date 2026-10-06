#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

protected:
    // 有新客户端接入时触发
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QTcpSocket *m_clientSocket = nullptr;
};

#endif // TCPSERVER_H
