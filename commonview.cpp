#include"commonview.h"
#include"ui_commonview.h"

CommonView::CommonView(QWidget *parent) : QMainWindow(parent),ui(new Ui::CommonView)
{
    ui->setupUi(this);
    //###Инициализация
    //Развёртка (амплитуда)
    ui->ChangeMainScanAmp->valueChanged(ui->ChangeMainScanAmp->value());
    ui->ChangeMainScanAmp->hide();
    ui->ChangeMainScanAmp->setDisabled(true);

    //Развёртка (выравнивание)
    ui->ChangeMainScanEqua->valueChanged(ui->ChangeMainScanEqua->value());
    ui->ChangeMainScanEqua->hide();
    ui->ChangeMainScanEqua->setDisabled(true);

    //Амплитуда развёртки (вертикальное)
    ui->ChangeEquingularScanAmpVertical->valueChanged(ui->ChangeEquingularScanAmpVertical->value());
    ui->ChangeEquingularScanAmpVertical->hide();
    ui->ChangeEquingularScanAmpVertical->setDisabled(true);

    ui->ChangeRightScanAmpVertical->valueChanged(ui->ChangeRightScanAmpVertical->value());
    ui->ChangeRightScanAmpVertical->hide();
    ui->ChangeRightScanAmpVertical->setDisabled(true);

    //Амплитуда развёртки (горизонтальное)
    ui->ChangeEquingularScanAmpHorizontal->valueChanged(ui->ChangeEquingularScanAmpHorizontal->value());
    ui->ChangeEquingularScanAmpHorizontal->hide();
    ui->ChangeEquingularScanAmpHorizontal->setDisabled(true);

    ui->ChangeRightScanAmpHorizontal->valueChanged(ui->ChangeRightScanAmpHorizontal->value());
    ui->ChangeRightScanAmpHorizontal->hide();
    ui->ChangeRightScanAmpHorizontal->setDisabled(true);

    //Смещение (вертикальное)
    ui->ChangeMainOffsetVertical->valueChanged(ui->ChangeMainOffsetVertical->value());
    ui->ChangeMainOffsetVertical->hide();
    ui->ChangeMainOffsetVertical->setDisabled(true);

    ui->ChangeEquingularOffsetVertical->valueChanged(ui->ChangeEquingularOffsetVertical->value());
    ui->ChangeEquingularOffsetVertical->hide();
    ui->ChangeEquingularOffsetVertical->setDisabled(true);

    ui->ChangeRightOffsetVertical->valueChanged(ui->ChangeRightOffsetVertical->value());
    ui->ChangeRightOffsetVertical->hide();
    ui->ChangeRightOffsetVertical->setDisabled(true);


    //Смещение (горизонтальное)
    ui->ChangeMainOffsetHorizontal->valueChanged(ui->ChangeMainOffsetHorizontal->value());
    ui->ChangeMainOffsetHorizontal->hide();
    ui->ChangeMainOffsetHorizontal->setDisabled(true);

    ui->ChangeEquingularOffsetHorizontal->valueChanged(ui->ChangeEquingularOffsetHorizontal->value());
    ui->ChangeEquingularOffsetHorizontal->hide();
    ui->ChangeEquingularOffsetHorizontal->setDisabled(true);

    ui->ChangeRightOffsetHorizontal->valueChanged(ui->ChangeRightOffsetHorizontal->value());
    ui->ChangeRightOffsetHorizontal->hide();
    ui->ChangeRightOffsetHorizontal->setDisabled(true);

    //Яркость меток (дальность)
    ui->ChangeMainBrightnessRange->valueChanged(ui->ChangeMainBrightnessRange->value());
    ui->ChangeMainBrightnessRange->hide();
    ui->ChangeMainBrightnessRange->setDisabled(true);

    ui->ChangeRightBrightnessRange->valueChanged(ui->ChangeRightBrightnessRange->value());
    ui->ChangeRightBrightnessRange->hide();
    ui->ChangeRightBrightnessRange->setDisabled(true);

    //Яркость меток (азимут)
    ui->ChangeMainBrightnessAzimuth->valueChanged(ui->ChangeMainBrightnessAzimuth->value());
    ui->ChangeMainBrightnessAzimuth->hide();
    ui->ChangeMainBrightnessAzimuth->setDisabled(true);

    ui->ChangeRightBrightnessAzimuth->valueChanged(ui->ChangeRightBrightnessAzimuth->value());
    ui->ChangeRightBrightnessAzimuth->hide();
    ui->ChangeRightBrightnessAzimuth->setDisabled(true);

    //Установка нуля (вертикальная составляющая)
    ui->ChangeMainNullSetVertical->valueChanged(ui->ChangeMainNullSetVertical->value());
    ui->ChangeMainNullSetVertical->hide();
    ui->ChangeMainNullSetVertical->setDisabled(true);

    //Установка нуля (горизонтальная составляющая)
    ui->ChangeMainNullSetHorizontal->valueChanged(ui->ChangeMainNullSetHorizontal->value());
    ui->ChangeMainNullSetHorizontal->hide();
    ui->ChangeMainNullSetHorizontal->setDisabled(true);

    //Уровень курса
    ui->ChangeEquingularDirectionTrack->valueChanged(ui->ChangeEquingularDirectionTrack->value());
    ui->ChangeEquingularDirectionTrack->hide();
    ui->ChangeEquingularDirectionTrack->setDisabled(true);

    ui->ChangeRightDirectionTrack->valueChanged(ui->ChangeRightDirectionTrack->value());
    ui->ChangeRightDirectionTrack->hide();
    ui->ChangeRightDirectionTrack->setDisabled(true);


    //Уровень глиссады
    ui->ChangeEquingularDirectionGlide->valueChanged(ui->ChangeEquingularDirectionGlide->value());
    ui->ChangeEquingularDirectionGlide->hide();
    ui->ChangeEquingularDirectionGlide->setDisabled(true);

    ui->ChangeRightDirectionGlide->valueChanged(ui->ChangeRightDirectionGlide->value());
    ui->ChangeRightDirectionGlide->hide();
    ui->ChangeRightDirectionGlide->setDisabled(true);

    //Фокус
    ui->ChangeMainFocus->valueChanged(ui->ChangeMainFocus->value());
    ui->ChangeMainFocus->hide();
    ui->ChangeMainFocus->setDisabled(true);

    ui->ChangeEquingularFocus->valueChanged(ui->ChangeEquingularFocus->value());
    ui->ChangeEquingularFocus->hide();
    ui->ChangeEquingularFocus->setDisabled(true);

    ui->ChangeRightFocus->valueChanged(ui->ChangeRightFocus->value());
    ui->ChangeRightFocus->hide();
    ui->ChangeRightFocus->setDisabled(true);

    //Яркость
    ui->ChangeMainFocusBrightness->valueChanged(ui->ChangeMainFocusBrightness->value());
    ui->ChangeMainFocusBrightness->hide();
    ui->ChangeMainFocusBrightness->setDisabled(true);

    ui->ChangeEquingularBrightness->valueChanged(ui->ChangeEquingularBrightness->value());
    ui->ChangeEquingularBrightness->hide();
    ui->ChangeEquingularBrightness->setDisabled(true);

    ui->ChangeRightFocusBrightness->valueChanged(ui->ChangeRightFocusBrightness->value());
    ui->ChangeRightFocusBrightness->hide();
    ui->ChangeRightFocusBrightness->setDisabled(true);

    //Усиление приёмника (активный режим)
    ui->ChangeMainTrashAKT->valueChanged(ui->ChangeMainTrashAKT->value());
    ui->ChangeMainTrashAKT->hide();
    ui->ChangeMainTrashAKT->setDisabled(true);

    ui->ChangeEquingularTrashAKT->valueChanged(ui->ChangeEquingularTrashAKT->value());
    ui->ChangeEquingularTrashAKT->hide();
    ui->ChangeEquingularTrashAKT->setDisabled(true);

    //Усиление приёмника (пассивный режим)
    ui->ChangeMainTrashPASS->valueChanged(ui->ChangeMainTrashPASS->value());
    ui->ChangeMainTrashPASS->hide();
    ui->ChangeMainTrashPASS->setDisabled(true);

    ui->ChangeEquingularTrashPASS->valueChanged(ui->ChangeEquingularTrashPASS->value());
    ui->ChangeEquingularTrashPASS->hide();
    ui->ChangeEquingularTrashPASS->setDisabled(true);

    //Усиление приёмника (селекция движущихся целей)
    ui->ChangeEquingularTrashSDC->valueChanged(ui->ChangeEquingularTrashSDC->value());
    ui->ChangeEquingularTrashSDC->hide();
    ui->ChangeEquingularTrashSDC->setDisabled(true);

    //Масштаб
    ui->SelectMainScale->clicked();

    ui->SelectEquingularScale->clicked();
    ui->SelectEquingularScale->clicked();
    ui->SelectEquingularScale->clicked();

    //Режим индикатора
    ui->SelectEquingularMode->clicked();

    //Статика
    ui->RenderMainLocator->SetSettings("system","azimuth",2u);
    ui->RenderMainLocator->SetSettings("system","range",1u);

    ui->RenderEquingularTriangleLocator->SetSettings("system","azimuth",2u);
    ui->RenderEquingularTriangleLocator->SetSettings("system","range",1u);

    ui->RenderRightTriangleLocator->SetSettings("system","azimuth",2u);
    ui->RenderRightTriangleLocator->SetSettings("system","range",1u);
    //###\Инициализация

    ui->RenderMainLocator->ChangeFPS(static_cast<qreal>(1000)/24);
    ui->RenderEquingularTriangleLocator->ChangeFPS(static_cast<qreal>(1000)/24);
    ui->RenderRightTriangleLocator->ChangeFPS(static_cast<qreal>(1000)/24);
}

CommonView::~CommonView()
{
    delete ui;
}

void CommonView::on_ChangeMainScanAmpButton_pressed()
{
    ui->ChangeMainScanAmp->show();
    ui->ChangeMainScanAmp->setEnabled(true);
    ui->ChangeMainScanAmpButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainScanAmp_sliderPressed()
{
    ui->ChangeMainScanAmp->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainScanAmp_sliderReleased()
{
    ui->ChangeMainScanAmp->hide();
    ui->ChangeMainScanAmp->setDisabled(true);
    ui->ChangeMainScanAmp->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainScanAmpButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeMainScanAmp_valueChanged(int value)
{
    if(value<0)
        return;
    //ui->RenderMainLocator->SetSettings("system","amplitude",static_cast<qreal>(value)/100);
    ui->RenderMainLocator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->ChangeMainScanAmpButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeMainScanAmp->maximum())));
}

void CommonView::on_ChangeMainScanEquaButton_pressed()
{
    ui->ChangeMainScanEqua->show();
    ui->ChangeMainScanEqua->setEnabled(true);
    ui->ChangeMainScanEquaButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainScanEqua_sliderPressed()
{
    ui->ChangeMainScanEqua->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainScanEqua_sliderReleased()
{
    ui->ChangeMainScanEqua->hide();
    ui->ChangeMainScanEqua->setDisabled(true);
    ui->ChangeMainScanEqua->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainScanEquaButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeMainScanEqua_valueChanged(int value)
{
    if(value<0)
        return;
    //ui->RenderMainLocator->SetSettings("system","equalization",static_cast<qreal>(value)/100);
    ui->RenderMainLocator->SetSettings("system","varu",static_cast<qreal>(value)/100);
    ui->ChangeMainScanEquaButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeMainScanEqua->maximum())));
}

void CommonView::on_ChangeMainOffsetVerticalButton_pressed()
{
    ui->ChangeMainOffsetVertical->show();
    ui->ChangeMainOffsetVertical->setEnabled(true);
    ui->ChangeMainOffsetVerticalButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainOffsetVertical_sliderPressed()
{
    ui->ChangeMainOffsetVertical->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainOffsetVertical_sliderReleased()
{
    ui->ChangeMainOffsetVertical->hide();
    ui->ChangeMainOffsetVertical->setDisabled(true);
    ui->ChangeMainOffsetVertical->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainOffsetVerticalButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeMainOffsetVertical_valueChanged(int value)
{
    ui->RenderMainLocator->SetSettings("offset","vertical",static_cast<qreal>(value)/100);
    ui->ChangeMainOffsetVerticalButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeMainOffsetVertical->maximum())));
}

void CommonView::on_ChangeMainOffsetHorizontalButton_pressed()
{
    ui->ChangeMainOffsetHorizontal->show();
    ui->ChangeMainOffsetHorizontal->setEnabled(true);
    ui->ChangeMainOffsetHorizontalButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainOffsetHorizontal_sliderPressed()
{
    ui->ChangeMainOffsetHorizontal->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainOffsetHorizontal_sliderReleased()
{
    ui->ChangeMainOffsetHorizontal->hide();
    ui->ChangeMainOffsetHorizontal->setDisabled(true);
    ui->ChangeMainOffsetHorizontal->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainOffsetHorizontalButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeMainOffsetHorizontal_valueChanged(int value)
{
    ui->RenderMainLocator->SetSettings("offset","horizontal",static_cast<qreal>(value)/100);
    ui->ChangeMainOffsetHorizontalButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeMainOffsetHorizontal->maximum())));
}

void CommonView::on_ChangeMainBrightnessRangeButton_pressed()
{
    ui->ChangeMainBrightnessRange->show();
    ui->ChangeMainBrightnessRange->setEnabled(true);
    ui->ChangeMainBrightnessRangeButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainBrightnessRange_sliderPressed()
{
    ui->ChangeMainBrightnessRange->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainBrightnessRange_sliderReleased()
{
    ui->ChangeMainBrightnessRange->hide();
    ui->ChangeMainBrightnessRange->setDisabled(true);
    ui->ChangeMainBrightnessRange->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainBrightnessRangeButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeMainBrightnessRange_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("brightness","range",static_cast<qreal>(value)/100);
    ui->ChangeMainBrightnessRangeButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeMainBrightnessRange->maximum())));
}

void CommonView::on_ChangeMainBrightnessAzimuthButton_pressed()
{
    ui->ChangeMainBrightnessAzimuth->show();
    ui->ChangeMainBrightnessAzimuth->setEnabled(true);
    ui->ChangeMainBrightnessAzimuthButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainBrightnessAzimuth_sliderPressed()
{
    ui->ChangeMainBrightnessAzimuth->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainBrightnessAzimuth_sliderReleased()
{
    ui->ChangeMainBrightnessAzimuth->hide();
    ui->ChangeMainBrightnessAzimuth->setDisabled(true);
    ui->ChangeMainBrightnessAzimuth->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainBrightnessAzimuthButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeMainBrightnessAzimuth_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("brightness","azimuth",static_cast<qreal>(value)/100);
    ui->ChangeMainBrightnessAzimuthButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeMainBrightnessAzimuth->maximum())));
}

void CommonView::on_ChangeMainNullSetVerticalButton_pressed()
{
    ui->ChangeMainNullSetVertical->show();
    ui->ChangeMainNullSetVertical->setEnabled(true);
    ui->ChangeMainNullSetVerticalButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainNullSetVertical_sliderPressed()
{
    ui->ChangeMainNullSetVertical->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainNullSetVertical_sliderReleased()
{
    ui->ChangeMainNullSetVertical->hide();
    ui->ChangeMainNullSetVertical->setDisabled(true);
    ui->ChangeMainNullSetVertical->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainNullSetVerticalButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeMainNullSetVertical_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("null","vertical",static_cast<qreal>(value)/100);
    ui->ChangeMainNullSetVerticalButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeMainNullSetVertical->maximum())));
}

void CommonView::on_ChangeMainNullSetHorizontalButton_pressed()
{
    ui->ChangeMainNullSetHorizontal->show();
    ui->ChangeMainNullSetHorizontal->setEnabled(true);
    ui->ChangeMainNullSetHorizontalButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainNullSetHorizontal_sliderPressed()
{
    ui->ChangeMainNullSetHorizontal->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainNullSetHorizontal_sliderReleased()
{
    ui->ChangeMainNullSetHorizontal->hide();
    ui->ChangeMainNullSetHorizontal->setDisabled(true);
    ui->ChangeMainNullSetHorizontal->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainNullSetHorizontalButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeMainNullSetHorizontal_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("null","horizontal",static_cast<qreal>(value)/100);
    ui->ChangeMainNullSetHorizontalButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeMainNullSetHorizontal->maximum())));
}

void CommonView::on_ChangeMainFocusButton_pressed()
{
    ui->ChangeMainFocus->show();
    ui->ChangeMainFocus->setEnabled(true);
    ui->ChangeMainFocusButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainFocus_sliderPressed()
{
    ui->ChangeMainFocus->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainFocus_sliderReleased()
{
    ui->ChangeMainFocus->hide();
    ui->ChangeMainFocus->setDisabled(true);
    ui->ChangeMainFocus->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainFocusButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeMainFocus_valueChanged(int value)
{
    ui->ChangeMainFocusButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeMainFocus->maximum())));
    value=value>=0 ? value+100 : 100-value;
    ui->RenderMainLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void CommonView::on_ChangeMainFocusBrightnessButton_pressed()
{
    ui->ChangeMainFocusBrightness->show();
    ui->ChangeMainFocusBrightness->setEnabled(true);
    ui->ChangeMainFocusBrightnessButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainFocusBrightness_sliderPressed()
{
    ui->ChangeMainFocusBrightness->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainFocusBrightness_sliderReleased()
{
    ui->ChangeMainFocusBrightness->hide();
    ui->ChangeMainFocusBrightness->setDisabled(true);
    ui->ChangeMainFocusBrightness->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainFocusBrightnessButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeMainFocusBrightness_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->ChangeMainFocusBrightnessButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeMainFocusBrightness->maximum())));
}

void CommonView::on_ChangeMainTrashAKTButton_pressed()
{
    ui->ChangeMainTrashAKT->show();
    ui->ChangeMainTrashAKT->setEnabled(true);
    ui->ChangeMainTrashAKTButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainTrashAKT_sliderPressed()
{
    ui->ChangeMainTrashAKT->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainTrashAKT_sliderReleased()
{
    ui->ChangeMainTrashAKT->hide();
    ui->ChangeMainTrashAKT->setDisabled(true);
    ui->ChangeMainTrashAKT->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainTrashAKTButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeMainTrashAKT_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderMainLocator->SetSettings("trash","show",value>0);
    ui->ChangeMainTrashAKTButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeMainTrashAKT->maximum())));
}

void CommonView::on_ChangeMainTrashPASSButton_pressed()
{
    ui->ChangeMainTrashPASS->show();
    ui->ChangeMainTrashPASS->setEnabled(true);
    ui->ChangeMainTrashPASSButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainTrashPASS_sliderPressed()
{
    ui->ChangeMainTrashPASS->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeMainTrashPASS_sliderReleased()
{
    ui->ChangeMainTrashPASS->hide();
    ui->ChangeMainTrashPASS->setDisabled(true);
    ui->ChangeMainTrashPASS->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainTrashPASSButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeMainTrashPASS_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderMainLocator->SetSettings("trash","show",value>0);
    ui->ChangeMainTrashPASSButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeMainTrashPASS->maximum())));
}

void CommonView::on_SelectMainScale_clicked()
{
    static quint8 status=0u;
    if(status>1u)
        status=0u;
    else
        status++;

    qreal max;
    qint16 degree=0u;

    switch(status)
    {
        case 0u:
            degree=-60;
            max=45.0f;
            break;
        case 1u:
            degree=0u;
            max=90.0f;
            break;
        case 2u:
            degree=60u;
            max=150.0f;
            break;
    }
    ui->SelectMainScale->setIcon(QIcon(degree==0u ? QPixmap(":/buttons/knob") : MainLocator::RotateResourceImage(":/buttons/knob",degree)));
    ui->RenderMainLocator->SetSettings("system","scale",static_cast<quint8>(max));

    //Усиление приёмника
    ui->RenderMainLocator->SetSettings("trash","begin",.0f);
    ui->RenderMainLocator->SetSettings("trash","end",static_cast<qreal>(max));

    /*
    if(ui->InputScatterTrashFrom->value()>max)
        ui->InputScatterTrashFrom->setValue(max);
    if(ui->InputScatterTrashTo->value()>max)
        ui->InputScatterTrashTo->setValue(max);
    ui->InputScatterTrashFrom->setMaximum(max);
    ui->InputScatterTrashTo->setMaximum(max);
    */
}

void CommonView::on_ChangeEquingularFocusButton_pressed()
{
    ui->ChangeEquingularFocus->show();
    ui->ChangeEquingularFocus->setEnabled(true);
    ui->ChangeEquingularFocusButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularFocus_sliderPressed()
{
    ui->ChangeEquingularFocus->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularFocus_sliderReleased()
{
    ui->ChangeEquingularFocus->hide();
    ui->ChangeEquingularFocus->setDisabled(true);
    ui->ChangeEquingularFocus->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularFocusButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeEquingularFocus_valueChanged(int value)
{
    ui->ChangeEquingularFocusButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquingularFocus->maximum())));
    value=value>=0 ? value+100 : 100-value;
    ui->RenderEquingularTriangleLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void CommonView::on_ChangeEquingularBrightnessButton_pressed()
{
    ui->ChangeEquingularBrightness->show();
    ui->ChangeEquingularBrightness->setEnabled(true);
    ui->ChangeEquingularBrightnessButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularBrightness_sliderPressed()
{
    ui->ChangeEquingularBrightness->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularBrightness_sliderReleased()
{
    ui->ChangeEquingularBrightness->hide();
    ui->ChangeEquingularBrightness->setDisabled(true);
    ui->ChangeEquingularBrightness->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularBrightnessButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeEquingularBrightness_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->ChangeEquingularBrightnessButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquingularBrightness->maximum())));
}

void CommonView::on_ChangeEquingularTrashSDCButton_pressed()
{
    ui->ChangeEquingularTrashSDC->show();
    ui->ChangeEquingularTrashSDC->setEnabled(true);
    ui->ChangeEquingularTrashSDCButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularTrashSDC_sliderPressed()
{
    ui->ChangeEquingularTrashSDC->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularTrashSDC_sliderReleased()
{
    ui->ChangeEquingularTrashSDC->hide();
    ui->ChangeEquingularTrashSDC->setDisabled(true);
    ui->ChangeEquingularTrashSDC->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularTrashSDCButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeEquingularTrashSDC_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderEquingularTriangleLocator->SetSettings("trash","show",value>0);

    ui->RenderRightTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderRightTriangleLocator->SetSettings("trash","show",value>0);

    ui->ChangeEquingularTrashSDCButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquingularTrashSDC->maximum())));
}

void CommonView::on_ChangeEquingularTrashPASSButton_pressed()
{
    ui->ChangeEquingularTrashPASS->show();
    ui->ChangeEquingularTrashPASS->setEnabled(true);
    ui->ChangeEquingularTrashPASSButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularTrashPASS_sliderPressed()
{
    ui->ChangeEquingularTrashPASS->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularTrashPASS_sliderReleased()
{
    ui->ChangeEquingularTrashPASS->hide();
    ui->ChangeEquingularTrashPASS->setDisabled(true);
    ui->ChangeEquingularTrashPASS->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularTrashPASSButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeEquingularTrashPASS_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderEquingularTriangleLocator->SetSettings("trash","show",value>0);

    ui->RenderRightTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderRightTriangleLocator->SetSettings("trash","show",value>0);

    ui->ChangeEquingularTrashPASSButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquingularTrashPASS->maximum())));
}

void CommonView::on_ChangeEquingularTrashAKTButton_pressed()
{
    ui->ChangeEquingularTrashAKT->show();
    ui->ChangeEquingularTrashAKT->setEnabled(true);
    ui->ChangeEquingularTrashAKTButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularTrashAKT_sliderPressed()
{
    ui->ChangeEquingularTrashAKT->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularTrashAKT_sliderReleased()
{
    ui->ChangeEquingularTrashAKT->hide();
    ui->ChangeEquingularTrashAKT->setDisabled(true);
    ui->ChangeEquingularTrashAKT->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularTrashAKTButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeEquingularTrashAKT_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderEquingularTriangleLocator->SetSettings("trash","show",value>0);

    ui->RenderRightTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderRightTriangleLocator->SetSettings("trash","show",value>0);

    ui->ChangeEquingularTrashAKTButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquingularTrashAKT->maximum())));
}

void CommonView::on_SelectEquingularScale_clicked()
{
    static quint8 status=0u;
    if(status>1u)
        status=0u;
    else
        status++;

    qreal max;
    qint16 degree=0u;

    switch(status)
    {
        case 0u:
            degree=0u;
            max=60.0f;
            break;
        case 1u:
            degree=45u;
            max=20.0f;
            break;
        case 2u:
            degree=180u;
            max=30.0f;
            break;
    }

    ui->SelectEquingularScale->setIcon(QIcon(degree==45u ? QPixmap(":/buttons/switch_base") : MainLocator::RotateResourceImage(":/buttons/switch_up",degree)));
    ui->RenderEquingularTriangleLocator->SetSettings("system","scale",static_cast<quint8>(max));
    ui->RenderRightTriangleLocator->SetSettings("system","scale",static_cast<quint8>(max));

    //Усиление приёмника
    ui->RenderEquingularTriangleLocator->SetSettings("trash","begin",.0f);
    ui->RenderEquingularTriangleLocator->SetSettings("trash","end",static_cast<qreal>(max));

    ui->RenderRightTriangleLocator->SetSettings("trash","begin",.0f);
    ui->RenderRightTriangleLocator->SetSettings("trash","end",static_cast<qreal>(max));
    /*
    if(ui->InputScatterTrashFrom->value()>max)
        ui->InputScatterTrashFrom->setValue(max);
    if(ui->InputScatterTrashTo->value()>max)
        ui->InputScatterTrashTo->setValue(max);
    ui->InputScatterTrashFrom->setMaximum(max);
    ui->InputScatterTrashTo->setMaximum(max);
    */
}

void CommonView::on_SelectEquingularMode_clicked()
{
    static quint8 status=0u;
    if(status>1u)
        status=0u;
    else
        status++;

    qreal max;
    qint16 degree=0u;

    switch(status)
    {
        case 0u:
            degree=-60;
            max=0u;
            break;
        case 1u:
            degree=0u;
            max=1u;
            break;
        case 2u:
            degree=60u;
            max=2u;
            break;
    }
    ui->SelectEquingularMode->setIcon(QIcon(degree==0u ? QPixmap(":/buttons/knob") : MainLocator::RotateResourceImage(":/buttons/knob",degree)));
    ui->RenderEquingularTriangleLocator->SetSettings("system","mode",static_cast<quint8>(max));
}

void CommonView::on_ChangeEquingularScanAmpVerticalButton_pressed()
{
    ui->ChangeEquingularScanAmpVertical->show();
    ui->ChangeEquingularScanAmpVertical->setEnabled(true);
    ui->ChangeEquingularScanAmpVerticalButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularScanAmpVertical_sliderPressed()
{
    ui->ChangeEquingularScanAmpVertical->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularScanAmpVertical_sliderReleased()
{
    ui->ChangeEquingularScanAmpVertical->hide();
    ui->ChangeEquingularScanAmpVertical->setDisabled(true);
    ui->ChangeEquingularScanAmpVertical->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularScanAmpVerticalButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeEquingularScanAmpVertical_valueChanged(int value)
{
    if(value<0)
        return;
    //ui->RenderEquingularTriangleLocator->SetSettings("scan","vertical",static_cast<qreal>(value)/100);
    ui->RenderEquingularTriangleLocator->SetSettings("system","varu",static_cast<qreal>(value)/100);
    ui->ChangeEquingularScanAmpVerticalButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeEquingularScanAmpVertical->maximum())));
}

void CommonView::on_ChangeEquingularScanAmpHorizontalButton_pressed()
{
    ui->ChangeEquingularScanAmpHorizontal->show();
    ui->ChangeEquingularScanAmpHorizontal->setEnabled(true);
    ui->ChangeEquingularScanAmpHorizontalButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularScanAmpHorizontal_sliderPressed()
{
    ui->ChangeEquingularScanAmpHorizontal->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularScanAmpHorizontal_sliderReleased()
{
    ui->ChangeEquingularScanAmpHorizontal->hide();
    ui->ChangeEquingularScanAmpHorizontal->setDisabled(true);
    ui->ChangeEquingularScanAmpHorizontal->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularScanAmpHorizontalButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeEquingularScanAmpHorizontal_valueChanged(int value)
{
    if(value<0)
        return;
    //ui->RenderEquingularTriangleLocator->SetSettings("scan","horizontal",static_cast<qreal>(value)/100);
    ui->RenderEquingularTriangleLocator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->ChangeEquingularScanAmpHorizontalButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeEquingularScanAmpHorizontal->maximum())));
}

void CommonView::on_ChangeEquingularOffsetVerticalButton_pressed()
{
    ui->ChangeEquingularOffsetVertical->show();
    ui->ChangeEquingularOffsetVertical->setEnabled(true);
    ui->ChangeEquingularOffsetVerticalButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularOffsetVertical_sliderPressed()
{
    ui->ChangeEquingularOffsetVertical->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularOffsetVertical_sliderReleased()
{
    ui->ChangeEquingularOffsetVertical->hide();
    ui->ChangeEquingularOffsetVertical->setDisabled(true);
    ui->ChangeEquingularOffsetVertical->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularOffsetVerticalButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeEquingularOffsetVertical_valueChanged(int value)
{
    ui->RenderEquingularTriangleLocator->SetSettings("offset","vertical",static_cast<qreal>(value)/100);
    ui->ChangeEquingularOffsetVerticalButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeEquingularOffsetVertical->maximum())));
}

void CommonView::on_ChangeEquingularOffsetHorizontalButton_pressed()
{
    ui->ChangeEquingularOffsetHorizontal->show();
    ui->ChangeEquingularOffsetHorizontal->setEnabled(true);
    ui->ChangeEquingularOffsetHorizontalButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularOffsetHorizontal_sliderPressed()
{
    ui->ChangeEquingularOffsetHorizontal->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularOffsetHorizontal_sliderReleased()
{
    ui->ChangeEquingularOffsetHorizontal->hide();
    ui->ChangeEquingularOffsetHorizontal->setDisabled(true);
    ui->ChangeEquingularOffsetHorizontal->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularOffsetHorizontalButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeEquingularOffsetHorizontal_valueChanged(int value)
{
    ui->RenderEquingularTriangleLocator->SetSettings("offset","horizontal",static_cast<qreal>(value)/100);
    ui->ChangeEquingularOffsetHorizontalButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeEquingularOffsetHorizontal->maximum())));
}

void CommonView::on_ChangeEquingularDirectionTrackButton_pressed()
{
    ui->ChangeEquingularDirectionTrack->show();
    ui->ChangeEquingularDirectionTrack->setEnabled(true);
    ui->ChangeEquingularDirectionTrackButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularDirectionTrack_sliderPressed()
{
    ui->ChangeEquingularDirectionTrack->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularDirectionTrack_sliderReleased()
{
    ui->ChangeEquingularDirectionTrack->hide();
    ui->ChangeEquingularDirectionTrack->setDisabled(true);
    ui->ChangeEquingularDirectionTrack->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularDirectionTrackButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeEquingularDirectionTrack_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("direction","track",static_cast<qreal>(value)/100);
    ui->ChangeEquingularDirectionTrackButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeEquingularDirectionTrack->maximum())));
}

void CommonView::on_ChangeEquingularDirectionGlideButton_pressed()
{
    ui->ChangeEquingularDirectionGlide->show();
    ui->ChangeEquingularDirectionGlide->setEnabled(true);
    ui->ChangeEquingularDirectionGlideButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularDirectionGlide_sliderPressed()
{
    ui->ChangeEquingularDirectionGlide->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeEquingularDirectionGlide_sliderReleased()
{
    ui->ChangeEquingularDirectionGlide->hide();
    ui->ChangeEquingularDirectionGlide->setDisabled(true);
    ui->ChangeEquingularDirectionGlide->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularDirectionGlideButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeEquingularDirectionGlide_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("direction","glide",static_cast<qreal>(value)/100);
    ui->ChangeEquingularDirectionGlideButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeEquingularDirectionGlide->maximum())));
}

void CommonView::on_ChangeRightFocusButton_pressed()
{
    ui->ChangeRightFocus->show();
    ui->ChangeRightFocus->setEnabled(true);
    ui->ChangeRightFocusButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightFocus_sliderPressed()
{
    ui->ChangeRightFocus->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightFocus_sliderReleased()
{
    ui->ChangeRightFocus->hide();
    ui->ChangeRightFocus->setDisabled(true);
    ui->ChangeRightFocus->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightFocusButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeRightFocus_valueChanged(int value)
{
    ui->ChangeRightFocusButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightFocus->maximum())));
    value=value>=0 ? value+100 : 100-value;
    ui->RenderRightTriangleLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void CommonView::on_ChangeRightFocusBrightnessButton_pressed()
{
    ui->ChangeRightFocusBrightness->show();
    ui->ChangeRightFocusBrightness->setEnabled(true);
    ui->ChangeRightFocusBrightnessButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightFocusBrightness_sliderPressed()
{
    ui->ChangeRightFocusBrightness->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightFocusBrightness_sliderReleased()
{
    ui->ChangeRightFocusBrightness->hide();
    ui->ChangeRightFocusBrightness->setDisabled(true);
    ui->ChangeRightFocusBrightness->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightFocusBrightnessButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeRightFocusBrightness_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->ChangeRightFocusBrightnessButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightFocusBrightness->maximum())));
}

void CommonView::on_ChangeRightScanAmpVerticalButton_pressed()
{
    ui->ChangeRightScanAmpVertical->show();
    ui->ChangeRightScanAmpVertical->setEnabled(true);
    ui->ChangeRightScanAmpVerticalButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightScanAmpVertical_sliderPressed()
{
    ui->ChangeRightScanAmpVertical->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightScanAmpVertical_sliderReleased()
{
    ui->ChangeRightScanAmpVertical->hide();
    ui->ChangeRightScanAmpVertical->setDisabled(true);
    ui->ChangeRightScanAmpVertical->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightScanAmpVerticalButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeRightScanAmpVertical_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    //ui->RenderRightTriangleLocator->SetSettings("scan","vertical",static_cast<qreal>(value)/100);
    ui->ChangeRightScanAmpVerticalButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeRightScanAmpVertical->maximum())));
}

void CommonView::on_ChangeRightScanAmpHorizontalButton_pressed()
{
    ui->ChangeRightScanAmpHorizontal->show();
    ui->ChangeRightScanAmpHorizontal->setEnabled(true);
    ui->ChangeRightScanAmpHorizontalButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightScanAmpHorizontal_sliderPressed()
{
    ui->ChangeRightScanAmpHorizontal->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightScanAmpHorizontal_sliderReleased()
{
    ui->ChangeRightScanAmpHorizontal->hide();
    ui->ChangeRightScanAmpHorizontal->setDisabled(true);
    ui->ChangeRightScanAmpHorizontal->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightScanAmpHorizontalButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeRightScanAmpHorizontal_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("system","varu",static_cast<qreal>(value)/100);
    //ui->RenderRightTriangleLocator->SetSettings("scan","horizontal",static_cast<qreal>(value)/100);
    ui->ChangeRightScanAmpHorizontalButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeRightScanAmpHorizontal->maximum())));
}

void CommonView::on_ChangeRightOffsetVerticalButton_pressed()
{
    ui->ChangeRightOffsetVertical->show();
    ui->ChangeRightOffsetVertical->setEnabled(true);
    ui->ChangeRightOffsetVerticalButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightOffsetVertical_sliderPressed()
{
    ui->ChangeRightOffsetVertical->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightOffsetVertical_sliderReleased()
{
    ui->ChangeRightOffsetVertical->hide();
    ui->ChangeRightOffsetVertical->setDisabled(true);
    ui->ChangeRightOffsetVertical->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightOffsetVerticalButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeRightOffsetVertical_valueChanged(int value)
{
    ui->RenderRightTriangleLocator->SetSettings("offset","vertical",static_cast<qreal>(value)/100);
    ui->ChangeRightOffsetVerticalButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeRightOffsetVertical->maximum())));
}

void CommonView::on_ChangeRightOffsetHorizontalButton_pressed()
{
    ui->ChangeRightOffsetHorizontal->show();
    ui->ChangeRightOffsetHorizontal->setEnabled(true);
    ui->ChangeRightOffsetHorizontalButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightOffsetHorizontal_sliderPressed()
{
    ui->ChangeRightOffsetHorizontal->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightOffsetHorizontal_sliderReleased()
{
    ui->ChangeRightOffsetHorizontal->hide();
    ui->ChangeRightOffsetHorizontal->setDisabled(true);
    ui->ChangeRightOffsetHorizontal->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightOffsetHorizontalButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeRightOffsetHorizontal_valueChanged(int value)
{
    ui->RenderRightTriangleLocator->SetSettings("offset","horizontal",static_cast<qreal>(value)/100);
    ui->ChangeRightOffsetHorizontalButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeRightOffsetHorizontal->maximum())));
}

void CommonView::on_ChangeRightDirectionTrackButton_pressed()
{
    ui->ChangeRightDirectionTrack->show();
    ui->ChangeRightDirectionTrack->setEnabled(true);
    ui->ChangeRightDirectionTrackButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightDirectionTrack_sliderPressed()
{
    ui->ChangeRightDirectionTrack->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightDirectionTrack_sliderReleased()
{
    ui->ChangeRightDirectionTrack->hide();
    ui->ChangeRightDirectionTrack->setDisabled(true);
    ui->ChangeRightDirectionTrack->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightDirectionTrackButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeRightDirectionTrack_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("direction","track",static_cast<qreal>(value)/100);
    ui->ChangeRightDirectionTrackButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeRightDirectionTrack->maximum())));
}

void CommonView::on_ChangeRightDirectionGlideButton_pressed()
{
    ui->ChangeRightDirectionGlide->show();
    ui->ChangeRightDirectionGlide->setEnabled(true);
    ui->ChangeRightDirectionGlideButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightDirectionGlide_sliderPressed()
{
    ui->ChangeRightDirectionGlide->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightDirectionGlide_sliderReleased()
{
    ui->ChangeRightDirectionGlide->hide();
    ui->ChangeRightDirectionGlide->setDisabled(true);
    ui->ChangeRightDirectionGlide->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightDirectionGlideButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeRightDirectionGlide_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("direction","glide",static_cast<qreal>(value)/100);
    ui->ChangeRightDirectionGlideButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/p_rotator.png") : MainLocator::RotateResourceImage(":/buttons/p_rotator.png",value*360/ui->ChangeRightDirectionGlide->maximum())));
}

void CommonView::on_ChangeRightBrightnessRangeButton_pressed()
{
    ui->ChangeRightBrightnessRange->show();
    ui->ChangeRightBrightnessRange->setEnabled(true);
    ui->ChangeRightBrightnessRangeButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightBrightnessRange_sliderPressed()
{
    ui->ChangeRightBrightnessRange->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightBrightnessRange_sliderReleased()
{
    ui->ChangeRightBrightnessRange->hide();
    ui->ChangeRightBrightnessRange->setDisabled(true);
    ui->ChangeRightBrightnessRange->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightBrightnessRangeButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeRightBrightnessRange_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("brightness","range",static_cast<qreal>(value)/100);
    ui->ChangeRightBrightnessRangeButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightBrightnessRange->maximum())));
}

void CommonView::on_ChangeRightBrightnessAzimuthButton_pressed()
{
    ui->ChangeRightBrightnessAzimuth->show();
    ui->ChangeRightBrightnessAzimuth->setEnabled(true);
    ui->ChangeRightBrightnessAzimuthButton->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightBrightnessAzimuth_sliderPressed()
{
    ui->ChangeRightBrightnessAzimuth->setCursor(Qt::ClosedHandCursor);
}

void CommonView::on_ChangeRightBrightnessAzimuth_sliderReleased()
{
    ui->ChangeRightBrightnessAzimuth->hide();
    ui->ChangeRightBrightnessAzimuth->setDisabled(true);
    ui->ChangeRightBrightnessAzimuth->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightBrightnessAzimuthButton->setCursor(Qt::OpenHandCursor);
}

void CommonView::on_ChangeRightBrightnessAzimuth_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("brightness","azimuth",static_cast<qreal>(value)/100);
    ui->ChangeRightBrightnessAzimuthButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightBrightnessAzimuth->maximum())));
}
