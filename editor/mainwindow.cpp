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
    
    m_tilesheetEditor->loadTilesheet(":/tiles/assets/gfx/tiles/embrador.bmp");
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
        "Cargar Mapa Base", 
        "", 
        "Images (*.png *.jpg *.bmp)"
    );
    
    if (!filePath.isEmpty()) {
        m_mapEditor->loadMap(filePath);
        
        if (!m_mapEditor->getMapImage().isNull()) {
            QSize imgSize = m_mapEditor->getMapImage().size();
            m_mapEditor->setMinimumSize(imgSize);
            ui->scrollArea->setMinimumSize(imgSize);
        }
    }
}

void MainWindow::on_SaveButton_clicked()
{
    if (m_mapEditor->getMapImage().isNull()) {
        QMessageBox::warning(this, "Error", "No hay imagen para guardar.");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Guardar como JPG",
        "map.jpg", 
        "JPEG Image (*.jpg *.jpeg)"
    );

    if (!filePath.isEmpty()) {
        if (!filePath.endsWith(".jpg", Qt::CaseInsensitive) && 
            !filePath.endsWith(".jpeg", Qt::CaseInsensitive)) {
            filePath += ".jpg";
        }

        bool success = m_mapEditor->getMapImage().save(filePath, "JPEG", 90);

        if (success) {
            QMessageBox::information(this, "Éxito", "Imagen guardada como JPG.");
        } else {
            QMessageBox::critical(this, "Error", "No se pudo guardar el JPG.");
        }
    }
}

void MainWindow::on_ExitButton_clicked()
{
    close();
}