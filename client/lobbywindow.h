#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QList>
#include "common/map_name.h"
#include "common/network/dtos/game_details_dto.h"
#define MAX_PLAYERS 10

namespace Ui {
class Lobby;
}

class LobbyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LobbyWindow(QWidget *parent = nullptr);
    ~LobbyWindow();
    void setMatchesList(const QList<GameDetailsDTO>& newMatches);

signals:
    void requestJoinGame(const QString & name, int teamIdx);
    void requestCreateGame(const QString & name,const MapName & mapname, int teamIdx);
    void requestListGames();

private slots:
    void on_refreshButton_clicked();
    void on_joinMatchButton_clicked();
    void on_createMatchButton_clicked();
private:
    void refreshMatchesListUI();
    Ui::Lobby *ui;
    int team_idx;
    QList<QSharedPointer<GameDetailsDTO>> currentMatches;
};

#endif // LOBBYWINDOW_H