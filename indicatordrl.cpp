#include"indicatordrl.h"
#include"ui_indicatordrl.h"

IndicatorDRL::IndicatorDRL(QWidget *parent) : QWidget(parent),ui(new Ui::IndicatorDRL)
{
    ui->setupUi(this);
}

IndicatorDRL::~IndicatorDRL()
{
    delete ui;
}
