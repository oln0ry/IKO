#ifndef INDICATORDRL_H
#define INDICATORDRL_H

#include <QWidget>

namespace Ui
{
    class IndicatorDRL;
}

class IndicatorDRL : public QWidget
{
    Q_OBJECT

    public:
        explicit IndicatorDRL(QWidget *parent = 0);
        ~IndicatorDRL();

private slots:
    void on_InputFrameFrequency_valueChanged(int arg1);

    void on_ButtonChangeColorDisplay_clicked();

    void on_SelectAzimuthMarks_currentIndexChanged(int index);

    void on_SelectRangeMarks_currentIndexChanged(int index);

    void on_SelectScale_currentIndexChanged(int index);

    void on_ChangeLocatorState_clicked();

    void on_ChangeViewStateAll_clicked();

    void on_ChangeIndicatorBrightness_valueChanged(int value);

    void on_ChangeDisplayLightning_valueChanged(int value);

    void on_ChangeIndicatorFocus_valueChanged(int value);

    void on_ChangeIndicatorVARU_valueChanged(int value);

    void on_CheckShowTrash_stateChanged(int arg1);

    void on_RegenerateTrash_clicked();

    void on_InputScatterTrashFrom_valueChanged(double arg1);

    void on_InputScatterTrashTo_valueChanged(double arg1);

    void on_CheckShowLocalItems_stateChanged(int arg1);

private:
        Ui::IndicatorDRL *ui;
};

#endif // INDICATORDRL_H
