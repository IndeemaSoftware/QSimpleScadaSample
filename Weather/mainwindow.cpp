#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QScadaBoard/qscadaboardcontroller.h"
#include "QScadaDevice/qscadadeviceinfo.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mController = new QScadaBoardController(ui->centralWidget);
#warning set correct path to file
    mController->openProject("/Users/vshevchyk/projects/QSimpleScadaSample/Weather/dashboard.irp");
    mController->setEditingMode(false);

    ui->centralWidget->layout()->addWidget(mController);

    mMgr = new QNetworkAccessManager();
    connect(mMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleResponse(QNetworkReply*)));

    on_pushButton_clicked();//automatic first call
}

MainWindow::~MainWindow()
{
    delete mMgr;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString lUrl = "http://api.openweathermap.org/data/2.5/weather?q=" + ui->lineEdit->text() + "&APPID=c3b5bb9d92eb4a926d433765b7b43412";
    QNetworkRequest lRequest(lUrl);

    mMgr->get(lRequest);
}

void MainWindow::handleResponse(QNetworkReply *reply)
{
    QByteArray lResponse = reply->readAll();

    QJsonObject lObject = QJsonDocument::fromJson(lResponse).object();

    QJsonObject lWeather = lObject.value("main").toObject();

    mController->updateValue("127.0.0.1", 0, 1, QVariant::fromValue(lWeather.value("temp").toDouble() - 273.15));
    mController->updateValue("127.0.0.1", 0, 2, QVariant::fromValue(lWeather.value("humidity").toDouble()));
    mController->updateValue("127.0.0.1", 0, 0, QVariant::fromValue(lWeather.value("pressure").toDouble()));
}
