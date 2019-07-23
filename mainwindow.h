#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QScadaBoard;
class QScadaBoardController;
class QScadaObjectInfo;
class QScadaObject;
class QScadaObjectInfoDialog;
class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateStatus();

    void save();
    void open();

private:
    Ui::MainWindow *ui;

    QScadaBoardController *mController;
    QScadaBoard *mBoard;
    QTimer *mTimer;
};

#endif // MAINWINDOW_H
