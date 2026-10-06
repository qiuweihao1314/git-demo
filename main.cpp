#include <QCoreApplication>
#include "tcpserver.h"
#include "tcpclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 启动服务器，监听端口8888
    TcpServer server;
    if(server.listen(QHostAddress::LocalHost, 8888))
    {
        qDebug() << "服务器启动成功，端口8888";
    }else{
        qDebug() << "服务器启动失败";
    }

    // 创建客户端，连接本机服务器
    TcpClient client;
    client.connectToServer("127.0.0.1", 8888);

    return a.exec();
}
