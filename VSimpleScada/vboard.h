#ifndef VBOARD_H
#define VBOARD_H

#include "vobject.h"

#include <QWidget>
#include <QList>

class VObjectInfo;

class VBoard : public QWidget
{
    Q_OBJECT
public:
    explicit VBoard(QWidget *parent = 0);
    ~VBoard();

    void createNewObject();
    void createNewObject(VObjectInfo *);
    void createNewObject(int id);

    bool editable() const;
    void setEditable(bool editable);

    bool showGrid() const;
    void setShowGrid(bool showGrid);

    int grid() const;
    void setGrid(int grid);

    void deleteObjectWithId(int);
    void deleteObject(VObject*);
    void updateObjectWithId(int);
    void updateStatusWithId(int, VObjectStatus);

    QList<VObject *> *objects() const;

    QList<VObject*> getSeletedObjects();

public slots:
    //objects order
    void bringToFront(VObject*);
    void sendToBack(VObject*);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *e);

signals:
    void objectDoubleClicked(VObject*);
    void objectSelected(VObject *);

private slots:
    void newObjectSelected(int id);

private:
    QList<VObject*> *mObjects;
    bool mEditable; //default value false
    bool mShowGrid; //default value true
    int mGrid; //default value 10
};

#endif // VBOARD_H
