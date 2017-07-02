#include "vobjectinfoaxis.h"

VObjectInfoAxis::VObjectInfoAxis()
{
    mX = VObjectInfoAxisDirrectionUpside;
    mY = VObjectInfoAxisDirrectionAside;
    mZ = VObjectInfoAxisDirrectionInside;
}

QString VObjectInfoAxis::stringFromAxis(VObjectInfoAxisDirrection dirr){
    switch (dirr) {
    case VObjectInfoAxisDirrectionUpside:
        return AXIS_UP;
    case VObjectInfoAxisDirrectionAside:
        return AXIS_ASIDE;
    case VObjectInfoAxisDirrectionInside:
        return AXIS_INSIDE;
    case VObjectInfoAxisDirrectionUndefined:
        return AXIS_UNDEFINED;
    }
}

VObjectInfoAxisDirrection VObjectInfoAxis::axisFromString(QString string){
    if (string == QString(AXIS_UP)) {
        return VObjectInfoAxisDirrectionUpside;
    } else if (string == AXIS_ASIDE) {
        return VObjectInfoAxisDirrectionAside;
    } else if (string == AXIS_INSIDE) {
        return VObjectInfoAxisDirrectionInside;
    } else {
        return VObjectInfoAxisDirrectionUndefined;
    }
}

QString VObjectInfoAxis::upsideAxisString()
{
    if (getX() == VObjectInfoAxisDirrectionUpside) {
        return ZXIS_X;
    } else if (getY() == VObjectInfoAxisDirrectionUpside) {
        return ZXIS_Y;
    } else if (getZ() == VObjectInfoAxisDirrectionUpside) {
        return ZXIS_Z;
    } else {
        return ZXIS_UNDEFINED;
    }
}

QString VObjectInfoAxis::asideAxisString()
{
    if (getX() == VObjectInfoAxisDirrectionAside) {
        return ZXIS_X;
    } else if (getY() == VObjectInfoAxisDirrectionAside) {
        return ZXIS_Y;
    } else if (getZ() == VObjectInfoAxisDirrectionAside) {
        return ZXIS_Z;
    } else {
        return ZXIS_UNDEFINED;
    }
}

QString VObjectInfoAxis::insideAxisString()
{
    if (getX() == VObjectInfoAxisDirrectionInside) {
        return ZXIS_X;
    } else if (getY() == VObjectInfoAxisDirrectionInside) {
        return ZXIS_Y;
    } else if (getZ() == VObjectInfoAxisDirrectionInside) {
        return ZXIS_Z;
    } else {
        return ZXIS_UNDEFINED;
    }
}

QString VObjectInfoAxis::getStringX()
{
    return stringFromAxis(getX());
}

VObjectInfoAxisDirrection VObjectInfoAxis::getX() const
{
    return mX;
}

void VObjectInfoAxis::setX(const VObjectInfoAxisDirrection &value)
{
    mX = value;
}

QString VObjectInfoAxis::getStringY()
{
    return stringFromAxis(getY());
}

VObjectInfoAxisDirrection VObjectInfoAxis::getY() const
{
    return mY;
}

void VObjectInfoAxis::setY(const VObjectInfoAxisDirrection &value)
{
    mY = value;
}

QString VObjectInfoAxis::getStringZ()
{
    return stringFromAxis(getZ());
}

VObjectInfoAxisDirrection VObjectInfoAxis::getZ() const
{
    return mZ;
}

void VObjectInfoAxis::setZ(const VObjectInfoAxisDirrection &value)
{
    mZ = value;
}
