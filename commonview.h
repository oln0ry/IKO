#ifndef COMMONVIEW_H
#define COMMONVIEW_H

#include<QWidget>
#include<QPointer>
#include"targetssettings.h"

namespace Ui {
class commonview;
}

class commonview : public QWidget
{
    Q_OBJECT

public:
    explicit commonview(QWidget *parent = 0);
    ~commonview();

private slots:
    void on_ChangeMainLocatorFocus_pressed();

    void on_ChangeMainLocatorFocusSlider_valueChanged(int value);

    void on_ChangeMainLocatorFocusSlider_sliderReleased();

    void on_ChangeMainLocatorFocusSlider_sliderPressed();

    void on_ChangeMainLocatorBrightness_pressed();

    void on_ChangeMainLocatorBrightnessSlider_sliderPressed();

    void on_ChangeMainLocatorBrightnessSlider_valueChanged(int value);

    void on_ChangeMainLocatorBrightnessSlider_sliderReleased();

    void on_ChangeMainLocatorMagnificationAKT_pressed();

    void on_ChangeMainLocatorMagnificationAKTSlider_valueChanged(int value);

    void on_ChangeMainLocatorMagnificationAKTSlider_sliderReleased();

    void on_ChangeMainLocatorMagnificationAKTSlider_sliderPressed();

    void on_ChangeMainLocatorMagnificationPASSSlider_valueChanged(int value);

    void on_ChangeMainLocatorMagnificationPASS_pressed();

    void on_ChangeMainLocatorMagnificationPASSSlider_sliderReleased();

    void on_ChangeMainLocatorMagnificationPASSSlider_sliderPressed();

    void on_ChangeMainLocatorScale_clicked();

    void on_ChangeEquingularLocatorMagnificationSDC_pressed();

    void on_ChangeEquingularLocatorMagnificationSDCSlider_valueChanged(int value);

    void on_ChangeEquingularLocatorMagnificationSDCSlider_sliderReleased();

    void on_ChangeEquingularLocatorMagnificationSDCSlider_sliderPressed();

    void on_ChangeMainLocatorScale_pressed();

    void on_ChangeMainLocatorScale_released();

    void on_ChangeEquingularLocatorScale_clicked();

    void on_ChangeEquingularLocatorScale_pressed();

    void on_ChangeEquingularLocatorScale_released();

    void on_ChangeEquingularLocatorMode_clicked();

    void on_ChangeEquingularLocatorMode_pressed();

    void on_ChangeEquingularLocatorMode_released();

    void on_ChangeRightTriangleBrightnessMarksRange_pressed();

    void on_ChangeRightTriangleBrightnessMarksRangeSlider_valueChanged(int value);

    void on_ChangeRightTriangleBrightnessMarksRangeSlider_sliderPressed();

    void on_ChangeRightTriangleBrightnessMarksRangeSlider_sliderReleased();

    void on_ChangeRightTriangleBrightnessMarksAzimuth_pressed();

    void on_ChangeRightTriangleBrightnessMarksAzimuthSlider_valueChanged(int value);

    void on_ChangeRightTriangleBrightnessMarksAzimuthSlider_sliderPressed();

    void on_ChangeRightTriangleBrightnessMarksAzimuthSlider_sliderReleased();

    void on_ChangeRightTriangleFocus_pressed();

    void on_ChangeRightTriangleFocusSlider_valueChanged(int value);

    void on_ChangeRightTriangleFocusSlider_sliderPressed();

    void on_ChangeRightTriangleFocusSlider_sliderReleased();

    void on_ChangeRightTriangleBrightness_pressed();

    void on_ChangeRightTriangleBrightnessSlider_valueChanged(int value);

    void on_ChangeRightTriangleBrightnessSlider_sliderPressed();

    void on_ChangeRightTriangleBrightnessSlider_sliderReleased();

    void on_SetTargetsSettings_clicked();

    void on_ChangeEquingularLocatorMagnificationPASS_pressed();

    void on_ChangeEquingularLocatorMagnificationPASSSlider_valueChanged(int value);

    void on_ChangeEquingularLocatorMagnificationPASSSlider_sliderPressed();

    void on_ChangeEquingularLocatorMagnificationPASSSlider_sliderReleased();

    void on_ChangeEquingularLocatorMagnificationAKT_pressed();

    void on_ChangeEquingularLocatorMagnificationAKTSlider_valueChanged(int value);

    void on_ChangeEquingularLocatorMagnificationAKTSlider_sliderPressed();

    void on_ChangeEquingularLocatorMagnificationAKTSlider_sliderReleased();

    void on_CheckActiveNoiseShow_stateChanged(int arg1);

    void on_InputActiveNoiseAzimuth_valueChanged(int arg1);

    void on_SelectActiveNoiseIntensity_currentIndexChanged(int index);

private:
    QPointer<TargetsSettings>tsettings;
    Ui::commonview *ui;
};

#endif // COMMONVIEW_H
