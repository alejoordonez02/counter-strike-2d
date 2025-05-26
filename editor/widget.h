#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include "ui_MapEditor.h"

class MapEditor : public QMainWindow
{
    Q_OBJECT  // <-- Esto es esencial

public:
    explicit MapEditor(QWidget *parent = nullptr);
    ~MapEditor();  // <-- Asegúrate de declarar el destructor

private slots:
    void onSaveClicked();
    void onSaveAndExitClicked();
    void onExitClicked();

private:
    Ui::MapEditor ui;
};

#endif // WIDGET_H