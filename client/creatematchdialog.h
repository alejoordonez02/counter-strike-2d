#ifndef CREATEMATCHDIALOG_H
#define CREATEMATCHDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>

#define MIN_PLAYERS 1
#define MAX_PLAYERS 20

namespace Ui {
class CreateMatch;
}

class CreateMatchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateMatchDialog(const QString& username, QWidget *parent = nullptr);
    ~CreateMatchDialog();

    QString getMatchName() const;
    QString getConfigPath() const;
    QString getMapName() const;
    int getMaxPlayers() const;
    bool isValid() const;

private slots:
    void on_browseButton_clicked();
    void on_createButton_clicked();
    void validateInputs();

private:
    Ui::CreateMatch *ui;
    QString username;
};

#endif // CREATEMATCHDIALOG_H