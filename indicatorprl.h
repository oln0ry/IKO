#ifndef INDICATORPRL_H
#define INDICATORPRL_H

#include <QWidget>

namespace Ui {
class IndicatorPRL;
}

class IndicatorPRL : public QWidget
{
    Q_OBJECT

public:
    explicit IndicatorPRL(QWidget *parent = 0);
    ~IndicatorPRL();

private slots:
    void on_SelectScaleEquiangular_currentIndexChanged(int index);

    void on_SelectRangeMarksEquiangular_currentIndexChanged(int index);

    void on_ChangeTrashIntensityEquiangular_valueChanged(int value);

    void on_ChangeIndicatorBrightnessEquiangular_valueChanged(int value);

    void on_ChangeIndicatorFocusEquiangular_valueChanged(int value);

    void on_ChangeLocatorStateEquiangular_clicked();

    void on_ChangeViewStateAllEquiangular_clicked();

    void on_ChangeDisplayLightningEquiangular_valueChanged(int value);

    void on_ChangeIndicatorVARUEquiangular_valueChanged(int value);

    void on_ChangeLocatorStateRightTriangle_clicked();

private:
    Ui::IndicatorPRL *ui;
};

#endif // INDICATORPRL_H
