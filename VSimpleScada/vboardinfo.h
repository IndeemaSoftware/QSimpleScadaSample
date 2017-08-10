#ifndef VBOARDINFO_H
#define VBOARDINFO_H

#include <QList>

class VObjectInfo;

struct VBoardInfo
{
    void appendObjectInfo(VObjectInfo* object){
        mObjectList.append(object);
    }
    QList<VObjectInfo*> objectList() {
        return mObjectList;
    }
private:
    QList<VObjectInfo*> mObjectList;
};

#endif // VBOARDINFO_H
