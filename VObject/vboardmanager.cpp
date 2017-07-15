#include "vboardmanager.h"
#include "vboard.h"

VBoardManager::VBoardManager(QObject *parent) : QObject(parent)
{

}

VBoard *VBoardManager::getBoardForDeviceWithIp(QString ip)
{
    VBoard *rBoard = nullptr;

    if (mBoardMap.contains(ip)) {
        rBoard = mBoardMap.value(ip);
    } else {
        rBoard = new VBoard();
        rBoard->setEditable(true);
        mBoardMap.insert(ip, rBoard);
    }

    return rBoard;
}

QList<VBoard *> VBoardManager::getBoardList()
{
    return mBoardMap.values();
}
