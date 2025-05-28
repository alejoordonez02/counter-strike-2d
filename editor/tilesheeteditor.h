#ifndef TILESHEETEDITOR_H
#define TILESHEETEDITOR_H

#include <QWidget>
#include <QPixmap>

class TileSheetEditor : public QWidget
{
    Q_OBJECT
public:
    explicit TileSheetEditor(QWidget *parent = nullptr);
    
    void loadTilesheet(const QString &imagePath);
    void setTileSize(int width, int height);
    QPixmap getSelectedTile() const;
    
signals:
    void tileSelected(const QPixmap &tile);
    
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_tilesheet;
    QPoint m_selectedTilePos;
    int m_tileWidth;
    int m_tileHeight;
};

#endif // TILESHEETEDITOR_H
