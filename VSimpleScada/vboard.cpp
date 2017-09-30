#include "vboard.h"

#include <QApplication>
#include <QPainter>
#include <QPen>
#include <QDebug>

VBoard::VBoard(QWidget *parent) :
    QWidget(parent),
    mObjects{new QList<VObject*>()},
    mEditable{false},
    mShowGrid{true},
    mGrid{10}
{
    setPalette(QPalette(Qt::transparent));
    setAutoFillBackground(true);

    setMouseTracking(true);//this not mouseMoveEven is called everytime mouse is moved
}

VBoard::~VBoard()
{
    qDeleteAll(*mObjects);
    delete mObjects;
}

void VBoard::createNewObject()
{
    createNewObject(mObjects->count());
}

void VBoard::createNewObject(VObjectInfo *info)
{
    VObject *lObject = new VObject(this);
    lObject->setInfo(info);
    //rize object if it's dynamic so general image will be on background
    if (info->isDynamic()) {
        bringToFront(lObject);
    }
    lObject->setIsEditable(mEditable);
    connect(lObject, SIGNAL(objectSelected(int)), this , SLOT(newObjectSelected(int)));
    lObject->show();
    lObject->update();
    mObjects->append(lObject);
}

void VBoard::createNewObject(int id)
{
    VObjectInfo *lInfo = new VObjectInfo();
    lInfo->setId(id);
    lInfo->setShowMarkers(true);
    lInfo->setShowBackground(true);
    lInfo->setShowBackgroundImage(false);
    lInfo->setIsDynamic(true);

    createNewObject(lInfo);
}

void VBoard::mouseMoveEvent(QMouseEvent *event)
{
    (void)event;
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void VBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        newObjectSelected(-1);
        emit objectSelected(nullptr);
    }
}

void VBoard::paintEvent(QPaintEvent *e)
{
    if (mEditable && mShowGrid) {
        QPainter lPainter(this);
        QPen lLinepen(Qt::darkGray);
        lLinepen.setCapStyle(Qt::RoundCap);
        lLinepen.setWidth(1);
        lPainter.setRenderHint(QPainter::Antialiasing,true);
        lPainter.setPen(lLinepen);

        int lX = geometry().width();
        int lY = geometry().height();

        for (int i=0; i<=lX; i++) {
            for (int j=1; j<=lY; j++) {
                lPainter.drawPoint(QPoint(mGrid*i, mGrid*j));
            }
        }
    }

    QWidget::paintEvent(e);
}

void VBoard::newObjectSelected(int id)
{
    for(VObject *object : *mObjects) {
        if (id != object->info()->id()) {
            object->setSelected(false);
        } else {
            emit objectSelected(object);
        }
    }
}

QList<VObject *> *VBoard::objects() const
{
    return mObjects;
}

QList<VObject*> VBoard::getSeletedObjects()
{
    QList<VObject*> rList;

    for(VObject *object : *mObjects) {
        if (object->selected()) {
            rList.append(object);
        }
    }

    return rList;
}

void VBoard::bringToFront(VObject *o)
{
    o->raise();
}

void VBoard::sendToBack(VObject *o)
{
    o->lower();
}

int VBoard::grid() const
{
    return mGrid;
}

void VBoard::setGrid(int grid)
{
    mGrid = grid;
}

void VBoard::deleteObjectWithId(int id)
{
    for (VObject *object : *mObjects) {
        if (id == object->info()->id()) {
            mObjects->removeOne(object);
            delete object;
            repaint();
        }
    }
}

void VBoard::deleteObject(VObject *object)
{
    deleteObjectWithId(object->info()->id());
}

void VBoard::updateObjectWithId(int id)
{
    for (VObject *object : *mObjects) {
        if (id == object->info()->id()) {
            object->update();
        }
    }
}

void VBoard::updateStatusWithId(int id, VObjectStatus status)
{
    for (VObject *object : *mObjects) {
        if (id == object->info()->id()) {
            object->setStatus(status);
            object->update();
        }
    }
}

bool VBoard::showGrid() const
{
    qDebug() << __FUNCTION__;
    return mShowGrid;
}

void VBoard::setShowGrid(bool showGrid)
{
    qDebug() << __FUNCTION__;
    mShowGrid = showGrid;

    repaint();
}

bool VBoard::editable() const
{
    qDebug() << __FUNCTION__;
    return mEditable;
}

void VBoard::setEditable(bool editable)
{
    qDebug() << __FUNCTION__;
    mEditable = editable;

    for (VObject *object : *mObjects) {
        object->setIsEditable(editable);
    }

    update();
}
