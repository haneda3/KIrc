#include <QApplication>
#include "html5applicationviewer.h"

#include "client.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Client client;
    client.connectToServer();

    Html5ApplicationViewer viewer;
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.showExpanded();
    viewer.loadFile(QLatin1String("html/index.html"));

    app.connect(&client, SIGNAL(addMessage(IRCMessage)), &viewer, SLOT(addIRCMessage(IRCMessage)));

//    Client* client = new Client();
    //client->connectToServer();
    return app.exec();
}

