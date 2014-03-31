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

    ui->ChangeMainLocatorFocusSlider->valueChanged(ui->ChangeMainLocatorFocusSlider->value());
    ui->ChangeMainLocatorBrightnessSlider->valueChanged(ui->ChangeMainLocatorBrightnessSlider->value());
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
    if(ui->InputScatterTrashFrom->value()>max)
        ui->InputScatterTrashFrom->setValue(max);
    if(ui->InputScatterTrashTo->value()>max)
        ui->InputScatterTrashTo->setValue(max);
    ui->InputScatterTrashFrom->setMaximum(max);
    ui->InputScatterTrashTo->setMaximum(max);
    */
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
            max=45.0f;
            break;
        case 1:
            ui->ChangeEquingularLocatorScale->setStyleSheet("border-image: url(:/buttons/switch_base);background-repeat: no-repeat;background-position: center;");
            max=90.0f;
            break;
        case 2:
            ui->ChangeEquingularLocatorScale->setStyleSheet("border-image: url(:/buttons/switch_down);background-repeat: no-repeat;background-position: center;");
            max=150.0f;
            break;
    }
    ui->RenderEquingularTriangleLocator->SetSettings("system","scale",static_cast<quint8>(max));
    ui->RenderRightTrinagleLocator->SetSettings("system","scale",static_cast<quint8>(max));
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
