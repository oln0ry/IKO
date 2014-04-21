#include"indicatordrl.h"
#include"ui_indicatordrl.h"
#include<QDebug>
IndicatorDRL::IndicatorDRL(QWidget *parent) : QWidget(parent),ui(new Ui::IndicatorDRL)
{
    ui->setupUi(this);
    ui->InputFrameFrequency->valueChanged(ui->InputFrameFrequency->value());
    //setLayout(ui->RenderLayout);
    QStringList intensity;
    ui->SelectAzimuthMarks->click();
    ui->SelectRangeMarks->click();
    //ui->SelectRangeMarks->addItems(range_marks);
    //ui->SelectRangeMarks->setCurrentIndex(1);
    ui->SelectScale->click();
    intensity<<"Слабая"<<"Средняя"<<"Сильная";
    //ui->SelectTrashIntensity->addItems(intensity);
    //ui->SelectTrashIntensity->setCurrentIndex(1);
    ui->SelectActiveNoiseIntensity->addItems(intensity);
    ui->SelectActiveNoiseIntensity->setCurrentIndex(1);

    ui->InputScatterTrashFrom->setValue(0.0f);
    ui->InputScatterTrashTo->setValue(150.0f);

    ui->ChangeIndicatorBrightness->hide();
    ui->ChangeIndicatorBrightness->valueChanged(ui->ChangeIndicatorBrightness->value());
    ui->ChangeDisplayLightning->hide();
    ui->ChangeDisplayLightning->valueChanged(ui->ChangeDisplayLightning->value());
    ui->ChangeIndicatorFocus->hide();
    ui->ChangeIndicatorFocus->valueChanged(ui->ChangeIndicatorFocus->value());
    ui->ChangeIndicatorVARU->hide();
    ui->ChangeIndicatorVARU->valueChanged(ui->ChangeIndicatorVARU->value());

    ui->CheckShowTrash->stateChanged(ui->CheckShowTrash->checkState());
    ui->ChangeTrashIntensity->valueChanged(ui->ChangeTrashIntensity->value());
    ui->CheckShowLocalItems->stateChanged(ui->CheckShowLocalItems->checkState());

    ui->InputActiveNoiseAzimuth->valueChanged(ui->InputActiveNoiseAzimuth->value());
    ui->InputActiveAnswerDistance->valueChanged(ui->InputActiveAnswerDistance->value());
    ui->InputActiveAnswerAzimuth->valueChanged(ui->InputActiveAnswerAzimuth->value());
    ui->CheckActiveInSyncShow->stateChanged(ui->CheckActiveInSyncShow->checkState());

    ui->SelectWorkVariant->click();
 }

IndicatorDRL::~IndicatorDRL()
{
    delete ui;
}

void IndicatorDRL::on_InputFrameFrequency_valueChanged(int frames_number)
{
    ui->RenderIndicator->ChangeFPS(frames_number>0 ? 1000/frames_number : 0);
}

void IndicatorDRL::on_ButtonChangeColorDisplay_clicked()
{
    //QColor c=ui->RenderIndicator->SelectColor("locator","Выберите цвет фона индикатора");
    //ui->ButtonChangeColorDisplay->setPalette(c);
}

void IndicatorDRL::on_ChangeLocatorState_clicked()
{
    quint16 fps;
    if(ui->RenderIndicator->IsActive())
    {
        fps=0;
        ui->ChangeLocatorState->setText("Продолжить");
    }
    else
    {
        fps=static_cast<quint8>(ui->InputFrameFrequency->value());
        ui->ChangeLocatorState->setText("Стоп");
    }
    ui->InputFrameFrequency->valueChanged(fps);
}

void IndicatorDRL::on_ChangeViewStateAll_clicked()
{
    if(ui->RenderIndicator->show)
    {
        ui->ChangeViewStateAll->setText("Отобразить все скрытые метки");
        ui->RenderIndicator->SetSettings("system","show",false);
    }
    else
    {
        ui->ChangeViewStateAll->setText("Вернуть состояние скрытых меток");
        ui->RenderIndicator->SetSettings("system","show",true);
    }
}

void IndicatorDRL::on_ChangeIndicatorBrightness_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderIndicator->SetSettings("system","brightness",static_cast<qreal>(value)/100);
}

void IndicatorDRL::on_ChangeDisplayLightning_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderIndicator->SetSettings("system","lightning",static_cast<qreal>(value)/100);
}

void IndicatorDRL::on_ChangeIndicatorFocus_valueChanged(int value)
{
    value=value>=0 ? value+100 : 100-value;
    ui->RenderIndicator->SetSettings("system","focus",static_cast<qreal>(value)/100);
}

void IndicatorDRL::on_ChangeIndicatorVARU_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderIndicator->SetSettings("system","varu",static_cast<qreal>(value)/100);
}

void IndicatorDRL::on_CheckShowTrash_stateChanged(int arg1)
{
    ui->RenderIndicator->SetSettings("trash","show",arg1==2);
}

void IndicatorDRL::on_RegenerateTrash_clicked()
{
    ui->RenderIndicator->GenerationTrash();
    ui->RenderIndicator->GenerationMeteo();
}

void IndicatorDRL::on_InputScatterTrashFrom_valueChanged(double arg1)
{
    qreal from=static_cast<qreal>(arg1),
          to=static_cast<qreal>(ui->InputScatterTrashTo->value());
    if(from>=to)
        ui->InputScatterTrashFrom->setMaximum(to);
    ui->InputScatterTrashTo->setMinimum(from);
    ui->RenderIndicator->SetSettings("trash","begin",from);
}

void IndicatorDRL::on_InputScatterTrashTo_valueChanged(double arg1)
{
    qreal from=static_cast<qreal>(ui->InputScatterTrashFrom->value()),
          to=static_cast<qreal>(arg1);
    if(to<=from)
        ui->InputScatterTrashTo->setMinimum(from);
    ui->InputScatterTrashFrom->setMaximum(to);
    ui->RenderIndicator->SetSettings("trash","end",to);
}

void IndicatorDRL::on_CheckShowLocalItems_stateChanged(int arg1)
{
    ui->RenderIndicator->SetSettings("local_items","show",arg1==2);
}

void IndicatorDRL::on_SelectTrashIntensity_currentIndexChanged(int index)
{
    if(index<0)
        return;
    ui->RenderIndicator->SetSettings("trash","intensity",static_cast<quint8>(index));
}

void IndicatorDRL::on_CheckActiveNoiseShow_stateChanged(int arg1)
{
    ui->RenderIndicator->SetSettings("active_noise_trash","show",static_cast<quint16>(arg1));
}

void IndicatorDRL::on_InputActiveNoiseAzimuth_valueChanged(int arg1)
{
    ui->RenderIndicator->SetSettings("active_noise_trash","azimuth",static_cast<quint16>(arg1));
}

void IndicatorDRL::on_SelectActiveNoiseIntensity_currentIndexChanged(int index)
{
    ui->RenderIndicator->SetSettings("active_noise_trash","intensity",static_cast<quint16>(index));
}

void IndicatorDRL::on_CheckActiveAnswerShow_stateChanged(int arg1)
{
    //ui->RenderIndicator->show_active_atrash=arg1==2;
}

void IndicatorDRL::on_InputActiveAnswerAzimuth_valueChanged(int arg1)
{
    ui->RenderIndicator->SetSettings("active_answer_trash","azimuth",static_cast<quint16>(arg1));
}

void IndicatorDRL::on_InputActiveAnswerDistance_valueChanged(double arg1)
{
    ui->RenderIndicator->SetSettings("active_answer_trash","distance",static_cast<qreal>(arg1));
}

void IndicatorDRL::on_CheckActiveInSyncShow_stateChanged(int arg1)
{
    //ui->RenderIndicator->show_active_isynctrash=arg1==2;
}

void IndicatorDRL::on_ButtonTargetsSettings_clicked()
{
    tsettings=new TargetsSettings;
    tsettings->show();
}

void IndicatorDRL::on_ChangeTargetsState_clicked()
{
    ui->RenderIndicator->ChangeTargetsState();
    if(ui->RenderIndicator->targets_pos<0)
        ui->ChangeTargetsState->setText(QString("Запуск целей"));
    else
        ui->ChangeTargetsState->setText(QString("Остановить цели"));
}

void IndicatorDRL::on_CleanLocatorDataBuffer_clicked()
{
    ui->RenderIndicator->CleanDataBuffer();
}

void IndicatorDRL::on_ChangeTrashIntensity_valueChanged(int value)
{
    if(value<0)
        return;
    ui->RenderIndicator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void IndicatorDRL::on_CheckShowMeteo_stateChanged(int arg1)
{
    ui->RenderIndicator->SetSettings("meteo","show",arg1==2);
}


void IndicatorDRL::on_SelectScale_clicked()
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
            ui->LabelScaleValue->setText("45 км.");
            ui->SelectScale->setStyleSheet("border-image: url(:/buttons/knob2);background-repeat: no-repeat;background-position: center;");
            max=45.0f;
            break;
        case 1:
            ui->LabelScaleValue->setText("90 км.");
            ui->SelectScale->setStyleSheet("border-image: url(:/buttons/knob);background-repeat: no-repeat;background-position: center;");
            max=90.0f;
            break;
        case 2:
            ui->LabelScaleValue->setText("150 км.");
            ui->SelectScale->setStyleSheet("border-image: url(:/buttons/knob1);background-repeat: no-repeat;background-position: center;");
            max=150.0f;
            break;
    }

    ui->RenderIndicator->SetSettings("system","scale",static_cast<quint8>(max));
    if(ui->InputScatterTrashFrom->value()>max)
        ui->InputScatterTrashFrom->setValue(max);
    if(ui->InputScatterTrashTo->value()>max)
        ui->InputScatterTrashTo->setValue(max);
    ui->InputScatterTrashFrom->setMaximum(max);
    ui->InputScatterTrashTo->setMaximum(max);
}

void IndicatorDRL::on_ChangeIndicatorBrightnessButton_clicked()
{
    if(ui->ChangeIndicatorBrightness->isHidden())
        ui->ChangeIndicatorBrightness->show();
}

void IndicatorDRL::on_ChangeIndicatorBrightness_sliderReleased()
{
    ui->ChangeIndicatorBrightness->hide();
}

void IndicatorDRL::on_ChangeDisplayLightningButton_clicked()
{
    if(ui->ChangeDisplayLightning->isHidden())
        ui->ChangeDisplayLightning->show();
}

void IndicatorDRL::on_ChangeDisplayLightning_sliderReleased()
{
    ui->ChangeDisplayLightning->hide();
}

void IndicatorDRL::on_ChangeIndicatorFocusButton_clicked()
{
    if(ui->ChangeIndicatorFocus->isHidden())
        ui->ChangeIndicatorFocus->show();
}

void IndicatorDRL::on_ChangeIndicatorFocus_sliderReleased()
{
    ui->ChangeIndicatorFocus->hide();
}

void IndicatorDRL::on_ChangeIndicatorVARUButton_clicked()
{
    if(ui->ChangeIndicatorVARU->isHidden())
        ui->ChangeIndicatorVARU->show();
}

void IndicatorDRL::on_ChangeIndicatorVARU_sliderReleased()
{
    ui->ChangeIndicatorVARU->hide();
}

void IndicatorDRL::on_SelectWorkVariant_clicked()
{
    static qint8 status=0;
    if(status<0 || status>1)
        status=0;
    else
        status++;
    switch(status)
    {
        case 0:
            ui->LabelSelectWorkVariantValue->setText("АКТ");
            ui->SelectWorkVariant->setStyleSheet("border-image: url(:/buttons/knob2);background-repeat: no-repeat;background-position: center;");
            if(ui->BoxTrashSettings->isEnabled())
                ui->BoxTrashSettings->setEnabled(false);
            if(ui->BoxActiveTrashSettings->isEnabled())
                ui->BoxActiveTrashSettings->setEnabled(false);
            break;
        case 1:
            ui->LabelSelectWorkVariantValue->setText("ПАСС");
            ui->SelectWorkVariant->setStyleSheet("border-image: url(:/buttons/knob);background-repeat: no-repeat;background-position: center;");
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
            break;
        case 2:
            ui->LabelSelectWorkVariantValue->setText("СДЦ");
            ui->SelectWorkVariant->setStyleSheet("border-image: url(:/buttons/knob1);background-repeat: no-repeat;background-position: center;");
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
            break;
    }
    ui->RenderIndicator->SetSettings("system","mode",static_cast<quint8>(status));
}

void IndicatorDRL::on_SelectRangeMarks_clicked()
{
    static qint8 status=0;
    if(status<0 || status>1)
        status=0;
    else
        status++;

    switch(status)
    {
        case 0:
            ui->LabelSelectRangeMarksValue->setText("НЕТ");
            ui->SelectRangeMarks->setStyleSheet("border-image: url(:/buttons/knob2);background-repeat: no-repeat;background-position: center;");
            break;
        case 1:
            ui->LabelSelectRangeMarksValue->setText("10 км.");
            ui->SelectRangeMarks->setStyleSheet("border-image: url(:/buttons/knob);background-repeat: no-repeat;background-position: center;");
            break;
        case 2:
            ui->LabelSelectRangeMarksValue->setText("50 км.");
            ui->SelectRangeMarks->setStyleSheet("border-image: url(:/buttons/knob1);background-repeat: no-repeat;background-position: center;");
            break;
    }
    ui->RenderIndicator->SetSettings("system","range",static_cast<quint16>(status));
}

void IndicatorDRL::on_SelectAzimuthMarks_clicked()
{
    static qint8 status=0;
    if(status<0 || status>1)
        status=0;
    else
        status++;

    switch(status)
    {
        case 0:
            ui->LabelSelectAzimuthMarksValue->setText("НЕТ");
            ui->SelectAzimuthMarks->setStyleSheet("border-image: url(:/buttons/knob2);background-repeat: no-repeat;background-position: center;");
            break;
        case 1:
            ui->LabelSelectAzimuthMarksValue->setText("30°");
            ui->SelectAzimuthMarks->setStyleSheet("border-image: url(:/buttons/knob);background-repeat: no-repeat;background-position: center;");
            break;
        case 2:
            ui->LabelSelectAzimuthMarksValue->setText("10°");
            ui->SelectAzimuthMarks->setStyleSheet("border-image: url(:/buttons/knob1);background-repeat: no-repeat;background-position: center;");
            break;
    }
    ui->RenderIndicator->SetSettings("system","azimuth",static_cast<quint16>(status));
}
