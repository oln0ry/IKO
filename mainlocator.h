#include<QGLWidget>
#include<QColorDialog>
#include<QVariant>
#include<qmath.h>
#include<QTime>
#include<QTimer>
#include<QDebug>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

#ifndef GetRadianValue
#define GetRadianValue(radian) M_PI*radian/180
#endif

//Макрос стырен из Chromium, т.к. это пока лучшее, что можно придумать для подсчёта элементов массива
#ifndef ArraySize
template<typename T,size_t N>
char(&ArraySizeHelper(T(&array)[N]))[N];
#define ArraySize(array)(sizeof(ArraySizeHelper(array)))
#endif

#ifndef ANGLE_RANGE
#define ANGLE_RANGE 361
#endif

#ifndef METEO
#define METEO 5
#endif

#ifndef MAINLOCATOR_H
#define MAINLOCATOR_H

class MainLocator : public QGLWidget
{
    Q_OBJECT
    public:
        explicit MainLocator(QWidget *parent = 0);
        ~MainLocator();
        template<typename OptionType>void SetSettings(const QString group,const QString name,OptionType option);
        template<typename OptionType>void SetSettings(const QString name,OptionType option);
        template<typename T>T CalcScaleValue(const T value)const;

        void GenerationRay();
        void GenerationRay(qint16 angle);
        void GenerationTrash();
        virtual void GenerationRange();
        void GenerationAzimuth();
        void GenerationLocalItems();
        void GenerationActiveNoiseTrash();
        void GenerationActiveAnswerTrash();
        void GenerationActiveInSyncTrash();
        void GenerationTargetPaths();
        void GenerationMeteo();
        void ChangeFPS(qreal fps);
        void CleanDataBuffer();
        void ChangeTargetsState();
        QColor SelectColor(const QString,const QString);
        bool IsActive() const;
        bool clockwise,
             show;
        qint8 targets_pos;

    signals:

    public slots:
    protected:
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void DrawStation() const;
        void LocatorArea() const;
        void DrawTrash() const;
        void DrawRange() const;
        void DrawAzimuth() const;
        void DrawLocalItems() const;
        void DrawActiveNoiseTrash() const;
        void DrawActiveAnswerTrash();
        void DrawActiveInSyncTrash();
        void DrawTargets();
        void DrawMeteo() const;
        qreal GetRandomCoord(quint8,const bool rsign=false) const;
        qint8 GetRandomSign() const;
        quint16 radians_size;
        qreal CalcAlpha(qreal angle) const;
        qreal fps;
        struct Points
        {
            qreal x,y,angle;
        }radians[ANGLE_RANGE];
        struct PointsPath:public Points
        {
            qreal r;
        };
        struct LineEntity
        {
            qreal width;
            Points *Coordinates;
        };
        struct Coordinates
        {
            QVector<PointsPath>trash,local_items,meteo;
            QVector<LineEntity>active_noise_trash;
        }Cache,Current;
        QVector<LineEntity>range;
        QVector<Points*>::const_iterator ray_position;
        QVector<Points*>circle,ray;
        QTimer* timer;
        QMap<QString,QMap<QString,QVariant> >settings;

    private:
        void CreateEllipseTrashArea(QVector<PointsPath>&storage,qreal offset_x,qreal offset_y,qreal intensity,bool ellipse,bool clear);
        void CreateEllipseTrashArea(QVector<PointsPath>&storage,qreal begin,qreal end,qreal offset_x,qreal offset_y,qreal intensity,bool ellipse,bool clear);
        void DrawEllipseTrashArea(QVector<PointsPath>storage, quint8 size) const;
        bool not_clean;
        QColorDialog* Color;
        QVector<LineEntity>azimuth;
        QMap<QString,QColor>color;

     protected slots:
        void ContinueSearch();
};

template<typename OptionType>void MainLocator::SetSettings(const QString group,const QString name,OptionType option)
{
    settings[group][name]=QVariant::fromValue(option);
    if(name=="show")
    {
        if(group=="system")
            show=static_cast<bool>(option);
    }
    else if(group=="system")
    {
        if(name=="scale")
        {
            GenerationTrash();
            GenerationRange();
            GenerationLocalItems();
            if(Cache.meteo.isEmpty())
                GenerationMeteo();
            if(Cache.active_noise_trash.isEmpty())
                GenerationActiveNoiseTrash();
        }
        else if(name=="range")
            GenerationRange();
        else if(name=="azimuth")
            GenerationAzimuth();
        else if(name=="focus")
        {
            //GenerationTrash();
            //GenerationRange();
            //GenerationAzimuth();
        }
    }
    else if(group=="trash")
    {
        if(name=="intensity" || name=="begin" || name=="end")
            GenerationTrash();
    }
    else if (group=="active_noise_trash")
    {
        if(name=="azimuth" || name=="intensity")
            GenerationActiveNoiseTrash();
    }
    if(group!="common")
        updateGL();
}

template<typename OptionType>void MainLocator::SetSettings(const QString name,OptionType option)
{
    SetSettings("common",name,option);
}

template<typename T>T MainLocator::CalcScaleValue(const T value) const
{
    return value/settings["system"]["scale"].toUInt();
}
#endif // MAINLOCATOR_H
