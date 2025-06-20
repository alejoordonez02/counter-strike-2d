#include "lobbywindow.h"
#include "creatematchdialog.h"
#include "ui_Lobby.h"
#include <QMessageBox>
#include <QListWidgetItem>

LobbyWindow::LobbyWindow(const QString& username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lobby)
    , username(username)
{
    ui->setupUi(this);
    populateMatchesList();
}

LobbyWindow::~LobbyWindow()
{
    delete ui;
}

void LobbyWindow::populateMatchesList()
{
    ui->matchesList->clear();
    // aca tendria que recibir las partidas del servidor y cargarlas
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
        item->setData(Qt::UserRole, match[0]);
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
    CreateMatchDialog dialog(username, this);
    
    if (dialog.exec() == QDialog::Accepted) {
        QString matchName = dialog.getMatchName();
        QString configPath = dialog.getConfigPath();
        int maxPlayers = dialog.getMaxPlayers();
        
        // Validar campos
        if (matchName.isEmpty()) {
            QMessageBox::warning(this, "Error", "Match name cannot be empty");
            return;
        }
        
        if (configPath.isEmpty()) {
            QMessageBox::warning(this, "Error", "You must select a configuration file");
            return;
        }
        
        // Enviar comando al servidor
        try {
            // Aquí iría tu lógica para enviar el comando al servidor
            // Por ejemplo:
            // client->sendCreateMatchCommand(matchName, configPath, maxPlayers);
            
            // Añadir a la lista local (simulación)
            QListWidgetItem* newItem = new QListWidgetItem(
                QString("%1\nMap: %2\nPlayers: 1/%3")
                    .arg(matchName)
                    .arg(QFileInfo(configPath).baseName())
                    .arg(maxPlayers),
                ui->matchesList
            );
            
            newItem->setData(Qt::UserRole, matchName);
            
            QMessageBox::information(this, "Success", 
                QString("Match '%1' created successfully!").arg(matchName));
            
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", 
                QString("Failed to create match: %1").arg(e.what()));
        }
    }
}