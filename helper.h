#ifndef HELPER_H
#define HELPER_H
#include<QWidget>
struct Daddy
{
    qreal x,angle;
};

struct Points:public Daddy
{
    qreal y;
};
struct PointsPath:public Points
{
    qreal r;
};
struct LineEntity
{
    qreal width;
    Points *Coordinates;
};


struct Targets
{
    Daddy Coordinates[5];
    //Points Coordinates[5];
    qreal speed;
    quint8 landing;
};
#endif // HELPER_H
