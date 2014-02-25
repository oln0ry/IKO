#ifndef RSPINDICATORS_H
#define RSPINDICATORS_H

#include <QWidget>

namespace Ui {
class RSPIndicators;
}

class RSPIndicators : public QWidget
{
    Q_OBJECT

public:
    explicit RSPIndicators(QWidget *parent = 0);
    ~RSPIndicators();

private:
    Ui::RSPIndicators *ui;
};

#endif // RSPINDICATORS_H
