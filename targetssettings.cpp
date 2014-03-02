#include"targetssettings.h"
#include"ui_targetssettings.h"
#include<QDebug>
TargetsSettings::TargetsSettings(QWidget *parent) : QWidget(parent),ui(new Ui::TargetsSettings)
{
    ui->setupUi(this);
    targets_count=ui->Targets->count();
    QCheckBox* checkbox;
    for(quint8 widget=0u;widget<Count();widget++)
    {
        ui->Targets->setCurrentIndex(widget);
        checkbox=ui->Targets->currentWidget()->findChild<QCheckBox*>(QString("%1%2").arg("TargetGoHome_").arg(widget+1)),
        connect(
            checkbox,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(on_TargetsGoHome_stateChanged(int))
        );
        checkbox->stateChanged(checkbox->checkState());
    }
    ui->Targets->setCurrentIndex(0);
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
    if(pos<Count()-1u)
        pos++;
    else
        pos=0u;
    ui->Targets->setCurrentIndex(pos);
}

void TargetsSettings::on_SwitchTargetPrev_clicked()
{
    quint8 pos=static_cast<quint8>(ui->Targets->currentIndex());
    if(pos>0u)
        pos--;
    else
        pos=Count()-1u;
    ui->Targets->setCurrentIndex(pos);
}

void TargetsSettings::on_ApplyTargets_clicked()
{
    Targs=new Targets[Count()];
    quint8 old=ui->Targets->currentIndex();
    QGroupBox* Gb;
    for(quint8 widget=0u;widget<Count();widget++)
    {
        ui->Targets->setCurrentIndex(widget);
        Targs[widget].speed=ui->Targets->currentWidget()->findChild<QDoubleSpinBox*>(QString("%1%2").arg("TargetSpeed_").arg(widget+1u))->value();
        if(ui->Targets->currentWidget()->findChild<QCheckBox*>(QString("%1%2").arg("TargetGoHome_").arg(widget+1u))->isChecked())
            Targs[widget].landing=ui->Targets->currentWidget()->findChild<QRadioButton*>(QString("%1%2").arg("TargetGoHome330_").arg(widget+1u))->isChecked() ? 2u : 1u;
        else
            Targs[widget].landing=0u;
        Gb=ui->Targets->currentWidget()->findChild<QGroupBox*>(QString("%1%2").arg("TargetExtremums_").arg(widget+1u));
        Gb->findChild<QGroupBox*>(QString("%1%2").arg("TargetExtremumFirst_").arg(widget+1u))
          ->findChild<QDoubleSpinBox*>(QString("%1%2").arg("TargetRangeExtremumFirst_").arg(widget+1u));
    }
    ui->Targets->setCurrentIndex(old);
//close();
}

void TargetsSettings::on_TargetsGoHome_stateChanged(int arg)
{
    QRadioButton *radio1,*radio2;
    radio1=QObject::sender()->parent()->findChild<QRadioButton*>(QString("%1%2").arg("TargetGoHome150_").arg(ui->Targets->currentIndex()+1));
    radio2=QObject::sender()->parent()->findChild<QRadioButton*>(QString("%1%2").arg("TargetGoHome330_").arg(ui->Targets->currentIndex()+1));
    if((radio1->isChecked() && radio2->isChecked()) || (!radio1->isChecked() && !radio2->isChecked()))
    {
        radio1->setChecked(true);
        radio2->setChecked(false);
    }
    radio1->setEnabled(arg==2);
    radio2->setEnabled(arg==2);
}
