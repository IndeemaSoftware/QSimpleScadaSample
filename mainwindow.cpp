#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "VObject/vobject.h"

#include <QDebug>
#include <QTimer>

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
