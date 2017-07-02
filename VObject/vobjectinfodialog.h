#ifndef VOBJECTINFODIALOG_H
#define VOBJECTINFODIALOG_H

#include <QWidget>

namespace Ui {
class VObjectInfoDialog;
}

class VObjectInfo;

class VObjectInfoDialog : public QWidget
{
    Q_OBJECT

public:
    explicit VObjectInfoDialog(QWidget *parent = 0);
    ~VObjectInfoDialog();

public slots:
    void updateWithObjectInfo(VObjectInfo *info);

private:
    void enableAxis(bool);
    void initAxiesList();

private slots:
    void geometryUpdated(VObjectInfo*);
    void on_pushButton_2_pressed();

    void on_pushButton_pressed();

    void on_checkBox_stateChanged(int arg1);

signals:
    void deletePressed(VObjectInfo*);
    void savePressed(VObjectInfo*);

private:
    Ui::VObjectInfoDialog *ui;

    VObjectInfo *mLatestObject;
};

#endif // VOBJECTINFODIALOG_H
