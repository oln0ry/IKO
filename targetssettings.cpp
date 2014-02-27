#include"targetssettings.h"
#include"ui_targetssettings.h"
#include<QDebug>

TargetsSettings::TargetsSettings(QWidget *parent) : QWidget(parent),ui(new Ui::TargetsSettings)
{
    ui->setupUi(this);
    targets_count=ui->Targets->count();
}

TargetsSettings::~TargetsSettings()
{
    delete ui;
}

quint8 TargetsSettings::Count()
{
    return targets_count;
}

void TargetsSettings::on_SwitchTargetNext_clicked()
{
    quint8 pos=static_cast<quint8>(ui->Targets->currentIndex());
    if(pos<Count()-1)
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
        pos=Count()-1;
    ui->Targets->setCurrentIndex(pos);
}

void TargetsSettings::on_ApplyTargets_clicked()
{
    struct Targets
    {
        qreal x,y,r;

    };
    for(quint8 widget=0u;widget<Count();widget++)
    {
        ui->Targets->setCurrentIndex(widget);
        ui->Targets->currentWidget()->findChild<QDoubleSpinBox*>(QString("%1%2").arg("TargetSpeed_").arg(widget+1));
    }

//close();
}
