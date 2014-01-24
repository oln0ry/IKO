#ifndef MAINLOCATOR_H
#define MAINLOCATOR_H

#include<QGLWidget>

class MainLocator : public QGLWidget
{
    Q_OBJECT
    public:
        explicit MainLocator(QWidget *parent = 0);
        ~MainLocator();

    signals:

    public slots:
    protected:
        void initializeGL();
        void resizeGL(int nWidth, int nHeight);
        void paintGL();
        void GenerationTrash();
        void GenerationRange();
        void GenerationAzimuth();
        void LocatorArea();
        void DrawTrash();
        void DrawRange();
        void DrawAzimuth();
        qreal GetRandomCoord(const quint8,const bool rsign=false);
        qint8 GetRandomSign();
    private:
        quint16 seconds;
        QTimer* timer;
        QVector<QVector<QHash<QString,qreal> >::const_iterator>::const_iterator line_position,line_end;
        //Кеш координат
        QVector<QHash<QString,qreal> >radians,trash,azimuth;
        QVector<QVector<QHash<QString,qreal> >::const_iterator>circle,line;
        QHash<quint16,QVector<QHash<QString,qreal> > >range;

    private slots:
        void ContinueSearch();
};

#endif // MAINLOCATOR_H
