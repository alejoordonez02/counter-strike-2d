#include "lobbywindow.h"
#include "creatematchdialog.h"
#include "teamselectiondialog.h"
#include "ui_Lobby.h"
#include <QMessageBox>
#include <QSharedPointer>

LobbyWindow::LobbyWindow(QWidget *parent) : 
    QMainWindow(parent),
    ui(new Ui::Lobby),
    team_idx(0)
{
    ui->setupUi(this);
    refreshMatchesListUI();
}

LobbyWindow::~LobbyWindow()
{
    delete ui;
}

void LobbyWindow::setMatchesList(const QList<GameDetailsDTO>& newMatches) {
    currentMatches.clear();
    
    for (const auto& match : newMatches) {
        currentMatches.append(QSharedPointer<GameDetailsDTO>::create(match));
    }
    
    refreshMatchesListUI();
}

void LobbyWindow::refreshMatchesListUI() {
    ui->matchesList->clear();
    
    for (const auto& match : currentMatches) {
        QString name = QString::fromStdString(match->getName());
        QString mapName = QString::fromStdString(mapNameToString(match->getMapName()));
        
        QString matchText = QString("%1\nPlayers: %2/%3 - %4")
                          .arg(name)
                          .arg(match->getTtCount() + match->getCtCount())
                          .arg(MAX_PLAYERS)
                          .arg(mapName);
        
        QListWidgetItem* item = new QListWidgetItem(matchText, ui->matchesList);
        item->setData(Qt::UserRole, QVariant::fromValue(match));
        
        if (!match->isJoinable()) {
            item->setForeground(Qt::red);
            item->setToolTip(tr("Cannot join - Match in progress or full"));
        } else if (match->getTtCount() + match->getCtCount() >= MAX_PLAYERS - 2) {
            item->setForeground(Qt::darkYellow);
            item->setToolTip(tr("Almost full"));
        } else {
            item->setForeground(Qt::darkGreen);
            item->setToolTip(tr("click to select"));
        }

    }
}

void LobbyWindow::on_joinMatchButton_clicked() {   
    QListWidgetItem* selected = ui->matchesList->currentItem();
    if (!selected) {
        QMessageBox::warning(this, "Error", "Please select a match first");
        return;
    }
    
    auto matchInfo = selected->data(Qt::UserRole).value<QSharedPointer<GameDetailsDTO>>();
    
    if (matchInfo->getTtCount() + matchInfo->getCtCount() >= 10 || !matchInfo->isJoinable()) {
        QMessageBox::warning(this, "Cannot Join Match", 
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
    refreshMatchesListUI();
}