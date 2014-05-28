#include"rspindicators.h"
#include"ui_rspindicators.h"

RSPIndicators::RSPIndicators(QWidget *parent) : QMainWindow(parent),ui(new Ui::RSPIndicators)
{
    ui->setupUi(this);
    //###Инициализация
    //Интенсивность усиления приёмника

    //ui->ChangeMainTrashIntensity->valueChanged(ui->ChangeMainTrashIntensity->value());
    ui->ChangeMainTrashIntensity->sliderReleased();
    ui->ChangeMainTrashIntensity->hide();
    ui->ChangeMainTrashIntensity->setDisabled(true);

    //ui->ChangeEquiangularTrashIntensity->valueChanged(ui->ChangeEquiangularTrashIntensity->value());
    ui->ChangeEquiangularTrashIntensity->sliderReleased();
    ui->ChangeEquiangularTrashIntensity->hide();
    ui->ChangeEquiangularTrashIntensity->setDisabled(true);

    //ui->ChangeRightTrashIntensity->valueChanged(ui->ChangeRightTrashIntensity->value());
    ui->ChangeRightTrashIntensity->sliderReleased();
    ui->ChangeRightTrashIntensity->hide();
    ui->ChangeRightTrashIntensity->setDisabled(true);

    //Отметки азимута
    ui->SelectMainAzimuthMarks->clicked();

    //Отметки дальности
    ui->SelectMainRangeMarks->clicked();

    ui->SelectEquiangularRangeMarks->clicked();

    ui->SelectRightRangeMarks->clicked();

    //Масштаб
    ui->SelectMainScale->clicked();
    ui->SelectMainScale->clicked();
    ui->SelectMainScale->clicked();

    ui->SelectEquiangularScale->clicked();
    ui->SelectEquiangularScale->clicked();
    ui->SelectEquiangularScale->clicked();

    ui->SelectRightScale->clicked();
    ui->SelectRightScale->clicked();
    ui->SelectRightScale->clicked();

    //Яркость индикаторов
    ui->ChangeMainBrightness->valueChanged(ui->ChangeMainBrightness->value());
    ui->ChangeMainBrightness->hide();
    ui->ChangeMainBrightness->setDisabled(true);

    ui->ChangeEquiangularBrightness->valueChanged(ui->ChangeEquiangularBrightness->value());
    ui->ChangeEquiangularBrightness->hide();
    ui->ChangeEquiangularBrightness->setDisabled(true);

    ui->ChangeRightBrightness->valueChanged(ui->ChangeRightBrightness->value());
    ui->ChangeRightBrightness->hide();
    ui->ChangeRightBrightness->setDisabled(true);

    //Подсветка луча индикаторов (остаточное изображение)
    ui->ChangeMainLightning->valueChanged(ui->ChangeMainLightning->value());
    ui->ChangeMainLightning->hide();
    ui->ChangeMainLightning->setDisabled(true);

    ui->ChangeEquiangularLightning->valueChanged(ui->ChangeEquiangularLightning->value());
    ui->ChangeEquiangularLightning->hide();
    ui->ChangeEquiangularLightning->setDisabled(true);

    ui->ChangeRightLightning->valueChanged(ui->ChangeRightLightning->value());
    ui->ChangeRightLightning->hide();
    ui->ChangeRightLightning->setDisabled(true);

    //Фокус изображения, отображаемого на индикаторах
    ui->ChangeMainFocus->valueChanged(ui->ChangeMainFocus->value());
    ui->ChangeMainFocus->hide();
    ui->ChangeMainFocus->setDisabled(true);

    ui->ChangeEquiangularFocus->valueChanged(ui->ChangeEquiangularFocus->value());
    ui->ChangeEquiangularFocus->hide();
    ui->ChangeEquiangularFocus->setDisabled(true);

    ui->ChangeRightFocus->valueChanged(ui->ChangeRightFocus->value());
    ui->ChangeRightFocus->hide();
    ui->ChangeRightFocus->setDisabled(true);

    //Автоматическая регулировка усиления индикатора
    ui->ChangeMainVARU->valueChanged(ui->ChangeMainVARU->value());
    ui->ChangeMainVARU->hide();
    ui->ChangeMainVARU->setDisabled(true);

    ui->ChangeEquiangularVARU->valueChanged(ui->ChangeMainVARU->value());
    ui->ChangeEquiangularVARU->hide();
    ui->ChangeEquiangularVARU->setDisabled(true);

    ui->ChangeRightVARU->valueChanged(ui->ChangeMainVARU->value());
    ui->ChangeRightVARU->hide();
    ui->ChangeRightVARU->setDisabled(true);

    //Статика
    ui->RenderMainLocator->SetSettings("offset","horizontal",.0f);
    ui->RenderMainLocator->SetSettings("offset","vertical",.0f);

    ui->RenderEquingularTriangleLocator->SetSettings("offset","horizontal",.0f);
    ui->RenderEquingularTriangleLocator->SetSettings("offset","vertical",.0f);

    ui->RenderRightTriangleLocator->SetSettings("offset","horizontal",.0f);
    ui->RenderRightTriangleLocator->SetSettings("offset","vertical",.0f);
    //###\Инициализация

    ui->ChangeMainLocatorState->clicked(); //Запуск индикатора
    ui->ChangeEquingularState->clicked();
    ui->ChangeRightState->clicked();
}

RSPIndicators::~RSPIndicators()
{
    delete ui;
}

/**
 * Этот метод является чистой воды диким шаманством
 */
bool RSPIndicators::eventFilter(QObject *O, QEvent *E)
{
    if((O->objectName()=="MainLocator" || O->inherits("MainLocator")) && E->type()==QEvent::MouseButtonDblClick)
    {
        if(isFullScreen())
        {
            ui->gridLayout_52->addWidget(ui->RenderMainLocator,0,0,1,1);
            ui->gridLayout_52->addWidget(ui->RenderEquingularTriangleLocator,0,1,1,1);
            ui->gridLayout_52->addWidget(ui->RenderRightTriangleLocator,0,2,1,1);
            ui->centralwidget->raise();
            showNormal();
        }
        else
        {
            if(O->objectName()=="RenderEquingularTriangleLocator" && O->inherits("EquiangularTriangleLocator"))
            {
                ui->gridLayout_52->addWidget(ui->RenderEquingularTriangleLocator,0,0,0,0);
                ui->RenderEquingularTriangleLocator->raise();
            }
            else if(O->objectName()=="RenderRightTriangleLocator" && O->inherits("RightTriangleLocator"))
            {
                ui->gridLayout_52->addWidget(ui->RenderRightTriangleLocator,0,0,0,0);
                ui->RenderRightTriangleLocator->raise();
            }
            else
            {
                ui->gridLayout_52->addWidget(ui->RenderMainLocator,0,0,0,0);
                ui->RenderMainLocator->raise();
            }
            showFullScreen();
        }
        activateWindow();
    }
    return QMainWindow::eventFilter(O,E);
}

void RSPIndicators::on_ChangeMainTrashIntensityButton_pressed()
{
    ui->ChangeMainTrashIntensity->show();
    ui->ChangeMainTrashIntensity->setEnabled(true);
    ui->ChangeMainTrashIntensityButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeMainTrashIntensity_sliderPressed()
{
    ui->ChangeMainTrashIntensity->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeMainTrashIntensity_sliderReleased()
{
    ui->ChangeMainTrashIntensity->hide();
    ui->ChangeMainTrashIntensity->setDisabled(true);
    ui->ChangeMainTrashIntensity->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainTrashIntensityButton->setCursor(Qt::OpenHandCursor);

    ui->RenderMainLocator->SetSettings("trash","intensity",static_cast<quint8>(ui->ChangeMainTrashIntensity->value()));
    ui->RenderMainLocator->SetSettings("trash","show",ui->ChangeMainTrashIntensity->value()>0);
}

void RSPIndicators::on_ChangeMainTrashIntensity_valueChanged(int value)
{
    if(value<0)
        return;
    //ui->RenderMainLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    //ui->RenderMainLocator->SetSettings("trash","show",value>0);
    ui->ChangeMainTrashIntensityButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeMainTrashIntensity->maximum())));
}

void RSPIndicators::on_SelectMainAzimuthMarks_clicked()
{
    static quint8 status=0u;

    if(status>1u)
        status=0u;
    else
        status++;

    qint16 degree=0;

    switch(status)
    {
        case 0u:
            //ui->LabelSelectAzimuthMarksValue->setText("НЕТ");
            degree=-60;
            break;
        case 1u:
            //ui->LabelSelectAzimuthMarksValue->setText("10°");
            degree=0u;
            break;
        case 2u:
            //ui->LabelSelectAzimuthMarksValue->setText("30°");
            degree=60u;
            break;
    }
    ui->SelectMainAzimuthMarks->setIcon(QIcon(degree==0u ? QPixmap(":/buttons/knob") : MainLocator::RotateResourceImage(":/buttons/knob",degree)));
    ui->RenderMainLocator->SetSettings("system","azimuth",static_cast<quint16>(status));

}

void RSPIndicators::on_SelectMainRangeMarks_clicked()
{
    static quint8 status=0u;
    if(status>1u)
        status=0u;
    else
        status++;

    qint16 degree=0u;

    switch(status)
    {
        case 0u:
            //ui->LabelSelectRangeMarksValue->setText("НЕТ");
            degree=-60;
            break;
        case 1u:
            //ui->LabelSelectRangeMarksValue->setText("10 км.");
            degree=0u;
            break;
        case 2u:
            //ui->LabelSelectRangeMarksValue->setText("50 км.");
            degree=60u;
            break;
    }
    ui->SelectMainRangeMarks->setIcon(QIcon(degree==0u ? QPixmap(":/buttons/knob") : MainLocator::RotateResourceImage(":/buttons/knob",degree)));
    ui->RenderMainLocator->SetSettings("system","range",static_cast<quint16>(status));
}

void RSPIndicators::on_SelectMainScale_clicked()
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
            //ui->LabelScaleValue->setText("45 км.");
            degree=0u;
            max=45.0f;
            break;
        case 1u:
            //ui->LabelScaleValue->setText("90 км.");
            degree=45u;
            max=90.0f;
            break;
        case 2u:
            //ui->LabelScaleValue->setText("150 км.");
            degree=180u;
            max=150.0f;
            break;
    }

    ui->SelectMainScale->setIcon(QIcon(degree==45u ? QPixmap(":/buttons/switch_base") : MainLocator::RotateResourceImage(":/buttons/switch_up",degree)));
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

void RSPIndicators::on_ChangeMainBrightnessButton_pressed()
{
    ui->ChangeMainBrightness->show();
    ui->ChangeMainBrightness->setEnabled(true);
    ui->ChangeMainBrightnessButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeMainBrightness_sliderPressed()
{
    ui->ChangeMainBrightness->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeMainBrightness_sliderReleased()
{
    ui->ChangeMainBrightness->hide();
    ui->ChangeMainBrightness->setDisabled(true);
    ui->ChangeMainBrightness->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainBrightnessButton->setCursor(Qt::OpenHandCursor);
}

void RSPIndicators::on_ChangeMainBrightness_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->ChangeMainBrightnessButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeMainBrightness->maximum())));
}

void RSPIndicators::on_ChangeMainLightningButton_pressed()
{
    ui->ChangeMainLightning->show();
    ui->ChangeMainLightning->setEnabled(true);
    ui->ChangeMainLightningButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeMainLightning_sliderPressed()
{
    ui->ChangeMainLightning->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeMainLightning_sliderReleased()
{
    ui->ChangeMainLightning->hide();
    ui->ChangeMainLightning->setDisabled(true);
    ui->ChangeMainLightning->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainLightningButton->setCursor(Qt::OpenHandCursor);
}

void RSPIndicators::on_ChangeMainLightning_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->ChangeMainLightningButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeMainLightning->maximum())));
}

void RSPIndicators::on_ChangeMainFocusButton_pressed()
{
    ui->ChangeMainFocus->show();
    ui->ChangeMainFocus->setEnabled(true);
    ui->ChangeMainFocusButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeMainFocus_sliderPressed()
{
    ui->ChangeMainFocus->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeMainFocus_sliderReleased()
{
    ui->ChangeMainFocus->hide();
    ui->ChangeMainFocus->setDisabled(true);
    ui->ChangeMainFocus->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainFocusButton->setCursor(Qt::OpenHandCursor);
}

void RSPIndicators::on_ChangeMainFocus_valueChanged(int value)
{
    ui->ChangeMainFocusButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeMainFocus->maximum())));
    value=value>=0 ? value+100 : 100-value;
    ui->RenderMainLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void RSPIndicators::on_ChangeMainVARUButton_pressed()
{
    ui->ChangeMainVARU->show();
    ui->ChangeMainVARU->setEnabled(true);
    ui->ChangeMainVARUButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeMainVARU_sliderPressed()
{
    ui->ChangeMainVARU->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeMainVARU_sliderReleased()
{
    ui->ChangeMainVARU->hide();
    ui->ChangeMainVARU->setDisabled(true);
    ui->ChangeMainVARU->setCursor(Qt::OpenHandCursor);
    ui->ChangeMainVARUButton->setCursor(Qt::OpenHandCursor);
}

void RSPIndicators::on_ChangeMainVARU_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("system","varu",static_cast<qreal>(value)/100);
    ui->ChangeMainVARUButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeMainVARU->maximum())));
}

void RSPIndicators::on_ChangeMainViewStateAll_clicked()
{
    if(ui->RenderMainLocator->show)
    {
        ui->ChangeMainViewStateAll->setText("Отобразить все скрытые метки");
        ui->RenderMainLocator->SetSettings("system","show",false);
    }
    else
    {
        ui->ChangeMainViewStateAll->setText("Вернуть состояние скрытых меток");
        ui->RenderMainLocator->SetSettings("system","show",true);
    }
}

void RSPIndicators::on_ChangeMainLocatorState_clicked()
{
    if(ui->RenderMainLocator->IsActive())
    {
        ui->RenderMainLocator->ChangeFPS(0u);
        ui->ChangeMainLocatorState->setText("Продолжить");
    }
    else
    {
        ui->RenderMainLocator->ChangeFPS(static_cast<qreal>(1000)/24);
        ui->ChangeMainLocatorState->setText("Стоп");
    }
}

void RSPIndicators::on_ChangeEquiangularTrashIntensityButton_pressed()
{
    ui->ChangeEquiangularTrashIntensity->show();
    ui->ChangeEquiangularTrashIntensity->setEnabled(true);
    ui->ChangeEquiangularTrashIntensityButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeEquiangularTrashIntensity_sliderPressed()
{
    ui->ChangeEquiangularTrashIntensity->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeEquiangularTrashIntensity_sliderReleased()
{
    ui->ChangeEquiangularTrashIntensity->hide();
    ui->ChangeEquiangularTrashIntensity->setDisabled(true);
    ui->ChangeEquiangularTrashIntensity->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquiangularTrashIntensityButton->setCursor(Qt::OpenHandCursor);

    ui->RenderEquingularTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(ui->ChangeEquiangularTrashIntensity->value()));
    ui->RenderEquingularTriangleLocator->SetSettings("trash","show",ui->ChangeEquiangularTrashIntensity->value()>0);
}

void RSPIndicators::on_ChangeEquiangularTrashIntensity_valueChanged(int value)
{
    if(value<0)
        return;
    //ui->RenderEquingularTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    //ui->RenderEquingularTriangleLocator->SetSettings("trash","show",value>0);
    ui->ChangeEquiangularTrashIntensityButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquiangularTrashIntensity->maximum())));
}

void RSPIndicators::on_SelectEquiangularRangeMarks_clicked()
{
    static quint8 status=0u;
    if(status>1u)
        status=0u;
    else
        status++;

    qint16 degree=0u;

    switch(status)
    {
        case 0u:
            //ui->LabelSelectRangeMarksValue->setText("НЕТ");
            degree=-60;
            break;
        case 1u:
            //ui->LabelSelectRangeMarksValue->setText("10 км.");
            degree=0u;
            break;
        case 2u:
            //ui->LabelSelectRangeMarksValue->setText("50 км.");
            degree=60u;
            break;
    }
    ui->SelectEquiangularRangeMarks->setIcon(QIcon(degree==0u ? QPixmap(":/buttons/knob") : MainLocator::RotateResourceImage(":/buttons/knob",degree)));
    ui->RenderEquingularTriangleLocator->SetSettings("system","range",static_cast<quint16>(status));
}

void RSPIndicators::on_SelectEquiangularScale_clicked()
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
            //ui->LabelScaleValue->setText("45 км.");
            degree=0u;
            max=20.0f;
            break;
        case 1u:
            //ui->LabelScaleValue->setText("90 км.");
            degree=45u;
            max=30.0f;
            break;
        case 2u:
            //ui->LabelScaleValue->setText("150 км.");
            degree=180u;
            max=60.0f;
            break;
    }

    ui->SelectEquiangularScale->setIcon(QIcon(degree==45u ? QPixmap(":/buttons/switch_base") : MainLocator::RotateResourceImage(":/buttons/switch_up",degree)));
    ui->RenderEquingularTriangleLocator->SetSettings("system","scale",static_cast<quint8>(max));

    //Усиление приёмника
    ui->RenderEquingularTriangleLocator->SetSettings("trash","begin",.0f);
    ui->RenderEquingularTriangleLocator->SetSettings("trash","end",static_cast<qreal>(max));

    /*
    if(ui->InputScatterTrashFrom->value()>max)
        ui->InputScatterTrashFrom->setValue(max);
    if(ui->InputScatterTrashTo->value()>max)
        ui->InputScatterTrashTo->setValue(max);
    ui->InputScatterTrashFrom->setMaximum(max);
    ui->InputScatterTrashTo->setMaximum(max);
    */
}

void RSPIndicators::on_ChangeEquiangularBrightnessButton_pressed()
{
    ui->ChangeEquiangularBrightness->show();
    ui->ChangeEquiangularBrightness->setEnabled(true);
    ui->ChangeEquiangularBrightnessButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeEquiangularBrightness_sliderPressed()
{
    ui->ChangeEquiangularBrightness->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeEquiangularBrightness_sliderReleased()
{
    ui->ChangeEquiangularBrightness->hide();
    ui->ChangeEquiangularBrightness->setDisabled(true);
    ui->ChangeEquiangularBrightness->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquiangularBrightnessButton->setCursor(Qt::OpenHandCursor);
}

void RSPIndicators::on_ChangeEquiangularBrightness_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->ChangeEquiangularBrightnessButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquiangularBrightness->maximum())));
}

void RSPIndicators::on_ChangeEquiangularLightningButton_pressed()
{
    ui->ChangeEquiangularLightning->show();
    ui->ChangeEquiangularLightning->setEnabled(true);
    ui->ChangeEquiangularLightningButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeEquiangularLightning_sliderPressed()
{
    ui->ChangeEquiangularLightning->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeEquiangularLightning_sliderReleased()
{
    ui->ChangeEquiangularLightning->hide();
    ui->ChangeEquiangularLightning->setDisabled(true);
    ui->ChangeEquiangularLightning->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquiangularLightningButton->setCursor(Qt::OpenHandCursor);
}

void RSPIndicators::on_ChangeEquiangularLightning_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->ChangeEquiangularLightningButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquiangularLightning->maximum())));
}

void RSPIndicators::on_ChangeEquiangularFocusButton_pressed()
{
    ui->ChangeEquiangularFocus->show();
    ui->ChangeEquiangularFocus->setEnabled(true);
    ui->ChangeEquiangularFocusButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeEquiangularFocus_sliderPressed()
{
    ui->ChangeEquiangularFocus->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeEquiangularFocus_sliderReleased()
{
    ui->ChangeEquiangularFocus->hide();
    ui->ChangeEquiangularFocus->setDisabled(true);
    ui->ChangeEquiangularFocus->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquiangularFocusButton->setCursor(Qt::OpenHandCursor);
}

void RSPIndicators::on_ChangeEquiangularFocus_valueChanged(int value)
{
    ui->ChangeEquiangularFocusButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquiangularFocus->maximum())));
    value=value>=0 ? value+100 : 100-value;
    ui->RenderEquingularTriangleLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void RSPIndicators::on_ChangeEquiangularVARUButton_pressed()
{
    ui->ChangeEquiangularVARU->show();
    ui->ChangeEquiangularVARU->setEnabled(true);
    ui->ChangeEquiangularVARUButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeEquiangularVARU_sliderPressed()
{
    ui->ChangeEquiangularVARU->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeEquiangularVARU_sliderReleased()
{
    ui->ChangeEquiangularVARU->hide();
    ui->ChangeEquiangularVARU->setDisabled(true);
    ui->ChangeEquiangularVARU->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquiangularVARUButton->setCursor(Qt::OpenHandCursor);
}

void RSPIndicators::on_ChangeEquiangularVARU_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("system","varu",static_cast<qreal>(value)/100);
    ui->ChangeEquiangularVARUButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquiangularVARU->maximum())));
}

void RSPIndicators::on_ChangeEquingularViewStateAll_clicked()
{
    if(ui->RenderEquingularTriangleLocator->show)
    {
        ui->ChangeEquingularViewStateAll->setText("Отобразить все скрытые метки");
        ui->RenderEquingularTriangleLocator->SetSettings("system","show",false);
    }
    else
    {
        ui->ChangeEquingularViewStateAll->setText("Вернуть состояние скрытых меток");
        ui->RenderEquingularTriangleLocator->SetSettings("system","show",true);
    }
}

void RSPIndicators::on_ChangeEquingularState_clicked()
{
    if(ui->RenderEquingularTriangleLocator->IsActive())
    {
        ui->RenderEquingularTriangleLocator->ChangeFPS(0u);
        ui->ChangeEquingularState->setText("Продолжить");
    }
    else
    {
        ui->RenderEquingularTriangleLocator->ChangeFPS(static_cast<qreal>(1000)/24);
        ui->ChangeEquingularState->setText("Стоп");
    }
}

void RSPIndicators::on_ChangeRightTrashIntensityButton_pressed()
{
    ui->ChangeRightTrashIntensity->show();
    ui->ChangeRightTrashIntensity->setEnabled(true);
    ui->ChangeRightTrashIntensityButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeRightTrashIntensity_sliderPressed()
{
    ui->ChangeRightTrashIntensity->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeRightTrashIntensity_sliderReleased()
{
    ui->ChangeRightTrashIntensity->hide();
    ui->ChangeRightTrashIntensity->setDisabled(true);
    ui->ChangeRightTrashIntensity->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightTrashIntensityButton->setCursor(Qt::OpenHandCursor);

    ui->RenderRightTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(ui->ChangeRightTrashIntensity->value()));
    ui->RenderRightTriangleLocator->SetSettings("trash","show",ui->ChangeRightTrashIntensity->value()>0);
}

void RSPIndicators::on_ChangeRightTrashIntensity_valueChanged(int value)
{
    if(value<0)
        return;
    //ui->RenderRightTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    //ui->RenderRightTriangleLocator->SetSettings("trash","show",value>0);
    ui->ChangeRightTrashIntensityButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightTrashIntensity->maximum())));
}

void RSPIndicators::on_SelectRightRangeMarks_clicked()
{
    static quint8 status=0u;
    if(status>1u)
        status=0u;
    else
        status++;

    qint16 degree=0u;

    switch(status)
    {
        case 0u:
            //ui->LabelSelectRangeMarksValue->setText("НЕТ");
            degree=-60;
            break;
        case 1u:
            //ui->LabelSelectRangeMarksValue->setText("10 км.");
            degree=0u;
            break;
        case 2u:
            //ui->LabelSelectRangeMarksValue->setText("50 км.");
            degree=60u;
            break;
    }
    ui->SelectRightRangeMarks->setIcon(QIcon(degree==0u ? QPixmap(":/buttons/knob") : MainLocator::RotateResourceImage(":/buttons/knob",degree)));
    ui->RenderRightTriangleLocator->SetSettings("system","range",static_cast<quint16>(status));
}

void RSPIndicators::on_SelectRightScale_clicked()
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
            //ui->LabelScaleValue->setText("45 км.");
            degree=0u;
            max=20.0f;
            break;
        case 1u:
            //ui->LabelScaleValue->setText("90 км.");
            degree=45u;
            max=30.0f;
            break;
        case 2u:
            //ui->LabelScaleValue->setText("150 км.");
            degree=180u;
            max=60.0f;
            break;
    }

    ui->SelectRightScale->setIcon(QIcon(degree==45u ? QPixmap(":/buttons/switch_base") : MainLocator::RotateResourceImage(":/buttons/switch_up",degree)));
    ui->RenderRightTriangleLocator->SetSettings("system","scale",static_cast<quint8>(max));

    //Усиление приёмника
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

void RSPIndicators::on_ChangeRightBrightnessButton_pressed()
{
    ui->ChangeRightBrightness->show();
    ui->ChangeRightBrightness->setEnabled(true);
    ui->ChangeRightBrightness->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeRightBrightness_sliderPressed()
{
    ui->ChangeRightBrightness->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeRightBrightness_sliderReleased()
{
    ui->ChangeRightBrightness->hide();
    ui->ChangeRightBrightness->setDisabled(true);
    ui->ChangeRightBrightness->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightBrightnessButton->setCursor(Qt::OpenHandCursor);
}

void RSPIndicators::on_ChangeRightBrightness_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->ChangeRightBrightnessButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightBrightness->maximum())));
}

void RSPIndicators::on_ChangeRightLightningButton_pressed()
{
    ui->ChangeRightLightning->show();
    ui->ChangeRightLightning->setEnabled(true);
    ui->ChangeRightLightningButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeRightLightning_sliderPressed()
{
    ui->ChangeRightLightning->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeRightLightning_sliderReleased()
{
    ui->ChangeRightLightning->hide();
    ui->ChangeRightLightning->setDisabled(true);
    ui->ChangeRightLightning->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightLightningButton->setCursor(Qt::OpenHandCursor);
}

void RSPIndicators::on_ChangeRightLightning_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->ChangeRightLightningButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightLightning->maximum())));
}

void RSPIndicators::on_ChangeRightFocusButton_pressed()
{
    ui->ChangeRightFocus->show();
    ui->ChangeRightFocus->setEnabled(true);
    ui->ChangeRightFocusButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeRightFocus_sliderPressed()
{
    ui->ChangeRightFocus->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeRightFocus_sliderReleased()
{
    ui->ChangeRightFocus->hide();
    ui->ChangeRightFocus->setDisabled(true);
    ui->ChangeRightFocus->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightFocusButton->setCursor(Qt::OpenHandCursor);
}

void RSPIndicators::on_ChangeRightFocus_valueChanged(int value)
{
    ui->ChangeRightFocusButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightFocus->maximum())));
    value=value>=0 ? value+100 : 100-value;
    ui->RenderRightTriangleLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void RSPIndicators::on_ChangeRightVARUButton_pressed()
{
    ui->ChangeRightVARU->show();
    ui->ChangeRightVARU->setEnabled(true);
    ui->ChangeRightVARUButton->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeRightVARU_sliderPressed()
{
    ui->ChangeRightVARU->setCursor(Qt::ClosedHandCursor);
}

void RSPIndicators::on_ChangeRightVARU_sliderReleased()
{
    ui->ChangeRightVARU->hide();
    ui->ChangeRightVARU->setDisabled(true);
    ui->ChangeRightVARU->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightVARUButton->setCursor(Qt::OpenHandCursor);
}

void RSPIndicators::on_ChangeRightVARU_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("system","varu",static_cast<qreal>(value)/100);
    ui->ChangeRightVARUButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightVARU->maximum())));
}

void RSPIndicators::on_ChangeRightViewStateAll_clicked()
{
    if(ui->RenderRightTriangleLocator->show)
    {
        ui->ChangeRightViewStateAll->setText("Отобразить все скрытые метки");
        ui->RenderRightTriangleLocator->SetSettings("system","show",false);
    }
    else
    {
        ui->ChangeRightViewStateAll->setText("Вернуть состояние скрытых меток");
        ui->RenderRightTriangleLocator->SetSettings("system","show",true);
    }
}

void RSPIndicators::on_ChangeRightState_clicked()
{
    if(ui->RenderRightTriangleLocator->IsActive())
    {
        ui->RenderRightTriangleLocator->ChangeFPS(0u);
        ui->ChangeRightState->setText("Продолжить");
    }
    else
    {
        ui->RenderRightTriangleLocator->ChangeFPS(static_cast<qreal>(1000)/24);
        ui->ChangeRightState->setText("Стоп");
    }
}
