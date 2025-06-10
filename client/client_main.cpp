#include <iostream>
#include "mainwindow.h"
#include <QApplication>
#include "client/client.h"

int main(int argc, char** argv) {
    /*
    if (argc < 2) {
        std::cerr << "Bad call. Usage: " << argv[0] << ". No args expected"
                  << std::endl;
        return EXIT_FAILURE;
    }
    */
    QApplication a(argc, argv);

    try {
        MainWindow w;
        w.show();
        // TODO: Ejecutar el lobby de QT
        // TODO: Logica de lobby, de aca obtiene socker (puerto, ip), nombre
        // jugador, partida, etc. Socket socket = lobby->getSocket() int
        // player_id = lobby->getPlayerID()
        // ...
        QObject::connect(&w, &MainWindow::connectToServer, [&](const QString& host, const QString& port) {
            try {
                std::cout << "Connecting to " << host.toStdString() << ":" << port.toStdString() << std::endl;
                auto client = std::make_unique<Client>(host.toStdString(), port.toStdString());
                client->run();
            } catch (const std::exception& e) {
                w.showError(QString("Connection error: %1").arg(e.what()));
            }
        });
        
        return a.exec();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
