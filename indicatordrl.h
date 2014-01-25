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

private:
        Ui::IndicatorDRL *ui;
};

#endif // INDICATORDRL_H
