#ifndef COMMONVIEW_H
#define COMMONVIEW_H

#include<QMainWindow>

namespace Ui
{
    class CommonView;
}

class CommonView : public QMainWindow
{
    Q_OBJECT

public:
    explicit CommonView(QWidget *parent = 0);
    ~CommonView();

private slots:
    void on_ChangeMainScanAmpButton_pressed();

    void on_ChangeMainScanAmp_sliderPressed();

    void on_ChangeMainScanAmp_sliderReleased();

    void on_ChangeMainScanAmp_valueChanged(int value);

    void on_ChangeMainScanEquaButton_pressed();

    void on_ChangeMainScanEqua_sliderPressed();

    void on_ChangeMainScanEqua_sliderReleased();

    void on_ChangeMainScanEqua_valueChanged(int value);

    void on_ChangeMainOffsetVerticalButton_pressed();

    void on_ChangeMainOffsetVertical_sliderPressed();

    void on_ChangeMainOffsetVertical_sliderReleased();

    void on_ChangeMainOffsetVertical_valueChanged(int value);

    void on_ChangeMainOffsetHorizontalButton_pressed();

    void on_ChangeMainOffsetHorizontal_sliderPressed();

    void on_ChangeMainOffsetHorizontal_sliderReleased();

    void on_ChangeMainOffsetHorizontal_valueChanged(int value);

    void on_ChangeMainBrightnessRangeButton_pressed();

    void on_ChangeMainBrightnessRange_sliderPressed();

    void on_ChangeMainBrightnessRange_sliderReleased();

    void on_ChangeMainBrightnessRange_valueChanged(int value);

    void on_ChangeMainBrightnessAzimuthButton_pressed();

    void on_ChangeMainBrightnessAzimuth_sliderPressed();

    void on_ChangeMainBrightnessAzimuth_sliderReleased();

    void on_ChangeMainBrightnessAzimuth_valueChanged(int value);

    void on_ChangeMainNullSetVerticalButton_pressed();

    void on_ChangeMainNullSetVertical_sliderPressed();

    void on_ChangeMainNullSetVertical_sliderReleased();

    void on_ChangeMainNullSetVertical_valueChanged(int value);

    void on_ChangeMainNullSetHorizontalButton_pressed();

    void on_ChangeMainNullSetHorizontal_sliderPressed();

    void on_ChangeMainNullSetHorizontal_sliderReleased();

    void on_ChangeMainNullSetHorizontal_valueChanged(int value);

    void on_ChangeMainFocusButton_pressed();

    void on_ChangeMainFocus_sliderPressed();

    void on_ChangeMainFocus_sliderReleased();

    void on_ChangeMainFocus_valueChanged(int value);

    void on_ChangeMainFocusBrightnessButton_pressed();

    void on_ChangeMainFocusBrightness_sliderPressed();

    void on_ChangeMainFocusBrightness_sliderReleased();

    void on_ChangeMainFocusBrightness_valueChanged(int value);

    void on_ChangeMainTrashAKTButton_pressed();

    void on_ChangeMainTrashAKT_sliderPressed();

    void on_ChangeMainTrashAKT_sliderReleased();

    void on_ChangeMainTrashAKT_valueChanged(int value);

    void on_ChangeMainTrashPASSButton_pressed();

    void on_ChangeMainTrashPASS_sliderPressed();

    void on_ChangeMainTrashPASS_sliderReleased();

    void on_ChangeMainTrashPASS_valueChanged(int value);

    void on_SelectMainScale_clicked();

    void on_ChangeEquingularFocusButton_pressed();

    void on_ChangeEquingularFocus_sliderPressed();

    void on_ChangeEquingularFocus_sliderReleased();

    void on_ChangeEquingularFocus_valueChanged(int value);

    void on_ChangeEquingularBrightnessButton_pressed();

    void on_ChangeEquingularBrightness_sliderPressed();

    void on_ChangeEquingularBrightness_sliderReleased();

    void on_ChangeEquingularBrightness_valueChanged(int value);

    void on_ChangeEquingularTrashSDCButton_pressed();

    void on_ChangeEquingularTrashSDC_sliderPressed();

    void on_ChangeEquingularTrashSDC_sliderReleased();

    void on_ChangeEquingularTrashSDC_valueChanged(int value);

    void on_ChangeEquingularTrashPASSButton_pressed();

    void on_ChangeEquingularTrashPASS_sliderPressed();

    void on_ChangeEquingularTrashPASS_sliderReleased();

    void on_ChangeEquingularTrashPASS_valueChanged(int value);

    void on_ChangeEquingularTrashAKTButton_pressed();

    void on_ChangeEquingularTrashAKT_sliderPressed();

    void on_ChangeEquingularTrashAKT_sliderReleased();

    void on_ChangeEquingularTrashAKT_valueChanged(int value);

    void on_SelectEquingularScale_clicked();

    void on_SelectEquingularMode_clicked();

    void on_ChangeEquingularScanAmpVerticalButton_pressed();

    void on_ChangeEquingularScanAmpVertical_sliderPressed();

    void on_ChangeEquingularScanAmpVertical_sliderReleased();

    void on_ChangeEquingularScanAmpVertical_valueChanged(int value);

    void on_ChangeEquingularScanAmpHorizontalButton_pressed();

    void on_ChangeEquingularScanAmpHorizontal_sliderPressed();

    void on_ChangeEquingularScanAmpHorizontal_sliderReleased();

    void on_ChangeEquingularScanAmpHorizontal_valueChanged(int value);

    void on_ChangeEquingularOffsetVerticalButton_pressed();

    void on_ChangeEquingularOffsetVertical_sliderPressed();

    void on_ChangeEquingularOffsetVertical_sliderReleased();

    void on_ChangeEquingularOffsetVertical_valueChanged(int value);

    void on_ChangeEquingularOffsetHorizontalButton_pressed();

    void on_ChangeEquingularOffsetHorizontal_sliderPressed();

    void on_ChangeEquingularOffsetHorizontal_sliderReleased();

    void on_ChangeEquingularOffsetHorizontal_valueChanged(int value);

    void on_ChangeEquingularDirectionTrackButton_pressed();

    void on_ChangeEquingularDirectionTrack_sliderPressed();

    void on_ChangeEquingularDirectionTrack_sliderReleased();

    void on_ChangeEquingularDirectionTrack_valueChanged(int value);

    void on_ChangeEquingularDirectionGlideButton_pressed();

    void on_ChangeEquingularDirectionGlide_sliderPressed();

    void on_ChangeEquingularDirectionGlide_sliderReleased();

    void on_ChangeEquingularDirectionGlide_valueChanged(int value);

private:
    Ui::CommonView *ui;
};

#endif // COMMONVIEW_H
