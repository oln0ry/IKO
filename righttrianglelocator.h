#include"equiangulartrianglelocator.h"

#ifndef RIGHTTRIANGLELOCATOR_H
#define RIGHTTRIANGLELOCATOR_H

class RightTriangleLocator : public EquiangularTriangleLocator
{
    Q_OBJECT
    public:
        explicit RightTriangleLocator(QWidget *parent = 0);

    protected:
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void LocatorArea() const;
        void DrawStation() const;
        virtual void GenerationRay();
    signals:
};

#endif // RIGHTTRIANGLELOCATOR_H
