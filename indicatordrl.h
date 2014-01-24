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

    private:
        Ui::IndicatorDRL *ui;
};

#endif // INDICATORDRL_H
