#include "creatematchdialog.h"
#include "ui_CreateMatch.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QPushButton>

CreateMatchDialog::CreateMatchDialog(const QString& username, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateMatch)
    , username(username)
{
    ui->setupUi(this);
    setWindowTitle(tr("Create New Match - %1").arg(username));
    
    ui->matchNameEdit->setText(tr("Match by %1").arg(username));
    ui->maxPlayersSpin->setRange(MIN_PLAYERS, MAX_PLAYERS);

    connect(ui->matchNameEdit, &QLineEdit::textChanged, this, &CreateMatchDialog::validateInputs);
    connect(ui->configPathEdit, &QLineEdit::textChanged, this, &CreateMatchDialog::validateInputs);
    connect(ui->maxPlayersSpin, QOverload<int>::of(&QSpinBox::valueChanged), 
            this, &CreateMatchDialog::validateInputs);

    ui->createButton->setText(tr("Create"));
    ui->createButton->setEnabled(false);
    
    connect(ui->createButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

CreateMatchDialog::~CreateMatchDialog()
{
    delete ui;
}

void CreateMatchDialog::on_createButton_clicked()
{
    if (isValid()) {
        accept();
    } else {
        QMessageBox::warning(this, 
                           tr("Invalid Input"), 
                           tr("Please check your inputs and try again"));
    }
}

void CreateMatchDialog::on_browseButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Select Map Configuration"),
        QDir::homePath(),
        tr("YAML Files (*.yaml *.yml);;All Files (*)")
    );
    
    if (!filePath.isEmpty()) {
        ui->configPathEdit->setText(filePath);
    }
}

void CreateMatchDialog::validateInputs()
{
    bool valid = true;
    
    // Validar nombre de partida
    QString matchName = getMatchName();
    if (matchName.isEmpty() || matchName.length() > 30) {
        valid = false;
    }
    
    QFile configFile(getConfigPath());
    if (!configFile.exists() || !getConfigPath().endsWith(".yaml", Qt::CaseInsensitive)) {
        valid = false;
    }
    
    if (getMaxPlayers() < MIN_PLAYERS || getMaxPlayers() > MAX_PLAYERS) { // Mínimo 2 jugadores
        valid = false;
    }
    
    ui->createButton->setEnabled(valid);
}

QString CreateMatchDialog::getMatchName() const
{
    return ui->matchNameEdit->text().trimmed();
}

QString CreateMatchDialog::getConfigPath() const
{
    return ui->configPathEdit->text();
}

QString CreateMatchDialog::getMapName() const
{
    if (getConfigPath().isEmpty()) return "";
    QFileInfo fileInfo(getConfigPath());
    return fileInfo.baseName();
}

int CreateMatchDialog::getMaxPlayers() const
{
    return ui->maxPlayersSpin->value();
}

bool CreateMatchDialog::isValid() const
{
    QFile configFile(getConfigPath());
    return !getMatchName().isEmpty() && 
           configFile.exists() && 
           getConfigPath().endsWith(".yaml", Qt::CaseInsensitive) &&
           getMaxPlayers() >= MIN_PLAYERS && 
           getMaxPlayers() <= MAX_PLAYERS;
}