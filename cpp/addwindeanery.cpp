#include "addwindeanery.h"
#include "ui_addwindeanery.h"

AddWindowDeanery::AddWindowDeanery(QWidget *parent, Deanery *deaneryObject) :
    QDialog(parent),
    ui(new Ui::AddWindowDeanery)
{
    this->deaneryObject = deaneryObject;
    QString str;
    ui->setupUi(this);
    ui->lineLName->setText(deaneryObject->getLName());
    ui->lineFName->setText(deaneryObject->getFName());
    ui->lineMName->setText(deaneryObject->getMName());
    ui->lineEMail->setText(deaneryObject->getEmail());
    ui->lineTelNum->setText(str.setNum(deaneryObject->getTelNumber()));
    ui->lineOffice->setText(deaneryObject->getOffice());
    ui->lineBuild->setText(str.setNum(deaneryObject->getBuild()));
}

AddWindowDeanery::~AddWindowDeanery()
{
    delete ui;
}
