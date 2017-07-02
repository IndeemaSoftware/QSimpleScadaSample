#include "vobjectinfodialog.h"
#include "ui_vobjectinfodialog.h"

#include "vobjectinfo.h"

VObjectInfoDialog::VObjectInfoDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VObjectInfoDialog),
    mLatestObject{nullptr}
{
    ui->setupUi(this);

    initAxiesList();
}

VObjectInfoDialog::~VObjectInfoDialog()
{
    delete ui;
}

void VObjectInfoDialog::updateWithObjectInfo(VObjectInfo *info)
{
    mLatestObject = info;

    //title
    ui->lineEditName->setText(info->title());

    //axies
    VObjectInfoAxis lAxis = mLatestObject->axis();
    enableAxis(info->axiesEnabled());
    ui->comboBoxX->setCurrentText(lAxis.getStringX());
    ui->comboBoxY->setCurrentText(lAxis.getStringY());
    ui->comboBoxZ->setCurrentText(lAxis.getStringZ());
}

void VObjectInfoDialog::enableAxis(bool enable)
{
    ui->comboBoxX->setEnabled(enable);
    ui->comboBoxY->setEnabled(enable);
    ui->comboBoxZ->setEnabled(enable);
}

void VObjectInfoDialog::initAxiesList()
{
    ui->comboBoxX->clear();
    ui->comboBoxY->clear();
    ui->comboBoxZ->clear();

    QStringList lList;
    lList.append(AXIS_UP);
    lList.append(AXIS_ASIDE);
    lList.append(AXIS_INSIDE);

    ui->comboBoxX->addItems(lList);
    ui->comboBoxY->addItems(lList);
    ui->comboBoxZ->addItems(lList);
}

void VObjectInfoDialog::on_pushButton_2_pressed()
{
    //title
    mLatestObject->setTitle(ui->lineEditName->text());

    //axies
    mLatestObject->setAxiesEnabled(ui->checkBox->isChecked());//status
    VObjectInfoAxis lAxis;
    lAxis.setX(lAxis.axisFromString(ui->comboBoxX->currentText()));
    lAxis.setY(lAxis.axisFromString(ui->comboBoxY->currentText()));
    lAxis.setZ(lAxis.axisFromString(ui->comboBoxZ->currentText()));
    mLatestObject->setAxis(lAxis);

    if (mLatestObject != nullptr) {
        emit savePressed(mLatestObject);
    }
}

void VObjectInfoDialog::on_pushButton_pressed()
{
    if (mLatestObject != nullptr) {
        emit deletePressed(mLatestObject);
        mLatestObject = nullptr;
    }
}

void VObjectInfoDialog::on_checkBox_stateChanged(int arg1)
{
    bool lEnabled = false;
    switch(arg1) {
    case Qt::Unchecked: {
        lEnabled = false;
        break;
    }
    case Qt::Checked:{
        lEnabled = true;
        break;
    }
    }

    enableAxis(lEnabled);
}
