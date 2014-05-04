#ifndef IRCMESSAGE_H
#define IRCMESSAGE_H

#include <QObject>

class IRCMessage
{
public:
    QString channel;
    QString nick;
    QString msg;
};

class Line
{
public:
    Line(QString line) {
        QRegExp regex("^:(\\S+)\\s+(\\S+)\\s+(.+)$");
        regex.indexIn(line);

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

        _prefix = prefix;
        _command = command;
        _params = params;

        _user = "";
        _host = "";

        int hostIndex = prefix.indexOf('@');
        if (hostIndex != -1) {
            _host = prefix.mid(hostIndex);
            prefix = prefix.left(hostIndex);
        }
        int userIndex = prefix.indexOf("!");
        if (userIndex != -1) {
            _user = prefix.mid(userIndex);
            prefix = prefix.left(userIndex);
        }

        _nick = prefix;
    }

    QString _prefix;

    QString _nick;
    QString _user;
    QString _host;

    QString _command;
    QString _params;

    QString prefix() {
        return _prefix;
    }

    QString nick() {
        return _nick;
    }

    QString host() {
        return _host;
    }

    QString command() {
        return _command;
    }

    QString params() {
        return _params;
    }
};

#endif // IRCMESSAGE_H
