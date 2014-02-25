#include "indicatorprl.h"
#include "ui_indicatorprl.h"

IndicatorPRL::IndicatorPRL(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndicatorPRL)
{
    ui->setupUi(this);
}

IndicatorPRL::~IndicatorPRL()
{
    delete ui;
}
