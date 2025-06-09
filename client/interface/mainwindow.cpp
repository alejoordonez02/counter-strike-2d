#include "mainwindow.h"
#include "ui_ClientInterface.h" 
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QSize>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientInterface),
{
    ui->setupUi(this);
    setupUI();
    loadConfigurations();
    connectSignals();
}

void MainWindow::setupUI() {
    
}

void MainWindow::connectSignals() {

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_StartButton_clicked()
{

}

void MainWindow::on_JoinMatchButton_clicked()
{
    
}

void MainWindow::on_CreateMatchButton_clicked()
{

}