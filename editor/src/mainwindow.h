#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tilesheeteditor.h"
#include "mapeditor.h"
#include "maploader.h"

namespace Ui {
class MapEditor;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_LoadButton_clicked();
    void on_SaveButton_clicked();
    void on_ExitButton_clicked();

private:
    Ui::MapEditor *ui;
    TileSheetEditor *m_tilesheetEditor;
    MapEditor *m_mapEditor;
    MapLoader *m_mapLoader;
    QPixmap m_currentBrush;
};

#endif // MAINWINDOW_H
