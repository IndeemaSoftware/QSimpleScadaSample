#include "vboard.h"
#include "vobject.h"

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
    setMouseTracking(true);//this not mouseMoveEven is called everytime mouse is moved
}

VBoard::~VBoard()
{
    qDeleteAll(*mObjects);
    delete mObjects;
}

void VBoard::createNewObject()
{
    VObject *lObject = new VObject(this);
    lObject->info()->setId(mObjects->count());
    lObject->setIsEditable(mEditable);
    connect(lObject, SIGNAL(objectSelected(int)), this , SLOT(newObjectSelected(int)));
    lObject->show();
    mObjects->append(lObject);
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
    (void)e;
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

void VBoard::updateObjectWithId(int id)
{
    for (VObject *object : *mObjects) {
        if (id == object->info()->id()) {
            object->update();
        }
    }
}

bool VBoard::showGrid() const
{
    return mShowGrid;
}

void VBoard::setShowGrid(bool showGrid)
{
    mShowGrid = showGrid;

    repaint();
}

bool VBoard::editable() const
{
    return mEditable;
}

void VBoard::setEditable(bool editable)
{
    mEditable = editable;

    for (VObject *object : *mObjects) {
        object->setEnabled(editable);
    }
}
