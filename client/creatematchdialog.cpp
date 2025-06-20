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
    
    // Configuración inicial
    ui->matchNameEdit->setText(tr("Match by %1").arg(username));
    ui->maxPlayersSpin->setValue(10);
    ui->maxPlayersSpin->setRange(2, 20);
    
    // Conectar señales
    connect(ui->matchNameEdit, &QLineEdit::textChanged, this, &CreateMatchDialog::validateInputs);
    connect(ui->configPathEdit, &QLineEdit::textChanged, this, &CreateMatchDialog::validateInputs);
    connect(ui->maxPlayersSpin, QOverload<int>::of(&QSpinBox::valueChanged), 
            this, &CreateMatchDialog::validateInputs);
    
    // Configurar botón Create
    ui->createButton->setText(tr("Create"));
    ui->createButton->setEnabled(false);
    
    // Conectar el botón create para cerrar el diálogo
    connect(ui->createButton, &QPushButton::clicked, this, &QDialog::accept);
    
    // Conectar el botón cancel si existe
    if (ui->cancelButton) {
        connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    }
}

CreateMatchDialog::~CreateMatchDialog()
{
    delete ui;
}

void CreateMatchDialog::on_createButton_clicked()
{
    if (isValid()) {
        // Emitir señal con los datos si es necesario
        // emit matchCreated(getMatchName(), getConfigPath(), getMaxPlayers());
        
        // Cerrar el diálogo con resultado Accepted
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
    
    // Validar archivo de configuración
    QFile configFile(getConfigPath());
    if (!configFile.exists() || !getConfigPath().endsWith(".yaml", Qt::CaseInsensitive)) {
        valid = false;
    }
    
    // Validar número de jugadores
    if (getMaxPlayers() < 2 || getMaxPlayers() > 20) { // Mínimo 2 jugadores
        valid = false;
    }
    
    // Actualizar estado del botón OK
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
           getMaxPlayers() >= 2 && 
           getMaxPlayers() <= 20;
}