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
}

LobbyWindow::~LobbyWindow()
{
    delete ui;
}

void LobbyWindow::setMatchesList(const QList<QGameDetailsDTO>& newMatches) {
    currentMatches.clear();

    for (const auto& match : newMatches) {
        currentMatches.append(QSharedPointer<QGameDetailsDTO>::create(match));
    }
}

void LobbyWindow::refreshMatchesListUI() {
    ui->matchesList->clear();
    
    for (const auto& match : currentMatches) {
        QString name = QString::fromStdString(match->getName());
        QString mapName = QString::fromStdString(mapNameToString(match->getMapName()));
        
        QString matchText = QString(
            "%1\nTerrorists: %2/%4  |  Counter-Terrorists: %3/%4\n%5")
                          .arg(name)
                          .arg(match->getTtCount())
                          .arg(match->getCtCount())
                          .arg(TEAM_MAX_PLAYERS)
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
    auto matchInfo = selected->data(Qt::UserRole).value<QSharedPointer<QGameDetailsDTO>>();

    TeamSelectionDialog teamDialog(this);
    if (teamDialog.exec() != QDialog::Accepted)
        return; 

    QString matchName = QString::fromStdString(matchInfo->getName());
    TeamName teamName = static_cast<TeamName>(teamDialog.selectedTeamIndex());
    MapName mapName = matchInfo->getMapName();

    emit requestJoinGame(matchName, teamName, mapName);
}

void LobbyWindow::on_createMatchButton_clicked() {
    CreateMatchDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;

    QString matchName = dialog.getMatchName();
    MapName mapName = dialog.getSelectedMapName();
    TeamName teamName = static_cast<TeamName>(dialog.getSelectedTeamIndex());

    if (matchName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Match name cannot be empty");
        return;
    }

    emit requestCreateGame(matchName, mapName, teamName);
}

void LobbyWindow::on_refreshButton_clicked() {
    ui->matchesList->clear();
    ui->matchesList->addItem("Loading...");
    emit requestListGames();
}