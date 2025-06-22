#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class Lobby;
}

struct MatchInfo {
    QString name;
    QString map;
    int currentPlayers;
    int maxPlayers;
    
    MatchInfo(QString n = "", QString m = "", int cp = 0, int mp = 0)
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
    void requestJoinGame(const QString& username, int teamIdx);
    void requestCreateGame(const QString& username,int mapIdx, int teamIdx);
    void requestListGames();

private slots:
    void on_refreshButton_clicked();
    void on_joinMatchButton_clicked();
    void on_createMatchButton_clicked();
private:
    void populateMatchesList();
    Ui::Lobby *ui;
    QString username;
    int map_idx;
    int team_idx;
};

#endif // LOBBYWINDOW_H