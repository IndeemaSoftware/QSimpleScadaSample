#ifndef VVIEWCONFIGURAOT_H
#define VVIEWCONFIGURAOT_H

#include <QWidget>
#include <QList>

#include "vobject.h"

class VBoard;
class QGridLayout;
class VObjectInfoDialog;
class VObjectInfo;
class VObject;
class VUnitModel;
class VBoardManager;
class VBoardInfo;

class VBoardController : public QWidget
{
    Q_OBJECT
public:
    explicit VBoardController(QWidget *parent = 0);
    ~VBoardController();

    void initConnectedDevices(const QList<VBoardInfo*>list);

    void clearBoard(VBoard*);
    void clearAllBoards();

    void initBoardForDeviceIp(QString);
    void updateBoardForDeviceIp(QString);
    QList<VBoard*> getBoardList();
    QList<VBoard*> getBoardListForDeviceIp(QString);

    void updateStatus(QString device, int objectId, VObjectStatus status);

    void setEditingMode(bool);

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
