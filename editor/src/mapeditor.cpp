#include "mapeditor.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPainter>
#include <QBitmap>
#include <QApplication>
#include <QMimeData>
#include <QFileInfo>
#include <algorithm>
#include <fstream>

MapEditor::MapEditor(QWidget *parent) : QWidget(parent),
    m_tileWidth(32), m_tileHeight(32)
{
    setAcceptDrops(true);
    setMouseTracking(true);
}

void MapEditor::loadMapFromData(const MapData& data) {
    mapdata= data;
    loadBackground(mapdata.backgroundPath);
    setFixedSize(m_background.size());
    update();
}

void MapEditor::saveMapData(const QString& filePath) {
    bool hasCtSpawn = false;
    bool hasTSpawn = false;
    int PlantingSpots = 0;

    for (const Block& block : mapdata.blocks) {
        QString type = block.getTypeString();
        if (type == "CtSpawn") hasCtSpawn = true;
        if (type == "TSpawn") hasTSpawn = true;
        if (type == "Plantable") PlantingSpots++;
    }

    if (!hasCtSpawn || !hasTSpawn || PlantingSpots <= 1) {
        QString errorMsg;
        if (!hasCtSpawn) errorMsg += "• There should be atleast one CT spawn\n";
        if (!hasTSpawn) errorMsg += "• There should be atleast one T spawn\n";
        if (PlantingSpots <= 1) errorMsg += "• There should be atleast one planting spot\n";
        
        throw std::runtime_error(errorMsg.toStdString());
    }

    YAML::Emitter out;
    out << YAML::BeginMap;
        
    if (!mapdata.backgroundPath.isEmpty()) {
        QString bgPath = mapdata.backgroundPath;
        if (bgPath.contains("../resources/backgrounds/")) {
            bgPath = "../resources/backgrounds/" + bgPath.section("../resources/backgrounds/", -1);
            out << YAML::Key << "background";
            out << YAML::DoubleQuoted << bgPath.toStdString();
        } else {
            out << YAML::Key << "background" << YAML::Value << bgPath.toStdString();
        }
    }
        
    out << YAML::Key << "planting_spots" << YAML::Value << PlantingSpots;
        
    out << YAML::Key << "blocks" << YAML::Value << YAML::BeginSeq;
    for (const Block& block : mapdata.blocks) {
        out << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << block.getPosition().x();
        out << YAML::Key << "y" << YAML::Value << block.getPosition().y();
        out << YAML::Key << "type" << YAML::Value << block.getTypeString().toStdString();

        QString texPath = block.getTexturePath();
        if (texPath.contains("../resources/tiles/")) {
            texPath = "../resources/tiles/" + texPath.section("../resources/tiles/", -1);
            out << YAML::Key << "texture";
            out << YAML::DoubleQuoted << texPath.toStdString();
        } else {
            out << YAML::Key << "texture" << YAML::Value << texPath.toStdString();
        }
        
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;
    out << YAML::EndMap;

    std::ofstream fout(filePath.toStdString());
    if (!fout) {
        throw std::runtime_error("No se pudo abrir el archivo para escritura");
    }
    fout << out.c_str();  
}

void MapEditor::loadBackground(const QString &imagePath) {
    if (m_background.load(imagePath) && !m_background.isNull()) {
        QSize imageSize = m_background.size();
        
        if (parentWidget()) {
            QSize parentSize = parentWidget()->size();
            
            QSize scaledSize = imageSize.scaled(parentSize, Qt::KeepAspectRatioByExpanding);
            
            scaledSize.setWidth(scaledSize.width() - (scaledSize.width() % 32));
            scaledSize.setHeight(scaledSize.height() - (scaledSize.height() % 32));
            
            m_background = m_background.scaled(scaledSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
        else {
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

void MapEditor::placeTile(const QPoint& position, const QString& texturePath, const QString& type) {
    Block::Type blockType = Block::stringToType(type);
    
    static const QVector<Block::Type> weaponTypes = {
        Block::DropedGlock, 
        Block::DropedAk47, 
        Block::DropedM4, 
        Block::DropedAwp
    };

    bool isWeapon = weaponTypes.contains(blockType);

    auto it = std::find_if(mapdata.blocks.begin(), mapdata.blocks.end(),
        [&position](const Block& block) {
            return block.getPosition() == position;
        });

    if (isWeapon) {
        bool hasNonSolidBlock = false;
        
        for (const Block& block : mapdata.blocks) {
            if (block.getPosition() == position && block.getType() != Block::Solid) {
                hasNonSolidBlock = true;
                break;
            }
        }

        if (!hasNonSolidBlock) {
            return;
        }else{
            Block block;
            block.setPosition(position);
            block.setTexture(texturePath);
            block.setType(type);
            mapdata.addBlock(block);  
            update();
            return;
        }
    }

    if (it != mapdata.blocks.end()) {
        it->setTexture(texturePath);
        it->setType(type);
    } else {
        Block block;
        block.setPosition(position);
        block.setTexture(texturePath);
        block.setType(type);
        mapdata.addBlock(block);
    }
    
    update();
}


MapData MapEditor::getMapData(){
    return mapdata;
}

void MapEditor::dragEnterEvent(QDragEnterEvent *event) {   
    if (event->mimeData()->hasImage()) {
        m_dragStartPos = event->pos();
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
}

void MapEditor::dropEvent(QDropEvent* event) {   
     if (event->mimeData()->hasFormat("application/x-tiledata")) {
        QByteArray itemData = event->mimeData()->data("application/x-tiledata");
        QDataStream stream(&itemData, QIODevice::ReadOnly);
        QPoint tilePos;
        QString texturePath;
        QString typeString;
        stream >> tilePos >> texturePath >> typeString;
        
        QPoint dropPos(
            (event->pos().x() / m_tileWidth) * m_tileWidth,
            (event->pos().y() / m_tileHeight) * m_tileHeight
        );
        
        placeTile(dropPos, texturePath, typeString);
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

    QHash<QString, QPixmap> textureCache; 
    const QColor white(255, 255, 255);

    for (const Block &block : mapdata.blocks) {
    
        if (!textureCache.contains(block.getTexturePath())) {
            QPixmap tile;
            if (tile.load(block.getTexturePath())) {
                QBitmap mask = tile.createMaskFromColor(white, Qt::MaskInColor);
                tile.setMask(mask);
                
                textureCache[block.getTexturePath()] = tile;
            }
        }

        if (textureCache.contains(block.getTexturePath())) {
            painter.drawPixmap(block.getPosition(), textureCache[block.getTexturePath()]);
        }
    }
}
