#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "common/map_name.h"

namespace Ui {
class Lobby;
}

struct MatchInfo {
    QString name;
    MapName map;
    int currentPlayers;
    int maxPlayers;
    
    MatchInfo(QString n = "", MapName m = MapName::AZTEC, int cp = 0, int mp = 0)
        : name(n), map(m), currentPlayers(cp), maxPlayers(mp) {}
};

Q_DECLARE_METATYPE(MatchInfo)

class LobbyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LobbyWindow(QWidget *parent = nullptr);
    ~LobbyWindow();
signals:
    void requestJoinGame(const QString & name, int teamIdx);
    void requestCreateGame(const QString & name,const MapName & mapname, int teamIdx);
    void requestListGames();

private slots:
    void on_refreshButton_clicked();
    void on_joinMatchButton_clicked();
    void on_createMatchButton_clicked();
private:
    void populateMatchesList();
    Ui::Lobby *ui;
    QString username;
    int team_idx;
};

#endif // LOBBYWINDOW_H