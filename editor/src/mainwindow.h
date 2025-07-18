#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sheeteditor.h"
#include "mapeditor.h"
#include "common/maploader.h"

#define SCROLL_AREA_SIZE_MULTIPLIER 80
#define weaponsheetConfigPath "config/weaponsheet_config.yaml"
#define tilesheetConfigPath "config/tilesheet_config.yaml"

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
    MapDataEditor convertToMapData(MapData data_struct);

    Ui::MapEditor *ui;
    SheetEditor *m_tilesheetEditor;
    SheetEditor *m_weaponsheetEditor;
    MapEditor *m_mapEditor;
    MapLoader m_mapLoader;
    QPixmap m_currentBrush;
};

#endif // MAINWINDOW_H
