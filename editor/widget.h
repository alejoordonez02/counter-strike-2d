#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include "ui_MapEditor.h"

class MapEditor : public QMainWindow
{
    Q_OBJECT  

public:
    explicit MapEditor(QWidget *parent = nullptr);
    ~MapEditor();  

private slots:
    void onLoadClicked();
    void onSaveClicked();
    void onExitClicked();

private:
    Ui::MapEditor ui;
};

#endif // WIDGET_H