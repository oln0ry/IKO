#include"indicatorprl.h"
#include"ui_indicatorprl.h"

IndicatorPRL::IndicatorPRL(QWidget *parent) : QMainWindow(parent),ui(new Ui::IndicatorPRL)
{
    ui->setupUi(this);
    //###Инициализация
    //Отметки дальности
    ui->SelectEquingularRangeMarks->clicked();

    ui->SelectRightRangeMarks->clicked();

    //Интенсивность усиления приёмника
    ui->ChangeEquingularTrashIntensity->valueChanged(ui->ChangeEquingularTrashIntensity->value());
    ui->ChangeEquingularTrashIntensity->hide();
    ui->ChangeEquingularTrashIntensity->setDisabled(true);

    ui->ChangeRightTrashIntensity->valueChanged(ui->ChangeRightTrashIntensity->value());
    ui->ChangeRightTrashIntensity->hide();
    ui->ChangeRightTrashIntensity->setDisabled(true);

    //Яркость индикаторов
    ui->ChangeEquingularBrightness->valueChanged(ui->ChangeEquingularBrightness->value());
    ui->ChangeEquingularBrightness->hide();
    ui->ChangeEquingularBrightness->setDisabled(true);

    ui->ChangeRightBrightness->valueChanged(ui->ChangeRightBrightness->value());
    ui->ChangeRightBrightness->hide();
    ui->ChangeRightBrightness->setDisabled(true);

    //Подсветка луча индикаторов (остаточное изображение)
    ui->ChangeEquingularLightning->valueChanged(ui->ChangeEquingularLightning->value());
    ui->ChangeEquingularLightning->hide();
    ui->ChangeEquingularLightning->setDisabled(true);

    ui->ChangeRightLightning->valueChanged(ui->ChangeRightLightning->value());
    ui->ChangeRightLightning->hide();
    ui->ChangeRightLightning->setDisabled(true);

    //Фокус изображений, отображаемого на индикаторах
    ui->ChangeEquingularFocus->valueChanged(ui->ChangeEquingularFocus->value());
    ui->ChangeEquingularFocus->hide();
    ui->ChangeEquingularFocus->setDisabled(true);

    ui->ChangeRightFocus->valueChanged(ui->ChangeRightFocus->value());
    ui->ChangeRightFocus->hide();
    ui->ChangeRightFocus->setDisabled(true);

    //Автоматическая регулировка усиления индикаторов
    ui->ChangeEquingularVARU->valueChanged(ui->ChangeEquingularVARU->value());
    ui->ChangeEquingularVARU->hide();
    ui->ChangeEquingularVARU->setDisabled(true);

    ui->ChangeRightVARU->valueChanged(ui->ChangeRightVARU->value());
    ui->ChangeRightVARU->hide();
    ui->ChangeRightVARU->setDisabled(true);

    //Масштаб
    ui->SelectEquingularScale->clicked();
    ui->SelectEquingularScale->clicked();
    ui->SelectEquingularScale->clicked();

    ui->SelectRightScale->clicked();
    ui->SelectRightScale->clicked();
    ui->SelectRightScale->clicked();
    //###\Инициализация

    //Запуск индикаторов
    ui->ChangeEquingularState->clicked();
    ui->ChangeRightState->clicked();
}

IndicatorPRL::~IndicatorPRL()
{
    delete ui;
}

/**
 * Этот метод является чистой воды диким шаманством
 */
bool IndicatorPRL::eventFilter(QObject *O, QEvent *E)
{
    if((O->objectName()=="MainLocator" || O->inherits("MainLocator")) && E->type()==QEvent::MouseButtonDblClick)
    {
        if(isFullScreen())
        {
            ui->gridLayout_3->addWidget(ui->RenderEquingularTriangleLocator,0,0,1,1);
            ui->gridLayout_3->addWidget(ui->RenderRightTriangleLocator,0,3,1,1);
            ui->centralwidget->raise();
            showNormal();
        }
        else
        {
            if(O->objectName()=="RenderEquingularTriangleLocator" && O->inherits("EquiangularTriangleLocator"))
            {
                ui->gridLayout_3->addWidget(ui->RenderEquingularTriangleLocator,0,0,0,0);
                ui->RenderEquingularTriangleLocator->raise();
            }
            else if(O->objectName()=="RenderRightTriangleLocator" && O->inherits("RightTriangleLocator"))
            {
                ui->gridLayout_3->addWidget(ui->RenderRightTriangleLocator,0,0,0,0);
                ui->RenderRightTriangleLocator->raise();
            }
            showFullScreen();
        }
        activateWindow();
    }
    return QMainWindow::eventFilter(O,E);
}

void IndicatorPRL::on_SelectEquingularRangeMarks_clicked()
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
            degree=-60;
            break;
        case 1u:
            degree=0u;
            break;
        case 2u:
            degree=60u;
            break;
    }
    ui->SelectEquingularRangeMarks->setIcon(QIcon(degree==0u ? QPixmap(":/buttons/knob") : MainLocator::RotateResourceImage(":/buttons/knob",degree)));
    ui->RenderEquingularTriangleLocator->SetSettings("system","range",static_cast<quint16>(status));
}

void IndicatorPRL::on_ChangeEquingularTrashIntensityButton_pressed()
{
    ui->ChangeEquingularTrashIntensity->show();
    ui->ChangeEquingularTrashIntensity->setEnabled(true);
    ui->ChangeEquingularTrashIntensityButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeEquingularTrashIntensity_sliderPressed()
{
    ui->ChangeEquingularTrashIntensity->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeEquingularTrashIntensity_sliderReleased()
{
    ui->ChangeEquingularTrashIntensity->hide();
    ui->ChangeEquingularTrashIntensity->setDisabled(true);
    ui->ChangeEquingularTrashIntensity->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularTrashIntensityButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorPRL::on_ChangeEquingularTrashIntensity_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderEquingularTriangleLocator->SetSettings("trash","show",value>0);
    ui->ChangeEquingularTrashIntensityButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquingularTrashIntensity->maximum())));
}

void IndicatorPRL::on_ChangeEquingularBrightnessButton_pressed()
{
    ui->ChangeEquingularBrightness->show();
    ui->ChangeEquingularBrightness->setEnabled(true);
    ui->ChangeEquingularBrightnessButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeEquingularBrightness_sliderPressed()
{
    ui->ChangeEquingularBrightness->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeEquingularBrightness_sliderReleased()
{
    ui->ChangeEquingularBrightness->hide();
    ui->ChangeEquingularBrightness->setDisabled(true);
    ui->ChangeEquingularBrightness->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularBrightnessButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorPRL::on_ChangeEquingularBrightness_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->ChangeEquingularBrightnessButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquingularBrightness->maximum())));
}

void IndicatorPRL::on_ChangeEquingularLightningButton_pressed()
{
    ui->ChangeEquingularLightning->show();
    ui->ChangeEquingularLightning->setEnabled(true);
    ui->ChangeEquingularLightningButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeEquingularLightning_sliderPressed()
{
    ui->ChangeEquingularLightning->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeEquingularLightning_sliderReleased()
{
    ui->ChangeEquingularLightning->hide();
    ui->ChangeEquingularLightning->setDisabled(true);
    ui->ChangeEquingularLightning->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularLightningButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorPRL::on_ChangeEquingularLightning_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->ChangeEquingularLightningButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquingularLightning->maximum())));
}

void IndicatorPRL::on_ChangeEquingularFocusButton_pressed()
{
    ui->ChangeEquingularFocus->show();
    ui->ChangeEquingularFocus->setEnabled(true);
    ui->ChangeEquingularFocusButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeEquingularFocus_sliderPressed()
{
    ui->ChangeEquingularFocus->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeEquingularFocus_sliderReleased()
{
    ui->ChangeEquingularFocus->hide();
    ui->ChangeEquingularFocus->setDisabled(true);
    ui->ChangeEquingularFocus->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularFocusButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorPRL::on_ChangeEquingularFocus_valueChanged(int value)
{
    ui->ChangeEquingularFocusButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquingularFocus->maximum())));
    value=value>=0 ? value+100 : 100-value;
    ui->RenderEquingularTriangleLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void IndicatorPRL::on_ChangeEquingularVARUButton_pressed()
{
    ui->ChangeEquingularVARU->show();
    ui->ChangeEquingularVARU->setEnabled(true);
    ui->ChangeEquingularVARUButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeEquingularVARU_sliderPressed()
{
    ui->ChangeEquingularVARU->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeEquingularVARU_sliderReleased()
{
    ui->ChangeEquingularVARU->hide();
    ui->ChangeEquingularVARU->setDisabled(true);
    ui->ChangeEquingularVARU->setCursor(Qt::OpenHandCursor);
    ui->ChangeEquingularVARUButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorPRL::on_ChangeEquingularVARU_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderEquingularTriangleLocator->SetSettings("system","varu",static_cast<qreal>(value)/100);
    ui->ChangeEquingularVARUButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeEquingularVARU->maximum())));
}

void IndicatorPRL::on_SelectEquingularScale_clicked()
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
            max=20.0f;
            break;
        case 1u:
            degree=45u;
            max=30.0f;
            break;
        case 2u:
            degree=180u;
            max=60.0f;
            break;
    }

    ui->SelectEquingularScale->setIcon(QIcon(degree==45u ? QPixmap(":/buttons/switch_base") : MainLocator::RotateResourceImage(":/buttons/switch_up",degree)));
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

void IndicatorPRL::on_ChangeEquingularViewStateAll_clicked()
{
    if(ui->RenderEquingularTriangleLocator->show)
    {
        ui->ChangeEquingularViewStateAll->setText("Отобразить все\nскрытые метки");
        ui->RenderEquingularTriangleLocator->SetSettings("system","show",false);
    }
    else
    {
        ui->ChangeEquingularViewStateAll->setText("Вернуть состояние\nскрытых меток");
        ui->RenderEquingularTriangleLocator->SetSettings("system","show",true);
    }
}

void IndicatorPRL::on_ChangeEquingularState_clicked()
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

void IndicatorPRL::on_SelectRightRangeMarks_clicked()
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
            degree=-60;
            break;
        case 1u:
            degree=0u;
            break;
        case 2u:
            degree=60u;
            break;
    }
    ui->SelectRightRangeMarks->setIcon(QIcon(degree==0u ? QPixmap(":/buttons/knob") : MainLocator::RotateResourceImage(":/buttons/knob",degree)));
    ui->RenderRightTriangleLocator->SetSettings("system","range",static_cast<quint16>(status));
}

void IndicatorPRL::on_ChangeRightTrashIntensityButton_pressed()
{
    ui->ChangeRightTrashIntensity->show();
    ui->ChangeRightTrashIntensity->setEnabled(true);
    ui->ChangeRightTrashIntensityButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeRightTrashIntensity_sliderPressed()
{
    ui->ChangeRightTrashIntensity->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeRightTrashIntensity_sliderReleased()
{
    ui->ChangeRightTrashIntensity->hide();
    ui->ChangeRightTrashIntensity->setDisabled(true);
    ui->ChangeRightTrashIntensity->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightTrashIntensityButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorPRL::on_ChangeRightTrashIntensity_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderRightTriangleLocator->SetSettings("trash","show",value>0);
    ui->ChangeRightTrashIntensityButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightTrashIntensity->maximum())));
}

void IndicatorPRL::on_ChangeRightBrightnessButton_pressed()
{
    ui->ChangeRightBrightness->show();
    ui->ChangeRightBrightness->setEnabled(true);
    ui->ChangeRightBrightnessButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeRightBrightness_sliderPressed()
{
    ui->ChangeRightBrightness->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeRightBrightness_sliderReleased()
{
    ui->ChangeRightBrightness->hide();
    ui->ChangeRightBrightness->setDisabled(true);
    ui->ChangeRightBrightness->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightBrightnessButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorPRL::on_ChangeRightBrightness_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->ChangeRightBrightnessButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightBrightness->maximum())));
}

void IndicatorPRL::on_ChangeRightLightningButton_pressed()
{
    ui->ChangeRightLightning->show();
    ui->ChangeRightLightning->setEnabled(true);
    ui->ChangeRightLightningButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeRightLightning_sliderPressed()
{
    ui->ChangeRightLightning->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeRightLightning_sliderReleased()
{
    ui->ChangeRightLightning->hide();
    ui->ChangeRightLightning->setDisabled(true);
    ui->ChangeRightLightning->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightLightningButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorPRL::on_ChangeRightLightning_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->ChangeRightLightningButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightLightning->maximum())));
}

void IndicatorPRL::on_ChangeRightFocusButton_pressed()
{
    ui->ChangeRightFocus->show();
    ui->ChangeRightFocus->setEnabled(true);
    ui->ChangeRightFocusButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeRightFocus_sliderPressed()
{
    ui->ChangeRightFocus->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeRightFocus_sliderReleased()
{
    ui->ChangeRightFocus->hide();
    ui->ChangeRightFocus->setDisabled(true);
    ui->ChangeRightFocus->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightFocusButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorPRL::on_ChangeRightFocus_valueChanged(int value)
{
    ui->ChangeRightFocusButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightFocus->maximum())));
    value=value>=0 ? value+100 : 100-value;
    ui->RenderRightTriangleLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void IndicatorPRL::on_ChangeRightVARUButton_pressed()
{
    ui->ChangeRightVARU->show();
    ui->ChangeRightVARU->setEnabled(true);
    ui->ChangeRightVARUButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeRightVARU_sliderPressed()
{
    ui->ChangeRightVARU->show();
    ui->ChangeRightVARU->setEnabled(true);
    ui->ChangeRightVARUButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorPRL::on_ChangeRightVARU_sliderReleased()
{
    ui->ChangeRightVARU->hide();
    ui->ChangeRightVARU->setDisabled(true);
    ui->ChangeRightVARU->setCursor(Qt::OpenHandCursor);
    ui->ChangeRightVARUButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorPRL::on_ChangeRightVARU_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderRightTriangleLocator->SetSettings("system","varu",static_cast<qreal>(value)/100);
    ui->ChangeRightVARUButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeRightVARU->maximum())));
}

void IndicatorPRL::on_SelectRightScale_clicked()
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
            max=20.0f;
            break;
        case 1u:
            degree=45u;
            max=30.0f;
            break;
        case 2u:
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

void IndicatorPRL::on_ChangeRightViewStateAll_clicked()
{
    if(ui->RenderRightTriangleLocator->show)
    {
        ui->ChangeRightViewStateAll->setText("Отобразить все\nскрытые метки");
        ui->RenderRightTriangleLocator->SetSettings("system","show",false);
    }
    else
    {
        ui->ChangeRightViewStateAll->setText("Вернуть состояние\nскрытых меток");
        ui->RenderRightTriangleLocator->SetSettings("system","show",true);
    }
}

void IndicatorPRL::on_ChangeRightState_clicked()
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
