#include <QMainWindow>

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
        void connectToServer(const QString& host, const QString& port);
        void showError(const QString& message);
    private slots:
        void on_startButton_clicked();
        void on_joinMatchButton_clicked();
        void on_createMatchButton_clicked();

    private:
        Ui::ClientInterface *ui;
        std::string host_;
        std::string port_;
};