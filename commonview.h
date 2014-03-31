#ifndef COMMONVIEW_H
#define COMMONVIEW_H

#include <QWidget>

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

private:
    Ui::commonview *ui;
};

#endif // COMMONVIEW_H
