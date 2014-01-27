#include"indicatordrl.h"
#include"ui_indicatordrl.h"
#include"QDebug"
IndicatorDRL::IndicatorDRL(QWidget *parent) : QWidget(parent),ui(new Ui::IndicatorDRL)
{
    ui->setupUi(this);
    ui->InputFrameFrequency->valueChanged(ui->InputFrameFrequency->value());
    //setLayout(ui->RenderLayout);
    QStringList azimuth_marks,range_marks,scale,intensity;
    azimuth_marks<<"Не отображать"<<"30°"<<"10°";
    ui->SelectAzimuthMarks->addItems(azimuth_marks);
    ui->SelectAzimuthMarks->setCurrentIndex(1);
    range_marks<<"Не отображать"<<"10 километров"<<"50 километров";
    ui->SelectRangeMarks->addItems(range_marks);
    ui->SelectRangeMarks->setCurrentIndex(1);
    scale<<"150 километров"<<"300 километров"<<"400 километров";
    ui->SelectScale->addItems(scale);
    ui->SelectScale->setCurrentIndex(0);
    intensity<<"Слабая"<<"Умеренная"<<"Сильная";
    ui->SelectTrashIntensity->addItems(intensity);
    ui->SelectTrashIntensity->setCurrentIndex(1);
    ui->SelectActiveNoiseIntensity->addItems(intensity);
    ui->SelectActiveNoiseIntensity->setCurrentIndex(1);
    ui->RenderIndicator->show=false;
}

IndicatorDRL::~IndicatorDRL()
{
    delete ui;
}

void IndicatorDRL::on_InputFrameFrequency_valueChanged(int frames_number)
{
    ui->RenderIndicator->ChangeFPS(1000/frames_number);
}

void IndicatorDRL::on_ButtonChangeColorDisplay_clicked()
{
    QColor c=ui->RenderIndicator->SelectColor("locator","Выберите цвет фона индикатора");
    ui->ButtonChangeColorDisplay->setPalette(c);
}

void IndicatorDRL::on_SelectAzimuthMarks_currentIndexChanged(int index)
{
    ui->RenderIndicator->SetSettings("azimuth_marks",static_cast<quint8>(index));
}

void IndicatorDRL::on_SelectRangeMarks_currentIndexChanged(int index)
{
    ui->RenderIndicator->SetSettings("range_marks",static_cast<quint8>(index));
}

void IndicatorDRL::on_SelectScale_currentIndexChanged(int index)
{
    ui->RenderIndicator->SetSettings("scale",static_cast<quint8>(index));
    qreal max;
    switch(index)
    {
        case 2:
            max=400.0f;
            break;
        case 1:
            max=300.0f;
            break;
        default:
            max=150.0f;
    }
    if(ui->InputScatterTrashFrom->value()>max)
        ui->InputScatterTrashFrom->setValue(max);
    if(ui->InputScatterTrashTo->value()>max)
        ui->InputScatterTrashTo->setValue(max);
    ui->InputScatterTrashFrom->setMaximum(max);
    ui->InputScatterTrashTo->setMaximum(max);
}

void IndicatorDRL::on_ChangeLocatorState_clicked()
{
    qreal fps;
    if(ui->RenderIndicator->IsActive())
    {
        fps=0.0f;
        ui->ChangeLocatorState->setText("Продолжить");
    }
    else
    {
        fps=static_cast<qreal>(ui->InputFrameFrequency->value());
        ui->ChangeLocatorState->setText("Стоп");
    }
    ui->RenderIndicator->ChangeFPS(fps);
}

void IndicatorDRL::on_ChangeViewStateAll_clicked()
{
    if(ui->RenderIndicator->show)
    {
        ui->ChangeViewStateAll->setText("Отобразить все скрытые метки");
        ui->RenderIndicator->show=false;
    }
    else
    {
        ui->ChangeViewStateAll->setText("Вернуть состояние скрытых меток");
        ui->RenderIndicator->show=true;
    }
}

void IndicatorDRL::on_ChangeIndicatorBrightness_valueChanged(int value)
{
    ui->RenderIndicator->SetSettings("brightness",static_cast<qreal>(value)/100);
}

void IndicatorDRL::on_ChangeDisplayLightning_valueChanged(int value)
{
    ui->RenderIndicator->SetSettings("interval",static_cast<qreal>(value)/100);
}

void IndicatorDRL::on_ChangeIndicatorFocus_valueChanged(int value)
{
    ui->RenderIndicator->SetSettings("focus",static_cast<qreal>(value)/100);
}

void IndicatorDRL::on_ChangeIndicatorVARU_valueChanged(int value)
{
    ui->RenderIndicator->SetSettings("varu",static_cast<qreal>(value)/100);
}

void IndicatorDRL::on_CheckShowTrash_stateChanged(int arg1)
{
    ui->RenderIndicator->show_trash=arg1==2 ? true : false;
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
    ui->RenderIndicator->SetSettings("trash_begin",from);
}

void IndicatorDRL::on_InputScatterTrashTo_valueChanged(double arg1)
{
    qreal from=static_cast<qreal>(ui->InputScatterTrashFrom->value()),
          to=static_cast<qreal>(arg1);
    if(to<=from)
        ui->InputScatterTrashTo->setMinimum(from);
    ui->InputScatterTrashFrom->setMaximum(to);
    ui->RenderIndicator->SetSettings("trash_end",to);
}

void IndicatorDRL::on_CheckShowLocalItems_stateChanged(int arg1)
{

}
