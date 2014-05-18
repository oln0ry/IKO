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

    void on_ChangeRightFocusButton_pressed();

    void on_ChangeRightFocus_sliderPressed();

    void on_ChangeRightFocus_sliderReleased();

    void on_ChangeRightFocus_valueChanged(int value);

    void on_ChangeRightFocusBrightnessButton_pressed();

    void on_ChangeRightFocusBrightness_sliderPressed();

    void on_ChangeRightFocusBrightness_sliderReleased();

    void on_ChangeRightFocusBrightness_valueChanged(int value);

    void on_ChangeRightScanAmpVerticalButton_pressed();

    void on_ChangeRightScanAmpVertical_sliderPressed();

    void on_ChangeRightScanAmpVertical_sliderReleased();

    void on_ChangeRightScanAmpVertical_valueChanged(int value);

    void on_ChangeRightScanAmpHorizontalButton_pressed();

    void on_ChangeRightScanAmpHorizontal_sliderPressed();

    void on_ChangeRightScanAmpHorizontal_sliderReleased();

    void on_ChangeRightScanAmpHorizontal_valueChanged(int value);

    void on_ChangeRightOffsetVerticalButton_pressed();

    void on_ChangeRightOffsetVertical_sliderPressed();

    void on_ChangeRightOffsetVertical_sliderReleased();

    void on_ChangeRightOffsetVertical_valueChanged(int value);

    void on_ChangeRightOffsetHorizontalButton_pressed();

    void on_ChangeRightOffsetHorizontal_sliderPressed();

    void on_ChangeRightOffsetHorizontal_sliderReleased();

    void on_ChangeRightOffsetHorizontal_valueChanged(int value);

    void on_ChangeRightDirectionTrackButton_pressed();

    void on_ChangeRightDirectionTrack_sliderPressed();

    void on_ChangeRightDirectionTrack_sliderReleased();

    void on_ChangeRightDirectionTrack_valueChanged(int value);

    void on_ChangeRightDirectionGlideButton_pressed();

    void on_ChangeRightDirectionGlide_sliderPressed();

    void on_ChangeRightDirectionGlide_sliderReleased();

    void on_ChangeRightDirectionGlide_valueChanged(int value);

    void on_ChangeRightBrightnessRangeButton_pressed();

    void on_ChangeRightBrightnessRange_sliderPressed();

    void on_ChangeRightBrightnessRange_sliderReleased();

    void on_ChangeRightBrightnessRange_valueChanged(int value);

    void on_ChangeRightBrightnessAzimuthButton_pressed();

    void on_ChangeRightBrightnessAzimuth_sliderPressed();

    void on_ChangeRightBrightnessAzimuth_sliderReleased();

    void on_ChangeRightBrightnessAzimuth_valueChanged(int value);

private:
    Ui::CommonView *ui;
};

#endif // COMMONVIEW_H
