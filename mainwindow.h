#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class VBoard;
class VObjectInfo;
class VObject;
class VObjectInfoDialog;
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
    void updateObjectInfoDialog(VObject *);
    void deleteObject(VObjectInfo *);
    void updateSavedObject(VObjectInfo *);
    void updateStatus();

    void save();
    void open();

private:
    Ui::MainWindow *ui;

    VBoard *mBoard;
    VObjectInfoDialog *mObjectInfoDialog;
    QTimer *mTimer;
};

#endif // MAINWINDOW_H
