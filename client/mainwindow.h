#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class ClientInterface;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    signals:
        void connectToLobby(const QString& host, const QString& serv);
        void showError(const QString& message);
    private slots:
        void on_startButton_clicked();
    private:
        Ui::ClientInterface *ui;

};

#endif
