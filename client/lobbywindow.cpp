#include "lobbywindow.h"
#include "creatematchdialog.h"
#include "teamselectiondialog.h"
#include "common/network/dtos/game_details_dto.h"
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

void LobbyWindow::populateMatchesList() {
    emit requestListGames();
    ui->matchesList->clear();
    
    // Store matches as QSharedPointer
    QList<QSharedPointer<GameDetailsDTO>> matches = {
        QSharedPointer<GameDetailsDTO>::create("Dust", 1, 1, MapName::DUST, true),
        QSharedPointer<GameDetailsDTO>::create("Headshot Only", 1, 1, MapName::AZTEC, true),
        QSharedPointer<GameDetailsDTO>::create("Tournament", 5, 5, MapName::AZTEC, false),
        QSharedPointer<GameDetailsDTO>::create("1v5", 1, 5, MapName::AZTEC, false),
        QSharedPointer<GameDetailsDTO>::create("Nuke", 1, 0, MapName::NUKE, true)
    };
    
    for (const auto& match : matches) {
        QString matchText = QString("%1\nPlayers: %2/10")
                          .arg(QString::fromStdString(match->getName()))
                          .arg(match->getTtCount() + match->getCtCount());
        
        QListWidgetItem* item = new QListWidgetItem(matchText, ui->matchesList);
        // Store the shared pointer in the item
        item->setData(Qt::UserRole, QVariant::fromValue(match));
        
        if (!match->isJoinable()) {
            item->setForeground(Qt::red);
            item->setToolTip("Cannot join Match");
        }
    }
}

void LobbyWindow::on_joinMatchButton_clicked() {   
    QListWidgetItem* selected = ui->matchesList->currentItem();
    if (!selected) {
        QMessageBox::warning(this, "Error", "Please select a match first");
        return;
    }
    
    // Retrieve the shared pointer from the item
    auto matchInfo = selected->data(Qt::UserRole).value<QSharedPointer<GameDetailsDTO>>();
    
    if (matchInfo->getTtCount() + matchInfo->getCtCount() >= 10) {
        QMessageBox::warning(this, "Match Full", 
            QString("%1\nPlayers: %2/10")
            .arg(QString::fromStdString(matchInfo->getName()))
            .arg(matchInfo->getTtCount() + matchInfo->getCtCount()));
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Join",
        QString("Do you want to join?\nGame: %1\nPlayers: %2/10")
            .arg(QString::fromStdString(matchInfo->getName()))
            .arg(matchInfo->getTtCount() + matchInfo->getCtCount()),
        QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes) {
        return;
    }

    TeamSelectionDialog teamDialog(this);
    if (teamDialog.exec() != QDialog::Accepted) {
        return; 
    }

    int teamIdx = teamDialog.selectedTeamIndex();
    QString teamName = teamIdx == 0 ? "Terrorist" : "Counter-Terrorist";

    try {
        QMessageBox::information(this, "Success", 
            QString("Joining match '%1' as %2...")
                .arg(QString::fromStdString(matchInfo->getName()))
                .arg(teamName)
        );
        emit requestJoinGame(QString::fromStdString(matchInfo->getName()), teamIdx);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error",
            QString("Failed to join match: %1").arg(e.what()));
    }
}

void LobbyWindow::on_createMatchButton_clicked() {
    CreateMatchDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString matchName = dialog.getMatchName();
        MapName mapName = dialog.getSelectedMapName();
        int teamIdx = dialog.getSelectedTeamIndex();

        if (matchName.isEmpty()) {
            QMessageBox::warning(this, "Error", "Match name cannot be empty");
            return;
        }
        
        try {
            emit requestCreateGame(matchName, mapName, teamIdx);
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", 
                QString("Failed to create match: %1").arg(e.what()));
        }
    }
}

void LobbyWindow::on_refreshButton_clicked() {
    QMessageBox::information(this, "Refreshing", "Match list updated");
    populateMatchesList();
}