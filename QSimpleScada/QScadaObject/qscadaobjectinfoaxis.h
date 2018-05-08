#ifndef VOBJECTINFOAXIS_H
#define VOBJECTINFOAXIS_H

#include <QString>

#define AXIS_UP "Upside"
#define AXIS_ASIDE "Aside"
#define AXIS_INSIDE "Inside"
#define AXIS_UNDEFINED "UNDEFINED"

#define ZXIS_X "x"
#define ZXIS_Y "y"
#define ZXIS_Z "z"
#define ZXIS_UNDEFINED "-1"

typedef enum {
    VObjectInfoAxisDirrectionUndefined,
    VObjectInfoAxisDirrectionUpside,
    VObjectInfoAxisDirrectionAside,
    VObjectInfoAxisDirrectionInside
} VObjectInfoAxisDirrection;

class VObjectInfoAxis
{
public:
    explicit VObjectInfoAxis();

    QString stringFromAxis(VObjectInfoAxisDirrection dirr);

    VObjectInfoAxisDirrection axisFromString(QString string);

    QString upsideAxisString();
    QString asideAxisString();
    QString insideAxisString();

    QString getStringX();
    VObjectInfoAxisDirrection getX() const;
    void setX(const VObjectInfoAxisDirrection &value);

    QString getStringY();
    VObjectInfoAxisDirrection getY() const;
    void setY(const VObjectInfoAxisDirrection &value);

    QString getStringZ();
    VObjectInfoAxisDirrection getZ() const;
    void setZ(const VObjectInfoAxisDirrection &value);

private:
    VObjectInfoAxisDirrection mX;
    VObjectInfoAxisDirrection mY;
    VObjectInfoAxisDirrection mZ;
};

#endif // VOBJECTINFOAXIS_H
