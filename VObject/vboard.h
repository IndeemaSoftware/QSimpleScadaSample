#ifndef VBOARD_H
#define VBOARD_H

#include <QWidget>
#include <QList>

class VObject;
class VObjectInfo;

class VBoard : public QWidget
{
    Q_OBJECT
public:
    explicit VBoard(QWidget *parent = 0);
    ~VBoard();

    void createNewObject();

    bool editable() const;
    void setEditable(bool editable);

    bool showGrid() const;
    void setShowGrid(bool showGrid);

    int grid() const;
    void setGrid(int grid);

    void deleteObjectWithId(int);
    void updateObjectWithId(int);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *e);

signals:
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
