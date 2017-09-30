#include "vboardcontroller.h"
#include "vboardmanager.h"

#include "vboard.h"
#include "vboardinfo.h"
#include "vobjectinfodialog.h"

#include <QGridLayout>
#include <QMenu>
#include <QDebug>

VBoardController::VBoardController(QWidget *parent) :
    QWidget(parent),
    mBoard{nullptr}
{
    mBoardManager = new VBoardManager();

    setPalette(QPalette(Qt::transparent));
    setAutoFillBackground(true);

    mParametersDialod = new VObjectInfoDialog();
    connect(mParametersDialod, SIGNAL(deletePressed(VObjectInfo*)), this, SLOT(deleteObject(VObjectInfo *)));
    connect(mParametersDialod, SIGNAL(savePressed(VObjectInfo*)), this, SLOT(updateSavedObject(VObjectInfo *)));

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(showContextMenu(const QPoint&)));
}

VBoardController::~VBoardController()
{
    delete mBoardManager;
    delete mParametersDialod;
    delete mBoard;
}

void VBoardController::initConnectedDevices(const QList<VBoardInfo *> list)
{
    qDebug() << __FUNCTION__;
    for (VBoardInfo *boardInfo : list) {
        if (boardInfo != nullptr) {
            mBoard->setEditable(false);
            for (VObjectInfo *info : boardInfo->objectList()) {
                mBoard->createNewObject(info);
            }
        }
    }
    mBoard->update();
}

void VBoardController::clearBoard(VBoard* board)
{
    qDebug() << __FUNCTION__;

    for (VObject *object : *board->objects()) {
        board->deleteObject(object);
    }
    board->update();
}

void VBoardController::clearAllBoards()
{
    qDebug() << __FUNCTION__;
    for (VBoard *board:mBoardManager->getBoardList()) {
        clearBoard(board);
    }
}

void VBoardController::initBoardForDeviceIp(QString ip)
{
    qDebug() << __FUNCTION__;
    if (mBoard != nullptr
            && mBoard->isVisible()) {
        mBoard->hide();
        disconnect(mBoard, SIGNAL(objectSelected(VObject *)), this, SLOT(updateObjectInfoDialog(VObject *)));
    }

    mBoard = mBoardManager->getBoardForDeviceWithIp(ip);
    mBoard->setGeometry(QRect(0, 0, this->geometry().width(), this->geometry().height()));
    connect(mBoard, SIGNAL(objectSelected(VObject *)), this, SLOT(updateObjectInfoDialog(VObject *)));
    connect(mBoard, SIGNAL(objectDoubleClicked(VObject*)), this, SLOT(objectDoubleClickedHandler(VObject*)));
}

void VBoardController::updateBoardForDeviceIp(QString ip)
{
    initBoardForDeviceIp(ip);

    mBoard->setParent(this);
    mBoard->show();
}

void VBoardController::showContextMenu(const QPoint &pos)
{
    if (mBoard != nullptr
            && mBoard->isVisible()
            && mBoard->editable()) { //show context menu if only VBoard is visible
        bool lSelectedObject = (mBoard->getSeletedObjects().count()>0);
        QMenu lContextMenu{this};

        lContextMenu.addAction(tr("Add Object"), this, SLOT(addNewObject()));
        lContextMenu.addAction(tr("Show Parameters"), this, SLOT(showParameters()))->setEnabled(lSelectedObject);
        QMenu *lOrderMenu = lContextMenu.addMenu(tr("Order"));
        lOrderMenu->setEnabled(lSelectedObject);

        if (lSelectedObject) {
            lOrderMenu->addAction(tr("Bring to front"), this, SLOT(bringToFront()));
            lOrderMenu->addAction(tr("Send to back"), this, SLOT(sendToBack()));
        }

        lContextMenu.exec(mapToGlobal(pos));
    }
}

void VBoardController::addNewObject()
{
    mBoard->createNewObject();
}

void VBoardController::bringToFront()
{
    if (!mBoard->getSeletedObjects().isEmpty()) {
        VObject *lObject = mBoard->getSeletedObjects().first();
        mBoard->bringToFront(lObject);
    }
}

void VBoardController::sendToBack()
{
    if (!mBoard->getSeletedObjects().isEmpty()) {
        VObject *lObject = mBoard->getSeletedObjects().first();
        mBoard->sendToBack(lObject);
    }
}

void VBoardController::showParameters()
{
    if (mParametersDialod->isVisible()) {
        mParametersDialod->raise();
    } else {
        mParametersDialod->show();
    }
}

void VBoardController::updateObjectInfoDialog(VObject *object)
{
    if (object != nullptr) {
        mParametersDialod->updateWithObjectInfo(object->info());
    } else {
        mParametersDialod->updateWithObjectInfo(nullptr);
    }
}

void VBoardController::deleteObject(VObjectInfo *info)
{
    qDebug() << __FUNCTION__;

    if (info != nullptr) {
        mBoard->deleteObjectWithId(info->id());
    }
}

void VBoardController::updateSavedObject(VObjectInfo *info)
{
    qDebug() << __FUNCTION__;

    if (info != nullptr) {
        mBoard->updateObjectWithId(info->id());
    }
}

void VBoardController::updateStatus()
{
    qDebug() << __FUNCTION__;

    int lNumber = 3;
    int lRandomValue = qrand() % lNumber;
    mBoard->updateStatusWithId(0, (VObjectStatus)lRandomValue);
    lRandomValue = qrand() % lNumber;
    mBoard->updateStatusWithId(1, (VObjectStatus)lRandomValue);
}

void VBoardController::objectDoubleClickedHandler(VObject *o)
{
    emit objectDoubleClicked(o);
}

void VBoardController::resizeEvent(QResizeEvent*)
{
    qDebug() << __FUNCTION__;

    if (mBoard != nullptr) {
        mBoard->setGeometry(QRect(0, 0, this->geometry().width(), this->geometry().height()));
    }
}

QList<VBoard *> VBoardController::getBoardList()
{
    return mBoardManager->getBoardList();
}

QList<VBoard *> VBoardController::getBoardListForDeviceIp(QString ip)
{
    QList<VBoard *> rList;
    rList.append(mBoardManager->getBoardForDeviceWithIp(ip));

    return rList;
}

void VBoardController::updateStatus(QString id, int objectId, VObjectStatus status)
{
    qDebug() << __FUNCTION__;

    VBoard *lBoard = mBoardManager->getBoardForDeviceWithIp(id);

    for (VObject *object :*lBoard->objects()) {
        if (object->info()->id() == objectId) {
            object->setStatus(status);
        }
    }
}

void VBoardController::updateStatus(QStringList device, QList<int> objectId, QList<VObjectStatus> status)
{
    for (int i=0; i< device.count(); i++) {
        updateStatus(device.at(i), objectId.at(i), status.at(i));
    }
}

void VBoardController::setEditingMode(bool editing)
{
    mBoard->setEditable(editing);
}
