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
    
    if(username.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please insert a username ");
        return;
    }
    
    QMessageBox::information(this, "Connection", 
        QString("Connecting to lobby as %2").arg(username));

    emit connectToLobby();
    this->close();
}