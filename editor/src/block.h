#ifndef BLOCK_H
#define BLOCK_H

#include <QPixmap>
#include <QPoint>
#include <QString>

class Block {
public:
    enum Type {
        Common,     
        Solid,      
        Plantable, 
        TSpawn,   
        CtSpawn     
    };

    Block();
    Block(const QPoint& position, const QString& texturePath, Type type = Common);

    QPoint getPosition() const;
    QString getTexturePath() const;
    Type getType() const;
    QString getTypeString() const; 

    void setPosition(const QPoint& position);
    void setTexture(const QString& texturePath);
    void setType(const QString& typeString);
    static Type stringToType(const QString& typeString);
private:
    QPoint m_position;
    QString m_texturePath;
    Type m_type;
};

#endif // BLOCK_H
