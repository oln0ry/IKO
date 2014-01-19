#ifndef MENU_H
#define MENU_H

#include<QMainWindow>
#include<QPointer>
#include"indicatordrl.h"

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

    private:
        Ui::Menu *ui;
        QPointer<IndicatorDRL>DRL;
};

#endif // MENU_H
