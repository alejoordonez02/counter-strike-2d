#ifndef TILESHEETDATA_H
#define TILESHEETDATA_H

#include <QString>
#include <QMap>
#include <QPoint>

class TileSheetData {
public:
    struct TileInfo {
        QString texturePath;
        QString type;
    };

    bool loadFromYAML(const QString& filePath);
    TileInfo getTileInfo(int x, int y) const;
    QString getTilesheetPath() const;

private:
    int rows;
    int cols;
    QString tilesheetPath;
    QMap<QPoint, TileInfo> tileData;
};

#endif // TILESHEETDATA_H
