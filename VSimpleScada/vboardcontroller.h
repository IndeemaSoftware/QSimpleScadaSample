#ifndef VVIEWCONFIGURAOT_H
#define VVIEWCONFIGURAOT_H

#include <QWidget>
#include <QList>

#include "vobject.h"

class VBoard;
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
    void updateStatus(QStringList device, QList<int> objectId, QList<VObjectStatus> status);

    void setEditingMode(bool);

signals:
    void objectDoubleClicked(VObject*);

private slots:
    void showContextMenu(const QPoint&);
    void addNewObject();
    void bringToFront();
    void sendToBack();
    void showParameters();
    void updateObjectInfoDialog(VObject *);
    void deleteObject(VObjectInfo *);
    void updateSavedObject(VObjectInfo *);
    void updateStatus();
    void objectDoubleClickedHandler(VObject*);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    VBoardManager *mBoardManager;
    VBoard *mBoard;
    VObjectInfoDialog *mParametersDialod;
    QList<int> mObjectIds;
};

#endif // VVIEWCONFIGURAOT_H
