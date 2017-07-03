#ifndef VVIEWCONFIGURAOT_H
#define VVIEWCONFIGURAOT_H

#include <QWidget>
#include <QList>

class VBoard;
class QGridLayout;
class VObjectInfoDialog;
class VObjectInfo;
class VObject;
class VUnitModel;
class VBoardManager;

class VBoardController : public QWidget
{
    Q_OBJECT
public:
    explicit VBoardController(QWidget *parent = 0);
    ~VBoardController();

    void updateBoardForDeviceIp(QString);

private slots:
    void showContextMenu(const QPoint&);
    void addNewObject();
    void showParameters();
    void updateObjectInfoDialog(VObject *);
    void deleteObject(VObjectInfo *);
    void updateSavedObject(VObjectInfo *);
    void updateStatus();

private:
    QGridLayout *mLayout;
    VBoardManager *mBoardManager;
    VBoard *mBoard;
    VObjectInfoDialog *mParametersDialod;
    QList<int> mObjectIds;
};

#endif // VVIEWCONFIGURAOT_H
