#include "commonview.h"
#include "ui_commonview.h"

commonview::commonview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::commonview)
{
    ui->setupUi(this);
}

commonview::~commonview()
{
    delete ui;
}
