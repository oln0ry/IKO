#ifndef MENU_H
#define MENU_H

#include<QMainWindow>
#include<QPointer>
#include"indicatordrl.h"
#include"indicatorprl.h"
#include"rspindicators.h"

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_ButtonIndicatorDRL_clicked();

    void on_ButtonIndicatorPRL_clicked();

    void on_ButtonRSP_clicked();

private:
        Ui::Menu *ui;
        QPointer<IndicatorDRL>DRL;
        QPointer<IndicatorPRL>PRL;
        QPointer<RSPIndicators>RSP;
};

#endif // MENU_H
