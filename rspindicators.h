#ifndef RSPINDICATORS_H
#define RSPINDICATORS_H

#include<QWidget>
#include<QPointer>
#include"targetssettings.h"

namespace Ui {
class RSPIndicators;
}

class RSPIndicators:public QWidget
{
    Q_OBJECT

    public:
        explicit RSPIndicators(QWidget *parent = 0);
        ~RSPIndicators();

    private slots:
    void on_ChangeLocatorState_clicked();

    void on_ChangeLocatorStateEquiangular_clicked();

    void on_ChangeLocatorStateRightTriangle_clicked();

    void on_ChangeViewStateAll_clicked();

    void on_ChangeViewStateAllEquiangular_clicked();

    void on_ChangeViewStateAllRightTriangle_clicked();

    void on_ButtonTargetsSettings_clicked();

    void on_SelectRangeMarksEquiangular_currentIndexChanged(int index);

    void on_SelectRangeMarksRightTriangle_currentIndexChanged(int index);

    void on_SelectScaleEquiangular_currentIndexChanged(int index);

    void on_SelectScaleRightTriangle_currentIndexChanged(int index);

    void on_SelectRangeMarks_currentIndexChanged(int index);

    void on_SelectScale_currentIndexChanged(int index);

    void on_SelectWorkVariant_currentIndexChanged(int index);

    void on_SelectAzimuthMarks_currentIndexChanged(int index);

    void on_ChangeIndicatorVARU_valueChanged(int value);

    void on_ChangeIndicatorFocusEquiangular_valueChanged(int value);

    void on_ChangeIndicatorFocusRightTriangle_valueChanged(int value);

    void on_ChangeIndicatorFocus_valueChanged(int value);

    void on_ChangeIndicatorBrightnessEquiangular_valueChanged(int value);

    void on_ChangeIndicatorBrightnessRightTriangle_valueChanged(int value);

    void on_ChangeIndicatorBrightness_valueChanged(int value);

    void on_ChangeDisplayLightning_valueChanged(int value);

    void on_ChangeTrashIntensityEquiangular_valueChanged(int value);

    void on_ChangeTrashIntensityRightTriangle_valueChanged(int value);

    void on_ChangeTrashIntensity_valueChanged(int value);

    void on_ChangeLightningEquiangular_valueChanged(int value);

    void on_ChangeLightningRightTriangle_valueChanged(int value);

    void on_ChangeIndicatorVARUEquiangular_valueChanged(int value);

    void on_ChangeIndicatorVARURightTriangle_valueChanged(int value);

    void on_SelectActiveNoiseTrashIntensity_currentIndexChanged(int index);

private:
    QPointer<TargetsSettings>tsettings;
    Ui::RSPIndicators *ui;
};

#endif // RSPINDICATORS_H
