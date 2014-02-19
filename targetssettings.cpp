#include"targetssettings.h"
#include"ui_targetssettings.h"
#include"qdebug.h"

TargetsSettings::TargetsSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TargetsSettings)
{
    ui->setupUi(this);
}

TargetsSettings::~TargetsSettings()
{
    delete ui;
}

void TargetsSettings::on_AddTarget_clicked()
{
    QGroupBox *Target;
    QGroupBox *TargetStart;
    QLabel *LabelTargetAzimuthStart;
    QSpinBox *TargetAzimuthStart;
    QLabel *LabelTargetRangeStart;
    QDoubleSpinBox *TargetRangeStart;
    QGroupBox *TargetFinish;
    QLabel *LabelTargetAzimuthFinish;
    QSpinBox *TargetAzimuthFinish;
    QLabel *LabelTargetRangeFinish;
    QDoubleSpinBox *TargetRangeFinish;
    QCheckBox *TargetWidePath;

    Target = new QGroupBox(ui->scrollAreaWidgetContents);
    Target->setObjectName(QStringLiteral("Target1"));
    //Target->setGeometry(QRect(10, 10, 391, 141));
    Target->setGeometry(QRect(10, 146, 391, 277));
    TargetStart = new QGroupBox(Target);
    TargetStart->setObjectName(QStringLiteral("TargetStart1"));
    TargetStart->setGeometry(QRect(10, 20, 181, 91));
    LabelTargetAzimuthStart = new QLabel(TargetStart);
    LabelTargetAzimuthStart->setObjectName(QStringLiteral("LabelTargetAzimuthStart1"));
    LabelTargetAzimuthStart->setGeometry(QRect(33, 32, 57, 15));
    TargetAzimuthStart = new QSpinBox(TargetStart);
    TargetAzimuthStart->setObjectName(QStringLiteral("TargetAzimuthStart1"));
    TargetAzimuthStart->setGeometry(QRect(90, 27, 81, 24));
    LabelTargetRangeStart = new QLabel(TargetStart);
    LabelTargetRangeStart->setObjectName(QStringLiteral("LabelTargetRangeStart1"));
    LabelTargetRangeStart->setGeometry(QRect(10, 58, 71, 16));
    TargetRangeStart = new QDoubleSpinBox(TargetStart);
    TargetRangeStart->setObjectName(QStringLiteral("TargetRangeStart1"));
    TargetRangeStart->setGeometry(QRect(90, 55, 81, 24));
    TargetFinish = new QGroupBox(Target);
    TargetFinish->setObjectName(QStringLiteral("TargetFinish1"));
    TargetFinish->setGeometry(QRect(200, 20, 181, 91));
    LabelTargetAzimuthFinish = new QLabel(TargetFinish);
    LabelTargetAzimuthFinish->setObjectName(QStringLiteral("LabelTargetAzimuthFinish1"));
    LabelTargetAzimuthFinish->setGeometry(QRect(33, 32, 57, 15));
    TargetAzimuthFinish = new QSpinBox(TargetFinish);
    TargetAzimuthFinish->setObjectName(QStringLiteral("TargetAzimuthFinish1"));
    TargetAzimuthFinish->setGeometry(QRect(90, 27, 81, 24));
    LabelTargetRangeFinish = new QLabel(TargetFinish);
    LabelTargetRangeFinish->setObjectName(QStringLiteral("LabelTargetRangeFinish1"));
    LabelTargetRangeFinish->setGeometry(QRect(10, 58, 71, 16));
    TargetRangeFinish = new QDoubleSpinBox(TargetFinish);
    TargetRangeFinish->setObjectName(QStringLiteral("TargetRangeFinish1"));
    TargetRangeFinish->setGeometry(QRect(90, 55, 81, 24));
    TargetWidePath = new QCheckBox(Target);
    TargetWidePath->setObjectName(QStringLiteral("TargetWidePath1"));
    TargetWidePath->setGeometry(QRect(10, 115, 161, 21));
}

void TargetsSettings::on_SwitchTargetNext_clicked()
{
    quint8 pos=static_cast<quint8>(ui->Targets->currentIndex());
    if(pos<9)
        pos++;
    else
        pos=0;
    ui->Targets->setCurrentIndex(pos);
}

void TargetsSettings::on_SwitchTargetPrev_clicked()
{
    quint8 pos=static_cast<quint8>(ui->Targets->currentIndex());
    if(pos>0)
        pos--;
    else
        pos=9;
    ui->Targets->setCurrentIndex(pos);
}
