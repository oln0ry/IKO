#ifndef EQUIANGULARTRIANGLELOCATOR_H
#define EQUIANGULARTRIANGLELOCATOR_H

#ifndef TRIANGLE_ANGLE
#define TRIANGLE_ANGLE  46
#endif

#ifndef GRID_OFFSET
#define GRID_OFFSET  1.0f
#endif

#include"mainlocator.h"

class EquiangularTriangleLocator : public MainLocator
{
    Q_OBJECT
    public:
        explicit EquiangularTriangleLocator(QWidget *parent = 0);
        virtual void GenerationRange();

    protected:
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void LocatorArea() const;
        void DrawStation() const;
        void DrawRange() const;
        virtual void GenerationRay();
        qreal CalcAlpha(qreal angle) const;
        Points radians_triangle_ray[ANGLE_RANGE];
        virtual void CreateEllipseTrashArea(QVector<PointsPath>&storage,qreal begin,qreal end,qreal offset_x,qreal offset_y,qreal intensity,bool ellipse,bool clear);

    signals:

    private slots:
        virtual void ContinueSearch();
};

#endif // EQUIANGULARTRIANGLELOCATOR_H
