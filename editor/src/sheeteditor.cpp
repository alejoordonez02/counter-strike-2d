#include "sheeteditor.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDrag>
#include <QMimeData>
#include <QFileInfo>

SheetEditor::SheetEditor(QWidget *parent) : QWidget(parent),
    m_tileWidth(DEFAULT_TILE_WIDTH), m_tileHeight(DEFAULT_TILE_HEIGHT)
{
    setMouseTracking(true);
}

void SheetEditor::loadsheet(const QString &configPath)
{
    if (!QFileInfo::exists(configPath)) {
        throw std::runtime_error("File does not exist: " + configPath.toStdString());
    }
    sheetdata.loadFromYAML(configPath);
    m_tilesheet.load(sheetdata.getTilesheetPath());
    if (!m_tilesheet.isNull()) {
        setFixedSize(m_tilesheet.size());
        update();
    }
}

void SheetEditor::setTileSize(int width, int height)
{
    m_tileWidth = width;
    m_tileHeight = height;
    update();
}

QPixmap SheetEditor::getSelectedTile() const
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

void SheetEditor::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        int tileX = event->pos().x() / m_tileWidth;
        int tileY = event->pos().y() / m_tileHeight;

        if (tileX >= 0 && tileY >= 0) {
            auto tileInfo = sheetdata.getTileInfo(tileX, tileY);
            m_selectedTilePos = QPoint(tileX, tileY);
    
            emit tileSelected(tileInfo.texturePath, tileInfo.type);
            
            QByteArray itemData;
            QDataStream stream(&itemData, QIODevice::WriteOnly);
            stream << tileInfo.texturePath << tileInfo.type;

            QMimeData* mimeData = new QMimeData;
            mimeData->setData("application/x-tiledata", itemData);
            mimeData->setImageData(getSelectedTile().toImage());
            
            QDrag* drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setPixmap(getSelectedTile());
            
            QApplication::setOverrideCursor(Qt::ClosedHandCursor);
            drag->exec(Qt::CopyAction);
            
            QApplication::restoreOverrideCursor();
            
        }
    }
}

void SheetEditor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    
    if (!m_tilesheet.isNull()) {
        painter.drawPixmap(0, 0, m_tilesheet);
    }

    if (m_selectedTilePos.x() >= 0 && m_selectedTilePos.y() >= 0) {
        QPen pen(Qt::red, 2, Qt::SolidLine); 
        painter.setPen(pen);
        
        int x = m_selectedTilePos.x() * m_tileWidth;
        int y = m_selectedTilePos.y() * m_tileHeight;
        QRect selectionRect(x, y, m_tileWidth, m_tileHeight);
        
        painter.drawRect(selectionRect);
    }
}
