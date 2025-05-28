#include "mapeditor.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPainter>
#include <QMimeData>

MapEditor::MapEditor(QWidget *parent) : QWidget(parent),
    m_tileWidth(32), m_tileHeight(32)
{
    setAcceptDrops(true);
}

void MapEditor::loadMap(const QString &imagePath)
{
    m_background.load(imagePath);
    if (!m_background.isNull()) {
        setFixedSize(m_background.size());
        update();
    }
}

void MapEditor::setTileSize(int width, int height)
{
    m_tileWidth = width;
    m_tileHeight = height;
    update();
}

void MapEditor::placeTile(const QPixmap &tile, const QPoint &position)
{
    if (!tile.isNull()) {
        m_placedTiles.append(qMakePair(tile, position));
        update();
    }
}

void MapEditor::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void MapEditor::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void MapEditor::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasImage()) {
        QPixmap tile = qvariant_cast<QPixmap>(event->mimeData()->imageData());
        
        QPoint dropPos = event->pos();
        dropPos.setX((dropPos.x() / m_tileWidth) * m_tileWidth);
        dropPos.setY((dropPos.y() / m_tileHeight) * m_tileHeight);
        
        placeTile(tile, dropPos);
        event->acceptProposedAction();
    }
}

void MapEditor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    
    if (!m_background.isNull()) {
        painter.drawPixmap(0, 0, m_background);
    }
    for (const auto &tilePair : m_placedTiles) {
        painter.drawPixmap(tilePair.second, tilePair.first);
    }
}

QPixmap MapEditor::getMapImage() {
    QPixmap pixmap(this->size());
    pixmap.fill(Qt::transparent);
    

    QPainter painter(&pixmap);
    this->render(&painter);  
    
    return pixmap;
}