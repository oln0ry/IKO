#ifndef RSPINDICATORS_H
#define RSPINDICATORS_H

#include<QMainWindow>

namespace Ui
{
    class RSPIndicators;
}

class RSPIndicators : public QMainWindow
{
    Q_OBJECT

    public:
        explicit RSPIndicators(QWidget *parent = 0);
        ~RSPIndicators();

    private slots:
        void on_ChangeMainTrashIntensityButton_pressed();

        void on_ChangeMainTrashIntensity_sliderPressed();

        void on_ChangeMainTrashIntensity_sliderReleased();

        void on_ChangeMainTrashIntensity_valueChanged(int value);

        void on_SelectMainAzimuthMarks_clicked();

        void on_SelectMainRangeMarks_clicked();

        void on_SelectMainScale_clicked();

        void on_ChangeMainBrightnessButton_pressed();

        void on_ChangeMainBrightness_sliderPressed();

        void on_ChangeMainBrightness_sliderReleased();

        void on_ChangeMainBrightness_valueChanged(int value);

        void on_ChangeMainLightningButton_pressed();

        void on_ChangeMainLightning_sliderPressed();

        void on_ChangeMainLightning_sliderReleased();

        void on_ChangeMainLightning_valueChanged(int value);

        void on_ChangeMainFocusButton_pressed();

        void on_ChangeMainFocus_sliderPressed();

        void on_ChangeMainFocus_sliderReleased();

        void on_ChangeMainFocus_valueChanged(int value);

        void on_ChangeMainVARUButton_pressed();

        void on_ChangeMainVARU_sliderPressed();

        void on_ChangeMainVARU_sliderReleased();

        void on_ChangeMainVARU_valueChanged(int value);

        void on_ChangeMainViewStateAll_clicked();

        void on_ChangeMainLocatorState_clicked();

        void on_ChangeEquiangularTrashIntensityButton_pressed();

        void on_ChangeEquiangularTrashIntensity_sliderPressed();

        void on_ChangeEquiangularTrashIntensity_sliderReleased();

        void on_ChangeEquiangularTrashIntensity_valueChanged(int value);

        void on_SelectEquiangularRangeMarks_clicked();

        void on_SelectEquiangularScale_clicked();

        void on_ChangeEquiangularBrightnessButton_pressed();

        void on_ChangeEquiangularBrightness_sliderPressed();

        void on_ChangeEquiangularBrightness_sliderReleased();

        void on_ChangeEquiangularBrightness_valueChanged(int value);

        void on_ChangeEquiangularLightningButton_pressed();

        void on_ChangeEquiangularLightning_sliderPressed();

        void on_ChangeEquiangularLightning_sliderReleased();

        void on_ChangeEquiangularLightning_valueChanged(int value);

        void on_ChangeEquiangularFocusButton_pressed();

        void on_ChangeEquiangularFocus_sliderPressed();

        void on_ChangeEquiangularFocus_sliderReleased();

        void on_ChangeEquiangularFocus_valueChanged(int value);

        void on_ChangeEquiangularVARUButton_pressed();

        void on_ChangeEquiangularVARU_sliderPressed();

        void on_ChangeEquiangularVARU_sliderReleased();

        void on_ChangeEquiangularVARU_valueChanged(int value);

        void on_ChangeEquingularViewStateAll_clicked();

        void on_ChangeEquingularState_clicked();

        void on_ChangeRightTrashIntensityButton_pressed();

        void on_ChangeRightTrashIntensity_sliderPressed();

        void on_ChangeRightTrashIntensity_sliderReleased();

        void on_ChangeRightTrashIntensity_valueChanged(int value);

        void on_SelectRightRangeMarks_clicked();

        void on_SelectRightScale_clicked();

        void on_ChangeRightBrightnessButton_pressed();

        void on_ChangeRightBrightness_sliderPressed();

        void on_ChangeRightBrightness_sliderReleased();

        void on_ChangeRightBrightness_valueChanged(int value);

        void on_ChangeRightLightningButton_pressed();

        void on_ChangeRightLightning_sliderPressed();

        void on_ChangeRightLightning_sliderReleased();

        void on_ChangeRightLightning_valueChanged(int value);

        void on_ChangeRightFocusButton_pressed();

        void on_ChangeRightFocus_sliderPressed();

        void on_ChangeRightFocus_sliderReleased();

        void on_ChangeRightFocus_valueChanged(int value);

        void on_ChangeRightVARUButton_pressed();

        void on_ChangeRightVARU_sliderPressed();

        void on_ChangeRightVARU_sliderReleased();

        void on_ChangeRightVARU_valueChanged(int value);

        void on_ChangeRightViewStateAll_clicked();

        void on_ChangeRightState_clicked();

protected:
        bool eventFilter(QObject *O,QEvent *E);

private:
        Ui::RSPIndicators *ui;
};

#endif // RSPINDICATORS_H
