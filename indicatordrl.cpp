#include"indicatordrl.h"
#include"ui_indicatordrl.h"
#include<QDebug>
IndicatorDRL::IndicatorDRL(QWidget *parent) : QWidget(parent),ui(new Ui::IndicatorDRL)
{
    ui->setupUi(this);
    ui->InputFrameFrequency->valueChanged(ui->InputFrameFrequency->value());
    //setLayout(ui->RenderLayout);
    QStringList azimuth_marks,range_marks,scale,intensity,work_variants;
    azimuth_marks<<"Не отображать"<<"30°"<<"10°";
    ui->SelectAzimuthMarks->addItems(azimuth_marks);
    ui->SelectAzimuthMarks->setCurrentIndex(1);
    range_marks<<"Не отображать"<<"10 километров"<<"50 километров";
    ui->SelectRangeMarks->addItems(range_marks);
    ui->SelectRangeMarks->setCurrentIndex(1);
    //scale<<"150 километров"<<"300 километров"<<"400 километров";
    scale<<"45 километров"<<"90 километров"<<"150 километров";
    ui->SelectScale->addItems(scale);
    ui->SelectScale->setCurrentIndex(0);
    intensity<<"Слабая"<<"Средняя"<<"Сильная";
    //ui->SelectTrashIntensity->addItems(intensity);
    //ui->SelectTrashIntensity->setCurrentIndex(1);
    ui->SelectActiveNoiseIntensity->addItems(intensity);
    ui->SelectActiveNoiseIntensity->setCurrentIndex(1);

    ui->InputScatterTrashFrom->setValue(0.0f);
    ui->InputScatterTrashTo->setValue(150.0f);

    ui->ChangeIndicatorBrightness->valueChanged(ui->ChangeIndicatorBrightness->value());
    ui->ChangeDisplayLightning->valueChanged(ui->ChangeDisplayLightning->value());
    ui->ChangeIndicatorFocus->valueChanged(ui->ChangeIndicatorFocus->value());
    ui->ChangeIndicatorVARU->valueChanged(ui->ChangeIndicatorVARU->value());

    ui->CheckShowTrash->stateChanged(ui->CheckShowTrash->checkState());
    ui->ChangeTrashIntensity->valueChanged(ui->ChangeTrashIntensity->value());

    ui->InputActiveNoiseAzimuth->valueChanged(ui->InputActiveNoiseAzimuth->value());
    ui->InputActiveAnswerDistance->valueChanged(ui->InputActiveAnswerDistance->value());
    ui->InputActiveAnswerAzimuth->valueChanged(ui->InputActiveAnswerAzimuth->value());
    ui->CheckActiveInSyncShow->stateChanged(ui->CheckActiveInSyncShow->checkState());
    ui->RenderIndicator->show=false;
    //ui->LabelTargetsSettings->hide();
    //ui->ButtonTargetsSettings->hide();
    ui->LabelColorIndicator->hide();
    ui->ButtonChangeColorDisplay->hide();
    ui->SelectTrashIntensity->hide();
    work_variants<<"Активный"<<"Пассивный"<<"СДЦ";
    ui->SelectWorkVariant->addItems(work_variants);
    ui->SelectWorkVariant->setCurrentIndex(0);
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
    QColor c=ui->RenderIndicator->SelectColor("locator","Выберите цвет фона индикатора");
    ui->ButtonChangeColorDisplay->setPalette(c);
}

void IndicatorDRL::on_SelectAzimuthMarks_currentIndexChanged(int index)
{
    if(index<0)
        return;
    ui->RenderIndicator->SetSettings("system","azimuth",static_cast<quint16>(index));
}

void IndicatorDRL::on_SelectRangeMarks_currentIndexChanged(int index)
{
    if(index<0)
        return;
    ui->RenderIndicator->SetSettings("system","range",static_cast<quint16>(index));
}

void IndicatorDRL::on_SelectScale_currentIndexChanged(int index)
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
    ui->RenderIndicator->SetSettings("system","scale",static_cast<quint8>(max));
    if(ui->InputScatterTrashFrom->value()>max)
        ui->InputScatterTrashFrom->setValue(max);
    if(ui->InputScatterTrashTo->value()>max)
        ui->InputScatterTrashTo->setValue(max);
    ui->InputScatterTrashFrom->setMaximum(max);
    ui->InputScatterTrashTo->setMaximum(max);
}

void IndicatorDRL::on_ChangeLocatorState_clicked()
{
    quint8 fps;
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
    //ui->RenderIndicator->ChangeFPS(fps);
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
    if(value<0)
        return;
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
    ui->RenderIndicator->show_local_items=arg1==2;
}

void IndicatorDRL::on_SelectTrashIntensity_currentIndexChanged(int index)
{
    ui->RenderIndicator->SetSettings("trash","intensity",static_cast<quint8>(index));
}

void IndicatorDRL::on_CheckActiveNoiseShow_stateChanged(int arg1)
{
    ui->RenderIndicator->show_active_ntrash=arg1==2;
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
    ui->RenderIndicator->show_active_atrash=arg1==2;
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
    ui->RenderIndicator->show_active_isynctrash=arg1==2;
}

void IndicatorDRL::on_ButtonTargetsSettings_clicked()
{
    //if(tsettings)
      //  return;
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
    ui->RenderIndicator->SetSettings("trash","intensity",static_cast<quint8>(value));
}

void IndicatorDRL::on_CheckShowMeteo_stateChanged(int arg1)
{
    ui->RenderIndicator->show_meteo=arg1==2;
}
