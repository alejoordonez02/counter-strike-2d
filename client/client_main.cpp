#include <QApplication>
#include <QEventLoop>

#include "client/client.h"
#include "mainwindow.h"
#include "client/q_game_details_dto.h"

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
    qputenv("QT_LOGGING_RULES", "qt.qpa.wayland=false");
    qRegisterMetaType<QGameDetailsDTO>();
    MainWindow mainWindow;
    mainWindow.show();

    QObject::connect(&mainWindow, &MainWindow::connectToLobby,
                     [&](const QString& host, const QString& serv) {
                         mainWindow.close();
                         Client client(host.toStdString(), serv.toStdString());
                         client.run();
                     });

    return a.exec();
}
