#ifndef VOBJECTINFODIALOG_H
#define VOBJECTINFODIALOG_H

#include <QWidget>

namespace Ui {
class QScadaObjectInfoDialog;
}

class VObjectInfo;

class QScadaObjectInfoDialog : public QWidget
{
    Q_OBJECT

public:
    explicit QScadaObjectInfoDialog(QWidget *parent = 0);
    ~QScadaObjectInfoDialog();

public slots:
    void updateWithObjectInfo(VObjectInfo *info);

private:
    void enableAxis(bool);
    void initAxiesList();

private slots:
    void geometryUpdated(VObjectInfo*);
    void on_pushButton_2_pressed();

    void on_pushButton_pressed();

    void on_checkBoxAxis_stateChanged(int arg1);

    void on_pushButton_3_clicked();

signals:
    void deletePressed(VObjectInfo*);
    void savePressed(VObjectInfo*);

private:
    Ui::QScadaObjectInfoDialog *ui;

    QString mMarkerImage;

    VObjectInfo *mLatestObject;
};

#endif // VOBJECTINFODIALOG_H
