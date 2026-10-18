#include <QApplication>
#include <QLabel>
#include <QTcpSocket>
#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QLabel label("Connecting...");
    label.resize(500, 300);
    label.show();

    auto* socket = new QTcpSocket(&app);

    QObject::connect(
        socket,
        &QTcpSocket::connected,
        [&label, socket]()
        {
            label.setText("Connected to DeviceSimulator");
            socket->write("HELLO\n");
        }
    );

    QObject::connect(
        socket,
        &QTcpSocket::readyRead,
        [&label, socket]()
        {
            const QByteArray data = socket->readAll();
            qDebug() << "Simulator response:" << data;
            label.setText("DeviceSimulator connected");
        }
    );

    QObject::connect(
        socket,
        &QTcpSocket::errorOccurred,
        [&label, socket](QAbstractSocket::SocketError)
        {
            label.setText(
                "Connection failed: " + socket->errorString()
            );
        }
    );

    socket->connectToHost("127.0.0.1", 9000);

    return app.exec();
}