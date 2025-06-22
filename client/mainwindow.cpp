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
    QString host = ui->hostInput->text();
    QString serv = ui->servInput->text();
    
    if(serv.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please insert a serv ");
        return;
    }

    if(host.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please insert a host ");
        return;
    }
    
    QMessageBox::information(this, "Connection", 
        QString("Connecting to %1:%2").arg(host).arg(serv));

    emit connectToLobby(host, serv);
    this->close();
}