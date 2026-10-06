#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QDebug>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    void connectToServer(const QString &ip, quint16 port);

private:
    QTcpSocket *m_socket;
    // 粘包新增变量
    QByteArray m_recvBuf;
    quint32 m_waitLen = 0;

private slots:
    void onReadyRead();
    void sendMsg(const QByteArray &data);
};

#endif
