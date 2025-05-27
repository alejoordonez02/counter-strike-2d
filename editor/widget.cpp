#include "widget.h"
#include <QMessageBox>

MapEditor::MapEditor(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    
    connect(ui.LoadButton, &QPushButton::clicked, this, &MapEditor::onLoadClicked);
    connect(ui.SaveButton, &QPushButton::clicked, this, &MapEditor::onSaveClicked);
    connect(ui.ExitButton, &QPushButton::clicked, this, &MapEditor::onExitClicked);
}   

MapEditor::~MapEditor()
{
    // Implementación del destructor (puede estar vacía)
}
void MapEditor::onLoadClicked()
{
    QMessageBox::information(this, "Load", "Map loaded successfully!");
}

void MapEditor::onSaveClicked()
{
    QMessageBox::information(this, "Save", "Map saved successfully!");
}

void MapEditor::onExitClicked()
{
    close();
}