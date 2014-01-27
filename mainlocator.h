#ifndef MAINLOCATOR_H
#define MAINLOCATOR_H

#include<QGLWidget>
#include<QColorDialog>

class MainLocator : public QGLWidget
{
    Q_OBJECT
    public:
        explicit MainLocator(QWidget *parent = 0);
        ~MainLocator();
        void GenerationTrash();
        void GenerationRange();
        void GenerationAzimuth();
        void ChangeFPS(qreal fps);
        void SetSettings(const QString,const quint8);
        void SetSettings(const QString,const qreal);
        QColor SelectColor(const QString,const QString);
        bool IsActive();
        bool show,show_trash;

    signals:

    public slots:
    protected:
        void initializeGL();
        void resizeGL(int nWidth, int nHeight);
        void paintGL();
        void LocatorArea();
        void DrawTrash();
        void DrawRange();
        void DrawAzimuth();
        qreal GetRandomCoord(const quint8,const bool rsign=false);
        qint8 GetRandomSign();

    private:
        qreal fps;
        bool not_clean;
        QTimer* timer;
        QVector<QVector<QHash<QString,qreal> >::const_iterator>::const_iterator line_position,line_end;
        QVector<QHash<QString,qreal> >radians,trash,azimuth;
        QVector<QVector<QHash<QString,qreal> >::const_iterator>circle,line;
        QHash<quint16,QVector<QHash<QString,qreal> > >range;
        QMap<QString,QColor>color;
        QMap<QString,quint8>settings;
        QMap<QString,qreal>options;
        QColorDialog* Color;

    private slots:
        void ContinueSearch();
};

#endif // MAINLOCATOR_H
