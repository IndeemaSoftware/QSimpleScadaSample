#include "vobjectinfo.h"

VObjectInfo::VObjectInfo(QObject *parent) :
    QObject(parent),
    mTitle{"Noname"},
    mAxiesEnabled{false}
{

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
