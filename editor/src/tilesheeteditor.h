#ifndef TILESHEETEDITOR_H
#define TILESHEETEDITOR_H
#include "tilesheetdata.h"
#include <QWidget>
#include <QPixmap>
#include <QApplication>

class TileSheetEditor : public QWidget
{
    Q_OBJECT
public:
    explicit TileSheetEditor(QWidget *parent = nullptr);
    
    void loadTilesheet(const QString &configPath);
    void setTileSize(int width, int height);
    QPixmap getSelectedTile() const;

signals:
    void tileSelected(const QPixmap &tile);
    
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    QString getTypeStringForTile(int tileX, int tileY);
private:
    QPixmap m_tilesheet;
    QPoint m_selectedTilePos;
    int m_tileWidth;
    int m_tileHeight;
    TileSheetData tilesheetdata;
};

#endif // TILESHEETEDITOR_H
