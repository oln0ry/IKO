#include "indicatorprl.h"
#include "ui_indicatorprl.h"

IndicatorPRL::IndicatorPRL(QWidget *parent):QWidget(parent),ui(new Ui::IndicatorPRL)
{
    ui->setupUi(this);
    QStringList range_marks,
                scale;
    range_marks<<"Не отображать"<<"5 километров"<<"10 километров";
    ui->SelectRangeMarksEquiangular->addItems(range_marks);
    ui->SelectRangeMarksEquiangular->setCurrentIndex(1);
    ui->SelectRangeMarksRightTriangle->addItems(range_marks);
    ui->SelectRangeMarksRightTriangle->setCurrentIndex(1);
    scale<<"20 километров"<<"30 километров"<<"60 километров";
    ui->SelectScaleEquiangular->addItems(scale);
    ui->SelectScaleEquiangular->setCurrentIndex(1);
    ui->SelectScaleRightTriangle->addItems(scale);
    ui->SelectScaleRightTriangle->setCurrentIndex(1);

    ui->ChangeIndicatorBrightnessEquiangular->valueChanged(ui->ChangeIndicatorBrightnessEquiangular->value());
    ui->ChangeIndicatorFocusEquiangular->valueChanged(ui->ChangeIndicatorFocusEquiangular->value());
    ui->ChangeDisplayLightningEquiangular->valueChanged(ui->ChangeDisplayLightningEquiangular->value());
    ui->ChangeIndicatorVARUEquiangular->valueChanged(ui->ChangeIndicatorVARUEquiangular->value());
    ui->ChangeTrashIntensityEquiangular->valueChanged(ui->ChangeTrashIntensityEquiangular->value());

    ui->ChangeIndicatorBrightnessRightTriangle->valueChanged(ui->ChangeIndicatorBrightnessRightTriangle->value());
    ui->ChangeIndicatorFocusRightTriangle->valueChanged(ui->ChangeIndicatorFocusRightTriangle->value());
    ui->ChangeDisplayLightningRightTriangle->valueChanged(ui->ChangeDisplayLightningRightTriangle->value());
    ui->ChangeIndicatorVARURightTriangle->valueChanged(ui->ChangeIndicatorVARURightTriangle->value());
    ui->ChangeTrashIntensityRightTriangle->valueChanged(ui->ChangeTrashIntensityRightTriangle->value());

    ui->RenderEquiangularIndicator->ChangeFPS(1000/24);
    ui->RenderRightTriangleIndicator->ChangeFPS(1000/24);
}

IndicatorPRL::~IndicatorPRL()
{
    delete ui;
}

void IndicatorPRL::on_SelectScaleEquiangular_currentIndexChanged(int index)
{
    if(index<0)
        return;
    qreal max;
    switch(index)
    {
        case 2:
            max=60.0f;
            break;
        case 1:
            max=30.0f;
            break;
        default:
            max=20.0f;

    }
    ui->RenderEquiangularIndicator->SetSettings("system","scale",static_cast<quint8>(max));
    ui->RenderEquiangularIndicator->SetSettings("trash","end",max);
    ui->RenderEquiangularIndicator->SetSettings("trash","begin",0);
}

void IndicatorPRL::on_SelectRangeMarksEquiangular_currentIndexChanged(int index)
{
    if(index<0)
        return;
    ui->RenderEquiangularIndicator->SetSettings("system","range",static_cast<quint16>(index));
}

void IndicatorPRL::on_ChangeTrashIntensityEquiangular_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquiangularIndicator->SetSettings("trash","show",value>0);
    ui->RenderEquiangularIndicator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void IndicatorPRL::on_ChangeIndicatorBrightnessEquiangular_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquiangularIndicator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
}

void IndicatorPRL::on_ChangeIndicatorFocusEquiangular_valueChanged(int value)
{
    value=value>=0 ? value+100 : 100-value;
    ui->RenderEquiangularIndicator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void IndicatorPRL::on_ChangeLocatorStateEquiangular_clicked()
{
    quint16 fps;
    if(ui->RenderEquiangularIndicator->IsActive())
    {
        ui->RenderEquiangularIndicator->ChangeFPS(0);
        ui->ChangeLocatorStateEquiangular->setText("Продолжить");
    }
    else
    {
        fps=static_cast<quint8>(24);
        ui->RenderEquiangularIndicator->ChangeFPS(1000/fps);
        ui->ChangeLocatorStateEquiangular->setText("Стоп");
    }
    //ui->InputFrameFrequency->valueChanged(24);
}

void IndicatorPRL::on_ChangeViewStateAllEquiangular_clicked()
{
    if(ui->RenderEquiangularIndicator->show)
    {
        ui->ChangeViewStateAllEquiangular->setText("Отобразить всё");
        ui->RenderEquiangularIndicator->SetSettings("system","show",false);
    }
    else
    {
        ui->ChangeViewStateAllEquiangular->setText("Скрыть");
        ui->RenderEquiangularIndicator->SetSettings("system","show",true);
    }
}

void IndicatorPRL::on_ChangeDisplayLightningEquiangular_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquiangularIndicator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
}

void IndicatorPRL::on_ChangeIndicatorVARUEquiangular_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquiangularIndicator->SetSettings("system","varu",static_cast<qreal>(value)/100);
}

void IndicatorPRL::on_ChangeLocatorStateRightTriangle_clicked()
{
    quint16 fps;
    if(ui->RenderRightTriangleIndicator->IsActive())
    {
        ui->RenderRightTriangleIndicator->ChangeFPS(0);
        ui->ChangeLocatorStateRightTriangle->setText("Продолжить");
    }
    else
    {
        fps=static_cast<quint8>(24);
        ui->RenderRightTriangleIndicator->ChangeFPS(1000/fps);
        ui->ChangeLocatorStateRightTriangle->setText("Стоп");
    }
}

void IndicatorPRL::on_SelectRangeMarksRightTriangle_currentIndexChanged(int index)
{
    if(index<0)
        return;
    ui->RenderRightTriangleIndicator->SetSettings("system","range",static_cast<quint16>(index));
}

void IndicatorPRL::on_SelectScaleRightTriangle_currentIndexChanged(int index)
{
    if(index<0)
        return;
    qreal max;
    switch(index)
    {
        case 2:
            max=60.0f;
            break;
        case 1:
            max=30.0f;
            break;
        default:
            max=20.0f;

    }
    ui->RenderRightTriangleIndicator->SetSettings("system","scale",static_cast<quint8>(max));
    ui->RenderRightTriangleIndicator->SetSettings("trash","end",max);
    ui->RenderRightTriangleIndicator->SetSettings("trash","begin",0);
}

void IndicatorPRL::on_ChangeTrashIntensityRightTriangle_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleIndicator->SetSettings("trash","show",value>0);
    ui->RenderRightTriangleIndicator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void IndicatorPRL::on_ChangeDisplayLightningRightTriangle_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleIndicator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
}

void IndicatorPRL::on_ChangeIndicatorBrightnessRightTriangle_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleIndicator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
}


void IndicatorPRL::on_ChangeIndicatorFocusRightTriangle_valueChanged(int value)
{
    value=value>=0 ? value+100 : 100-value;
    ui->RenderRightTriangleIndicator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void IndicatorPRL::on_ChangeIndicatorVARURightTriangle_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleIndicator->SetSettings("system","varu",static_cast<qreal>(value)/100);
}

void IndicatorPRL::on_ChangeViewStateAllRightTriangle_clicked()
{
    if(ui->RenderRightTriangleIndicator->show)
    {
        ui->ChangeViewStateAllRightTriangle->setText("Отобразить всё");
        ui->RenderRightTriangleIndicator->SetSettings("system","show",false);
    }
    else
    {
        ui->ChangeViewStateAllRightTriangle->setText("Скрыть");
        ui->RenderRightTriangleIndicator->SetSettings("system","show",true);
    }
}
