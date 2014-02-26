#ifndef RSPINDICATORS_H
#define RSPINDICATORS_H

#include <QWidget>

namespace Ui {
class RSPIndicators;
}

class RSPIndicators : public QWidget
{
    Q_OBJECT

public:
    explicit RSPIndicators(QWidget *parent = 0);
    ~RSPIndicators();

private slots:
    void on_ChangeLocatorState_clicked();

    void on_ChangeLocatorStateEquiangular_clicked();

    void on_ChangeLocatorStateRightTriangle_clicked();

private:
    Ui::RSPIndicators *ui;
};

#endif // RSPINDICATORS_H
