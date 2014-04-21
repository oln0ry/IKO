#include "commonview.h"
#include "ui_commonview.h"

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
    ui->ChangeEquingularLocatorScale->clicked();
    ui->ChangeEquingularLocatorMode->clicked();

    ui->ChangeRightTriangleBrightnessMarksAzimuthSlider->hide();
    ui->ChangeRightTriangleBrightnessMarksRangeSlider->hide();

    ui->ChangeRightTriangleFocusSlider->hide();
    ui->ChangeRightTriangleBrightnessSlider->hide();

    ui->ChangeMainLocatorFocusSlider->valueChanged(ui->ChangeMainLocatorFocusSlider->value());
    ui->ChangeMainLocatorBrightnessSlider->valueChanged(ui->ChangeMainLocatorBrightnessSlider->value());

    ui->ChangeRightTriangleBrightnessSlider->valueChanged(ui->ChangeRightTriangleBrightnessSlider->value());
    ui->ChangeRightTriangleFocusSlider->valueChanged(ui->ChangeRightTriangleFocusSlider->value());

    ui->ChangeRightTriangleBrightnessMarksAzimuthSlider->valueChanged(ui->ChangeRightTriangleBrightnessMarksAzimuthSlider->value());
    ui->ChangeRightTriangleBrightnessMarksRangeSlider->valueChanged(ui->ChangeRightTriangleBrightnessMarksRangeSlider->value());

    ui->RenderMainLocator->ChangeFPS(1000/24);
    ui->RenderEquingularTriangleLocator->ChangeFPS(1000/24);
    ui->RenderRightTrinagleLocator->ChangeFPS(1000/24);
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
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void commonview::on_ChangeMainLocatorFocusSlider_sliderReleased()
{
    ui->ChangeMainLocatorFocusSlider->hide();
    ui->ChangeMainLocatorFocus->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeMainLocatorFocusSlider_sliderPressed()
{
    ui->ChangeMainLocatorFocusSlider->setCursor(Qt::ClosedHandCursor);
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
    ui->RenderMainLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    //[З]ui->RenderMainLocator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->RenderMainLocator->SetSettings("system","lightning",1.0f);
    ui->RenderMainLocator->SetSettings("system","varu",.0f);
}

void commonview::on_ChangeMainLocatorBrightnessSlider_sliderReleased()
{
    ui->ChangeMainLocatorBrightnessSlider->hide();
    ui->ChangeMainLocatorBrightness->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeMainLocatorBrightnessSlider_sliderPressed()
{
    ui->ChangeMainLocatorBrightnessSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeMainLocatorMagnificationAKT_pressed()
{
    ui->ChangeMainLocatorMagnificationAKT->setCursor(Qt::ClosedHandCursor);
    ui->ChangeMainLocatorMagnificationAKTSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainLocatorMagnificationAKTSlider->show();
}

void commonview::on_ChangeMainLocatorMagnificationAKTSlider_valueChanged(int value)
{
    ui->RenderMainLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void commonview::on_ChangeMainLocatorMagnificationAKTSlider_sliderReleased()
{
    ui->ChangeMainLocatorMagnificationAKTSlider->hide();
    ui->ChangeMainLocatorMagnificationAKT->setCursor(Qt::OpenHandCursor);
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
    ui->RenderMainLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void commonview::on_ChangeMainLocatorMagnificationPASSSlider_sliderReleased()
{
    ui->ChangeMainLocatorMagnificationPASSSlider->hide();
    ui->ChangeMainLocatorMagnificationPASS->setCursor(Qt::OpenHandCursor);
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
}

void commonview::on_ChangeRightTriangleBrightnessMarksRangeSlider_sliderReleased()
{
    ui->ChangeRightTriangleBrightnessMarksRangeSlider->hide();
    ui->ChangeRightTriangleBrightnessMarksRange->setCursor(Qt::OpenHandCursor);
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
    ui->RenderRightTrinagleLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
    ui->RenderEquingularTriangleLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void commonview::on_ChangeRightTriangleFocusSlider_sliderPressed()
{
    ui->ChangeRightTriangleFocusSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeRightTriangleFocusSlider_sliderReleased()
{
    ui->ChangeRightTriangleFocusSlider->hide();
    ui->ChangeRightTriangleFocus->setCursor(Qt::OpenHandCursor);
}

void commonview::on_ChangeRightTriangleBrightness_pressed()
{
    ui->ChangeRightTriangleBrightness->setCursor(Qt::ClosedHandCursor);
    ui->ChangeRightTriangleBrightnessSlider->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightTriangleBrightnessSlider->show();
}

void commonview::on_ChangeRightTriangleBrightnessSlider_valueChanged(int value)
{
    ui->RenderRightTrinagleLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->RenderRightTrinagleLocator->SetSettings("system","lightning",0.2f);
    ui->RenderRightTrinagleLocator->SetSettings("system","varu",.0f);
    ui->RenderEquingularTriangleLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->RenderEquingularTriangleLocator->SetSettings("system","lightning",0.2f);
    ui->RenderEquingularTriangleLocator->SetSettings("system","varu",.0f);
}

void commonview::on_ChangeRightTriangleBrightnessSlider_sliderPressed()
{
    ui->ChangeRightTriangleBrightnessSlider->setCursor(Qt::ClosedHandCursor);
}

void commonview::on_ChangeRightTriangleBrightnessSlider_sliderReleased()
{
    ui->ChangeRightTriangleBrightnessSlider->hide();
    ui->ChangeRightTriangleBrightness->setCursor(Qt::OpenHandCursor);
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
