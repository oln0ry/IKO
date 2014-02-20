#ifndef MAINLOCATOR_H
#define MAINLOCATOR_H

#ifndef ANGLE_RANGE
#define ANGLE_RANGE 360
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
        //[R]
        /**
         * @brief The Radians struct
         * Описывает формат хранения координат на основе трёх параметров:
         *  -абсцисса точки
         *  -ордината точки
         *  -угол точки
         */
        struct Radians
        {
            qreal x,y,angle;
        }
            n_radians[ANGLE_RANGE];

        /**
         * @brief The RadiansEx struct
         * Описывает формат хранения координат на основе трёх параметров:
         *  -абсцисса точки
         *  -ордината точки
         *  -угол точки
         *  -расстояние точки от центра
         */
        struct RadiansEx:public Radians
        {
            qreal r;
        };

        QVector<Radians>
            circle,
            ray;
        quint16
            radians_size;
        QVector<Radians>::const_iterator ray_position;
        struct Coordinates
        {
            QVector<RadiansEx>trash;
        }
            Cache,Current;
        QMap<QString,QMap<QString,QVariant> >settings;
        //\[R]
        qreal fps;
        bool not_clean;
        QTimer* timer;

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

template<typename OptionType>
void MainLocator::SetSettings(const QString group,const QString name,OptionType option)
{
    if(group=="system")
    {
        if(name=="show")
            show=static_cast<bool>(option);
    }
    if(group=="trash")
    {
        if(name=="intensity" || name=="begin" || name=="end")
            GenerationTrash();
    }
    settings[group][name]=QVariant::fromValue(option);
    if(group!="common")
        updateGL();
}

template<typename OptionType>
void MainLocator::SetSettings(const QString name,OptionType option)
{
    SetSettings("common",name,option);
}
#endif // MAINLOCATOR_H
