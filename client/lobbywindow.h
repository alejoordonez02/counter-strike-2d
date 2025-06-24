#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QList>
#include "common/map_name.h"
#include "common/team_name.h"
#include "client/q_game_details_dto.h"

constexpr int TEAM_MAX_PLAYERS = 5;
constexpr int MAX_PLAYERS = TEAM_MAX_PLAYERS * 2;
namespace Ui {
class Lobby;
}

class LobbyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LobbyWindow(QWidget *parent = nullptr);
    ~LobbyWindow();
    void setMatchesList(const QList<QGameDetailsDTO>& newMatches);
    void refreshMatchesListUI();

signals:
    void requestJoinGame(const QString& name, TeamName team, MapName map);
    void requestCreateGame(const QString& name, MapName map,
        TeamName team);
    void requestListGames();

public slots:
    void on_refreshButton_clicked();
    void on_joinMatchButton_clicked();
    void on_createMatchButton_clicked();
private:
    Ui::Lobby *ui;
    int team_idx;
    QList<QSharedPointer<QGameDetailsDTO>> currentMatches;
};

#endif // LOBBYWINDOW_H