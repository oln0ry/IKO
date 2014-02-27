#include"rspindicators.h"
#include"ui_rspindicators.h"

RSPIndicators::RSPIndicators(QWidget *parent):QWidget(parent),ui(new Ui::RSPIndicators)
{
    ui->setupUi(this);
    QStringList azimuth_marks,range_marks,scale,range_marks_triangles,scale_triangles,work_variants;
    azimuth_marks<<"Не отображать"<<"30°"<<"10°";
    ui->SelectAzimuthMarks->addItems(azimuth_marks);
    ui->SelectAzimuthMarks->setCurrentIndex(1);
    range_marks<<"Не отображать"<<"10 километров"<<"50 километров";
    ui->SelectRangeMarks->addItems(range_marks);
    ui->SelectRangeMarks->setCurrentIndex(1);
    scale<<"45 километров"<<"90 километров"<<"150 километров";
    ui->SelectScale->addItems(scale);
    ui->SelectScale->setCurrentIndex(0);
    work_variants<<"Активный"<<"Пассивный"<<"СДЦ";
    ui->SelectWorkVariant->addItems(work_variants);
    ui->SelectWorkVariant->setCurrentIndex(1);

    range_marks_triangles<<"Не отображать"<<"5 километров"<<"10 километров";
    ui->SelectRangeMarksEquiangular->addItems(range_marks_triangles);
    ui->SelectRangeMarksEquiangular->setCurrentIndex(1);
    ui->SelectRangeMarksRightTriangle->addItems(range_marks_triangles);
    ui->SelectRangeMarksRightTriangle->setCurrentIndex(1);
    scale_triangles<<"20 километров"<<"30 километров"<<"60 километров";
    ui->SelectScaleEquiangular->addItems(scale_triangles);
    ui->SelectScaleEquiangular->setCurrentIndex(1);
    ui->SelectScaleRightTriangle->addItems(scale_triangles);
    ui->SelectScaleRightTriangle->setCurrentIndex(1);

    //Настроим индикатор кругового обзора

    //Ползунки
    ui->ChangeIndicatorBrightness->valueChanged(ui->ChangeIndicatorBrightness->value());
    ui->ChangeDisplayLightning->valueChanged(ui->ChangeDisplayLightning->value());
    ui->ChangeIndicatorFocus->valueChanged(ui->ChangeDisplayLightning->value());
    ui->ChangeIndicatorVARU->valueChanged(ui->ChangeIndicatorVARU->value());
    ui->ChangeTrashIntensity->valueChanged(ui->ChangeTrashIntensity->value());

    //Чекбоксы
    ui->CheckActiveNoiseShow->stateChanged(ui->CheckActiveNoiseShow->checkState());
    ui->CheckActiveAnswerShow->stateChanged(ui->CheckActiveAnswerShow->checkState());
    ui->CheckActiveInSyncShow->stateChanged(ui->CheckActiveInSyncShow->checkState());

    //Настройки глиссадного индикатора
    ui->ChangeTrashIntensityEquiangular->valueChanged(ui->ChangeTrashIntensityEquiangular->value());
    ui->ChangeIndicatorBrightnessEquiangular->valueChanged(ui->ChangeIndicatorBrightnessEquiangular->value());
    ui->ChangeIndicatorFocusEquiangular->valueChanged(ui->ChangeIndicatorFocusEquiangular->value());

    //Настройки курсового индикатора
    ui->ChangeTrashIntensityRightTriangle->valueChanged(ui->ChangeTrashIntensityRightTriangle->value());
    ui->ChangeIndicatorBrightnessRightTriangle->valueChanged(ui->ChangeIndicatorBrightnessRightTriangle->value());
    ui->ChangeIndicatorFocusRightTriangle->valueChanged(ui->ChangeIndicatorFocusRightTriangle->value());

    //Запуск индикаторов
    ui->FirstIndicator->ChangeFPS(1000/24);
    ui->SecondIndicator->ChangeFPS(1000/24);
    ui->ThirdIndicator->ChangeFPS(1000/24);
}

RSPIndicators::~RSPIndicators()
{
    delete ui;
}

void RSPIndicators::on_ChangeLocatorState_clicked()
{
    quint16 fps;
    if(ui->FirstIndicator->IsActive())
    {
        ui->FirstIndicator->ChangeFPS(0);
        ui->ChangeLocatorState->setText("Продолжить");
    }
    else
    {
        fps=static_cast<quint8>(24);
        ui->FirstIndicator->ChangeFPS(1000/fps);
        ui->ChangeLocatorState->setText("Стоп");
    }
}

void RSPIndicators::on_ChangeLocatorStateEquiangular_clicked()
{
    quint16 fps;
    if(ui->SecondIndicator->IsActive())
    {
        ui->SecondIndicator->ChangeFPS(0);
        ui->ChangeLocatorStateEquiangular->setText("Продолжить");
    }
    else
    {
        fps=static_cast<quint8>(24);
        ui->SecondIndicator->ChangeFPS(1000/fps);
        ui->ChangeLocatorStateEquiangular->setText("Стоп");
    }
}

void RSPIndicators::on_ChangeLocatorStateRightTriangle_clicked()
{
    quint16 fps;
    if(ui->ThirdIndicator->IsActive())
    {
        ui->ThirdIndicator->ChangeFPS(0);
        ui->ChangeLocatorStateRightTriangle->setText("Продолжить");
    }
    else
    {
        fps=static_cast<quint8>(24);
        ui->ThirdIndicator->ChangeFPS(1000/fps);
        ui->ChangeLocatorStateRightTriangle->setText("Стоп");
    }
}

void RSPIndicators::on_ChangeViewStateAll_clicked()
{
    if(ui->FirstIndicator->show)
    {
        ui->ChangeViewStateAll->setText("Все отметки");
        ui->FirstIndicator->SetSettings("system","show",false);
    }
    else
    {
        ui->ChangeViewStateAll->setText("Скрыть");
        ui->FirstIndicator->SetSettings("system","show",true);
    }
}

void RSPIndicators::on_ChangeViewStateAllEquiangular_clicked()
{
    if(ui->SecondIndicator->show)
    {
        ui->ChangeViewStateAllEquiangular->setText("Отобразить все скрытые метки");
        ui->SecondIndicator->SetSettings("system","show",false);
    }
    else
    {
        ui->ChangeViewStateAllEquiangular->setText("Скрыть");
        ui->SecondIndicator->SetSettings("system","show",true);
    }
}

void RSPIndicators::on_ChangeViewStateAllRightTriangle_clicked()
{
    if(ui->ThirdIndicator->show)
    {
        ui->ChangeViewStateAllRightTriangle->setText("Отобразить все скрытые метки");
        ui->ThirdIndicator->SetSettings("system","show",false);
    }
    else
    {
        ui->ChangeViewStateAllRightTriangle->setText("Скрыть");
        ui->ThirdIndicator->SetSettings("system","show",true);
    }
}

void RSPIndicators::on_ButtonTargetsSettings_clicked()
{
    tsettings=new TargetsSettings;
    tsettings->show();
}

void RSPIndicators::on_SelectRangeMarksEquiangular_currentIndexChanged(int index)
{
    if(index<0)
        return;
    ui->SecondIndicator->SetSettings("system","range",static_cast<quint16>(index));
}

void RSPIndicators::on_SelectRangeMarksRightTriangle_currentIndexChanged(int index)
{
    if(index<0)
        return;
    ui->ThirdIndicator->SetSettings("system","range",static_cast<quint16>(index));
}

void RSPIndicators::on_SelectScaleEquiangular_currentIndexChanged(int index)
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
    ui->SecondIndicator->SetSettings("system","scale",static_cast<quint8>(max));
    ui->SecondIndicator->SetSettings("trash","end",max);
    ui->SecondIndicator->SetSettings("trash","begin",0);
}

void RSPIndicators::on_SelectScaleRightTriangle_currentIndexChanged(int index)
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
    ui->ThirdIndicator->SetSettings("system","scale",static_cast<quint8>(max));
    ui->ThirdIndicator->SetSettings("trash","end",max);
    ui->ThirdIndicator->SetSettings("trash","begin",0);
}

void RSPIndicators::on_SelectRangeMarks_currentIndexChanged(int index)
{
    if(index<0)
        return;
    ui->FirstIndicator->SetSettings("system","range",static_cast<quint16>(index));
}

void RSPIndicators::on_SelectScale_currentIndexChanged(int index)
{
    if(index<0)
        return;
    qreal max;
    switch(index)
    {
        case 2:
            max=150.0f;
            break;
        case 1:
            max=90.0f;
            break;
        default:
            max=45.0f;

    }
    ui->FirstIndicator->SetSettings("system","scale",static_cast<quint8>(max));
    ui->FirstIndicator->SetSettings("trash","end",max);
    ui->FirstIndicator->SetSettings("trash","begin",0);
}

void RSPIndicators::on_SelectWorkVariant_currentIndexChanged(int index)
{
    if(index<0)
        return;
    switch(index)
    {
        case 0:
            if(ui->ChangeTrashIntensity->isEnabled())
                ui->ChangeTrashIntensity->setEnabled(false);
            if(ui->ChangeTrashIntensityEquiangular->isEnabled())
                ui->ChangeTrashIntensityEquiangular->setEnabled(false);
            if(ui->ChangeTrashIntensityRightTriangle->isEnabled())
                ui->ChangeTrashIntensityRightTriangle->setEnabled(false);
            if(ui->CheckActiveNoiseShow->isEnabled())
                ui->CheckActiveNoiseShow->setEnabled(false);
            if(ui->CheckActiveAnswerShow->isEnabled())
                ui->CheckActiveAnswerShow->setEnabled(false);
            if(ui->CheckActiveInSyncShow->isEnabled())
                ui->CheckActiveInSyncShow->setEnabled(false);
            break;
        case 1:
            if(!ui->ChangeTrashIntensity->isEnabled())
                ui->ChangeTrashIntensity->setEnabled(true);
            if(!ui->ChangeTrashIntensityEquiangular->isEnabled())
                ui->ChangeTrashIntensityEquiangular->setEnabled(true);
            if(!ui->ChangeTrashIntensityRightTriangle->isEnabled())
                ui->ChangeTrashIntensityRightTriangle->setEnabled(true);
            if(!ui->CheckActiveNoiseShow->isEnabled())
                ui->CheckActiveNoiseShow->setEnabled(true);
            if(!ui->CheckActiveAnswerShow->isEnabled())
                ui->CheckActiveAnswerShow->setEnabled(true);
            if(!ui->CheckActiveInSyncShow->isEnabled())
                ui->CheckActiveInSyncShow->setEnabled(true);
            break;
        case 2:
            if(ui->ChangeTrashIntensity->isEnabled())
                ui->ChangeTrashIntensity->setEnabled(false);
            if(ui->ChangeTrashIntensityEquiangular->isEnabled())
                ui->ChangeTrashIntensityEquiangular->setEnabled(false);
            if(ui->ChangeTrashIntensityRightTriangle->isEnabled())
                ui->ChangeTrashIntensityRightTriangle->setEnabled(false);
            if(ui->CheckActiveNoiseShow->isEnabled())
                ui->CheckActiveNoiseShow->setEnabled(false);
            if(!ui->CheckActiveAnswerShow->isEnabled())
                ui->CheckActiveAnswerShow->setEnabled(true);
            if(!ui->CheckActiveInSyncShow->isEnabled())
                ui->CheckActiveInSyncShow->setEnabled(true);

    }
    ui->FirstIndicator->SetSettings("system","mode",static_cast<quint8>(index));
    ui->SecondIndicator->SetSettings("system","mode",static_cast<quint8>(index));
    ui->ThirdIndicator->SetSettings("system","mode",static_cast<quint8>(index));
}

void RSPIndicators::on_SelectAzimuthMarks_currentIndexChanged(int index)
{
    if(index<0)
        return;
    ui->FirstIndicator->SetSettings("system","azimuth",static_cast<quint16>(index));
}

void RSPIndicators::on_ChangeIndicatorVARU_valueChanged(int value)
{
    if(value<0)
        return;
    ui->FirstIndicator->SetSettings("system","varu",static_cast<qreal>(value)/100);
    ui->SecondIndicator->SetSettings("system","varu",static_cast<qreal>(value)/100);
    ui->ThirdIndicator->SetSettings("system","varu",static_cast<qreal>(value)/100);
}

void RSPIndicators::on_ChangeIndicatorFocusEquiangular_valueChanged(int value)
{
    if(value<0)
        return;
    ui->SecondIndicator->SetSettings("system","focus",static_cast<qreal>(value)/100);

}

void RSPIndicators::on_ChangeIndicatorFocusRightTriangle_valueChanged(int value)
{
    if(value<0)
        return;
    ui->ThirdIndicator->SetSettings("system","focus",static_cast<qreal>(value)/100);

}

void RSPIndicators::on_ChangeIndicatorFocus_valueChanged(int value)
{
    if(value<0)
        return;
    ui->FirstIndicator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void RSPIndicators::on_ChangeIndicatorBrightnessEquiangular_valueChanged(int value)
{
    if(value<0)
        return;
    ui->SecondIndicator->SetSettings("system","brightness",static_cast<qreal>(value)/100);

}

void RSPIndicators::on_ChangeIndicatorBrightnessRightTriangle_valueChanged(int value)
{
    if(value<0)
        return;
    ui->ThirdIndicator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
}

void RSPIndicators::on_ChangeIndicatorBrightness_valueChanged(int value)
{
    if(value<0)
        return;
    ui->FirstIndicator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
}

void RSPIndicators::on_ChangeDisplayLightning_valueChanged(int value)
{
    if(value<0)
        return;
    ui->FirstIndicator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->SecondIndicator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->ThirdIndicator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
}

void RSPIndicators::on_ChangeTrashIntensityEquiangular_valueChanged(int value)
{
    if(value<0)
        return;
    ui->SecondIndicator->SetSettings("trash","show",value>0);
    ui->SecondIndicator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void RSPIndicators::on_ChangeTrashIntensityRightTriangle_valueChanged(int value)
{
    if(value<0)
        return;
    ui->ThirdIndicator->SetSettings("trash","show",value>0);
    ui->ThirdIndicator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void RSPIndicators::on_ChangeTrashIntensity_valueChanged(int value)
{
    if(value<0)
        return;
    ui->FirstIndicator->SetSettings("trash","show",value>0);
    ui->FirstIndicator->SetSettings("trash","intensity",static_cast<quint8>(value));
}
