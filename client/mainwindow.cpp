#include "mainwindow.h"
#include "ui_ClientInterface.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientInterface)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString serverAddress = ui->serverAddressInput->text();
    
    if(username.isEmpty() || serverAddress.isEmpty()) {
        QMessageBox::warning(this, "Error", "Complete all ");
        return;
    }
    
    QMessageBox::information(this, "Connection", 
        QString("Connecting to %1 as %2").arg(serverAddress).arg(username));
}

void MainWindow::on_joinMatchButton_clicked()
{
    QString serverAddress = ui->serverAddressInput->text().trimmed();
    
    if (serverAddress.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter server address (host:port)");
        return;
    }

    QStringList parts = serverAddress.split(':');
    if (parts.size() != 2) {
        QMessageBox::warning(this, "Error", "Invalid format. Use host:port (e.g. localhost:8080)");
        return;
    }

    QString host = parts[0];
    QString port = parts[1];
    
    bool ok;
    int portNumber = port.toInt(&ok);
    if (!ok || portNumber < 1 || portNumber > 65535) {
        QMessageBox::warning(this, "Error", "Invalid port number (1-65535)");
        return;
    }

    emit connectToServer(host, port);
}

void MainWindow::on_createMatchButton_clicked()
{
    QMessageBox::information(this, "Creating a match", 
        "Creating match");
}