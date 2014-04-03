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

    QStringList strList = ssss.trimmed().split(" ");
    if (strList.at(1) == "PRIVMSG") {
        qDebug("privmsg");
//        qDebug(qPrintable(strList.at(2)));

        QString channel = strList.at(2);
        QString msg = strList.at(3);
        qDebug("%s %s", qPrintable(channel), qPrintable(msg));

        QString echo = "PRIVMSG " + channel + " " + msg;
        _socket->write(echo.toLocal8Bit());

        IRCMessage im;
        im.channel = channel;
        im.msg = msg;
        emit addMessage(im);

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
