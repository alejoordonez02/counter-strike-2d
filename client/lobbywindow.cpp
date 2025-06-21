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
    QList<MatchInfo> matches = {
        MatchInfo("Competitive Match", "de_dust2", 4, 10),
        MatchInfo("Casual Game", "cs_italy", 6, 12),
        MatchInfo("Tournament Practice", "de_inferno", 10, 10),
        MatchInfo("New Players Only", "de_mirage", 2, 10),
        MatchInfo("Headshot Only", "de_nuke", 5, 8)
    };
    
    for (const auto& match : matches) {
        QString matchText = QString("%1\nMap: %2\nPlayers: %3/%4")
                          .arg(match.name)
                          .arg(match.map)
                          .arg(match.currentPlayers)
                          .arg(match.maxPlayers);
        
        QListWidgetItem* item = new QListWidgetItem(matchText, ui->matchesList);
        item->setData(Qt::UserRole, QVariant::fromValue(match));
        
        if (match.currentPlayers >= match.maxPlayers) {
            item->setForeground(Qt::red);
            item->setToolTip("Esta partida está llena");
        }
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
    MatchInfo matchInfo = selected->data(Qt::UserRole).value<MatchInfo>();

    if (matchInfo.currentPlayers >= matchInfo.maxPlayers) {
        QMessageBox::warning(this, "Match Full",
            QString("Cannot join '%1'\nThe match is full (%2/%3 players)")
                .arg(matchInfo.name)
                .arg(matchInfo.currentPlayers)
                .arg(matchInfo.maxPlayers));
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Join",
        QString("Do you want to join '%1'?\nMap: %2\nPlayers: %3/%4")
            .arg(matchInfo.name)
            .arg(matchInfo.map)
            .arg(matchInfo.currentPlayers)
            .arg(matchInfo.maxPlayers),
        QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes) {
        return;
    }

    try {
        // aca el cliente tiene que enviar el comando de unirme al servidor
        
        QMessageBox::information(this, "Success", 
            QString("Joining match '%1'...").arg(matchInfo.name));
        
        // aca podria cerrar el lobby y abrir la pantalla de juego
        
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error",
            QString("Failed to join match: %1").arg(e.what()));
    }
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