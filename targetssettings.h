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
    quint8 Count();

    private slots:
        void on_SwitchTargetNext_clicked();

        void on_SwitchTargetPrev_clicked();

        void on_ApplyTargets_clicked();

    private:
        Ui::TargetsSettings *ui;
        quint8 targets_count;
};

#endif // TARGETSSETTINGS_H
