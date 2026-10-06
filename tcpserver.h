#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QDebug>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    // 双参数listen，匹配 main 里 server.listen(QHostAddress::Any,8888);
    bool listen(const QHostAddress &address, quint16 port);

private:
    QTcpServer *m_tcpServer;
    QTcpSocket *m_socket;
    // 粘包新增变量
    QByteArray m_recvBuf;
    quint32 m_waitLen = 0;

private slots:
    void onNewConnection();
    void onReadyRead();
    void sendMsg(const QByteArray &data);
};

#endif
