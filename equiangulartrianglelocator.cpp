#include"equiangulartrianglelocator.h"

EquiangularTriangleLocator::EquiangularTriangleLocator(QWidget *parent):MainLocator(parent)
{
    clockwise=true; //По часовой стрелке
    //Color=new QColorDialog(this);
    qsrand(QTime(0u,0u,0u).secsTo(QTime::currentTime()));
    //Переведём все используемые градусы в радианы
    qreal angle=qFastCos(GetRadianValue(TRIANGLE_ANGLE));
    for(quint16 i=0u;i<ANGLE_RANGE;i++)
    {
        radians[i].angle=GetRadianValue(i);
        radians[i].x=qFastCos(radians[i].angle);
        radians[i].y=qFastSin(radians[i].angle);
        radians_triangle_ray[i].angle=radians[i].angle;
        radians_triangle_ray[i].x=angle;
        radians_triangle_ray[i].y=radians[i].y;
    }
    radians_size=ArraySize(radians);
    for(Points*i=radians,*end=radians+radians_size;i<end;circle.append(i),i+=3u); //Получаем координаты для отрисовки фона индикатора
    GenerationRay();
    ray_position=ray.begin(); //Устанавливаем стартовую позицию луча
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(ContinueSearch()));
    GenerationRange();
}

void EquiangularTriangleLocator::initializeGL()
{
    qglClearColor(palette().background().color()); //Фон OpenGl-виджета
    glMatrixMode(GL_PROJECTION); //Устанавливаем матрицу
    glShadeModel(GL_SMOOTH);//GL_FLAT
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
    //glEnable(GL_DEPTH_TEST);
}

void EquiangularTriangleLocator::resizeGL(int width, int height)
{
    glEnable(GL_MULTISAMPLE);
    glLoadIdentity();
    glViewport(static_cast<GLint>(0u),static_cast<GLint>(0u),static_cast<GLint>(width),static_cast<GLint>(height));
}

void EquiangularTriangleLocator::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glLoadIdentity(); // загружаем матрицу
    glPushMatrix();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    LocatorArea();
    glColor4f(static_cast<GLfloat>(.925),static_cast<GLfloat>(.714),static_cast<GLfloat>(.262),1/*settings["system"]["brightness"].toFloat()*/);//перерисовка линии
    glRotatef(270.0f, 0.0, 0.0, 1.0);
    DrawStation();
    glBegin(GL_LINES);
        glVertex2d(qFastCos(GetRadianValue(180)),qFastSin(GetRadianValue(180)));
        glVertex2d((*ray_position)->x,(*ray_position)->y);
    glEnd();
    if(!range.isEmpty())
        DrawRange();
    glPopMatrix();
}

void EquiangularTriangleLocator::LocatorArea() const
{
    qglColor(Qt::black);
    glBegin(GL_TRIANGLE_FAN);
        for(QVector<Points*>::const_iterator it=circle.begin();it<circle.end();it++)
            glVertex2d((*it)->x,(*it)->y);
    glEnd();
}

void EquiangularTriangleLocator::GenerationRay()
{
    ray.clear();
    Points*i,*end;
    if(clockwise)
    {
        i=radians_triangle_ray+radians_size-46,end=radians_triangle_ray+radians_size;
        while(i<end)ray.append(clockwise ? i++ : end--);
        i=radians_triangle_ray,end=radians_triangle_ray+46;
        while(i<end)ray.append(clockwise ? i++ : end--);
    }
    else
    {
        i=radians_triangle_ray,end=radians_triangle_ray+46;
        while(i<end)ray.append(clockwise ? i++ : end--);
        i=radians_triangle_ray+radians_size-46,end=radians_triangle_ray+radians_size;
        while(i<end)ray.append(clockwise ? i++ : end--);
    }
}

void EquiangularTriangleLocator::DrawStation() const
{
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2d(qFastCos(GetRadianValue(180)),qFastSin(GetRadianValue(180)));
        glVertex2d(qFastCos(GetRadianValue(-TRIANGLE_ANGLE)),qFastSin(GetRadianValue(-TRIANGLE_ANGLE)));

        glVertex2d(qFastCos(GetRadianValue(180)),qFastSin(GetRadianValue(180)));
        glVertex2d(qFastCos(GetRadianValue(TRIANGLE_ANGLE)),qFastSin(GetRadianValue(TRIANGLE_ANGLE)));

        glVertex2d(qFastCos(GetRadianValue(180)),qFastSin(GetRadianValue(180)));
        glVertex2d(qFastCos(GetRadianValue(TRIANGLE_ANGLE)),qFastSin(GetRadianValue(20)));

        glVertex2d(qFastCos(GetRadianValue(-TRIANGLE_ANGLE)),qFastSin(GetRadianValue(-TRIANGLE_ANGLE)));
        glVertex2d(qFastCos(GetRadianValue(TRIANGLE_ANGLE)),qFastSin(GetRadianValue(TRIANGLE_ANGLE)));
    glEnd();
}

void EquiangularTriangleLocator::ContinueSearch()
{
    updateGL();
    if(ray_position==ray.end()-1u)
    {
        clockwise=!clockwise; //Для обращения в другую сторону!
        GenerationRay();
        ray_position=ray.begin();
    }
    ray_position++;
}

void EquiangularTriangleLocator::GenerationRange()
{
    qreal r=.0f,delta,distance;
    quint8 j=0u,d=0u;
    range.clear();

    distance=CalcScaleValue(1.0f);
    switch(settings["system"]["range"].toUInt())
    {
        case 1:
            delta=distance*5u;
            j=10u;
            break;
        case 0:
            return;
        default:
            delta=distance*10u;
            j=5u;
    }

    LineEntity cache;
    quint16 c;
    while(r<=1u)
    {
        cache.width=d%j==0u ? 3.5f : 1.0f;
        cache.Coordinates=new Points[radians_size];
        c=0u;
        for(Points *i=radians_triangle_ray+radians_size-TRIANGLE_ANGLE,*end=radians_triangle_ray+radians_size;i<end;i++,c++)
        {
            cache.Coordinates[c].angle=i->angle;
            cache.Coordinates[c].x=r*i->x;
            cache.Coordinates[c].y=r*i->y;
        }
        for(Points *i=radians_triangle_ray,*end=radians_triangle_ray+TRIANGLE_ANGLE;i<end;i++,c++)
        {
            cache.Coordinates[c].angle=i->angle;
            cache.Coordinates[c].x=r*i->x;
            cache.Coordinates[c].y=r*i->y;
        }
        range.append(cache);
        r+=delta;
        d++;
    }
}

void EquiangularTriangleLocator::DrawRange() const
{
    qreal alpha;
    for(QVector<LineEntity>::const_iterator it=range.begin();it<range.end();it++)
    {
        glLineWidth(it->width);
        glBegin(GL_LINE_STRIP);
        for(Points *i=it->Coordinates,*end=it->Coordinates+radians_size;i<end;i++)
        {
            alpha=CalcAlpha(i->angle);
            if(alpha>.0f)
            {
                //alpha=alpha<settings["system"]["lightning"].toDouble() ? 1.0f : settings["system"]["lightning"].toDouble()/alpha;
                glColor4f(static_cast<GLfloat>(.925),static_cast<GLfloat>(.714),static_cast<GLfloat>(.262),alpha*settings["system"]["brightness"].toDouble());
                glVertex2d(i->x,i->y);
            }
        }
        glEnd();
    }
}
