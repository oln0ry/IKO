#ifndef INDICATORPRL_H
#define INDICATORPRL_H

#include<QMainWindow>

namespace Ui
{
    class IndicatorPRL;
}

class IndicatorPRL : public QMainWindow
{
    Q_OBJECT

    public:
        explicit IndicatorPRL(QWidget *parent=0);
        ~IndicatorPRL();

    private slots:
        void on_SelectEquingularRangeMarks_clicked();
        void on_ChangeEquingularTrashIntensityButton_pressed();
        void on_ChangeEquingularTrashIntensity_sliderPressed();
        void on_ChangeEquingularTrashIntensity_sliderReleased();
        void on_ChangeEquingularTrashIntensity_valueChanged(int value);
        void on_ChangeEquingularBrightnessButton_pressed();
        void on_ChangeEquingularBrightness_sliderPressed();
        void on_ChangeEquingularBrightness_sliderReleased();
        void on_ChangeEquingularBrightness_valueChanged(int value);
        void on_ChangeEquingularLightningButton_pressed();
        void on_ChangeEquingularLightning_sliderPressed();
        void on_ChangeEquingularLightning_sliderReleased();
        void on_ChangeEquingularLightning_valueChanged(int value);
        void on_ChangeEquingularFocusButton_pressed();
        void on_ChangeEquingularFocus_sliderPressed();
        void on_ChangeEquingularFocus_sliderReleased();
        void on_ChangeEquingularFocus_valueChanged(int value);
        void on_ChangeEquingularVARUButton_pressed();
        void on_ChangeEquingularVARU_sliderPressed();
        void on_ChangeEquingularVARU_sliderReleased();
        void on_ChangeEquingularVARU_valueChanged(int value);
        void on_SelectEquingularScale_clicked();
        void on_ChangeEquingularViewStateAll_clicked();
        void on_ChangeEquingularState_clicked();
        void on_SelectRightRangeMarks_clicked();
        void on_ChangeRightTrashIntensityButton_pressed();
        void on_ChangeRightTrashIntensity_sliderPressed();
        void on_ChangeRightTrashIntensity_sliderReleased();
        void on_ChangeRightTrashIntensity_valueChanged(int value);
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
        void on_SelectRightScale_clicked();
        void on_ChangeRightViewStateAll_clicked();
        void on_ChangeRightState_clicked();

    protected:
        bool eventFilter(QObject *O,QEvent *E);

    private:
        Ui::IndicatorPRL *ui;
};

#endif // INDICATORPRL_H
