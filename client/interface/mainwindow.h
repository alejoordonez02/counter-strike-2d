#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class ClientInterface;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_StartButton_clicked();
    void on_JoinMatchButton_clicked();
    void on_CreateMatchButton_clicked();

private:
    void setupUI();
    void setupClientInterface();
    void connectSignals();

    Ui::ClientInterface *ui;
    MapLoader *m_mapLoader;
};

#endif // MAINWINDOW_H
