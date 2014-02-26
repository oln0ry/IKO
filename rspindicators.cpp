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
    ui->SelectWorkVariant->setCurrentIndex(0);

    range_marks_triangles<<"Не отображать"<<"5 километров"<<"10 километров";
    ui->SelectRangeMarksEquiangular->addItems(range_marks);
    ui->SelectRangeMarksEquiangular->setCurrentIndex(1);
    ui->SelectRangeMarksRightTriangle->addItems(range_marks);
    ui->SelectRangeMarksRightTriangle->setCurrentIndex(1);
    scale_triangles<<"20 километров"<<"30 километров"<<"60 километров";
    ui->SelectScaleEquiangular->addItems(scale);
    ui->SelectScaleEquiangular->setCurrentIndex(1);
    ui->SelectScaleRightTriangle->addItems(scale);
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
    ui->FirstIndicator->ChangeFPS(24);
    ui->SecondIndicator->ChangeFPS(24);
    ui->ThirdIndicator->ChangeFPS(24);
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
        ui->FirstIndicator->ChangeFPS(fps);
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
        ui->SecondIndicator->ChangeFPS(fps);
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
        ui->ThirdIndicator->ChangeFPS(fps);
        ui->ChangeLocatorStateRightTriangle->setText("Стоп");
    }
}
