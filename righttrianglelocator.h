#ifndef RIGHTTRIANGLELOCATOR_H
#define RIGHTTRIANGLELOCATOR_H
#include"equiangulartrianglelocator.h"

class RightTriangleLocator : public EquiangularTriangleLocator
{
    Q_OBJECT
    public:
        explicit RightTriangleLocator(QWidget *parent = 0);
        virtual void GenerationRange();

    protected:
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void LocatorArea() const;
        void DrawStation() const;
        void DrawRange() const;
        qreal CalcAlpha(qreal angle) const;
        virtual void GenerationRay();
        virtual void CreateEllipseTrashArea(QVector<PointsPath>&storage,qreal begin,qreal end,qreal offset_x,qreal offset_y,qreal intensity,bool ellipse,bool clear);

    signals:
    private slots:
        virtual void ContinueSearch();
};

#endif // RIGHTTRIANGLELOCATOR_H
