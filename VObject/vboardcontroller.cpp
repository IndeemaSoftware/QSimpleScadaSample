#include "vboardcontroller.h"
#include "vboardmanager.h"

#include "../../3rdparty/VObject/vboard.h"
#include "../../3rdparty/VObject/vobjectinfodialog.h"

#include <QGridLayout>
#include <QMenu>
#include <QDebug>

VBoardController::VBoardController(QWidget *parent) :
    QWidget(parent),
    mLayout{new QGridLayout},
    mBoard{nullptr}
{
    mBoardManager = new VBoardManager();

    this->setLayout(mLayout);

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
    delete mLayout;
}

void VBoardController::updateBoardForDeviceIp(QString ip)
{
    if (mBoard != nullptr
            && mBoard->isVisible()) {
        mBoard->hide();
        disconnect(mBoard, SIGNAL(objectSelected(VObject *)), this, SLOT(updateObjectInfoDialog(VObject *)));
    }

    mBoard = mBoardManager->getBoardForDeviceWithIp(ip);
    connect(mBoard, SIGNAL(objectSelected(VObject *)), this, SLOT(updateObjectInfoDialog(VObject *)));
    mBoard->setParent(this);
    mLayout->addWidget(mBoard);
    mBoard->show();
}

void VBoardController::showContextMenu(const QPoint &pos)
{
    if (mBoard != nullptr
            && mBoard->isVisible()) { //show context menu if only VBoard is visible
        QMenu lContextMenu{this};

        lContextMenu.addAction(tr("Add Object"), this, SLOT(addNewObject()));
        lContextMenu.addAction(tr("Show Parameters"), this, SLOT(showParameters()));

        lContextMenu.exec(mapToGlobal(pos));
    }
}

void VBoardController::addNewObject()
{
    mBoard->createNewObject();
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
    if (info != nullptr) {
        mBoard->deleteObjectWithId(info->id());
    }
}

void VBoardController::updateSavedObject(VObjectInfo *info)
{
    if (info != nullptr) {
        mBoard->updateObjectWithId(info->id());
    }
}

void VBoardController::updateStatus()
{
    qDebug() << "update";
    int lNumber = 3;
    int lRandomValue = qrand() % lNumber;
    mBoard->updateStatusWithId(0, (VObjectStatus)lRandomValue);
    lRandomValue = qrand() % lNumber;
    mBoard->updateStatusWithId(1, (VObjectStatus)lRandomValue);
}
