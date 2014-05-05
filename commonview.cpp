#include "commonview.h"
#include "ui_commonview.h"

#ifndef FPS
#define FPS 1000/24
#endif

commonview::commonview(QWidget *parent) : QWidget(parent),ui(new Ui::commonview)
{
    ui->setupUi(this);
    ui->ChangeMainLocatorFocusSlider->hide();
    ui->ChangeMainLocatorBrightnessSlider->hide();
    ui->ChangeMainLocatorMagnificationAKTSlider->hide();
    ui->ChangeMainLocatorMagnificationPASSSlider->hide();
    ui->ChangeMainLocatorScale->clicked();
    ui->ChangeEquingularLocatorMagnificationSDCSlider->hide();
    ui->ChangeEquingularLocatorMagnificationPASSSlider->hide();
    ui->ChangeEquingularLocatorMagnificationAKTSlider->hide();

    ui->ChangeRightTriangleAmplHorizontalSlider->hide();
    ui->ChangeRightTriangleAmplVerticalSlider->hide();
    ui->ChangeRightTriangleOffsetlHorizontalSlider->hide();
    ui->ChangeRightTriangleOffsetlVerticalSlider->hide();

    ui->ChangeEquingularTriangleAmplHorizontalSlider->hide();
    ui->ChangeEquingularTriangleAmplVerticalSlider->hide();
    ui->ChangeEquingularTriangleOffsetHorizontalSlider->hide();
    ui->ChangeEquingularTriangleOffsetVerticalSlider->hide();

    ui->ChangeEquingularLocatorScale->clicked();
    ui->ChangeEquingularLocatorMode->clicked();

    QStringList intensity;
    intensity<<"Слабая"<<"Средняя"<<"Сильная";
    ui->SelectActiveNoiseIntensity->addItems(intensity);
    ui->SelectActiveNoiseIntensity->setCurrentIndex(1);

    ui->ChangeRightTriangleBrightnessMarksAzimuthSlider->hide();
    ui->ChangeRightTriangleBrightnessMarksRangeSlider->hide();

    ui->ChangeRightTriangleFocusSlider->hide();
    ui->ChangeRightTriangleBrightnessSlider->hide();

    ui->ChangeMainLocatorFocusSlider->valueChanged(ui->ChangeMainLocatorFocusSlider->value());
    ui->ChangeMainLocatorBrightnessSlider->valueChanged(ui->ChangeMainLocatorBrightnessSlider->value());
    ui->ChangeMainLocatorBrightnessSlider->sliderReleased();
    ui->ChangeRightTriangleBrightnessSlider->sliderReleased();

    ui->ChangeRightTriangleBrightnessSlider->valueChanged(ui->ChangeRightTriangleBrightnessSlider->value());
    ui->ChangeRightTriangleFocusSlider->valueChanged(ui->ChangeRightTriangleFocusSlider->value());

    ui->ChangeRightTriangleBrightnessMarksAzimuthSlider->valueChanged(ui->ChangeRightTriangleBrightnessMarksAzimuthSlider->value());
    ui->ChangeRightTriangleBrightnessMarksRangeSlider->valueChanged(ui->ChangeRightTriangleBrightnessMarksRangeSlider->value());

    ui->RenderMainLocator->ChangeFPS(FPS);
    ui->RenderEquingularTriangleLocator->ChangeFPS(FPS);
    ui->RenderRightTrinagleLocator->ChangeFPS(FPS);
}

commonview::~commonview()
{
    delete ui;
}

void commonview::on_ChangeMainLocatorFocus_pressed()
{
    ui->ChangeMainLocatorFocus->setCursor(Qt::ClosedHandCursor);
    ui->ChangeMainLocatorFocusSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainLocatorFocusSlider->show();
}

void commonview::on_ChangeMainLocatorFocusSlider_valueChanged(int value)
{
    value=value>=0 ? value+100 : 100-value;
    ui->RenderMainLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void commonview::on_ChangeMainLocatorFocusSlider_sliderReleased()
{
    ui->ChangeMainLocatorFocusSlider->hide();
    ui->ChangeMainLocatorFocus->setCursor(Qt::OpenHandCursor);
    if(!ui->RenderMainLocator->IsActive())
        ui->RenderMainLocator->ChangeFPS(FPS);
}

void commonview::on_ChangeMainLocatorFocusSlider_sliderPressed()
{
    ui->ChangeMainLocatorFocusSlider->setCursor(Qt::ClosedHandCursor);
    if(ui->RenderMainLocator->IsActive())
        ui->RenderMainLocator->ChangeFPS(0);
}

void commonview::on_ChangeMainLocatorBrightness_pressed()
{
   ui->ChangeMainLocatorBrightness->setCursor(Qt::ClosedHandCursor);
   ui->ChangeMainLocatorBrightnessSlider->setCursor(Qt::OpenHandCursor);
   ui->ChangeMainLocatorBrightnessSlider->show();
}

void commonview::on_ChangeMainLocatorBrightnessSlider_valueChanged(int value)
{
    if(value<0)
        return;
    /*
    //ТОРМОЗА
    ui->RenderMainLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    //[З]ui->RenderMainLocator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->RenderMainLocator->SetSettings("system","lightning",1.0f);
    ui->RenderMainLocator->SetSettings("system","varu",.0f);
    */
}

void commonview::on_ChangeMainLocatorBrightnessSlider_sliderReleased()
{
    ui->ChangeMainLocatorBrightnessSlider->hide();
    ui->ChangeMainLocatorBrightness->setCursor(Qt::OpenHandCursor);
    if(!ui->RenderMainLocator->IsActive())
        ui->RenderMainLocator->ChangeFPS(FPS);

    ui->RenderMainLocator->SetSettings("system","brightness",static_cast<qreal>(ui->ChangeMainLocatorBrightnessSlider->value())/100);
    //[З]ui->RenderMainLocator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->RenderMainLocator->SetSettings("system","lightning",1.0f);
    ui->RenderMainLocator->SetSettings("system","varu",.0f);
}

void commonview::on_ChangeMainLocatorBrightnessSlider_sliderPressed()
{
    ui->ChangeMainLocatorBrightnessSlider->setCursor(Qt::ClosedHandCursor);
    if(ui->RenderMainLocator->IsActive())
        ui->RenderMainLocator->ChangeFPS(0);
}

void commonview::on_ChangeMainLocatorMagnificationAKT_pressed()
{
    ui->ChangeMainLocatorMagnificationAKT->setCursor(Qt::ClosedHandCursor);
    ui->ChangeMainLocatorMagnificationAKTSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainLocatorMagnificationAKTSlider->show();
}

void commonview::on_ChangeMainLocatorMagnificationAKTSlider_valueChanged(int value)
{
    //ui->RenderMainLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void commonview::on_ChangeMainLocatorMagnificationAKTSlider_sliderReleased()
{
    ui->ChangeMainLocatorMagnificationAKTSlider->hide();
    ui->ChangeMainLocatorMagnificationAKT->setCursor(Qt::OpenHandCursor);
    ui->RenderMainLocator->SetSettings("trash","intensity",static_cast<quint8>(ui->ChangeMainLocatorMagnificationAKTSlider->value()));
}

void commonview::on_ChangeMainLocatorMagnificationAKTSlider_sliderPressed()
{
    ui->ChangeMainLocatorMagnificationAKTSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeMainLocatorMagnificationPASS_pressed()
{
    ui->ChangeMainLocatorMagnificationPASS->setCursor(Qt::ClosedHandCursor);
    ui->ChangeMainLocatorMagnificationPASSSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainLocatorMagnificationPASSSlider->show();
}

void commonview::on_ChangeMainLocatorMagnificationPASSSlider_valueChanged(int value)
{
    //ТОРМОЗА
    //ui->RenderMainLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void commonview::on_ChangeMainLocatorMagnificationPASSSlider_sliderReleased()
{
    ui->ChangeMainLocatorMagnificationPASSSlider->hide();
    ui->ChangeMainLocatorMagnificationPASS->setCursor(Qt::OpenHandCursor);
    ui->RenderMainLocator->SetSettings("trash","intensity",static_cast<quint8>(ui->ChangeMainLocatorMagnificationPASSSlider->value()));
}

void commonview::on_ChangeMainLocatorMagnificationPASSSlider_sliderPressed()
{
    ui->ChangeMainLocatorMagnificationPASSSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeMainLocatorScale_clicked()
{
    static qint8 status=0;
    if(status<0 || status>1)
        status=0;
    else
        status++;

    qreal max;
    switch(status)
    {
        case 0:
            ui->ChangeMainLocatorScale->setStyleSheet("border-image: url(:/buttons/knob2);background-repeat: no-repeat;background-position: center;");
            max=45.0f;
            break;
        case 1:
            ui->ChangeMainLocatorScale->setStyleSheet("border-image: url(:/buttons/knob);background-repeat: no-repeat;background-position: center;");
            max=90.0f;
            break;
        case 2:
            ui->ChangeMainLocatorScale->setStyleSheet("border-image: url(:/buttons/knob1);background-repeat: no-repeat;background-position: center;");
            max=150.0f;
            break;
    }

    ui->RenderMainLocator->SetSettings("system","scale",static_cast<quint8>(max));
    /*
    if(ui->Iui->RenderIndicator->SetSettings("system","range",static_cast<quint16>(status));nputScatterTrashFrom->value()>max)
        ui->InputScatterTrashFrom->setValue(max);
    if(ui->InputScatterTrashTo->value()>max)
        ui->InputScatterTrashTo->setValue(max);
    ui->InputScatterTrashFrom->setMaximum(max);
    ui->InputScatterTrashTo->setMaximum(max);
    */
    ui->RenderMainLocator->SetSettings("trash","show",true);
    ui->RenderMainLocator->SetSettings("trash","begin",0);
    ui->RenderMainLocator->SetSettings("trash","end",static_cast<quint8>(max));

    ui->RenderMainLocator->SetSettings("system","azimuth",2u);
    ui->RenderMainLocator->SetSettings("system","range",1u);
}

void commonview::on_ChangeMainLocatorScale_pressed()
{
    ui->ChangeMainLocatorScale->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeMainLocatorScale_released()
{
    ui->ChangeMainLocatorScale->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeEquingularLocatorMagnificationSDC_pressed()
{
    ui->ChangeEquingularLocatorMagnificationSDC->setCursor(Qt::ClosedHandCursor);
    ui->ChangeEquingularLocatorMagnificationSDCSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularLocatorMagnificationSDCSlider->show();
}

void commonview::on_ChangeEquingularLocatorMagnificationSDCSlider_valueChanged(int value)
{
    ui->RenderEquingularTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderRightTrinagleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void commonview::on_ChangeEquingularLocatorMagnificationSDCSlider_sliderReleased()
{
    ui->ChangeEquingularLocatorMagnificationSDCSlider->hide();
    ui->ChangeEquingularLocatorMagnificationSDC->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeEquingularLocatorMagnificationSDCSlider_sliderPressed()
{
    ui->ChangeEquingularLocatorMagnificationSDCSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeEquingularLocatorScale_clicked()
{
    static qint8 status=0;
    if(status<0 || status>1)
        status=0;
    else
        status++;

    qreal max;
    switch(status)
    {
        case 0:
            ui->ChangeEquingularLocatorScale->setStyleSheet("border-image: url(:/buttons/switch_up);background-repeat: no-repeat;background-position: center;");
            max=60.0f;
            break;
        case 1:
            ui->ChangeEquingularLocatorScale->setStyleSheet("border-image: url(:/buttons/switch_base);background-repeat: no-repeat;background-position: center;");
            max=20.0f;
            break;
        case 2:
            ui->ChangeEquingularLocatorScale->setStyleSheet("border-image: url(:/buttons/switch_down);background-repeat: no-repeat;background-position: center;");
            max=30.0f;
            break;
    }
    ui->RenderEquingularTriangleLocator->SetSettings("system","scale",static_cast<quint8>(max));
    ui->RenderRightTrinagleLocator->SetSettings("system","scale",static_cast<quint8>(max));

    ui->RenderEquingularTriangleLocator->SetSettings("system","range",1u);
    ui->RenderEquingularTriangleLocator->SetSettings("system","azimuth",1u);

    ui->RenderRightTrinagleLocator->SetSettings("system","range",1u);
    ui->RenderRightTrinagleLocator->SetSettings("system","azimuth",1u);

    ui->RenderEquingularTriangleLocator->SetSettings("trash","show",true);
    //ui->RenderEquingularTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderEquingularTriangleLocator->SetSettings("trash","begin",0);
    ui->RenderEquingularTriangleLocator->SetSettings("trash","end",static_cast<quint8>(max));

    ui->RenderRightTrinagleLocator->SetSettings("trash","show",true);
    //ui->RenderRightTrinagleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderRightTrinagleLocator->SetSettings("trash","begin",0);
    ui->RenderRightTrinagleLocator->SetSettings("trash","end",static_cast<quint8>(max));

}

void commonview::on_ChangeEquingularLocatorScale_pressed()
{
    ui->ChangeEquingularLocatorScale->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeEquingularLocatorScale_released()
{
    ui->ChangeEquingularLocatorScale->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeEquingularLocatorMode_clicked()
{
    static qint8 status=0;
    if(status<0 || status>1)
        status=0;
    else
        status++;

    switch(status)
    {
        case 0:
            ui->ChangeEquingularLocatorMode->setStyleSheet("border-image: url(:/buttons/knob2);background-repeat: no-repeat;background-position: center;");
            break;
        case 1:
            ui->ChangeEquingularLocatorMode->setStyleSheet("border-image: url(:/buttons/knob);background-repeat: no-repeat;background-position: center;");
            break;
        case 2:
            ui->ChangeEquingularLocatorMode->setStyleSheet("border-image: url(:/buttons/knob1);background-repeat: no-repeat;background-position: center;");
            break;
    }
    ui->RenderMainLocator->SetSettings("system","mode",static_cast<quint8>(status));
}

void commonview::on_ChangeEquingularLocatorMode_pressed()
{
    ui->ChangeEquingularLocatorMode->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeEquingularLocatorMode_released()
{
    ui->ChangeEquingularLocatorMode->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeRightTriangleBrightnessMarksRange_pressed()
{
    ui->ChangeRightTriangleBrightnessMarksRange->setCursor(Qt::ClosedHandCursor);
    ui->ChangeRightTriangleBrightnessMarksRangeSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightTriangleBrightnessMarksRangeSlider->show();
}

void commonview::on_ChangeRightTriangleBrightnessMarksRangeSlider_valueChanged(int value)
{

}

void commonview::on_ChangeRightTriangleBrightnessMarksRangeSlider_sliderPressed()
{
    ui->ChangeRightTriangleBrightnessMarksRange->setCursor(Qt::ClosedHandCursor);
    if(ui->RenderRightTrinagleLocator->IsActive())
        ui->RenderRightTrinagleLocator->ChangeFPS(0);
    if(ui->RenderEquingularTriangleLocator->IsActive())
        ui->RenderEquingularTriangleLocator->ChangeFPS(0);
}

void commonview::on_ChangeRightTriangleBrightnessMarksRangeSlider_sliderReleased()
{
    ui->ChangeRightTriangleBrightnessMarksRangeSlider->hide();
    ui->ChangeRightTriangleBrightnessMarksRange->setCursor(Qt::OpenHandCursor);

    if(!ui->RenderRightTrinagleLocator->IsActive())
        ui->RenderRightTrinagleLocator->ChangeFPS(FPS);
    if(!ui->RenderEquingularTriangleLocator->IsActive())
        ui->RenderEquingularTriangleLocator->ChangeFPS(FPS);
}

void commonview::on_ChangeRightTriangleBrightnessMarksAzimuth_pressed()
{
    ui->ChangeRightTriangleBrightnessMarksAzimuth->setCursor(Qt::ClosedHandCursor);
    ui->ChangeRightTriangleBrightnessMarksAzimuthSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightTriangleBrightnessMarksAzimuthSlider->show();
}

void commonview::on_ChangeRightTriangleBrightnessMarksAzimuthSlider_valueChanged(int value)
{
    ui->RenderEquingularTriangleLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->RenderEquingularTriangleLocator->SetSettings("system","lightning",0.2f);
    ui->RenderEquingularTriangleLocator->SetSettings("system","varu",.0f);
}

void commonview::on_ChangeRightTriangleBrightnessMarksAzimuthSlider_sliderPressed()
{
    ui->ChangeRightTriangleBrightnessMarksAzimuth->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeRightTriangleBrightnessMarksAzimuthSlider_sliderReleased()
{
    ui->ChangeRightTriangleBrightnessMarksAzimuthSlider->hide();
    ui->ChangeRightTriangleBrightnessMarksAzimuth->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeRightTriangleFocus_pressed()
{
    ui->ChangeRightTriangleFocus->setCursor(Qt::ClosedHandCursor);
    ui->ChangeRightTriangleFocusSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightTriangleFocusSlider->show();
}

void commonview::on_ChangeRightTriangleFocusSlider_valueChanged(int value)
{
    //ТОРМОЗА
    value=value>=0 ? value+100 : 100-value;
    ui->RenderRightTrinagleLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
    ui->RenderEquingularTriangleLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void commonview::on_ChangeRightTriangleFocusSlider_sliderPressed()
{
    ui->ChangeRightTriangleFocusSlider->setCursor(Qt::ClosedHandCursor);
    if(ui->RenderRightTrinagleLocator->IsActive())
        ui->RenderRightTrinagleLocator->ChangeFPS(0);
    if(ui->RenderEquingularTriangleLocator->IsActive())
        ui->RenderEquingularTriangleLocator->ChangeFPS(0);
}

void commonview::on_ChangeRightTriangleFocusSlider_sliderReleased()
{
    ui->ChangeRightTriangleFocusSlider->hide();
    ui->ChangeRightTriangleFocus->setCursor(Qt::OpenHandCursor);
    int focus=ui->ChangeRightTriangleFocusSlider->value();
    focus=focus>=0 ? focus+100 : 100-focus;
    ui->RenderRightTrinagleLocator->SetSettings("system","focus",static_cast<qreal>(focus)/100);
    ui->RenderEquingularTriangleLocator->SetSettings("system","focus",static_cast<qreal>(focus)/100);
    if(!ui->RenderRightTrinagleLocator->IsActive())
        ui->RenderRightTrinagleLocator->ChangeFPS(FPS);
    if(!ui->RenderEquingularTriangleLocator->IsActive())
        ui->RenderEquingularTriangleLocator->ChangeFPS(FPS);
}

void commonview::on_ChangeRightTriangleBrightness_pressed()
{
    ui->ChangeRightTriangleBrightness->setCursor(Qt::ClosedHandCursor);
    ui->ChangeRightTriangleBrightnessSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightTriangleBrightnessSlider->show();
}

void commonview::on_ChangeRightTriangleBrightnessSlider_valueChanged(int value)
{
    /*
    //ТОРМОЗА
    ui->RenderRightTrinagleLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->RenderRightTrinagleLocator->SetSettings("system","lightning",0.2f);
    ui->RenderRightTrinagleLocator->SetSettings("system","varu",.0f);
    ui->RenderEquingularTriangleLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->RenderEquingularTriangleLocator->SetSettings("system","lightning",0.2f);
    ui->RenderEquingularTriangleLocator->SetSettings("system","varu",.0f);
    */
}

void commonview::on_ChangeRightTriangleBrightnessSlider_sliderPressed()
{
    ui->ChangeRightTriangleBrightnessSlider->setCursor(Qt::ClosedHandCursor);
    if(ui->RenderRightTrinagleLocator->IsActive())
        ui->RenderRightTrinagleLocator->ChangeFPS(0);
    if(ui->RenderEquingularTriangleLocator->IsActive())
        ui->RenderEquingularTriangleLocator->ChangeFPS(0);
}

void commonview::on_ChangeRightTriangleBrightnessSlider_sliderReleased()
{
    ui->ChangeRightTriangleBrightnessSlider->hide();
    ui->ChangeRightTriangleBrightness->setCursor(Qt::OpenHandCursor);

    ui->RenderRightTrinagleLocator->SetSettings("system","brightness",static_cast<qreal>(ui->ChangeRightTriangleBrightnessSlider->value())/100);
    ui->RenderRightTrinagleLocator->SetSettings("system","lightning",0.2f);
    ui->RenderRightTrinagleLocator->SetSettings("system","varu",.0f);
    ui->RenderEquingularTriangleLocator->SetSettings("system","brightness",static_cast<qreal>(ui->ChangeRightTriangleBrightnessSlider->value())/100);
    ui->RenderEquingularTriangleLocator->SetSettings("system","lightning",0.2f);
    ui->RenderEquingularTriangleLocator->SetSettings("system","varu",.0f);


    if(!ui->RenderRightTrinagleLocator->IsActive())
        ui->RenderRightTrinagleLocator->ChangeFPS(FPS);
    if(!ui->RenderEquingularTriangleLocator->IsActive())
        ui->RenderEquingularTriangleLocator->ChangeFPS(FPS);
}

void commonview::on_SetTargetsSettings_clicked()
{
    tsettings=new TargetsSettings;
    tsettings->show();
}

void commonview::on_ChangeEquingularLocatorMagnificationPASS_pressed()
{
    ui->ChangeEquingularLocatorMagnificationPASS->setCursor(Qt::ClosedHandCursor);
    ui->ChangeEquingularLocatorMagnificationPASSSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularLocatorMagnificationPASSSlider->show();
}

void commonview::on_ChangeEquingularLocatorMagnificationPASSSlider_valueChanged(int value)
{
    ui->RenderEquingularTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderRightTrinagleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void commonview::on_ChangeEquingularLocatorMagnificationPASSSlider_sliderPressed()
{
    ui->ChangeEquingularLocatorMagnificationPASSSlider->hide();
    ui->ChangeEquingularLocatorMagnificationPASS->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeEquingularLocatorMagnificationPASSSlider_sliderReleased()
{
    ui->ChangeEquingularLocatorMagnificationPASSSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeEquingularLocatorMagnificationAKT_pressed()
{
    ui->ChangeEquingularLocatorMagnificationAKT->setCursor(Qt::ClosedHandCursor);
    ui->ChangeEquingularLocatorMagnificationAKTSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularLocatorMagnificationAKTSlider->show();
}

void commonview::on_ChangeEquingularLocatorMagnificationAKTSlider_valueChanged(int value)
{
    ui->RenderEquingularTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderRightTrinagleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void commonview::on_ChangeEquingularLocatorMagnificationAKTSlider_sliderPressed()
{
    ui->ChangeEquingularLocatorMagnificationAKTSlider->hide();
    ui->ChangeEquingularLocatorMagnificationAKT->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeEquingularLocatorMagnificationAKTSlider_sliderReleased()
{
    ui->ChangeEquingularLocatorMagnificationAKTSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_CheckActiveNoiseShow_stateChanged(int arg1)
{
    ui->RenderMainLocator->SetSettings("active_noise_trash","show",static_cast<quint16>(arg1));
}

void commonview::on_InputActiveNoiseAzimuth_valueChanged(int arg1)
{
    ui->RenderMainLocator->SetSettings("active_noise_trash","azimuth",static_cast<quint16>(arg1));
}

void commonview::on_SelectActiveNoiseIntensity_currentIndexChanged(int index)
{
    ui->RenderMainLocator->SetSettings("active_noise_trash","intensity",static_cast<quint16>(index));
}

void commonview::on_ChangeRightTriangleAmplVertical_pressed()
{
    ui->ChangeRightTriangleAmplVertical->setCursor(Qt::ClosedHandCursor);
    ui->ChangeRightTriangleAmplVerticalSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightTriangleAmplVerticalSlider->show();
}

void commonview::on_ChangeRightTriangleAmplVerticalSlider_valueChanged(int value)
{

}

void commonview::on_ChangeRightTriangleAmplVerticalSlider_sliderPressed()
{
    ui->ChangeRightTriangleAmplVerticalSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeRightTriangleAmplVerticalSlider_sliderReleased()
{
    ui->ChangeRightTriangleAmplVerticalSlider->hide();
    ui->ChangeRightTriangleAmplVertical->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeRightTriangleAmplHorizontal_pressed()
{
    ui->ChangeRightTriangleAmplHorizontal->setCursor(Qt::ClosedHandCursor);
    ui->ChangeRightTriangleAmplHorizontalSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightTriangleAmplHorizontalSlider->show();
}

void commonview::on_ChangeRightTriangleAmplHorizontalSlider_valueChanged(int value)
{

}

void commonview::on_ChangeRightTriangleAmplHorizontalSlider_sliderPressed()
{
    ui->ChangeRightTriangleAmplHorizontalSlider->setCursor(Qt::ClosedHandCursor);
}


void commonview::on_ChangeRightTriangleAmplHorizontalSlider_sliderReleased()
{
    ui->ChangeRightTriangleAmplHorizontalSlider->hide();
    ui->ChangeRightTriangleAmplHorizontal->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeRightTriangleOffsetlVertical_pressed()
{
    ui->ChangeRightTriangleOffsetlVertical->setCursor(Qt::ClosedHandCursor);
    ui->ChangeRightTriangleOffsetlVerticalSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightTriangleOffsetlVerticalSlider->show();
}

void commonview::on_ChangeRightTriangleOffsetlVerticalSlider_valueChanged(int value)
{
    ui->RenderRightTrinagleLocator->SetSettings("disposition","vertical",static_cast<qint16>(value));
}

void commonview::on_ChangeRightTriangleOffsetlVerticalSlider_sliderPressed()
{
    ui->ChangeRightTriangleOffsetlVerticalSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeRightTriangleOffsetlVerticalSlider_sliderReleased()
{
    ui->ChangeRightTriangleOffsetlVerticalSlider->hide();
    ui->ChangeRightTriangleOffsetlVertical->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeRightTriangleOffsetlHorizontal_pressed()
{
    ui->ChangeRightTriangleOffsetlHorizontal->setCursor(Qt::ClosedHandCursor);
    ui->ChangeRightTriangleOffsetlHorizontalSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightTriangleOffsetlHorizontalSlider->show();
}

void commonview::on_ChangeRightTriangleOffsetlHorizontalSlider_valueChanged(int value)
{
    ui->RenderRightTrinagleLocator->SetSettings("disposition","horizontal",static_cast<qint16>(value));
}

void commonview::on_ChangeRightTriangleOffsetlHorizontalSlider_sliderPressed()
{
    ui->ChangeRightTriangleOffsetlHorizontalSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeRightTriangleOffsetlHorizontalSlider_sliderReleased()
{
    ui->ChangeRightTriangleOffsetlHorizontalSlider->hide();
    ui->ChangeRightTriangleOffsetlHorizontal->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeEquingularTriangleAmplVertical_pressed()
{
    ui->ChangeEquingularTriangleAmplVertical->setCursor(Qt::ClosedHandCursor);
    ui->ChangeEquingularTriangleAmplVerticalSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularTriangleAmplVerticalSlider->show();
}

void commonview::on_ChangeEquingularTriangleAmplVerticalSlider_valueChanged(int value)
{

}

void commonview::on_ChangeEquingularTriangleAmplVerticalSlider_sliderPressed()
{
    ui->ChangeEquingularTriangleAmplVerticalSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeEquingularTriangleAmplVerticalSlider_sliderReleased()
{
    ui->ChangeEquingularTriangleAmplVerticalSlider->hide();
    ui->ChangeEquingularTriangleAmplVertical->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeEquingularTriangleAmplHorizontal_pressed()
{
    ui->ChangeEquingularTriangleAmplHorizontal->setCursor(Qt::ClosedHandCursor);
    ui->ChangeEquingularTriangleAmplHorizontalSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularTriangleAmplHorizontalSlider->show();
}

void commonview::on_ChangeEquingularTriangleAmplHorizontalSlider_valueChanged(int value)
{

}

void commonview::on_ChangeEquingularTriangleAmplHorizontalSlider_sliderPressed()
{
    ui->ChangeEquingularTriangleAmplHorizontalSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeEquingularTriangleAmplHorizontalSlider_sliderReleased()
{
    ui->ChangeEquingularTriangleAmplHorizontalSlider->hide();
    ui->ChangeEquingularTriangleAmplHorizontal->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeEquingularTriangleOffsetVertical_pressed()
{
    ui->ChangeEquingularTriangleOffsetVertical->setCursor(Qt::ClosedHandCursor);
    ui->ChangeEquingularTriangleOffsetVerticalSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularTriangleOffsetVerticalSlider->show();
}

void commonview::on_ChangeEquingularTriangleOffsetVerticalSlider_valueChanged(int value)
{
    ui->RenderEquingularTriangleLocator->SetSettings("disposition","vertical",static_cast<qint16>(value));
}

void commonview::on_ChangeEquingularTriangleOffsetVerticalSlider_sliderPressed()
{
    ui->ChangeEquingularTriangleOffsetVerticalSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeEquingularTriangleOffsetVerticalSlider_sliderReleased()
{
    ui->ChangeEquingularTriangleOffsetVerticalSlider->hide();
    ui->ChangeEquingularTriangleOffsetVertical->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeEquingularTriangleOffsetHorizontal_pressed()
{
    ui->ChangeEquingularTriangleOffsetHorizontal->setCursor(Qt::ClosedHandCursor);
    ui->ChangeEquingularTriangleOffsetHorizontalSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularTriangleOffsetHorizontalSlider->show();
}

void commonview::on_ChangeEquingularTriangleOffsetHorizontalSlider_valueChanged(int value)
{
    ui->RenderEquingularTriangleLocator->SetSettings("disposition","horizontal",static_cast<qint16>(value));
}

void commonview::on_ChangeEquingularTriangleOffsetHorizontalSlider_sliderPressed()
{
    ui->ChangeEquingularTriangleOffsetHorizontalSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeEquingularTriangleOffsetHorizontalSlider_sliderReleased()
{
    ui->ChangeEquingularTriangleOffsetHorizontalSlider->hide();
    ui->ChangeEquingularTriangleOffsetHorizontal->setCursor(Qt::OpenHandCursor);
}
