#ifndef CREATEMATCHDIALOG_H
#define CREATEMATCHDIALOG_H

#include <QDialog>
#include <QMap>
#include "common/map_name.h" // Incluir el archivo con MapName

namespace Ui {
class CreateMatch;
}

class CreateMatchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateMatchDialog(QWidget *parent = nullptr);
    ~CreateMatchDialog();

    QString getMatchName() const;
    MapName getSelectedMapName() const;
    QString getSelectedMapDisplayName() const;
    int getSelectedTeamIndex() const;
    bool isTeamSelected() const;

private slots:
    void validateInputs();

private:
    Ui::CreateMatch *ui;
    QMap<QString, MapName> mapNames;

    void setupMaps();
    bool isValid() const;
};

#endif // CREATEMATCHDIALOG_H