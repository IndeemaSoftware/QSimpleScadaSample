#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QScadaObject/qscadaobject.h"
#include "QScadaBoard/qscadaboardinfo.h"
#include "QScadaBoard/qscadaboard.h"
#include "QScadaEntity/qscadaconnecteddeviceinfo.h"
#include "qscadaconfig.h"

#include <QDebug>
#include <QFileDialog>
#include <QTimer>
#include <QMessageBox>
#include <QGridLayout>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mController = new QScadaBoardController();
    mController->initBoardForDeviceIp("127.0.0.0");
    mController->setEditingMode(true);

    mBoard = mController->getBoardListForDeviceIp("127.0.0.0").at(0);
    connect(mBoard, SIGNAL(objectSelected(QScadaObject *)), this, SLOT(updateObjectInfoDialog(QScadaObject *)));

    QGridLayout *mainLayout = new QGridLayout(ui->centralWidget);

    connect(ui->widgetObjectParametrs, SIGNAL(deletePressed(QScadaObjectInfo*)), this, SLOT(deleteObject(QScadaObjectInfo *)));
    connect(ui->widgetObjectParametrs, SIGNAL(savePressed(QScadaObjectInfo*)), this, SLOT(updateSavedObject(QScadaObjectInfo *)));

    mObjectInfoDialog = ui->widgetObjectParametrs;
    mainLayout->addWidget(mBoard);

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
    delete mController;
    delete ui;
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    bool lShowOrder = (mBoard->getSeletedObjects().count() > 0);
    QMenu lContextMenu{this};

    QMenu lAddWidget(tr("Add Object"));
    lContextMenu.addMenu(&lAddWidget);

    for (QMLWidgetsConfig group : QMLConfig::instance().QMLWidgets()) {
        QMenu *lWidgetMenu = lAddWidget.addMenu(group.info.groupTitle);

        for (QString widget : group.widgets()) {
            QString lWidgetTitle = widget.split(".").at(0);
            QIcon lIcon(group.info.groupPath + lWidgetTitle +".png");
            QAction *lWidgetAction = new QAction(lIcon, lWidgetTitle);//remove qml from name
            lWidgetAction->setData(QVariant::fromValue<QMLWidgetsConfig>(group));

            lWidgetMenu->addAction(lWidgetAction);
            connect(lWidgetAction, SIGNAL(triggered()), this, SLOT(addNewObject()));
        }
    }

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
    QAction *lSender = static_cast<QAction*>(QObject::sender());
    QMLWidgetsConfig lConfig = lSender->data().value<QMLWidgetsConfig>();

    QString lQMLFilePath = lConfig.info.groupPath + lSender->text() + ".qml";//add qml to name

    mBoard->createQMLObject(lQMLFilePath);
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
    mBoard->updateValue(0, qrand() % 100);
    mBoard->updateValue(1, qrand() % 100);
    mBoard->updateValue(2, qrand() % 100);
}

void MainWindow::save()
{
    if (mBoard->objects()->count() == 0) {
        QString lMessage(tr("Nothing to be saved"));

        QMessageBox lMsgBox;
        lMsgBox.setText(lMessage);
        lMsgBox.exec();
        return;
    }

    QFileDialog lDialog(this);
    lDialog.setFileMode(QFileDialog::AnyFile);
    lDialog.setAcceptMode(QFileDialog::AcceptSave);
    lDialog.setDirectory(QDir::currentPath());
    lDialog.setWindowTitle(tr("Save Project"));
    lDialog.setNameFilter(tr("iReDS Project (*.irp)"));

    QScadaDeviceInfo lDeviceInfo;
    lDeviceInfo.setName("Test Device");
    lDeviceInfo.setIp(QHostAddress("127.0.0.0"));
    QList<QScadaDeviceInfo> lList;
    lList.append(lDeviceInfo);

    if (lDialog.exec() == QDialog::Accepted) {
        QStringList lFiles = lDialog.selectedFiles();
        if (lFiles.count() > 0) {
            QString lFileName = lFiles.at(0);
            if (!lFileName.contains(".irp")) {
                lFileName.append(".irp");
            }

            QString lDevices = QConnectedDeviceInfo::XMLFromDeviceInfo(lList, mController);   //<----;

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
        }
    }

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

        QConnectedDeviceInfo* lConnectedDevceInfo = new QConnectedDeviceInfo();
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
                        mBoard->initBoard(boardInfo);
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
