#include "tilesheetdata.h"
#include <QFile>
#include <yaml-cpp/yaml.h>
#include <QDebug>

inline bool operator<(const QPoint& p1, const QPoint& p2) {
    return (p1.y() < p2.y()) || (p1.y() == p2.y() && p1.x() < p2.x());
}

bool TileSheetData::loadFromYAML(const QString& filePath) {
    
    YAML::Node config = YAML::LoadFile(filePath.toStdString());
    
    tilesheetPath = QString::fromStdString(config["tilesheet"].as<std::string>());
    for (const auto& blockNode : config["blocks"]) {
        int x = blockNode["x"].as<int>();
        int y = blockNode["y"].as<int>();
        QString texture = QString::fromStdString(blockNode["texture"].as<std::string>());
        QString type = QString::fromStdString(blockNode["type"].as<std::string>());
            
        tileData[QPoint(x, y)] = {texture, type};
    }
        
    return true;
}

TileSheetData::TileInfo TileSheetData::getTileInfo(int x, int y) const {
    QPoint pos(x, y);
    if (tileData.contains(pos)) {
        return tileData.value(pos);
    }
    return {"", "Common"};
}

QString TileSheetData::getTilesheetPath() const {
    return tilesheetPath;
}
