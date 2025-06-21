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
        QString("Connecting to server as %2").arg(username));
    LobbyWindow *lobbyWindow = new LobbyWindow(username);
    lobbyWindow->setAttribute(Qt::WA_DeleteOnClose); 
    lobbyWindow->show();

    this->close();
}