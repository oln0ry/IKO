#include"mainlocator.h"

#ifndef TRIANGLE_ANGLE
#define TRIANGLE_ANGLE  46
#endif

#ifndef EQUIANGULARTRIANGLELOCATOR_H
#define EQUIANGULARTRIANGLELOCATOR_H

class EquiangularTriangleLocator : public MainLocator
{
    Q_OBJECT
    public:
        explicit EquiangularTriangleLocator(QWidget *parent = 0);
        void GenerationRange();

    protected:
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void LocatorArea() const;
        void DrawStation() const;
        void DrawRange() const;
        void GenerationRay();
        Points radians_triangle_ray[ANGLE_RANGE];
    signals:

    protected slots:
        void ContinueSearch();
};

#endif // EQUIANGULARTRIANGLELOCATOR_H
