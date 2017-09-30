#include "vobject.h"

#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPen>

#define RESIZE_FIELD_SIZE 10
#define RESIZE_AREA(x, y) ((geometry().width() - RESIZE_FIELD_SIZE) < x) && ((geometry().height() - RESIZE_FIELD_SIZE) < y)

VObject::VObject(QWidget *parent) :
    QWidget(parent),
    mInfo{new VObjectInfo},
    mEffect{new QGraphicsDropShadowEffect},
    mStatus{VObjectStatusNone}
{
    setGeometry(100, 100, 100, 100);
    if (info()->showBackground()) {
        setPalette(QPalette(Qt::transparent));
        setAutoFillBackground(true);
    }

    mEffect->setOffset(0);
    setGraphicsEffect(mEffect);

    dynamicStatusChanged(mInfo);

    setAction(VObjectActionNone);
    setMouseTracking(true);//this not mouseMoveEven is called everytime mouse is moved

    connect(mInfo, SIGNAL(dynamicStatusChanged(VObjectInfo *)), this, SLOT(dynamicStatusChanged(VObjectInfo *)));
}

VObject::~VObject()
{
    delete mInfo;
    delete mEffect;
}

void VObject::setGeometry(int x, int y, int width, int height)
{
    setGeometry(QRect(x, y, width, height));
}

void VObject::setGeometry(const QRect &r)
{
    info()->setGeometry(r);
    QWidget::setGeometry(r);
}

QRect VObject::geometry()
{
    return info()->geometry();
}

void VObject::mouseMoveEvent(QMouseEvent *event)
{
    if (mIsEditable) {
        switch (action()) {
        case VObjectActionMove:{
            move(event->x(), event->y());
            break;
        }
        case VObjectActionResize:{
            resize(event->x(), event->y());
            break;
        }
        case VObjectActionNone: {
            if (RESIZE_AREA(event->x(), event->y())) {
                QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
            } else if (underMouse()) {
                QApplication::setOverrideCursor(Qt::OpenHandCursor);
            }
        }
        }
    } else {
        QWidget::mouseMoveEvent(event);
    }
}

void VObject::mousePressEvent(QMouseEvent *event)
{
    if (mIsEditable) {
        if (event->button() == Qt::LeftButton) {
            int lX = event->x();
            int lY = event->y();

            if (RESIZE_AREA(lX, lY)) {
                setAction(VObjectActionResize);
            } else {
                setSelected(true);
                QApplication::setOverrideCursor(Qt::ClosedHandCursor);
                setAction(VObjectActionMove);

                mPosition.setX(lX);
                mPosition.setY(lY);
            }
        }
    } else {
        QWidget::mousePressEvent(event);
    }
}

void VObject::mouseReleaseEvent(QMouseEvent *event)
{
    if (mIsEditable) {
        (void)event;
        setAction(VObjectActionNone);
        QApplication::setOverrideCursor(Qt::ArrowCursor);
    } else {
        QWidget::mouseReleaseEvent(event);
    }
}

void VObject::paintEvent(QPaintEvent *e)
{
    QPainter lPainter(this);
    QPixmap lMarkerPixmap(info()->imageName(mStatus));
    QPixmap lBackgroundPixmap(info()->backGroundImage());
    QPen lLinepen(Qt::black);
    lLinepen.setCapStyle(Qt::RoundCap);
    lPainter.setRenderHint(QPainter::Antialiasing,true);
    lPainter.setPen(lLinepen);

    //draw object title
    lPainter.drawText(QPoint(10, 20), mInfo->title());
    int lX;
    int lY;

    if (info()->axiesEnabled()) {
        //draw axies

        switch(info()->axisPosition()) {
        case VObjectAxisPositionLeft:
            lX = 12;
            break;
        case VObjectAxisPositionRight:
            lX = geometry().width() - 30;
            break;
        }
        lY = geometry().height() - 10;
        int lWidth = 10;
        int lInner = 4;

        lPainter.drawEllipse(lX-lInner/2,
                             lY-lInner/2,
                             lInner,
                             lInner);
        lPainter.drawText(QPoint(lX - 10, geometry().height()-2), info()->axis().insideAxisString());//inside position

        lPainter.drawLine(lX, lY,
                          lX, lY -lWidth);
        lPainter.drawLine(lX, lY -lWidth-1,
                          lX-3, lY -lWidth+3);
        lPainter.drawLine(lX, lY -lWidth-1,
                          lX+3, lY -lWidth+3);
        lPainter.drawText(QPoint(lX - 3, lY -lWidth-3), info()->axis().upsideAxisString());//up possibtion

        lPainter.drawLine(lX, lY,
                          lX + lWidth, lY);
        lPainter.drawLine(lX + lWidth+1, lY,
                          lX + lWidth-3, lY-3);
        lPainter.drawLine(lX + lWidth+1, lY,
                          lX + lWidth-3, lY+3);
        lPainter.drawText(QPoint(lX + lWidth + 3, lY+3), info()->axis().asideAxisString());//aside position
    }

    //draw resize dots
    lX = geometry().width()-RESIZE_FIELD_SIZE;
    lY = geometry().height();

    lLinepen.setColor(Qt::darkGray);
    lLinepen.setWidth(1);
    lPainter.setPen(lLinepen);

    if (mIsEditable) {
        for (int i=1; i<=RESIZE_FIELD_SIZE; i++) {
            for (int j=1; j<=i; j++) {
                lPainter.drawPoint(QPoint(lX + 2*i, lY - 2*j));
            }
        }
    }

    if (info()->showMarkers()) {
        QSize lSize = lMarkerPixmap.size();
        lPainter.drawPixmap(QRect((width() - lSize.width()) /2,
                                  (height() - lSize.height()) / 2,
                                  lSize.width(),
                                  lSize.height()),
                            lMarkerPixmap);
    }

    if (info()->showBackgroundImage()) {
        lPainter.drawPixmap(QRect(0,
                                  0,
                                  width(),
                                  height()),
                            lBackgroundPixmap.scaled(width(), height(),
                                                     Qt::KeepAspectRatioByExpanding));
    }

    if (info()->isDynamic()) {
        switch(mStatus) {
        case VObjectStatusNone:
            lLinepen.setColor(Qt::darkGray);
            break;
        case VObjectStatusRed:
            lLinepen.setColor(QColor(171, 27, 227, 255));
            break;
        case VObjectStatusYellow:
            lLinepen.setColor(QColor(228, 221, 29, 255));
            break;
        case VObjectStatusGreen:
            lLinepen.setColor(QColor(14, 121, 7, 255));
            break;
        }
    } else {
        lLinepen.setColor(Qt::black);
    }

    if (info()->showBackground()) {
        lLinepen.setWidth(2);
        lPainter.setPen(lLinepen);
        lPainter.drawRoundedRect(0,0,width(), height(),3,3);
    }

    QWidget::paintEvent(e);
}

void VObject::dynamicStatusChanged(VObjectInfo *info)
{
    if (info->isDynamic()) {
        switch(mStatus) {
        case VObjectStatusNone:
            setPalette(QPalette(Qt::lightGray));
            break;
        case VObjectStatusRed:
            setPalette(QPalette(Qt::red));
            break;
        case VObjectStatusYellow:
            setPalette(QPalette(Qt::yellow));
            break;
        case VObjectStatusGreen:
            setPalette(QPalette(Qt::green));
            break;
        }
    } else {
        setPalette(QPalette(Qt::white));
    }

    if (!info->showBackground()) {
        setPalette(QPalette(Qt::transparent));
    }
}

VObjectStatus VObject::status() const
{
    return mStatus;
}

void VObject::setStatus(const VObjectStatus &status)
{
    mStatus = status;
    dynamicStatusChanged(mInfo);
}

bool VObject::isEditable() const
{
    return mIsEditable;
}

void VObject::setIsEditable(bool isEditable)
{
    mIsEditable = isEditable;
}

void VObject::update()
{
    if (info()->showBackground()) {
        setPalette(QPalette(Qt::transparent));
        setAutoFillBackground(true);
    }

    QWidget::update();

    setGeometry(info()->geometry());
    dynamicStatusChanged(info());
}

bool VObject::selected() const
{
    return mSelected;
}

void VObject::setSelected(bool selected)
{
    mSelected = selected;

    if (mSelected) {
        emit objectSelected(mInfo->id());

        mEffect->setBlurRadius(50);
        raise();
    } else {
        mEffect->setBlurRadius(0);
    }
}

VObjectInfo *VObject::info() const
{
    return mInfo;
}

void VObject::setInfo(VObjectInfo *info)
{
    setGeometry(info->geometry());
    mInfo = info;
}

VObjectAction VObject::action() const
{
    return mAction;
}

void VObject::setAction(const VObjectAction &action)
{
    mAction = action;
}

void VObject::move(int x, int y)
{
    int lX = geometry().x() + x - mPosition.x();
    int lY = geometry().y() + y - mPosition.y();

    setGeometry(lX,
                lY,
                geometry().width(),
                geometry().height());
}

void VObject::resize(int x, int y)
{
    int lX = x - geometry().width();
    int lY = y - geometry().height();

    setGeometry(geometry().x(),
                geometry().y(),
                geometry().width() + lX,
                geometry().height() + lY);

    repaint();
}
