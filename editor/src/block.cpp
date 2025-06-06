#include "block.h"

Block::Block() : m_position(0, 0), m_texturePath(""), m_type(Common) {}

Block::Block(const QPoint& position, const QString& texturePath, Type type) :
    m_position(position),
    m_texturePath(texturePath),
    m_type(type) {}

QPoint Block::getPosition() const {
    return m_position;
}

QString Block::getTexturePath() const {
    return m_texturePath;
}

Block::Type Block::getType() const {
    return m_type;
}

QString Block::getTypeString() const {
    switch(m_type) {
        case Common:    return "Common";
        case Solid:     return "Solid";
        case Plantable: return "Plantable";
        case TSpawn:    return "TSpawn";
        case CtSpawn:   return "CtSpawn";
        default:        return "Unknown";
    }
}

void Block::setPosition(const QPoint& position) {
    m_position = position;
}

void Block::setTexture(const QString& texturePath) {
    m_texturePath = texturePath;
}

void Block::setType(const QString& typeString) {
    m_type = stringToType(typeString);
}

Block::Type Block::stringToType(const QString& typeString) {
    QString lower = typeString.toLower();
    
    if (lower == "common")    return Common;
    if (lower == "solid")     return Solid;
    if (lower == "plantable") return Plantable;
    if (lower == "tspawn")    return TSpawn;
    if (lower == "ctspawn")   return CtSpawn;
    
    return Common;
}