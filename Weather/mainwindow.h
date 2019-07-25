#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QNetworkAccessManager;
class QNetworkReply;
class QScadaBoardController;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void handleResponse(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;

    QScadaBoardController *mController;

    QNetworkAccessManager* mMgr;
};

#endif // MAINWINDOW_H
