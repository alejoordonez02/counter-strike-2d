#include <QApplication>
#include <iostream>

#include "client/client.h"

#include "mainwindow.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);
    if (argc == 4) {
        // ONLY FOR DEVELOPMENT: se inicia cliente con los argumentos pasados,
        // saltea el lobby
        Client client(argv[1], argv[2]);
        client.run(std::stoi(argv[3]));
    }
    return a.exec();
}
