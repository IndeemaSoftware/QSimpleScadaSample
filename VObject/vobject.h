#ifndef VOBJECT_H
#define VOBJECT_H

#include "vobjectinfo.h"

#include <QWidget>
#include <QLabel>

typedef enum {
    VObjectActionNone,
    VObjectActionMove,
    VObjectActionResize
} VObjectAction;

class QGraphicsDropShadowEffect;

class VObject : public QWidget
{
    Q_OBJECT
public:
    explicit VObject(QWidget *parent = 0);
    ~VObject();

    void setGeometry(int x, int y, int width, int height);
    void setGeometry(const QRect &);
    QRect geometry();

    VObjectInfo *info() const;
    void setInfo(VObjectInfo *info);

    bool selected() const;
    void setSelected(bool selected);

    bool isEditable() const;
    void setIsEditable(bool isEditable);

    void update();

private:
    VObjectAction action() const;
    void setAction(const VObjectAction &action);

    void move(int x, int y);
    void resize(int x, int y);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *e);

signals:
    void objectSelected(int id);

private:
    QPoint mPosition;
    bool mIsEditable;

    VObjectAction mAction;
    VObjectInfo *mInfo;
    QGraphicsDropShadowEffect* mEffect;
    bool mSelected;
};

#endif // VOBJECT_H
