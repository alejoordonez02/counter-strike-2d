#include "widget.h"
#include <QMessageBox>

MapEditor::MapEditor(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    
    //connect(ui.pushButton, &QPushButton::clicked, this, &MapEditor::onSaveClicked);
    //connect(ui.pushButton_2, &QPushButton::clicked, this, &MapEditor::onSaveAndExitClicked);
    //connect(ui.pushButton_3, &QPushButton::clicked, this, &MapEditor::onExitClicked);
    //connect(ui.checkBox, &QCheckBox::clicked, this, &MapEditor::onSaveClicked); 
}   

MapEditor::~MapEditor()
{
    // Implementación del destructor (puede estar vacía)
}

void MapEditor::onSaveClicked()
{
    QMessageBox::information(this, "Save", "Map saved successfully!");
}

void MapEditor::onSaveAndExitClicked()
{
    onSaveClicked();
    close();
}

void MapEditor::onExitClicked()
{
    close();
}