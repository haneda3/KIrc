#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include <QTcpSocket>
#include "ircmessage.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void connectToServer();
    void sendMessage(const IRCMessage message);

signals:
    void addMessage(IRCMessage message);
    void addChannel(IRCChannel channel);

public slots:
    void on_connected();
    void on_disconnected();
    void on_read();

private:
    QTcpSocket* _socket;

protected:
    void parseMessage(QString message);
};

#endif // CLIENT_H
