#ifndef INDICATORDRL_H
#define INDICATORDRL_H

#include<QMainWindow>
#include<QPointer>
#include"targetssettings.h"

namespace Ui
{
    class IndicatorDRL;
}

class IndicatorDRL : public QMainWindow
{
    Q_OBJECT

    public:
        explicit IndicatorDRL(QWidget *parent = 0);
        ~IndicatorDRL();

    private slots:
        void on_SelectAzimuthMarks_clicked();
        void on_SelectRangeMarks_clicked();
        void on_SelectScale_clicked();
        void on_ChangeIndicatorBrightnessButton_pressed();
        void on_ChangeIndicatorBrightness_sliderPressed();
        void on_ChangeIndicatorBrightness_sliderReleased();
        void on_ChangeIndicatorBrightness_valueChanged(int value);
        void on_ChangeIndicatorLightningButton_pressed();
        void on_ChangeIndicatorLightning_sliderPressed();
        void on_ChangeIndicatorLightning_sliderReleased();
        void on_ChangeIndicatorLightning_valueChanged(int value);
        void on_ChangeIndicatorFocusButton_pressed();
        void on_ChangeIndicatorFocus_sliderPressed();
        void on_ChangeIndicatorFocus_sliderReleased();
        void on_ChangeIndicatorFocus_valueChanged(int value);
        void on_ChangeIndicatorVARUButton_pressed();
        void on_ChangeIndicatorVARU_sliderPressed();
        void on_ChangeIndicatorVARU_sliderReleased();
        void on_ChangeIndicatorVARU_valueChanged(int value);
        void on_SelectWorkVariant_clicked();
        void on_ChangeViewStateAll_clicked();
        void on_ChangeLocatorState_clicked();
        void on_SetTargetsSettings_clicked();
        void on_ChangeTrashIntensityButton_pressed();
        void on_ChangeTrashIntensity_sliderPressed();
        void on_ChangeTrashIntensity_sliderReleased();
        void on_ChangeTrashIntensity_valueChanged(int value);
        void on_InputScatterTrashFrom_valueChanged(double arg1);
        void on_InputScatterTrashTo_valueChanged(double arg1);
        void on_RegenerateTrash_clicked();
        void on_CheckShowLocalItems_stateChanged(int arg1);
        void on_CheckShowMeteo_stateChanged(int arg1);

        void on_InputActiveNoiseAzimuth_valueChanged(int arg1);

        void on_SelectActiveNoiseIntensity_currentIndexChanged(int index);

        void on_CheckActiveNoiseShow_stateChanged(int arg1);

        void on_InputActiveAnswerAzimuth_valueChanged(int arg1);

        void on_InputActiveAnswerDistance_valueChanged(double arg1);

        void on_CheckActiveAnswerShow_stateChanged(int arg1);

        void on_CheckActiveInSyncShow_stateChanged(int arg1);

protected:
        bool eventFilter(QObject *O,QEvent *E);
        void resizeEvent(QResizeEvent *E);

private:
        Ui::IndicatorDRL *ui;
        QPointer<TargetsSettings>tsettings;
        unsigned int change_view_bottom;
};

#endif // INDICATORDRL_H
