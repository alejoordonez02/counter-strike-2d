#ifndef SHEETDATA_H
#define SHEETDATA_H

#include <QString>
#include <QMap>
#include <QPoint>

class SheetData {
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

#endif // SHEETDATA_H
