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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showContextMenu(const QPoint&);
    void addNewObject();
    void bringToFront();
    void sendToBack();
    void updateObjectInfoDialog(QScadaObject *);
    void deleteObject(QScadaObjectInfo *);
    void updateSavedObject(QScadaObjectInfo *);
    void updateStatus();

    void save();
    void open();

private:
    Ui::MainWindow *ui;

    QScadaBoardController *mController;
    QScadaBoard *mBoard;
    QScadaObjectInfoDialog *mObjectInfoDialog;
    QTimer *mTimer;
};

#endif // MAINWINDOW_H
