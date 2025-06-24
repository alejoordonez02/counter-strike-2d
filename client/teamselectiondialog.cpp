#include "teamselectiondialog.h"
#include "ui_TeamSelection.h"
#include <QPushButton>

TeamSelectionDialog::TeamSelectionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TeamSelection)
{
    ui->setupUi(this);
    setWindowTitle("Select Your Team");
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    QPushButton *cancelButton = ui->buttonBox->button(QDialogButtonBox::Cancel);
    connect(okButton, &QPushButton::clicked, this, &TeamSelectionDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &TeamSelectionDialog::reject);
}

TeamSelectionDialog::~TeamSelectionDialog()
{
    delete ui;
}

int TeamSelectionDialog::selectedTeamIndex() const
{
    return ui->teamComboBox->currentIndex();
}