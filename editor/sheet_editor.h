#ifndef SHEETEDITOR_H
#define SHEETEDITOR_H
#include "sheetdata.h"
#include <QWidget>
#include <QPixmap>
#include <QApplication>

class SheetEditor : public QWidget
{
    Q_OBJECT
public:
    explicit SheetEditor(QWidget *parent = nullptr);
    
    void loadsheet(const QString &configPath);
    void setTileSize(int width, int height);
    QPixmap getSelectedTile() const;
    QString getCurrentTexturePath() const;
    QString getCurrentType() const;

signals:
    void tileSelected(const QString& texturePath, const QString& type);
    
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    QPixmap m_tilesheet;
    QPoint m_selectedTilePos;
    bool m_isDragging;
    int m_tileWidth;
    int m_tileHeight;
    SheetData sheetdata;
};

#endif // SHEETEDITOR_H
