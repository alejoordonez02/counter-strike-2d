#ifndef BLOCK_H
#define BLOCK_H

#include <QPixmap>
#include <QPoint>
#include <QString>

#define TEXTURE_PREFIX "resources/tiles/"
#define WEAPON_PREFIX "resources/weapons/"
#define SUFFIX ".png"

class Block {
public:
    enum Type {
        Common,     
        Solid,      
        Plantable, 
        TSpawn,   
        CtSpawn,
        DropedGlock,
        DropedAk47,
        DropedM4,
        DropedAwp 
    };

    Block();
    Block(const QPoint& position, const QString& texture, Type type);
    QPoint getPosition() const;
    QString getTexture() const;
    QString getTexturePath() const;
    Type getType() const;
    QString getTypeString() const; 

    void setPosition(const QPoint& position);
    void setTexture(const QString& texture);
    void setType(const QString& typeString);
    static Type stringToType(const QString& typeString);
private:
    bool isDroppedWeapon(Type type) const;
    QPoint m_position;
    QString m_texture;
    Type m_type;
};

#endif // BLOCK_H
