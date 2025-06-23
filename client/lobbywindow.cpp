#include "lobbywindow.h"
#include "creatematchdialog.h"
#include "teamselectiondialog.h"
#include "ui_Lobby.h"
#include <QMessageBox>

LobbyWindow::LobbyWindow(QWidget *parent) : 
    QMainWindow(parent),
    ui(new Ui::Lobby),
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
        MatchInfo("Dust", MapName::DUST, 4, 10),
        MatchInfo("Headshot Only", MapName::AZTEC, 6, 12),
        MatchInfo("Tournament", MapName::AZTEC, 10, 10),
        MatchInfo("1v5", MapName::AZTEC, 2, 10),
        MatchInfo("Nuke", MapName::NUKE, 5, 8)
    };
    
    for (const auto& match : matches) {
        QString matchText = QString("%1\nPlayers: %2/%3")
                          .arg(match.name)
                          .arg(match.currentPlayers)
                          .arg(match.maxPlayers);
        
        QListWidgetItem* item = new QListWidgetItem(matchText, ui->matchesList);
        item->setData(Qt::UserRole, QVariant::fromValue(match));
        
        if (match.currentPlayers >= match.maxPlayers) {
            item->setForeground(Qt::red);
            item->setToolTip("Match is full");
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
            QString("Cannot join map %1 \nThe match is full (%2/%3 players)")
                .arg(matchInfo.name)
                .arg(matchInfo.currentPlayers)
                .arg(matchInfo.maxPlayers));
        return;
    }

    // Primero confirmar unirse a la partida
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Join",
        QString("Do you want to join?\nGame: %1\nPlayers: %2/%3")
            .arg(matchInfo.name)
            .arg(matchInfo.currentPlayers)
            .arg(matchInfo.maxPlayers),
        QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes) {
        return;
    }

    // Mostrar diálogo de selección de equipo
    TeamSelectionDialog teamDialog(this);
    if (teamDialog.exec() != QDialog::Accepted) {
        return; 
    }

    int teamIdx = teamDialog.selectedTeamIndex();
    QString teamName = teamIdx == 0 ? "Terrorist" : "Counter-Terrorist";

    try {
        QMessageBox::information(this, "Success", 
            QString("Joining match '%1' as %2...").arg(matchInfo.name).arg(teamName));
        
        // Enviar señal con el equipo seleccionado
        emit requestJoinGame(matchInfo.name, teamIdx);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error",
            QString("Failed to join match: %1").arg(e.what()));
    }
}

void LobbyWindow::on_createMatchButton_clicked()
{
    CreateMatchDialog dialog(this);

    QListWidgetItem* selected = ui->matchesList->currentItem();
    MatchInfo matchInfo = selected->data(Qt::UserRole).value<MatchInfo>();
    if (dialog.exec() == QDialog::Accepted) {
        QString matchName = dialog.getMatchName();
        MapName mapName = dialog.getSelectedMapName();
        int teamIdx = dialog.getSelectedTeamIndex();

        if (matchName.isEmpty()) {
            QMessageBox::warning(this, "Error", "Match name cannot be empty");
            return;
        }
        
        try {
            //envio la senial que tiene lo necesari para crear el dto de CreateGame
            emit requestCreateGame(matchName, mapName, teamIdx);
            
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", 
                QString("Failed to create match: %1").arg(e.what()));
        }
    }
}