#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <QMainWindow>

namespace Ui {
class Lobby;
}

class LobbyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LobbyWindow(const QString& username, QWidget *parent = nullptr);
    ~LobbyWindow();
private slots:
    void on_refreshButton_clicked();
    void on_joinMatchButton_clicked();
    void on_createMatchButton_clicked();
private:
    void populateMatchesList();
    Ui::Lobby *ui;
    QString username;
};

#endif // LOBBYWINDOW_H