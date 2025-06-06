#include "tilesheeteditor.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDrag>
#include <QMimeData>
#include <QFileInfo>

TileSheetEditor::TileSheetEditor(QWidget *parent) : QWidget(parent),
    m_tileWidth(32), m_tileHeight(32)
{
    setMouseTracking(true);
}

void TileSheetEditor::loadTilesheet(const QString &configPath)
{
    if (!QFileInfo::exists(configPath)) {
        throw std::runtime_error("File does not exist: " + configPath.toStdString());
    }
    tilesheetdata.loadFromYAML(configPath);
    m_tilesheet.load(tilesheetdata.getTilesheetPath());
    if (!m_tilesheet.isNull()) {
        setFixedSize(m_tilesheet.size());
        update();
    }
}

void TileSheetEditor::setTileSize(int width, int height)
{
    m_tileWidth = width;
    m_tileHeight = height;
    update();
}

QPixmap TileSheetEditor::getSelectedTile() const
{
    if (m_selectedTilePos.x() < 0 || m_selectedTilePos.y() < 0)
        return QPixmap();
    
    return m_tilesheet.copy(
        m_selectedTilePos.x() * m_tileWidth,
        m_selectedTilePos.y() * m_tileHeight,
        m_tileWidth,
        m_tileHeight
    );
}

void TileSheetEditor::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
        int tileX = event->pos().x() / m_tileWidth;
        int tileY = event->pos().y() / m_tileHeight;

        if (tileX >= 0 && tileY >= 0) {
            auto tileInfo = tilesheetdata.getTileInfo(tileX, tileY);
            
            QByteArray itemData;
            QDataStream stream(&itemData, QIODevice::WriteOnly);
            stream << tileX << tileY << tileInfo.texturePath << tileInfo.type;

            m_selectedTilePos = QPoint(tileX, tileY);
            QMimeData* mimeData = new QMimeData;
            mimeData->setData("application/x-tiledata", itemData);
            mimeData->setImageData(getSelectedTile().toImage());
            
            QDrag* drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setPixmap(getSelectedTile());
            drag->exec(Qt::CopyAction);
        }
    }
    QApplication::restoreOverrideCursor();
}

QString TileSheetEditor::getTypeStringForTile(int tileX, int tileY) {
    switch(tileY) {
        case 0: return "Solid";
        case 1: return "Plantable";
        case 2: return "TSpawn";
        case 3: return "CtSpawn";
        default: return "Common";
    }
}

void TileSheetEditor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    
    if (!m_tilesheet.isNull()) {
        painter.drawPixmap(0, 0, m_tilesheet);
    }
    
    if (m_selectedTilePos.x() >= 0 && m_selectedTilePos.y() >= 0) {
        painter.setPen(QPen(Qt::red, 2));
        painter.drawRect(
            m_selectedTilePos.x() * m_tileWidth,
            m_selectedTilePos.y() * m_tileHeight,
            m_tileWidth, m_tileHeight
        );
    }
}
