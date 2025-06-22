#include <QApplication>
#include <QEventLoop>

#include "client/client.h"
#include "mainwindow.h"

using namespace DTOSerial::LobbyCommands;

int main(int argc, char** argv) {
    if (argc == 4) {
        std::string hostname = argv[1];
        std::string servname = argv[2];
        Client client(hostname, servname);
        client.run(1);
        return 0;
    }

    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    QEventLoop mainLoop;

    QObject::connect(&mainWindow, &MainWindow::connectToLobby,
                     [&](const QString& host, const QString& serv) {
                         mainWindow.close();
                         Client client(host.toStdString(), serv.toStdString());
                         client.run();
                     });

    mainLoop.quit();
    return a.exec();
}
