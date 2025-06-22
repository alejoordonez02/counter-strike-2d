#include "lobbywindow.h"
#include "creatematchdialog.h"
#include "ui_Lobby.h"
#include <QMessageBox>
#include <QListWidgetItem>

LobbyWindow::LobbyWindow(QWidget *parent) : 
    QMainWindow(parent),
    ui(new Ui::Lobby),
    map_idx(0),
    team_idx(0)
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
    emit requestListGames();
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
            QString("User %1 Cannot join '%2'\nThe match is full (%3/%4 players)")
                .arg(username)
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
        QMessageBox::information(this, "Success", 
            QString("Joining match '%1'...").arg(matchInfo.name));
        //envio la senial que tiene lo necesari para crear el dto de JoinGame
        emit requestJoinGame(matchInfo.name, team_idx);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error",
            QString("Failed to join match: %1").arg(e.what()));
    }
}

void LobbyWindow::on_createMatchButton_clicked()
{
    CreateMatchDialog dialog(username, this);

    QListWidgetItem* selected = ui->matchesList->currentItem();
    MatchInfo matchInfo = selected->data(Qt::UserRole).value<MatchInfo>();
    if (dialog.exec() == QDialog::Accepted) {
        QString matchName = dialog.getMatchName();
        QString configPath = dialog.getConfigPath();
        
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
            //envio la senial que tiene lo necesari para crear el dto de CreateGame
            emit requestCreateGame(matchInfo.name, map_idx, team_idx);
            
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", 
                QString("Failed to create match: %1").arg(e.what()));
        }
    }
}