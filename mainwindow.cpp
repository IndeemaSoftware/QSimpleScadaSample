#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QScadaObject/qscadaobject.h"
#include "QScadaBoard/qscadaboardinfo.h"
#include "QScadaEntity/qscadaconnecteddeviceinfo.h"

#include <QDebug>
#include <QFileDialog>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mBoard = ui->centralWidget;
    mBoard->setEditable(true);
    connect(mBoard, SIGNAL(objectSelected(QScadaObject *)), this, SLOT(updateObjectInfoDialog(QScadaObject *)));

    connect(ui->widgetObjectParametrs, SIGNAL(deletePressed(QScadaObjectInfo*)), this, SLOT(deleteObject(QScadaObjectInfo *)));
    connect(ui->widgetObjectParametrs, SIGNAL(savePressed(QScadaObjectInfo*)), this, SLOT(updateSavedObject(QScadaObjectInfo *)));

    mObjectInfoDialog = ui->widgetObjectParametrs;

    ui->centralWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->centralWidget, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(showContextMenu(const QPoint&)));

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(updateStatus()));
    mTimer->start(1000);

    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(save()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(open()));
}

MainWindow::~MainWindow()
{
    delete mTimer;
    delete ui;
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    bool lShowOrder = (mBoard->getSeletedObjects().count() > 0);
    QMenu lContextMenu{this};

    lContextMenu.addAction(tr("Add Object"), this, SLOT(addNewObject()));
    QMenu *lOrder = lContextMenu.addMenu("Order");
    lOrder->setEnabled(lShowOrder);

    if (lShowOrder) {
        lOrder->addAction(tr("Bring to front"), this, SLOT(bringToFront()));
        lOrder->addAction(tr("Send to back"), this, SLOT(sendToBack()));
    }

    lContextMenu.exec(ui->centralWidget->mapToGlobal(pos));
}

void MainWindow::addNewObject()
{
    if (mBoard->objects()->count() == 2) {
            QScadaObjectInfo *lInfo = new QScadaObjectInfo();
            lInfo->setId(2);
            lInfo->setBackGroundImage(":/resources/some_structure.png");
            lInfo->setShowBackgroundImage(true);
            lInfo->setShowMarkers(false);

            mBoard->createNewObject(lInfo);
    } else {
        mBoard->createNewObject();
    }
}

void MainWindow::bringToFront()
{
    if (!mBoard->getSeletedObjects().isEmpty()) {
        QScadaObject *lObject = mBoard->getSeletedObjects().first();
        mBoard->bringToFront(lObject);
    }
}

void MainWindow::sendToBack()
{
    if (!mBoard->getSeletedObjects().isEmpty()) {
        QScadaObject *lObject = mBoard->getSeletedObjects().first();
        mBoard->sendToBack(lObject);
    }
}

void MainWindow::updateObjectInfoDialog(QScadaObject *object)
{
    if (object != nullptr) {
        mObjectInfoDialog->updateWithObjectInfo(object->info());
    } else {
        mObjectInfoDialog->updateWithObjectInfo(nullptr);
    }
}

void MainWindow::deleteObject(QScadaObjectInfo *info)
{
    if (info != nullptr) {
        mBoard->deleteObjectWithId(info->id());
    }
}

void MainWindow::updateSavedObject(QScadaObjectInfo *info)
{
    if (info != nullptr) {
        mBoard->updateObjectWithId(info->id());
    }
}
//this method is called with timer
//You can use it to update statuses ok markers.
void MainWindow::updateStatus()
{
    int lNumber = 3;
    int lRandomValue = qrand() % lNumber;
    mBoard->updateStatusWithId(0, (QScadaObjectStatus)lRandomValue);
    lRandomValue = qrand() % lNumber;
    mBoard->updateStatusWithId(1, (QScadaObjectStatus)lRandomValue);
    lRandomValue = qrand() % lNumber;
    mBoard->updateStatusWithId(3, (QScadaObjectStatus)lRandomValue);
    lRandomValue = qrand() % lNumber;
    mBoard->updateStatusWithId(4, (QScadaObjectStatus)lRandomValue);
}

void MainWindow::save()
{
    QFileDialog lDialog(this);
    lDialog.setFileMode(QFileDialog::AnyFile);
    lDialog.setAcceptMode(QFileDialog::AcceptSave);
    lDialog.setDirectory(QDir::currentPath());
    lDialog.setWindowTitle(tr("Save Project"));
    lDialog.setNameFilter(tr("iReDS Project (*.irp)"));

    QScadaBoardInfo *lBoardInfo = new QScadaBoardInfo();
    QScadaBoardController *lController = new QScadaBoardController();
    QScadaDeviceInfo lDeviceInfo;

    if (lDialog.exec() == QDialog::Accepted) {
        QStringList lFiles = lDialog.selectedFiles();
        if (lFiles.count() > 0) {
            QString lFileName = lFiles.at(0);
            if (!lFileName.contains(".irp")) {
                lFileName.append(".irp");
            }
            QStringList lIps;
            for (QScadaObject *object :*mBoard->objects()) {
                lBoardInfo->appendObjectInfo(object->info());
            }
            QList<QScadaBoardInfo*> lBoardInfoList;
            lBoardInfoList.append(lBoardInfo);

            lController->initConnectedDevices(lBoardInfoList);

            lDeviceInfo.setName("Test Device");
            lDeviceInfo.setIp(QHostAddress("127.0.0.0"));
            QList<QScadaDeviceInfo> lList;
            lList.append(lDeviceInfo);
            QString lDevices = VConnectedDeviceInfo::XMLFromDeviceInfo(lList, lController);   //<----;

            //create xml for boards of each device

            QFile lFile(lFileName);
            if (lFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream lOut(&lFile);
                lOut.setCodec("UTF-8");
                lOut << lDevices;
            } else {
                QString lMessage(tr("Something went wrong while trying to create file"));
                lMessage.append(" ").append(lFileName);

                QMessageBox lMsgBox;
                lMsgBox.setText(lMessage);
                lMsgBox.exec();
            }
            lFile.close();
            qDeleteAll(lBoardInfoList);
        }
    }
    delete lController;
    mBoard->setEditable(true);
}

void MainWindow::open()
{
    QString lFileName = QFileDialog::getOpenFileName(this,
        tr("Open Project"), QDir::currentPath(), tr("iReDS Project (*.irp)"));

    if (!lFileName.isEmpty()) {
        mObjectInfoDialog->updateWithObjectInfo(nullptr);

        for (QScadaObject *object : *mBoard->objects()) {
                mBoard->deleteObject(object);
        }

        VConnectedDeviceInfo* lConnectedDevceInfo = new VConnectedDeviceInfo();
        QByteArray lRawData;
        QFile lFile(lFileName);
        if (lFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream lStreamFileOut(&lFile);
            lStreamFileOut.setCodec("UTF-8");
            lRawData = lStreamFileOut.readAll().toUtf8();
            lFile.close();

            lConnectedDevceInfo->initFromXml(lRawData);

            for (int i = 0; i < lConnectedDevceInfo->connecteDeviceList.count(); ++i) {
                for (QScadaBoardInfo *boardInfo : lConnectedDevceInfo->connecteDeviceList.at(i)->boardList) {
                    if (boardInfo != nullptr) {
                        mBoard->setEditable(false);
                        for (QScadaObjectInfo *info : boardInfo->objectList()) {
                            mBoard->createNewObject(info);
                        }
                    }
                }
            }

            mBoard->update();
            mBoard->setEditable(true);
        } else {
            qDebug() << "       - Error open preferences file -> " << lFile.fileName();
        }

        delete lConnectedDevceInfo;
    }
}
