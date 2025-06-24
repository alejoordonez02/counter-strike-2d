#ifndef TEAMSELECTIONDIALOG_H
#define TEAMSELECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class TeamSelection;
}

class TeamSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TeamSelectionDialog(QWidget *parent = nullptr);
    ~TeamSelectionDialog();

    int selectedTeamIndex() const;

private:
    Ui::TeamSelection *ui;
};

#endif // TEAMSELECTIONDIALOG_H