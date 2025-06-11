#include <iostream>
#include "mainwindow.h"
#include <QApplication>
#include "client/client.h"

int main(int argc, char** argv) {
    if (argc == 3) {
        // ONLY FOR DEVELOPMENT: se inicia cliente con los argumentos pasados, saltea el lobby
        Client client(argv[1], argv[2]);
        client.run();
        return 0;
    }
    QApplication a(argc, argv);

    try {
        MainWindow w;
        w.show();
        
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
