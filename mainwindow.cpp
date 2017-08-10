#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "VSimpleScada/vobject.h"
#include "VSimpleScada/vboardinfo.h"
#include "VSimpleScada/ventity/vconnecteddeviceinfo.h"

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
    connect(mBoard, SIGNAL(objectSelected(VObject *)), this, SLOT(updateObjectInfoDialog(VObject *)));

    connect(ui->widgetObjectParametrs, SIGNAL(deletePressed(VObjectInfo*)), this, SLOT(deleteObject(VObjectInfo *)));
    connect(ui->widgetObjectParametrs, SIGNAL(savePressed(VObjectInfo*)), this, SLOT(updateSavedObject(VObjectInfo *)));

    mObjectInfoDialog = ui->widgetObjectParametrs;

    ui->centralWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->centralWidget, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(showContextMenu(const QPoint&)));

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(updateStatus()));
    mTimer->start(1000);

    connect(ui->actionQuit, SIGNAL(toggled(bool)), this, SLOT(close()));
    connect(ui->actionSave, SIGNAL(toggled(bool)), this, SLOT(save()));
    connect(ui->actionOpen, SIGNAL(toggled(bool)), this, SLOT(open()));
}

MainWindow::~MainWindow()
{
    delete mTimer;
    delete ui;
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    QMenu lContextMenu{this};

    lContextMenu.addAction(tr("Add Object"), this, SLOT(addNewObject()));

    lContextMenu.exec(ui->centralWidget->mapToGlobal(pos));
}

void MainWindow::addNewObject()
{
    if (mBoard->objects()->count() == 2) {
            VObjectInfo *lInfo = new VObjectInfo();
            lInfo->setId(2);
            lInfo->setImageName(":/resources/some_structure.png", VObjectStatusNone);

            mBoard->createNewObject(lInfo);
    } else {
        mBoard->createNewObject();
    }
}

void MainWindow::updateObjectInfoDialog(VObject *object)
{
    if (object != nullptr) {
        mObjectInfoDialog->updateWithObjectInfo(object->info());
    } else {
        mObjectInfoDialog->updateWithObjectInfo(nullptr);
    }
}

void MainWindow::deleteObject(VObjectInfo *info)
{
    if (info != nullptr) {
        mBoard->deleteObjectWithId(info->id());
    }
}

void MainWindow::updateSavedObject(VObjectInfo *info)
{
    if (info != nullptr) {
        mBoard->updateObjectWithId(info->id());
    }
}

void MainWindow::updateStatus()
{
//    int lNumber = 3;
//    int lRandomValue = qrand() % lNumber;
//    mBoard->updateStatusWithId(0, (VObjectStatus)lRandomValue);
//    lRandomValue = qrand() % lNumber;
//    mBoard->updateStatusWithId(1, (VObjectStatus)lRandomValue);
}

void MainWindow::save()
{
    QFileDialog lDialog(this);
    lDialog.setFileMode(QFileDialog::AnyFile);
    lDialog.setAcceptMode(QFileDialog::AcceptSave);
    lDialog.setDirectory(QDir::currentPath());
    lDialog.setWindowTitle(tr("Save Project"));
    lDialog.setNameFilter(tr("iReDS Project (*.irp)"));

    VBoardInfo *lBoardInfo = new VBoardInfo();
    VBoardController *lController = new VBoardController();
    VDeviceInfo lDeviceInfo;

    if (lDialog.exec() == QDialog::Accepted) {
        QStringList lFiles = lDialog.selectedFiles();
        if (lFiles.count() > 0) {
            QString lFileName = lFiles.at(0);
            if (!lFileName.contains(".irp")) {
                lFileName.append(".irp");
            }
            QStringList lIps;
            for (VObject *object :*mBoard->objects()) {
                lBoardInfo->appendObjectInfo(object->info());
            }
            QList<VBoardInfo*> lBoardInfoList;
            lBoardInfoList.append(lBoardInfo);

            lController->initConnectedDevices(lBoardInfoList);

            lDeviceInfo.setName("Test Device");
            QList<VDeviceInfo> lList;
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
        }
    }

    delete lBoardInfo;
    delete lController;
}

void MainWindow::open()
{

}
