#include "client.h"
#include <QHostAddress>
#include <sstream>
using std::stringstream;


Client::Client(QObject *parent) :
    QObject(parent)
{
    _socket = new QTcpSocket(this);
    connect(_socket, SIGNAL(connected()), this, SLOT(on_connected()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
    connect(_socket,
            SIGNAL(error(QAbstractSocket::SocketError)),
            this,
            SLOT(displayError(QAbstractSocket::SocketError))
            );
    connect(_socket, SIGNAL(readyRead()), this, SLOT(on_read()));

    connect(this, SIGNAL(addMessage(IRCMessage)), this, SLOT(getMessage(IRCMessage)));
}

void Client::on_connected()
{
//    _socket->connectToHost(QHostAddress::LocalHost, 1234);
//    QByteArray* byte = new QByteArray
//    _socket->write()
    QString nick = "NICK testhaneda\n";
    QString user = "USER name host sever realname\n";

    QString join = "JOIN #testha\n";

    _socket->write(nick.toLocal8Bit());
    _socket->write(user.toLocal8Bit());
    _socket->write(join.toLocal8Bit());
    _socket->flush();

//    _socket
//    _socket->write(nick, strlen(nick));
//    _socket->write(user, strlen(user));
//    _socket->write(join, strlen(join));
}

void Client::on_read()
{
    qDebug("%s", "on_readyRead");
//    QDataStream readStream(_socket);
//    QDataStream stream();
//    QString str;
//    str<<readStream;
//    readStream>>str;
//    qDebug("%s", qPrintable(str));
/*
    quint16 next_block_size = 0;
    while(true) {
        if (!next_block_size) {
            if (_socket->bytesAvailable() < sizeof(quint16)) { // are size data available
                break;
            }
            readStream >> next_block_size;
        }

        if (_socket->bytesAvailable() < next_block_size) {
            break;
        }
        QString str;
        readStream >> str;

        next_block_size = 0;
    }
*/
    #define BUF_SIZE 16
    char buf[BUF_SIZE];
    std::stringstream sts;

    while (true) {
        if (_socket->bytesAvailable() <= 0) {
            break;
        }

        qint64 read_size = _socket->read(buf, BUF_SIZE);
        sts.write(buf, read_size);
//        if (read_size < 0) {

//        }
    }
    std::string sss(sts.str());
    QString ssss(sss.c_str());
    qDebug("%s", qPrintable(ssss));
//    char* ss;
//    readStream >> ss;
//    std::string sString(ss);
//    QString sss(sString.c_str());
//    qDebug("%s", qPrintable(sss));
/*


//     char buffer[12800];

//     char *buffer;

//     buffer = new char[_socket->bytesAvailable()];


     _socket->read(buffer, _socket->bytesAvailable());
     std::string sString(buffer);
     QString qString(sString.c_str());

//     ui->textEdit->setText(qString);
     qDebug("%s", qPrintable(qString));
*/
    int n = ssss.indexOf("PING ");
    if (n >= 0) {
        QString x = ssss.replace("PING ", "");
        qDebug("%s", qPrintable(x));
        QString pong = QString("PONG ");
        pong.append(x);
        qDebug("%s", qPrintable(pong));
        _socket->write(pong.toLocal8Bit());

        return;
    }

    QRegExp regex("^(\\S+)\\s+(\\S+)\\s+(.+)$");
    QString sx = ssss.trimmed();
    regex.indexIn(sx);

    if (regex.captureCount() != 3) {
        qDebug("fail paarse command");
        return;
    }
    QString prefix = regex.cap(1);
    QString command = regex.cap(2);
    QString params = regex.cap(3);

    qDebug("prefix %s", qPrintable(prefix));
    qDebug("command %s", qPrintable(command));
    qDebug("params %s", qPrintable(params));

    if (command == "PRIVMSG") {
        qDebug("find PRIVMSG command");
        QRegExp privmsgRegex("^#(\\S+)\\s+(.+)$");
        privmsgRegex.indexIn(params);
        if (privmsgRegex.captureCount() != 2) {
            qDebug("fail parse privmsg Command");
            return;
        }

        QString channel = privmsgRegex.cap(1);
        QString msg = privmsgRegex.cap(2);
        qDebug("%s/%s", qPrintable(channel), qPrintable(msg));

        IRCMessage im;
        im.channel = channel;
        im.msg = msg;
        emit addMessage(im);

        // echo test
        QString echo = "PRIVMSG #" + channel + " " + msg + "\r\n";
        qDebug("%s", qPrintable(echo));
        QByteArray ec = echo.toLocal8Bit();
        _socket->write(echo.toLocal8Bit());

        return;
    }



     qDebug("%s", "on_readyRead　end");
}

void Client::getMessage(IRCMessage message) {
    qDebug("A");
}


void Client::on_disconnected()
{

}

void Client::connectToServer()
{
//    _socket->connectToHost(QHostAddress::LocalHost, 1234);
    QHostAddress host("183.181.22.185");
    qDebug() << host;
//            QHostAddress a;
  //          a = QHostAddress( "127.0.0.1" );
    //        QString b;
      //      b = a.toString();
        //    qDebug() << b;
    _socket->connectToHost(QHostAddress("183.181.22.185"), 6666);
}

void Client::sendMessage(const IRCMessage message)
{
    QString sendCommand = "PRIVMSG #" + message.channel + " " + ":" + message.msg + "\r\n";
    qDebug("%s", qPrintable(sendCommand));
    _socket->write(sendCommand.toLocal8Bit());
}
