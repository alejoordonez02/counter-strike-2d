#include "mainwindow.h"
#include "ui_MapEditor.h" 
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QSize>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapEditor),
    m_tilesheetEditor(new SheetEditor(this)),
    m_weaponsheetEditor(new SheetEditor(this)),
    m_mapEditor(new MapEditor(this))
{
    ui->setupUi(this);
    setupUI();
    loadConfigurations();
    connectSignals();
}

void MainWindow::setupUI() {
    QLabel *tilesheetLabel = ui->scrollArea_2->findChild<QLabel*>("tylesheet");
    if (tilesheetLabel) {
        QLayout *layout = tilesheetLabel->parentWidget()->layout();
        layout->replaceWidget(tilesheetLabel, m_tilesheetEditor);
        delete tilesheetLabel;
    }

    QLabel *weaponsheetLabel = ui->scrollArea_3->findChild<QLabel*>("weaponsheet");
    if (weaponsheetLabel) {
        QLayout *layout = weaponsheetLabel->parentWidget()->layout();
        layout->replaceWidget(weaponsheetLabel, m_weaponsheetEditor);
        delete weaponsheetLabel;
    }

    QWidget *mapContainer = ui->scrollArea->findChild<QWidget*>("mapContainer");
    if (mapContainer) {
        QLayout *layout = mapContainer->parentWidget()->layout();
        layout->replaceWidget(mapContainer, m_mapEditor);
        delete mapContainer;
    }
}

void MainWindow::loadConfigurations() {
    QString weaponsheetConfigPath = "../config/weaponsheet_config.yaml";
    m_weaponsheetEditor->loadsheet(weaponsheetConfigPath);

    QString tilesheetConfigPath = "../config/tilesheet_config.yaml";
    m_tilesheetEditor->loadsheet(tilesheetConfigPath);
}

void MainWindow::connectSignals() {
    connect(m_weaponsheetEditor, &SheetEditor::tileSelected,
            m_mapEditor, &MapEditor::setCurrentTile);

    connect(m_tilesheetEditor, &SheetEditor::tileSelected,
            m_mapEditor, &MapEditor::setCurrentTile);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_LoadButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, 
        "Load Mapa", 
        "", 
        "YAML Files (*.yaml *.yml)"
    );

    if (!filePath.isEmpty()) {
        try {
            MapData data = m_mapLoader->loadMapData(filePath);
            m_mapEditor->loadMapFromData(data);
            
            
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", 
                QString("Error loading map:\n%1").arg(e.what()));
        }
    }
}

void MainWindow::on_LoadBackgroundButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, 
        "Load Background", 
        "", 
        "PNG Files (*.png)"
    );

    if (!filePath.isEmpty()) {
        try {
            m_mapEditor->loadBackground(filePath);
            
            
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", 
                QString("Error loading background:\n%1").arg(e.what()));
        }
    }
}

void MainWindow::on_SaveButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Save Mapa",
        "map_config.yaml", 
        "YAML Files (*.yaml *.yml)"
    );

    if (!filePath.isEmpty()) {
        if (!filePath.endsWith(".yaml", Qt::CaseInsensitive) && 
            !filePath.endsWith(".yml", Qt::CaseInsensitive)) {
            filePath += ".yaml";
        }

        try {
            m_mapEditor->saveMapData(filePath);
        } catch (const std::exception& e) {
            QString errorMessage = QString::fromStdString(e.what())
                                .replace("•", "•")
                                .replace("\n", "<br>"); 
            
            QMessageBox::critical(this, 
                                "Error al guardar el mapa",
                                QString("<html><b>No se pudo guardar el mapa:</b><br><br>%1</html>")
                                    .arg(errorMessage));
        }
    }
}