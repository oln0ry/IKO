#ifndef TARGETSSETTINGS_H
#define TARGETSSETTINGS_H

#include<QWidget>
#include"helper.h"

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
    Targets *Targs;
    static Targets* T;
    static quint16 time;
    static QHash<quint16,QHash<quint16,QVector<Points> > >targets;

    private slots:
        void on_SwitchTargetNext_clicked();

        void on_SwitchTargetPrev_clicked();

        void on_ApplyTargets_clicked();

        void on_TargetsGoHome_stateChanged(int arg);

    private:
        Ui::TargetsSettings *ui;
        static quint8 targets_count;
        void ApplyTargets(Targets*);
};

#endif // TARGETSSETTINGS_H
