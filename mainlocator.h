#ifndef MAINLOCATOR_H
#define MAINLOCATOR_H

#ifndef ANGLE_RANGE
#define ANGLE_RANGE 361
#endif

#include<QGLWidget>
#include<QColorDialog>
#include<QVariant>

class MainLocator : public QGLWidget
{
    Q_OBJECT
    public:
        explicit MainLocator(QWidget *parent = 0);
        ~MainLocator();
        //[R]
        bool clockwise;
        void GenerationRay();
        template<typename OptionType>void SetSettings(const QString group,const QString name,OptionType option);
        template<typename OptionType>void SetSettings(const QString name,OptionType option);
        template<typename T>T CalcScaleValue(const T value)const;
        //\[R]
        void GenerationTrash();
        void GenerationRange();
        void GenerationAzimuth();
        void GenerationLocalItems();
        void GenerationActiveNoiseTrash();
        void GenerationActiveAnswerTrash();
        void GenerationActiveInSyncTrash();
        void GenerationTargetPaths();
        void GenerationMeteo();
        void ChangeFPS(qreal fps) const;
        void CleanDataBuffer();
        void ChangeTargetsState();
        //void SetSettings(const QString,const quint16);
       // void SetSettings(const QString,const qreal);
        QColor SelectColor(const QString,const QString);
        bool IsActive() const;
        bool show,
             show_trash,
             show_local_items,
             show_active_ntrash,
             show_active_atrash,
             show_active_isynctrash,
             show_meteo;
        qint8 targets_pos;

    signals:

    public slots:
    protected:
        void initializeGL();
        void resizeGL(int nWidth, int nHeight);
        void paintGL();
        void DrawStation();
        void LocatorArea() const;
        void DrawTrash();
        void DrawRange();
        void DrawAzimuth();
        void DrawLocalItems();
        void DrawActiveNoiseTrash();
        void DrawActiveAnswerTrash();
        void DrawActiveInSyncTrash();
        void DrawTargets();
        void DrawMeteo();
        qreal GetRandomCoord(quint8,const bool rsign=false);
        qint8 GetRandomSign();

    private:
        quint16 radians_size;
        /**
         * @brief The Points struct
         * Описывает формат хранения координат на основе трёх параметров:
         *  -абсцисса точки
         *  -ордината точки
         *  -угол точки
         */
        struct Points
        {
            qreal x,y,angle;
        }
            radians[ANGLE_RANGE];

        /**
         * @brief The PointsPath struct
         * Описывает формат хранения координат на основе трёх параметров:
         *  -абсцисса точки
         *  -ордината точки
         *  -угол точки
         *  -расстояние точки от центра
         */
        struct PointsPath:public Points
        {
            qreal r;
        };

        struct LineEntity
        {
            qreal width;
            Points *Coordinates;
        };

        QVector<Points*>
            circle,
            ray;

        QVector<LineEntity>azimuth;
        QVector<Points*>::const_iterator ray_position;
        QVector<LineEntity>range;
        struct Coordinates
        {
            QVector<PointsPath>
                trash,
                local_items;
        }
            Cache,Current;
        QMap<QString,QMap<QString,QVariant> >settings;

        //----------------------
        qreal fps;
        bool not_clean;
        QTimer* timer;
        qreal CalcAlpha(qreal angle);
        /*
        QVector<QVector<QHash<QString,qreal> >::const_iterator>::const_iterator line_position,line_end;
        //QVector<QHash<QString,qreal> >radians,trash,azimuth,local_items,active_noise_trash,meteo;
        QVector<QVector<QHash<QString,qreal> >::const_iterator>circle,line;
        QHash<quint16,QVector<QHash<QString,qreal> > >range,active_answer_trash,active_insync_trash,targets;
        QMap<QString,quint16>settings;
        QMap<QString,qreal>options;
        */
        QMap<QString,QColor>color;
        QColorDialog* Color;

    private slots:
        void ContinueSearch();
};

template<typename OptionType>void MainLocator::SetSettings(const QString group,const QString name,OptionType option)
{
    settings[group][name]=QVariant::fromValue(option);
    if(group=="system")
    {
        if(name=="show")
            show=static_cast<bool>(option);
        if(name=="scale")
        {
            GenerationTrash();
            GenerationRange();
            GenerationLocalItems();
        }
        if(name=="range")
            GenerationRange();
        if(name=="azimuth")
            GenerationAzimuth();
        if(name=="focus")
        {
            //GenerationTrash();
            //GenerationRange();
            //GenerationAzimuth();
        }
    }
    if(group=="trash")
    {
        if(name=="intensity" || name=="begin" || name=="end")
            GenerationTrash();
    }
    if(group=="local_items")
    {
        if(name=="show")
            GenerationLocalItems();
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
