#ifndef VOBJECTINFO_H
#define VOBJECTINFO_H

#include "vobjectinfoaxis.h"

#include <QObject>
#include <QColor>
#include <QRect>

class VObjectInfo : public QObject
{
    Q_OBJECT
public:
    explicit VObjectInfo(QObject *parent = 0);

    int id() const;
    void setId(int id);

    QString title() const;
    void setTitle(const QString &title);

    VObjectInfoAxis axis() const;
    void setAxis(const VObjectInfoAxis &axis);

    bool axiesEnabled() const;
    void setAxiesEnabled(bool axiesEnabled);

private:
    QColor mColor;
    QRect mGeometry;
    int mId;
    QString mTitle;
    VObjectInfoAxis mAxis;
    bool mAxiesEnabled;
};

#endif // VOBJECTINFO_H
