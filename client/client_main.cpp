#include <QApplication>
#include <iostream>

#include "client/client.h"
#include "mainwindow.h"
#include <QEventLoop>

int main(int argc, char** argv) {
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    QEventLoop mainLoop;

    QObject::connect(&mainWindow, &MainWindow::connectToLobby, [&](const QString& host,const QString& serv) {
        mainWindow.close();
        Client client(host.toStdString(), serv.toStdString());
        client.run(0);
    });

    mainLoop.quit();
    return a.exec();
}
