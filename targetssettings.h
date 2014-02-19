#ifndef TARGETSSETTINGS_H
#define TARGETSSETTINGS_H

#include <QWidget>

namespace Ui {
class TargetsSettings;
}

class TargetsSettings : public QWidget
{
    Q_OBJECT

public:
    explicit TargetsSettings(QWidget *parent = 0);
    ~TargetsSettings();

private slots:
    void on_AddTarget_clicked();

    void on_SwitchTargetNext_clicked();

    void on_SwitchTargetPrev_clicked();

private:
    Ui::TargetsSettings *ui;
};

#endif // TARGETSSETTINGS_H
