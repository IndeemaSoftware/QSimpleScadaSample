#include "vobjectinfo.h"

#include <QDebug>

VObjectInfo::VObjectInfo(QObject *parent) :
    QObject(parent),
    mIsDynamic{false},
    mTitle{"Noname"},
    mAxiesEnabled{false},
    mAxisPosition{VObjectAxisPositionLeft},
    mShowBackgroundImage{false},
    mShowBackground{true},
    mShowMarkers{true}
{
    setGeometry(QRect(100, 100, 100, 100));
}

int VObjectInfo::id() const
{
    return mId;
}

void VObjectInfo::setId(int id)
{
    mId = id;
}

QString VObjectInfo::title() const
{
    return mTitle;
}

void VObjectInfo::setTitle(const QString &title)
{
    mTitle = title;
}

VObjectInfoAxis VObjectInfo::axis() const
{
    return mAxis;
}

void VObjectInfo::setAxis(const VObjectInfoAxis &axis)
{
    mAxis = axis;
}

bool VObjectInfo::axiesEnabled() const
{
    return mAxiesEnabled;
}

void VObjectInfo::setAxiesEnabled(bool axiesEnabled)
{
    mAxiesEnabled = axiesEnabled;
}

QRect VObjectInfo::geometry() const
{
    return mGeometry;
}

void VObjectInfo::setGeometry(const QRect &geometry)
{
    mGeometry = geometry;
    emit geometryChanged(this);
}

bool VObjectInfo::isDynamic() const
{
    return mIsDynamic;
}

void VObjectInfo::setIsDynamic(bool isDynamic)
{
    mIsDynamic = isDynamic;

    emit dynamicStatusChanged(this);
}

QString VObjectInfo::imageName(VObjectStatus status)
{
    return mImageName.getImageNameForStatus(status);
}

void VObjectInfo::setImageName(QString imageName, VObjectStatus status)
{
    mImageName.setImageNameForState(imageName, status);
}

bool VObjectInfo::showBackground() const
{
    return mShowBackground;
}

void VObjectInfo::setShowBackground(bool showBackground)
{
    mShowBackground = showBackground;
}

bool VObjectInfo::showMarkers() const
{
    return mShowMarkers;
}

void VObjectInfo::setShowMarkers(bool showMarkers)
{
    mShowMarkers = showMarkers;
}

VObjectAxisPosition VObjectInfo::axisPosition() const
{
    return mAxisPosition;
}

void VObjectInfo::setAxisPosition(const VObjectAxisPosition &axisPosition)
{
    mAxisPosition = axisPosition;
}

QString VObjectInfo::backGroundImage() const
{
    return mBackGroundImage;
}

void VObjectInfo::setBackGroundImage(const QString &backGroundImage)
{
    mBackGroundImage = backGroundImage;
}

bool VObjectInfo::showBackgroundImage() const
{
    return mShowBackgroundImage;
}

void VObjectInfo::setShowBackgroundImage(bool showBackgroundImage)
{
    mShowBackgroundImage = showBackgroundImage;
}

//implementations for VObjectInfoImage

QString VObjectInfoImage::getImageNameForStatus(VObjectStatus status)
{
    QString rValue;
    
    switch(status) {
    case VObjectStatusNone:
        rValue = normal;
        break;
    case VObjectStatusGreen:
        rValue = green;
        break;
    case VObjectStatusYellow:
        rValue = yellow;
        break;
    case VObjectStatusRed:
        rValue = red;
        break;
    }

    return rValue;
}

void VObjectInfoImage::setImageNameForState(QString name, VObjectStatus status)
{
    switch(status) {
    case VObjectStatusNone:
        normal = name;
        break;
    case VObjectStatusGreen:
        green = name;
        break;
    case VObjectStatusYellow:
        yellow = name;
        break;
    case VObjectStatusRed:
        red = name;
        break;
    }
}
