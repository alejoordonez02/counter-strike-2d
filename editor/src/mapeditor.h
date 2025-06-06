#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QWidget>
#include <QPixmap>
#include <yaml-cpp/yaml.h>
#include "mapdata.h"

class MapEditor : public QWidget
{
    Q_OBJECT
public:
    explicit MapEditor(QWidget *parent = nullptr);
    
    void loadMap(const QString &imagePath);
    void loadBackground(const QString &imagePath);
    void setTileSize(int width, int height);
    void placeTile(const QPoint& position, const QString& texturePath, const QString& type);
    void loadMapFromData(const MapData& data);
    void saveMapData(const QString& filePath);
    MapData getMapData();

    protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPoint m_dragStartPos;
    QPixmap m_background;
    QHash<QString, QPixmap> textureCache;
    int m_tileWidth;
    int m_tileHeight;
    MapData mapdata;
    
};

#endif // MAPEDITOR_H

