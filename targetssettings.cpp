#include"targetssettings.h"
#include"ui_targetssettings.h"
#include"qdebug.h"

TargetsSettings::TargetsSettings(QWidget *parent) : QWidget(parent),ui(new Ui::TargetsSettings)
{
    ui->setupUi(this);
}

TargetsSettings::~TargetsSettings()
{
    delete ui;
}

void TargetsSettings::on_SwitchTargetNext_clicked()
{
    quint8 pos=static_cast<quint8>(ui->Targets->currentIndex());
    if(pos<9)
        pos++;
    else
        pos=0;
    ui->Targets->setCurrentIndex(pos);
}

void TargetsSettings::on_SwitchTargetPrev_clicked()
{
    quint8 pos=static_cast<quint8>(ui->Targets->currentIndex());
    if(pos>0)
        pos--;
    else
        pos=9;
    ui->Targets->setCurrentIndex(pos);
}

void TargetsSettings::on_ApplyTargets_clicked()
{
    close();
}
