#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "maploader.h"
#include <QWidget>
#include <QPixmap>
#include <QApplication>

class MapEditor : public QWidget
{
    Q_OBJECT
public:
    explicit MapEditor(QWidget *parent = nullptr);
    
    void loadMap(const QString &imagePath);
    void loadBackground(const QString &imagePath);
    void setTileSize(int width, int height);
    void placeTile(const QPixmap &tile, const QPoint &position);
    void loadMapFromData(const MapData& data);
    QPixmap getMapImage();
    QVector<QPair<QPixmap, QPoint>> getPlacedTiles();

    protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    MapLoader m_mapLoader;
    QPixmap m_background;
    QVector<QPair<QPixmap, QPoint>> m_placedTiles;
    int m_tileWidth;
    int m_tileHeight;
};

#endif // MAPEDITOR_H
