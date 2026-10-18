#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    QTcpServer server;

    QObject::connect(
        &server,
        &QTcpServer::newConnection,
        [&server]()
        {
            while (server.hasPendingConnections()) {
                QTcpSocket* socket = server.nextPendingConnection();

                qDebug() << "Client connected:"
                         << socket->peerAddress()
                         << socket->peerPort();

                QObject::connect(
                    socket,
                    &QTcpSocket::readyRead,
                    [socket]()
                    {
                        const QByteArray data = socket->readAll();

                        qDebug() << "Received:" << data;

                        socket->write("SIMULATOR_OK\n");
                        socket->flush();
                    }
                );

                QObject::connect(
                    socket,
                    &QTcpSocket::disconnected,
                    socket,
                    &QTcpSocket::deleteLater
                );
            }
        }
    );

    if (!server.listen(QHostAddress::LocalHost, 9000)) {
        qCritical() << "Failed to listen:" << server.errorString();
        return 1;
    }

    qDebug() << "Device simulator listening on 127.0.0.1:9000";

    return app.exec();
}