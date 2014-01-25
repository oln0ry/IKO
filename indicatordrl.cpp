#include"indicatordrl.h"
#include"ui_indicatordrl.h"

IndicatorDRL::IndicatorDRL(QWidget *parent) : QWidget(parent),ui(new Ui::IndicatorDRL)
{
    ui->setupUi(this);
    ui->InputFrameFrequency->valueChanged(ui->InputFrameFrequency->value());
    //setLayout(ui->RenderLayout);
    QStringList azimuth_marks,range_marks,scale;
    azimuth_marks<<"Не отображать"<<"30°"<<"10°+30°";
    ui->SelectAzimuthMarks->addItems(azimuth_marks);
    ui->SelectAzimuthMarks->setCurrentIndex(1);
    range_marks<<"Не отображать"<<"10 + 50 километров"<<"50 километров";
    ui->SelectRangeMarks->addItems(range_marks);
    ui->SelectRangeMarks->setCurrentIndex(1);
    scale<<"150 километров"<<"300 километров"<<"300 километров";
    ui->SelectScale->addItems(scale);
    ui->SelectScale->setCurrentIndex(0);
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
    ui->ButtonChangeColorDisplay->setPalette(ui->RenderIndicator->SelectColor("locator","Выберите цвет фона индикатора"));
}

void IndicatorDRL::on_SelectAzimuthMarks_currentIndexChanged(int index)
{
    ui->RenderIndicator->SetSettings("azimuth_marks",index);
}

void IndicatorDRL::on_SelectRangeMarks_currentIndexChanged(int index)
{
    ui->RenderIndicator->SetSettings("range_marks",index);
}

void IndicatorDRL::on_SelectScale_currentIndexChanged(int index)
{
    ui->RenderIndicator->SetSettings("scale",index);
}
