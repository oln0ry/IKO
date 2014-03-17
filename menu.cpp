#include"menu.h"
#include"ui_menu.h"

Menu::Menu(QWidget *parent) : QMainWindow(parent),ui(new Ui::Menu)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->verticalLayout);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_ButtonIndicatorDRL_clicked()
{
    //if(DRL)
      //  return;
    DRL=new IndicatorDRL;
    DRL->show();
}

void Menu::on_ButtonIndicatorPRL_clicked()
{
    PRL=new IndicatorPRL;
    PRL->show();
}

void Menu::on_ButtonRSP_clicked()
{
    RSP=new commonview;
    RSP->show();
}
