#include "block.h"

Block::Block() : m_position(0, 0), m_texture(""), m_type(Common) {}

Block::Block(const QPoint& position, const QString& texture, Type type) :
    m_position(position),
    m_texture(texture),
    m_type(type) {}

QPoint Block::getPosition() const {
    return m_position;
}
QString Block::getTexture() const {
    return m_texture;
}

QString Block::getTexturePath() const {
    if (isDroppedWeapon(m_type)) {
        return WEAPON_PREFIX + m_texture.toLower() + SUFFIX;
    }
    
    return TEXTURE_PREFIX + m_texture.toLower() + SUFFIX;
}

bool Block::isDroppedWeapon(Type type) const {
    switch(type) {
        case Type::DropedGlock:
        case Type::DropedAk47:
        case Type::DropedM4:
        case Type::DropedAwp:
            return true;
        default:
            return false;
    }
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
        case DropedGlock:   return "DropedGlock";
        case DropedM4:   return "DropedM4";
        case DropedAk47:   return "DropedAk47";
        case DropedAwp:   return "DropedAwp";
        default:        return "Common";
    }
}

void Block::setPosition(const QPoint& position) {
    m_position = position;
}

void Block::setTexture(const QString& texture) {
    m_texture = texture;
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
    if (lower == "dropedglock")   return DropedGlock;
    if (lower == "dropedak47")   return DropedAk47;
    if (lower == "dropedm4")   return DropedM4;
    if (lower == "dropedawp")   return DropedAwp;
    
    return Common;
}