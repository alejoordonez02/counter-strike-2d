#include "mapeditor.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPainter>
#include <QApplication>
#include <QMimeData>
#include <algorithm>

MapEditor::MapEditor(QWidget *parent) : QWidget(parent),
    m_tileWidth(32), m_tileHeight(32)
{
    setAcceptDrops(true);
    setMouseTracking(true);
}
void MapEditor::loadMap(const QString &imagePath) {
    loadBackground(imagePath);
}

void MapEditor::loadMapFromData(const MapData& data) {
    // Load background
    loadBackground(data.backgroundPath);

    // Process new blocks
    for (const auto& block : data.blocks) {
        // Create visual representation
        QPixmap tile(m_tileWidth, m_tileHeight);
        
        if (block.isSolid) {
            tile.fill(Qt::darkGray);  // Solid blocks
        } else if (block.isPlantable) {
            tile.fill(Qt::green);     // Plantable areas
        } else {
            tile.fill(Qt::transparent); // Walkable areas
        }
        
        placeTile(tile, block.position);
    }

    setFixedSize(m_background.size());
    update();
}

void MapEditor::loadBackground(const QString &imagePath) {
    if (m_background.load(imagePath) && !m_background.isNull()) {
        // Tamaño original de la imagen
        QSize imageSize = m_background.size();
        
        // Si tenemos un widget padre, escalamos al tamaño disponible
        if (parentWidget()) {
            QSize parentSize = parentWidget()->size();
            
            // Escalar manteniendo relación de aspecto y que sea múltiplo de 32
            QSize scaledSize = imageSize.scaled(parentSize, Qt::KeepAspectRatioByExpanding);
            
            // Ajustar a múltiplo de 32
            scaledSize.setWidth(scaledSize.width() - (scaledSize.width() % 32));
            scaledSize.setHeight(scaledSize.height() - (scaledSize.height() % 32));
            
            // Redimensionar la imagen
            m_background = m_background.scaled(scaledSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
        else {
            // Sin widget padre, ajustar a múltiplo de 32
            imageSize.setWidth(imageSize.width() - (imageSize.width() % 32));
            imageSize.setHeight(imageSize.height() - (imageSize.height() % 32));
            m_background = m_background.scaled(imageSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }

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
    if (tile.isNull()) {
        return;
    }

    auto it = std::find_if(m_placedTiles.begin(), m_placedTiles.end(),
        [&position](const QPair<QPixmap, QPoint>& item) {
            return item.second == position;
        });

    if (it != m_placedTiles.end()) {
        it->first = tile;
    } else {
        m_placedTiles.append(qMakePair(tile, position));
    }

    update();
}

QVector<QPair<QPixmap, QPoint>> MapEditor::getPlacedTiles()
{
    return m_placedTiles;
}

void MapEditor::dragEnterEvent(QDragEnterEvent *event) {   
    if (event->mimeData()->hasImage()) {
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void MapEditor::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void MapEditor::dragLeaveEvent(QDragLeaveEvent *event) {
    Q_UNUSED(event);
    QApplication::restoreOverrideCursor();
}

void MapEditor::dropEvent(QDropEvent *event) {   
    QApplication::restoreOverrideCursor();
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
        painter.drawPixmap(rect(), m_background, m_background.rect());
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