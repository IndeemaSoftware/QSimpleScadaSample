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
    //initializing device info
    QScadaDeviceInfo *lDeviceInfo = new QScadaDeviceInfo();
    lDeviceInfo->setName("Test Device");
    lDeviceInfo->setIp(QHostAddress("127.0.0.1"));

    mController = new QScadaBoardController();
    mController->appendDevice(lDeviceInfo);
    mController->initBoardForDeviceIp("127.0.0.1");
    mController->setParametersDialod(ui->widgetObjectParametrs);

    mController->setEditingMode(true);

    //adding controller to central widget
    QGridLayout *mainLayout = new QGridLayout(ui->centralWidget);
    mainLayout->addWidget(mController);

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

//this method is called with timer
//You can use it to update statuses ok markers.
void MainWindow::updateStatus()
{
    mController->updateValue("127.0.0.1", 0, 0, qrand() % 100);
    mController->updateValue("127.0.0.1", 0, 1, qrand() % 100);
    mController->updateValue("127.0.0.1", 0, 2, qrand() % 100);
    mController->updateValue("127.0.0.1", 0, 3, qrand() % 3000);
}

void MainWindow::save()
{
    QFileDialog lDialog(this);
    lDialog.setFileMode(QFileDialog::AnyFile);
    lDialog.setAcceptMode(QFileDialog::AcceptSave);
    lDialog.setDirectory(QDir::currentPath());
    lDialog.setWindowTitle(tr("Save Project"));
    lDialog.setNameFilter(tr("iReDS Project (*.irp)"));

    if (lDialog.exec() == QDialog::Accepted) {
        QStringList lFiles = lDialog.selectedFiles();
        if (lFiles.count() > 0) {
            QString lFileName = lFiles.at(0);
            mController->saveProject(lFileName);
        }
    }
}

void MainWindow::open()
{
    QString lFileName = QFileDialog::getOpenFileName(this,
        tr("Open Project"), QDir::currentPath(), tr("QSimpleScadaSample project (*.irp)"));

    mController->openProject(lFileName);
    mController->setEditingMode(true);
}
