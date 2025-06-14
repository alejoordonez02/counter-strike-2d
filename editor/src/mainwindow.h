#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sheeteditor.h"
#include "mapeditor.h"
#include "common/maploader.h"

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
    void on_LoadBackgroundButton_clicked();
    void on_SaveButton_clicked();

private:
    void setupUI();
    void setupTilesheetEditor();
    void loadConfigurations();
    void connectSignals();
    MapData convertToMapData(MapOnlyData data_struct);

    Ui::MapEditor *ui;
    SheetEditor *m_tilesheetEditor;
    SheetEditor *m_weaponsheetEditor;
    MapEditor *m_mapEditor;
    MapLoader m_mapLoader;
    QPixmap m_currentBrush;
};

#endif // MAINWINDOW_H
