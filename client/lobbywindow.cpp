#include "lobbywindow.h"
#include "ui_Lobby.h"
#include <QMessageBox>
#include <QListWidgetItem>

LobbyWindow::LobbyWindow(const QString& username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lobby)
    , username(username)
{
    ui->setupUi(this);
    setWindowTitle("CS2D Lobby - " + username);
    
    ui->matchesList->setIconSize(QSize(32, 32));
    
    populateMatchesList();
}

LobbyWindow::~LobbyWindow()
{
    delete ui;
}

void LobbyWindow::populateMatchesList()
{
    ui->matchesList->clear();
    
    // Hardcodeo algunas partidas para que se vean
    QList<QStringList> matches = {
        // Formato: Nombre, Mapa, Jugadores actuales, Jugadores máximos
        {"Competitive Match", "de_dust2", "4", "10"},
        {"Casual Game", "cs_italy", "6", "12"},
        {"Tournament Practice", "de_inferno", "8", "10"},
        {"New Players Only", "de_mirage", "2", "10"},
        {"Headshot Only", "de_nuke", "5", "8"}
    };
    
    for (const auto& match : matches) {
        QString matchText = QString("%1\nMap: %2\nPlayers: %3/%4")
                              .arg(match[0])  // Nombre
                              .arg(match[1])  // Mapa
                              .arg(match[2])  // Jugadores actuales
                              .arg(match[3]); // Jugadores máximos
        
        QListWidgetItem* item = new QListWidgetItem(matchText, ui->matchesList);
        
        // Guardar datos adicionales en el item (opcional)
        item->setData(Qt::UserRole, match[0]); // Guardar nombre como dato extra
    }
}

void LobbyWindow::on_refreshButton_clicked()
{
    // Simular actualización de la lista
    QMessageBox::information(this, "Refreshing", "Match list updated");
    populateMatchesList();
}

void LobbyWindow::on_joinMatchButton_clicked()
{
    QListWidgetItem* selected = ui->matchesList->currentItem();
    if (!selected) {
        QMessageBox::warning(this, "Error", "Please select a match first");
        return;
    }
    //aca tengo que enviar el comando de unirme a partida al servidor
    QString matchName = selected->data(Qt::UserRole).toString();
    QMessageBox::information(this, "Joining Match", 
        QString("%1 is joining match: %2").arg(username).arg(matchName));
}

void LobbyWindow::on_createMatchButton_clicked()
{
    QMessageBox::information(this, "Create Match", 
        QString("%1 is creating a new match").arg(username));
    
    // aca tengo que enviar el comando de crear partida al servidor
    QListWidgetItem* newItem = new QListWidgetItem(
        QString("New Match by %1\nMap: de_dust2\nPlayers: 1/10").arg(username),
        ui->matchesList
    );
    newItem->setData(Qt::UserRole, QString("New Match by %1").arg(username));
}