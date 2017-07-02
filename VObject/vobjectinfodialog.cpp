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
    if (mLatestObject != nullptr) {
        disconnect(mLatestObject, SIGNAL(geometryChanged(VObjectInfo*)), this, SLOT(geometryUpdated(VObjectInfo *)));
    }
    mLatestObject = info;

    if (mLatestObject != nullptr) {
        //General
        connect(mLatestObject, SIGNAL(geometryChanged(VObjectInfo*)), this, SLOT(geometryUpdated(VObjectInfo *)));
        ui->lineEditName->setText(mLatestObject->title());
        ui->checkBoxDynamic->setChecked(info->isDynamic());
        ui->spinBoxId->setValue(info->id());

        //axies
        VObjectInfoAxis lAxis = mLatestObject->axis();
        enableAxis(info->axiesEnabled());
        ui->comboBoxX->setCurrentText(lAxis.getStringX());
        ui->comboBoxY->setCurrentText(lAxis.getStringY());
        ui->comboBoxZ->setCurrentText(lAxis.getStringZ());

        //geometry
        geometryUpdated(mLatestObject);
    } else {
        //clear title
        ui->lineEditName->clear();

        //clear axies
        enableAxis(false);

        //geometry
        ui->spinBoxX->clear();
        ui->spinBoxY->clear();
        ui->spinBoxWidth->clear();
        ui->spinBoxHeight->clear();
    }
}

void VObjectInfoDialog::enableAxis(bool enable)
{
    ui->checkBoxAxis->setChecked(enable);

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

void VObjectInfoDialog::geometryUpdated(VObjectInfo *info)
{
    ui->spinBoxX->setValue(info->geometry().x());
    ui->spinBoxY->setValue(info->geometry().y());
    ui->spinBoxWidth->setValue(info->geometry().width());
    ui->spinBoxHeight->setValue(info->geometry().height());
}
//save button pressed
void VObjectInfoDialog::on_pushButton_2_pressed()
{
    if (mLatestObject != nullptr) {
        //general
        mLatestObject->setTitle(ui->lineEditName->text());
        mLatestObject->setIsDynamic(ui->checkBoxDynamic->isChecked());
        mLatestObject->setId(ui->spinBoxId->value());

        //geometry
        int lX = ui->spinBoxX->value();
        int lY = ui->spinBoxY->value();
        int lWidth = ui->spinBoxWidth->value();
        int lHeight = ui->spinBoxHeight->value();

        mLatestObject->setGeometry(QRect(lX, lY, lWidth, lHeight));
        //axies
        mLatestObject->setAxiesEnabled(ui->checkBoxAxis->isChecked());//status
        VObjectInfoAxis lAxis;
        lAxis.setX(lAxis.axisFromString(ui->comboBoxX->currentText()));
        lAxis.setY(lAxis.axisFromString(ui->comboBoxY->currentText()));
        lAxis.setZ(lAxis.axisFromString(ui->comboBoxZ->currentText()));
        mLatestObject->setAxis(lAxis);

        if (mLatestObject != nullptr) {
            emit savePressed(mLatestObject);
        }
    }
}
//delete button pressed
void VObjectInfoDialog::on_pushButton_pressed()
{
    if (mLatestObject != nullptr) {
        emit deletePressed(mLatestObject);
        mLatestObject = nullptr;
    }
}

void VObjectInfoDialog::on_checkBoxAxis_stateChanged(int arg1)
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
