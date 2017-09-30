#ifndef VOBJECT_H
#define VOBJECT_H

#include "vobjectinfo.h"

#include <QWidget>
#include <QLabel>
#include <QImage>

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

    VObjectStatus status() const;
    void setStatus(const VObjectStatus &status);

private:
    VObjectAction action() const;
    void setAction(const VObjectAction &action);

    void move(int x, int y);
    void resize(int x, int y);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent*);

    void paintEvent(QPaintEvent *e);

signals:
    void objectSelected(int id);
    void objectDoubleClicked(VObject*);

private slots:
    void dynamicStatusChanged(VObjectInfo*);

private:
    QPoint mPosition;
    bool mIsEditable;//if tru object could be moveable, if false it's static

    VObjectAction mAction;
    VObjectInfo *mInfo;
    QGraphicsDropShadowEffect* mEffect;
    bool mSelected;

    VObjectStatus mStatus;// default is VObjectStatusNone
};

#endif // VOBJECT_H
