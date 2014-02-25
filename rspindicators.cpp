#include "rspindicators.h"
#include "ui_rspindicators.h"

RSPIndicators::RSPIndicators(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSPIndicators)
{
    ui->setupUi(this);
}

RSPIndicators::~RSPIndicators()
{
    delete ui;
}
