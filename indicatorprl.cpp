#include "indicatorprl.h"
#include "ui_indicatorprl.h"

IndicatorPRL::IndicatorPRL(QWidget *parent):QWidget(parent),ui(new Ui::IndicatorPRL)
{
    ui->setupUi(this);
    ui->RenderRightTriangleIndicator->ChangeFPS(1000/24);
    ui->RenderEquiangularIndicator->ChangeFPS(1000/24);
}

IndicatorPRL::~IndicatorPRL()
{
    delete ui;
}
