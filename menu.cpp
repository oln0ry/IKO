#include"menu.h"
#include"ui_menu.h"

Menu::Menu(QWidget *parent) : QMainWindow(parent),ui(new Ui::Menu)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->verticalLayout);
    ui->ButtonIndicatorPRL->hide();
    ui->ButtonRSP->hide();
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
