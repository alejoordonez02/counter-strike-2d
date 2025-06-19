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
    
    void loadBackground(const QString &imagePath);
    void setTileSize(int width, int height);
    void placeTile(const QPoint& position, const QString& texturePath, const QString& type);
    void loadMapFromData(const MapDataEditor& data);
    void saveMapData(const QString& filePath);
    MapDataEditor getMapData();

    protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void dropEvent(QDropEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    public slots:
    void setCurrentTile(const QString& texturePath, const QString& typeString);

private:
    QPoint m_dragStartPos;
    QPixmap m_background;
    QHash<QString, QPixmap> textureCache;
    int m_tileWidth;
    int m_tileHeight;
    MapDataEditor mapdata;
    struct {
        QString texturePath;
        QString typeString;
        bool isValid = false;
    } m_selectedTile;
    
};

#endif // MAPEDITOR_H

