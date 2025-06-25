#include "creatematchdialog.h"
#include "ui_CreateMatch.h"
#include <QMessageBox>
#include <QDebug>

CreateMatchDialog::CreateMatchDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateMatch)
{
    ui->setupUi(this);
    setWindowTitle(tr("Create New Match"));
    setupMaps();

    connect(ui->matchNameEdit, &QLineEdit::textChanged, this, &CreateMatchDialog::validateInputs);
    connect(ui->mapBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &CreateMatchDialog::validateInputs);
    connect(ui->createButton, &QPushButton::clicked, this, &CreateMatchDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &CreateMatchDialog::reject);

    validateInputs();
}

CreateMatchDialog::~CreateMatchDialog()
{
    delete ui;
}

void CreateMatchDialog::validateInputs()
{
    bool valid = !getMatchName().isEmpty() && 
                 ui->mapBox->currentIndex() >= 0;
    
    ui->createButton->setEnabled(valid);
}

void CreateMatchDialog::setupMaps()
{
    // Configurar mapas disponibles con sus MapNames correspondientes

    
    mapNames = {
        #define X(name, lowercase) \
                {lowercase, MapName::name},
            MAP_LIST
        #undef X
    };

    ui->mapBox->clear();
    for (const auto& displayName : mapNames.keys()) {
        ui->mapBox->addItem(displayName);
    }
}
QString CreateMatchDialog::getMatchName() const
{
    QString displayName = ui->matchNameEdit->text();
    return displayName;
}

MapName CreateMatchDialog::getSelectedMapName() const
{
    QString displayName = ui->mapBox->currentText();
    return mapNames.value(displayName); 
}

QString CreateMatchDialog::getSelectedMapDisplayName() const
{
    return ui->mapBox->currentText();
}


int CreateMatchDialog::getSelectedTeamIndex() const
{
    return ui->teamBox->currentIndex();
}

bool CreateMatchDialog::isTeamSelected() const
{
    return ui->teamBox->currentIndex() >= 0;
}

bool CreateMatchDialog::isValid() const
{
    return !getMatchName().isEmpty() && 
           ui->mapBox->currentIndex() >= 0;
}