#ifndef VBOARDMANAGER_H
#define VBOARDMANAGER_H

#include <QObject>
#include <QMap>

class VBoard;

class VBoardManager : public QObject
{
    Q_OBJECT
public:
    explicit VBoardManager(QObject *parent = 0);

    VBoard* getBoardForDeviceWithIp(QString);

    QList<VBoard*> getBoardList();

private:
    QMap<QString, VBoard*> mBoardMap;
};

#endif // VBOARDMANAGER_H
