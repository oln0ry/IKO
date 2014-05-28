#include"indicatordrl.h"
#include"ui_indicatordrl.h"
#include<QtGui>

IndicatorDRL::IndicatorDRL(QWidget *parent):QMainWindow(parent),ui(new Ui::IndicatorDRL)
{
    ui->setupUi(this);
    //ui->ShowRightPanel->hide();
    //###Инициализация
    ui->SelectAzimuthMarks->clicked(); //Отметки азимута
    ui->SelectRangeMarks->clicked(); //Отметки дальности

    //Масштаб
    ui->SelectScale->clicked();
    ui->SelectScale->clicked();
    ui->SelectScale->clicked();

    //Яркость индикатора
    ui->ChangeIndicatorBrightness->valueChanged(ui->ChangeIndicatorBrightness->value());
    ui->ChangeIndicatorBrightness->hide();
    ui->ChangeIndicatorBrightness->setDisabled(true);

    //Подсветка луча индикатора (остаточное изображение)
    ui->ChangeIndicatorLightning->valueChanged(ui->ChangeIndicatorLightning->value());
    ui->ChangeIndicatorLightning->hide();
    ui->ChangeIndicatorLightning->setDisabled(true);

    //Фокус изображения, отображаемого на индикаторе
    ui->ChangeIndicatorFocus->valueChanged(ui->ChangeIndicatorFocus->value());
    ui->ChangeIndicatorFocus->hide();
    ui->ChangeIndicatorFocus->setDisabled(true);

    //Автоматическая регулировка усиления индикатора
    ui->ChangeIndicatorVARU->valueChanged(ui->ChangeIndicatorVARU->value());
    ui->ChangeIndicatorVARU->hide();
    ui->ChangeIndicatorVARU->setDisabled(true);

    //Интенсивность усиления приёмника
    //ui->ChangeTrashIntensity->valueChanged(ui->ChangeTrashIntensity->value());
    ui->ChangeTrashIntensity->sliderReleased();
    ui->ChangeTrashIntensity->hide();
    ui->ChangeTrashIntensity->setDisabled(true);

    //Радиус генерации пассивных помех
    ui->InputScatterTrashFrom->valueChanged(ui->InputScatterTrashFrom->value());
    ui->InputScatterTrashTo->valueChanged(ui->InputScatterTrashTo->value());

    ui->CheckShowLocalItems->stateChanged(ui->CheckShowLocalItems->checkState()); //Засветка индикатора от местных предметов
    ui->CheckShowMeteo->stateChanged(ui->CheckShowMeteo->checkState()); //Метеообразования

    //Активные шумовые помехи
    QStringList intensity;
    intensity<<"Слабая"<<"Средняя"<<"Сильная";
    ui->SelectActiveNoiseIntensity->addItems(intensity);
    ui->SelectActiveNoiseIntensity->setCurrentIndex(1);
    ui->InputActiveNoiseAzimuth->valueChanged(ui->InputActiveNoiseAzimuth->value());

    //Активные ответно-импульсные помехи
    ui->InputActiveAnswerAzimuth->valueChanged(ui->InputActiveAnswerAzimuth->value());
    ui->InputActiveAnswerDistance->valueChanged(ui->InputActiveAnswerDistance->value());

    ui->SelectWorkVariant->clicked(); //Режим индикатора кругового обзора

    //Статика
    ui->RenderMainLocator->SetSettings("offset","horizontal",.0f);
    ui->RenderMainLocator->SetSettings("offset","vertical",.0f);
    //###\Инициализация
    ui->ChangeLocatorState->clicked(); //Запуск индикатора
}

IndicatorDRL::~IndicatorDRL()
{
    delete ui;
}

void IndicatorDRL::resizeEvent(QResizeEvent *E)
{
    QMainWindow::resizeEvent(E);
    if(isFullScreen())
        return;
    if(ui->BoxIndicatorSettings->geometry().y()+ui->BoxIndicatorSettings->geometry().height()<ui->BoxActiveTrashSettings->geometry().y())
    {
        if(change_view_bottom==0)
            change_view_bottom=ui->BoxActiveTrashSettings->geometry().y();
        ui->gridLayout_3->addWidget(ui->BoxTrashSettings,3,0,1,1,Qt::AlignRight|Qt::AlignBottom);
        ui->LayoutActiveAnswerTrashSettings->addWidget(ui->LabelActiveAnswerAzimuth,0,0,1,1,Qt::AlignLeft|Qt::AlignVCenter);
        ui->LayoutActiveAnswerTrashSettings->addWidget(ui->InputActiveAnswerAzimuth,0,1,1,1);
        ui->LayoutActiveAnswerTrashSettings->addWidget(ui->LabelActiveAnswerDistance,1,0,1,1,Qt::AlignLeft|Qt::AlignVCenter);
        ui->LayoutActiveAnswerTrashSettings->addWidget(ui->InputActiveAnswerDistance,1,1,1,1);
        ui->LayoutActiveAnswerTrashSettings->addWidget(ui->CheckActiveAnswerShow,2,0,1,2,Qt::AlignLeft|Qt::AlignVCenter);
        ui->gridLayout_6->addWidget(ui->BoxActiveAnswerTrash,0,1,1,1);
        ui->LayoutActiveNoiseTrashSettings->addWidget(ui->LabelActiveNoiseIntensity,1,0,1,1,Qt::AlignLeft|Qt::AlignBottom);
        ui->LayoutActiveNoiseTrashSettings->addWidget(ui->SelectActiveNoiseIntensity,2,0,1,1,Qt::AlignTop);
        ui->LayoutActiveNoiseTrashSettings->addWidget(ui->CheckActiveNoiseShow,3,0,1,1,Qt::AlignLeft|Qt::AlignVCenter);
        ui->gridLayout_6->addWidget(ui->BoxActiveNoiseTrash,0,0,2,1);
        ui->gridLayout_6->addWidget(ui->CheckActiveInSyncShow,1,1,1,1,Qt::AlignLeft|Qt::AlignVCenter);
        ui->gridLayout_3->addWidget(ui->BoxActiveTrashSettings,3,2,1,1);
    }

    if(change_view_bottom>0 && change_view_bottom>static_cast<unsigned int>(ui->BoxActiveTrashSettings->geometry().y()))
    {
        ui->gridLayout_3->addWidget(ui->BoxTrashSettings,1,0,1,1,Qt::AlignLeft|Qt::AlignBottom);
        ui->LayoutActiveAnswerTrashSettings->addWidget(ui->LabelActiveAnswerAzimuth,0,0,1,1,Qt::AlignLeft|Qt::AlignVCenter);
        ui->LayoutActiveAnswerTrashSettings->addWidget(ui->InputActiveAnswerAzimuth,0,1,1,1);
        ui->LayoutActiveAnswerTrashSettings->addWidget(ui->LabelActiveAnswerDistance,1,0,1,1,Qt::AlignLeft|Qt::AlignVCenter);
        ui->LayoutActiveAnswerTrashSettings->addWidget(ui->InputActiveAnswerDistance,1,1,1,1);
        ui->LayoutActiveAnswerTrashSettings->addWidget(ui->CheckActiveAnswerShow,2,0,1,2,Qt::AlignLeft|Qt::AlignVCenter);
        ui->gridLayout_6->addWidget(ui->BoxActiveAnswerTrash,0,1,1,1);
        ui->LayoutActiveNoiseTrashSettings->addWidget(ui->LabelActiveNoiseIntensity,1,0,1,1,Qt::AlignLeft|Qt::AlignBottom);
        ui->LayoutActiveNoiseTrashSettings->addWidget(ui->SelectActiveNoiseIntensity,2,0,1,1,Qt::AlignTop);
        ui->LayoutActiveNoiseTrashSettings->addWidget(ui->CheckActiveNoiseShow,3,0,1,1,Qt::AlignLeft|Qt::AlignVCenter);
        ui->gridLayout_6->addWidget(ui->BoxActiveNoiseTrash,0,0,2,1);
        ui->gridLayout_6->addWidget(ui->CheckActiveInSyncShow,1,1,1,1,Qt::AlignLeft|Qt::AlignVCenter);
        ui->gridLayout_3->addWidget(ui->BoxActiveTrashSettings,2,0,1,1);
    }
}

/**
 * Этот метод является чистой воды диким шаманством
 */
bool IndicatorDRL::eventFilter(QObject *O, QEvent *E)
{
    if((O->objectName()=="MainLocator" || O->inherits("MainLocator")) && E->type()==QEvent::MouseButtonDblClick)
    {
        if(isFullScreen())
        {
            ui->gridLayout_3->addWidget(ui->RenderMainLocator,0,0,1,1);
            ui->centralwidget->raise();
            showNormal();
        }
        else
        {
            ui->gridLayout_3->addWidget(ui->RenderMainLocator,0,0,0,0);
            ui->RenderMainLocator->raise();
            //ui->gridLayout_3->addWidget(ui->ShowRightPanel,1,3,1,1);
            //ui->ShowRightPanel->show();
            showFullScreen();
        }
        activateWindow();
    }
    return QMainWindow::eventFilter(O,E);
}

void IndicatorDRL::on_SelectAzimuthMarks_clicked()
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
    ui->SelectAzimuthMarks->setIcon(QIcon(degree==0u ? QPixmap(":/buttons/knob") : MainLocator::RotateResourceImage(":/buttons/knob",degree)));
    ui->RenderMainLocator->SetSettings("system","azimuth",static_cast<quint16>(status));
}

void IndicatorDRL::on_SelectRangeMarks_clicked()
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
    ui->SelectRangeMarks->setIcon(QIcon(degree==0u ? QPixmap(":/buttons/knob") : MainLocator::RotateResourceImage(":/buttons/knob",degree)));
    ui->RenderMainLocator->SetSettings("system","range",static_cast<quint16>(status));
}

void IndicatorDRL::on_SelectScale_clicked()
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

    ui->SelectScale->setIcon(QIcon(degree==45u ? QPixmap(":/buttons/switch_base") : MainLocator::RotateResourceImage(":/buttons/switch_up",degree)));
    ui->RenderMainLocator->SetSettings("system","scale",static_cast<quint8>(max));

    if(ui->InputScatterTrashFrom->value()>max)
        ui->InputScatterTrashFrom->setValue(max);
    if(ui->InputScatterTrashTo->value()>max)
        ui->InputScatterTrashTo->setValue(max);
    ui->InputScatterTrashFrom->setMaximum(max);
    ui->InputScatterTrashTo->setMaximum(max);
}

void IndicatorDRL::on_ChangeIndicatorBrightnessButton_pressed()
{
    ui->ChangeIndicatorBrightness->show();
    ui->ChangeIndicatorBrightness->setEnabled(true);
    ui->ChangeIndicatorBrightnessButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorDRL::on_ChangeIndicatorBrightness_sliderPressed()
{
    ui->ChangeIndicatorBrightness->setCursor(Qt::ClosedHandCursor);
}

void IndicatorDRL::on_ChangeIndicatorBrightness_sliderReleased()
{
    ui->ChangeIndicatorBrightness->hide();
    ui->ChangeIndicatorBrightness->setDisabled(true);
    ui->ChangeIndicatorBrightness->setCursor(Qt::OpenHandCursor);
    ui->ChangeIndicatorBrightnessButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorDRL::on_ChangeIndicatorBrightness_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
    ui->ChangeIndicatorBrightnessButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeIndicatorBrightness->maximum())));
}

void IndicatorDRL::on_ChangeIndicatorLightningButton_pressed()
{
    ui->ChangeIndicatorLightning->show();
    ui->ChangeIndicatorLightning->setEnabled(true);
    ui->ChangeIndicatorLightningButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorDRL::on_ChangeIndicatorLightning_sliderPressed()
{
    ui->ChangeIndicatorLightning->setCursor(Qt::ClosedHandCursor);
}

void IndicatorDRL::on_ChangeIndicatorLightning_sliderReleased()
{
    ui->ChangeIndicatorLightning->hide();
    ui->ChangeIndicatorLightning->setDisabled(true);
    ui->ChangeIndicatorLightning->setCursor(Qt::OpenHandCursor);
    ui->ChangeIndicatorLightningButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorDRL::on_ChangeIndicatorLightning_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
    ui->ChangeIndicatorLightningButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeIndicatorLightning->maximum())));
}

void IndicatorDRL::on_ChangeIndicatorFocusButton_pressed()
{
    ui->ChangeIndicatorFocus->show();
    ui->ChangeIndicatorFocus->setEnabled(true);
    ui->ChangeIndicatorFocusButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorDRL::on_ChangeIndicatorFocus_sliderPressed()
{
    ui->ChangeIndicatorFocus->setCursor(Qt::ClosedHandCursor);
}

void IndicatorDRL::on_ChangeIndicatorFocus_sliderReleased()
{
    ui->ChangeIndicatorFocus->hide();
    ui->ChangeIndicatorFocus->setDisabled(true);
    ui->ChangeIndicatorFocus->setCursor(Qt::OpenHandCursor);
    ui->ChangeIndicatorFocusButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorDRL::on_ChangeIndicatorFocus_valueChanged(int value)
{
    ui->ChangeIndicatorFocusButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeIndicatorFocus->maximum())));
    value=value>=0 ? value+100 : 100-value;
    ui->RenderMainLocator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void IndicatorDRL::on_ChangeIndicatorVARUButton_pressed()
{
    ui->ChangeIndicatorVARU->show();
    ui->ChangeIndicatorVARU->setEnabled(true);
    ui->ChangeIndicatorVARUButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorDRL::on_ChangeIndicatorVARU_sliderPressed()
{
    ui->ChangeIndicatorVARU->setCursor(Qt::ClosedHandCursor);
}

void IndicatorDRL::on_ChangeIndicatorVARU_sliderReleased()
{
    ui->ChangeIndicatorVARU->hide();
    ui->ChangeIndicatorVARU->setDisabled(true);
    ui->ChangeIndicatorVARU->setCursor(Qt::OpenHandCursor);
    ui->ChangeIndicatorVARUButton->setCursor(Qt::OpenHandCursor);
}

void IndicatorDRL::on_ChangeIndicatorVARU_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderMainLocator->SetSettings("system","varu",static_cast<qreal>(value)/100);
    ui->ChangeIndicatorVARUButton->setIcon(QIcon(value%100u==0 || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeIndicatorVARU->maximum())));
}

void IndicatorDRL::on_SelectWorkVariant_clicked()
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
            //ui->LabelSelectWorkVariantValue->setText("АКТ");
            degree=-60;
            //ui->SelectWorkVariant->setStyleSheet("border-image: url(:/buttons/knob2);background-repeat: no-repeat;background-position: center;");
            /*
            if(ui->BoxTrashSettings->isEnabled())
                ui->BoxTrashSettings->setEnabled(false);
            if(ui->BoxActiveTrashSettings->isEnabled())
                ui->BoxActiveTrashSettings->setEnabled(false);
            */
            break;
        case 1u:
            //ui->LabelSelectWorkVariantValue->setText("ПАСС");
            degree=0;
            //ui->SelectWorkVariant->setStyleSheet("border-image: url(:/buttons/knob);background-repeat: no-repeat;background-position: center;");
            /*
            if(!ui->BoxTrashSettings->isEnabled())
                ui->BoxTrashSettings->setEnabled(true);
            if(!ui->BoxActiveTrashSettings->isEnabled())
                ui->BoxActiveTrashSettings->setEnabled(true);
            if(!ui->BoxActiveNoiseTrash->isEnabled())
                ui->BoxActiveNoiseTrash->setEnabled(true);
            ui->CheckShowTrash->stateChanged(ui->CheckShowTrash->checkState());
            ui->CheckShowMeteo->stateChanged(ui->CheckShowMeteo->checkState());
            ui->CheckShowLocalItems->stateChanged(ui->CheckShowLocalItems->checkState());
            ui->CheckActiveNoiseShow->stateChanged(ui->CheckActiveNoiseShow->checkState());
            ui->CheckActiveAnswerShow->stateChanged(ui->CheckActiveAnswerShow->checkState());
            ui->CheckActiveInSyncShow->stateChanged(ui->CheckActiveInSyncShow->checkState());
            */
            break;
        case 2u:
            degree=60;
            //ui->LabelSelectWorkVariantValue->setText("СДЦ");
            //ui->SelectWorkVariant->setStyleSheet("border-image: url(:/buttons/knob1);background-repeat: no-repeat;background-position: center;");
            /*
            if(!ui->BoxActiveTrashSettings->isEnabled())
                ui->BoxActiveTrashSettings->setEnabled(true);
            if(!ui->BoxActiveTrashSettings->isEnabled())
                ui->BoxActiveTrashSettings->setEnabled(true);
            if(ui->BoxActiveNoiseTrash->isEnabled())
                ui->BoxActiveNoiseTrash->setEnabled(false);
            if(ui->BoxTrashSettings->isEnabled())
                ui->BoxTrashSettings->setEnabled(false);
            ui->CheckActiveAnswerShow->stateChanged(ui->CheckActiveAnswerShow->checkState());
            ui->CheckActiveInSyncShow->stateChanged(ui->CheckActiveInSyncShow->checkState());
            */
            break;
    }
    ui->SelectWorkVariant->setIcon(QIcon(degree==0u ? QPixmap(":/buttons/knob") : MainLocator::RotateResourceImage(":/buttons/knob",degree)));
    ui->RenderMainLocator->SetSettings("system","mode",static_cast<quint8>(status));
}

void IndicatorDRL::on_ChangeViewStateAll_clicked()
{
    if(ui->RenderMainLocator->show)
    {
        ui->ChangeViewStateAll->setText("Отобразить все\nскрытые метки");
        ui->RenderMainLocator->SetSettings("system","show",false);
    }
    else
    {
        ui->ChangeViewStateAll->setText("Вернуть состояние\nскрытых меток");
        ui->RenderMainLocator->SetSettings("system","show",true);
    }
}

void IndicatorDRL::on_ChangeLocatorState_clicked()
{
    if(ui->RenderMainLocator->IsActive())
    {
        ui->RenderMainLocator->ChangeFPS(0u);
        ui->ChangeLocatorState->setText("Продолжить");
    }
    else
    {
        ui->RenderMainLocator->ChangeFPS(static_cast<qreal>(1000)/24);
        ui->ChangeLocatorState->setText("Стоп");
    }
}

void IndicatorDRL::on_SetTargetsSettings_clicked()
{
    tsettings=new TargetsSettings;
    tsettings->show();
}

void IndicatorDRL::on_ChangeTrashIntensityButton_pressed()
{
    ui->ChangeTrashIntensity->show();
    ui->ChangeTrashIntensity->setEnabled(true);
    ui->ChangeTrashIntensityButton->setCursor(Qt::ClosedHandCursor);
}

void IndicatorDRL::on_ChangeTrashIntensity_sliderPressed()
{
    ui->ChangeTrashIntensity->setCursor(Qt::ClosedHandCursor);
}

void IndicatorDRL::on_ChangeTrashIntensity_sliderReleased()
{
    ui->ChangeTrashIntensity->hide();
    ui->ChangeTrashIntensity->setDisabled(true);
    ui->ChangeTrashIntensity->setCursor(Qt::OpenHandCursor);
    ui->ChangeTrashIntensityButton->setCursor(Qt::OpenHandCursor);
    //---------------------------
    ui->RenderMainLocator->SetSettings("trash","intensity",static_cast<quint8>(ui->ChangeTrashIntensity->value()));
    ui->RenderMainLocator->SetSettings("trash","show",ui->ChangeTrashIntensity->value()>0);
}

void IndicatorDRL::on_ChangeTrashIntensity_valueChanged(int value)
{
    if(value<0)
        return;

    /*
    ui->RenderMainLocator->SetSettings("trash","intensity",static_cast<quint8>(value));
    ui->RenderMainLocator->SetSettings("trash","show",value>0);
    */
    ui->ChangeTrashIntensityButton->setIcon(QIcon(value==100u || value==0u ? QPixmap(":/buttons/reo_knob.png") : MainLocator::RotateResourceImage(":/buttons/reo_knob.png",value*360/ui->ChangeTrashIntensity->maximum())));
}

void IndicatorDRL::on_InputScatterTrashFrom_valueChanged(double arg1)
{
    qreal from=static_cast<qreal>(arg1),
          to=static_cast<qreal>(ui->InputScatterTrashTo->value());
    if(from>=to)
        ui->InputScatterTrashFrom->setMaximum(to);
    ui->InputScatterTrashTo->setMinimum(from);
    ui->RenderMainLocator->SetSettings("trash","begin",from);
}

void IndicatorDRL::on_InputScatterTrashTo_valueChanged(double arg1)
{
    qreal from=static_cast<qreal>(ui->InputScatterTrashFrom->value()),
          to=static_cast<qreal>(arg1);
    if(to<=from)
        ui->InputScatterTrashTo->setMinimum(from);
    ui->InputScatterTrashFrom->setMaximum(to);
    ui->RenderMainLocator->SetSettings("trash","end",to);
}

void IndicatorDRL::on_RegenerateTrash_clicked()
{
    ui->RenderMainLocator->GenerationTrash();
    ui->RenderMainLocator->GenerationMeteo();
}

void IndicatorDRL::on_CheckShowLocalItems_stateChanged(int arg1)
{
    ui->RenderMainLocator->SetSettings("local_items","show",arg1==2);
}

void IndicatorDRL::on_CheckShowMeteo_stateChanged(int arg1)
{
    ui->RenderMainLocator->SetSettings("meteo","show",arg1==2);
}

void IndicatorDRL::on_InputActiveNoiseAzimuth_valueChanged(int arg1)
{
    ui->RenderMainLocator->SetSettings("active_noise_trash","azimuth",static_cast<quint16>(arg1));
}

void IndicatorDRL::on_SelectActiveNoiseIntensity_currentIndexChanged(int index)
{
    ui->RenderMainLocator->SetSettings("active_noise_trash","intensity",static_cast<quint16>(index));
}

void IndicatorDRL::on_CheckActiveNoiseShow_stateChanged(int arg1)
{
    ui->RenderMainLocator->SetSettings("active_noise_trash","show",arg1==2);
}

void IndicatorDRL::on_InputActiveAnswerAzimuth_valueChanged(int arg1)
{
    ui->RenderMainLocator->SetSettings("active_answer_trash","azimuth",static_cast<quint16>(arg1));
}

void IndicatorDRL::on_InputActiveAnswerDistance_valueChanged(double arg1)
{
    ui->RenderMainLocator->SetSettings("active_answer_trash","distance",static_cast<qreal>(arg1));
}

void IndicatorDRL::on_CheckActiveAnswerShow_stateChanged(int arg1)
{
    ui->RenderMainLocator->SetSettings("active_answer_trash","show",arg1==2);
}

void IndicatorDRL::on_CheckActiveInSyncShow_stateChanged(int arg1)
{
    ui->RenderMainLocator->SetSettings("active_insync_trash","show",arg1==2);
}
