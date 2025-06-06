#include "mainwindow.h"
#include "ui_MapEditor.h" 
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QSize>
#include <QPainter> 
#include <QPen>  

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapEditor),
    m_tilesheetEditor(new TileSheetEditor(this)),
    m_mapEditor(new MapEditor(this))
{
    ui->setupUi(this);
    
    QLabel *tilesheetLabel = ui->scrollArea_2->findChild<QLabel*>("label_2");
    if (tilesheetLabel) {
        QLayout *layout = tilesheetLabel->parentWidget()->layout();
        layout->replaceWidget(tilesheetLabel, m_tilesheetEditor);
        delete tilesheetLabel;
    }
    
    QWidget *mapContainer = ui->scrollArea->findChild<QWidget*>("mapContainer");
    if (mapContainer) {
        QLayout *layout = mapContainer->parentWidget()->layout();
        layout->replaceWidget(mapContainer, m_mapEditor);
        delete mapContainer;
    }
    QString TilesheetconfigPath = "../config/tilesheet_config.yaml";
    m_tilesheetEditor->loadTilesheet(TilesheetconfigPath);
    m_tilesheetEditor->setTileSize(32, 32);
    m_mapEditor->setTileSize(32, 32);
}

MainWindow::~MainWindow()
{
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
            QMessageBox::critical(this, "Error", 
                QString("Error saving map:\n%1").arg(e.what()));
        }
    }
}

void MainWindow::on_ExitButton_clicked()
{
    qDebug() << "===DEBUG Lista de Bloques al cerrar ===";
    
    for (const Block &block : m_mapEditor->getMapData().blocks) {
        qDebug() << "Posición:" << block.getPosition();  
        qDebug() << "Textura:" << block.getTexturePath();
        qDebug() << "--------------------------";
    }
    
    close();
}