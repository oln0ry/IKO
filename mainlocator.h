#ifndef MAINLOCATOR_H
#define MAINLOCATOR_H

#ifndef ANGLE_RANGE
#define ANGLE_RANGE 361
#endif

#ifndef METEO
#define METEO 5
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
        void resizeGL(int width, int height);
        void paintGL();
        void DrawStation();
        void LocatorArea() const;
        void DrawTrash() const;
        void DrawRange() const;
        void DrawAzimuth() const;
        void DrawLocalItems() const;
        void DrawActiveNoiseTrash();
        void DrawActiveAnswerTrash();
        void DrawActiveInSyncTrash();
        void DrawTargets();
        void DrawMeteo() const;
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
            QVector<PointsPath>meteo;
        }
            Cache,Current;
        QMap<QString,QMap<QString,QVariant> >settings;

        //----------------------
        qreal fps;
        bool not_clean;
        QTimer* timer;
        qreal CalcAlpha(qreal angle) const;
        void CreateEllipseTrashArea(QVector<PointsPath>&storage,qreal offset_x,qreal offset_y,qreal intensity,bool ellipse,bool clear);
        void CreateEllipseTrashArea(QVector<PointsPath>&storage,qreal begin,qreal end,qreal offset_x,qreal offset_y,qreal intensity,bool ellipse,bool clear);
        void DrawEllipseTrashArea(QVector<PointsPath>storage, quint8 size) const;
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
