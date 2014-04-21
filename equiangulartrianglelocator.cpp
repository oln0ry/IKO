#include"equiangulartrianglelocator.h"
#include"targetssettings.h"

EquiangularTriangleLocator::EquiangularTriangleLocator(QWidget *parent):MainLocator(parent)
{
    clockwise=true; //По часовой стрелке
    not_clean=true;
    //Color=new QColorDialog(this);
    qsrand(QTime(0u,0u,0u).secsTo(QTime::currentTime()));
    //Переведём все используемые градусы в радианы
    qreal angle=GRID_OFFSET+qFastCos(GetRadianValue(TRIANGLE_ANGLE));
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
    circle.clear();
    for(Points*i=radians,*end=radians+radians_size;i<end;circle.append(i),i+=3u); //Получаем координаты для отрисовки фона индикатора
    GenerationRay();
    ray_position=ray.begin(); //Устанавливаем стартовую позицию луча
    ChangeFPS(0u);
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(.0f, .0f, .0f, 1.0, 1.0, -1.0f);
    if(width>height)
        glViewport(static_cast<GLint>(0u),static_cast<GLint>(0u),static_cast<GLint>(height),static_cast<GLint>(height));
    else
        glViewport(static_cast<GLint>(0u),static_cast<GLint>(0u),static_cast<GLint>(width),static_cast<GLint>(width));
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
    glRotatef(270.0f,.0f,.0f,1.0f);
    glTranslatef(-GRID_OFFSET,.0f,.0f);
    DrawStation();
    glLineWidth(2.0f*settings["system"]["focus"].toDouble());
    glBegin(GL_LINES);
        glVertex2d(.0f,.0f);
        glVertex2d((*ray_position)->x,(*ray_position)->y);
    glEnd();
    if(!range.isEmpty())
        DrawRange();
    //if(!azimuth.isEmpty())
        //DrawAzimuth();
    if(!Cache.trash.isEmpty())
        DrawTrash();

    if(!TargetsSettings::targets.isEmpty())
        DrawTargets();

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
        i=radians_triangle_ray+radians_size-TRIANGLE_ANGLE,end=radians_triangle_ray+radians_size;
        while(i<end)ray.append(clockwise ? i++ : end--);
        i=radians_triangle_ray,end=radians_triangle_ray+TRIANGLE_ANGLE;
        while(i<end)ray.append(clockwise ? i++ : end--);
    }
    else
    {
        i=radians_triangle_ray,end=radians_triangle_ray+TRIANGLE_ANGLE;
        while(i<end)ray.append(clockwise ? i++ : end--);
        i=radians_triangle_ray+radians_size-TRIANGLE_ANGLE,end=radians_triangle_ray+radians_size;
        while(i<end)ray.append(clockwise ? i++ : end--);
    }
}

void EquiangularTriangleLocator::DrawStation() const
{
    glLineWidth(2.0f);

    glBegin(GL_LINES);
        glVertex2f(.0f,.0f);
        glVertex2f(GRID_OFFSET+qFastCos(GetRadianValue(-TRIANGLE_ANGLE)),qFastSin(GetRadianValue(-TRIANGLE_ANGLE)));

        glVertex2f(.0f,.0f);
        glVertex2d(GRID_OFFSET+qFastCos(GetRadianValue(TRIANGLE_ANGLE)),qFastSin(GetRadianValue(TRIANGLE_ANGLE)));

        glVertex2f(.0f,.0f);
        glVertex2d(GRID_OFFSET+qFastCos(GetRadianValue(TRIANGLE_ANGLE)),qFastSin(GetRadianValue(10)));

        glVertex2d(GRID_OFFSET+qFastCos(GetRadianValue(-TRIANGLE_ANGLE)),qFastSin(GetRadianValue(-TRIANGLE_ANGLE)));
        glVertex2d(GRID_OFFSET+qFastCos(GetRadianValue(TRIANGLE_ANGLE)),qFastSin(GetRadianValue(TRIANGLE_ANGLE)));
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

qreal EquiangularTriangleLocator::CalcAlpha(qreal angle) const
{
    qreal alpha;
    if(settings["system"]["show"].toBool())
        alpha=1.0f;
    else
    {
        alpha=(clockwise ? 1 : -1)*((*ray_position)->angle-angle)-.01;
        if(not_clean && alpha<.0f)
            alpha+=2*M_PI;
    }
    return alpha;
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
            j=2u;
            break;
        case 0:
            return;
        default:
            delta=distance*10u;
            j=1u;
    }

    LineEntity cache;
    quint16 c;
    while(r<=1.0f)
    {
        cache.width=d%j==0u ? 3.5f : 1.0f;
        cache.Coordinates=new Points[2*TRIANGLE_ANGLE];
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
        glLineWidth(it->width*settings["system"]["focus"].toDouble());
        glBegin(GL_LINE_STRIP);
        for(Points *i=it->Coordinates,*end=it->Coordinates+2*TRIANGLE_ANGLE;i<end;i++)
        {
            alpha=CalcAlpha(i->angle);
            if(alpha>.0f)
            {
                alpha=alpha<settings["system"]["lightning"].toDouble() ? 1.0f : settings["system"]["lightning"].toDouble()/alpha;
                glColor4f(static_cast<GLfloat>(.925),static_cast<GLfloat>(.714),static_cast<GLfloat>(.262),alpha*settings["system"]["brightness"].toDouble());
                glVertex2d(i->x,i->y);
            }
        }
        glEnd();
    }
}

void EquiangularTriangleLocator::GenerationAzimuth()
{
    quint8 delta;
    azimuth.clear();
    switch(settings["system"]["azimuth"].toUInt())
    {
        case 1:
            delta=30u;
            break;
        case 0:
            return;
        default:
            delta=10u;
    }
    LineEntity cache;

    for(Points *i=radians_triangle_ray+radians_size-TRIANGLE_ANGLE,*k=radians_triangle_ray+radians_size;i<k;i+=delta)
    {
        cache.width=(i-radians)%30u>0u ? 1.0f : 3.5f;
        cache.Coordinates=new Points[1];
        cache.Coordinates->angle=i->angle;
        cache.Coordinates->x=i->x+124;
        cache.Coordinates->y=i->y+124;
        azimuth.append(cache);
    }

    for(Points *i=radians_triangle_ray,*k=radians_triangle_ray+TRIANGLE_ANGLE;i<k;i+=delta)
    {
        cache.width=(i-radians)%30u>0u ? 1.0f : 3.5f;
        cache.Coordinates=new Points[1];
        cache.Coordinates->angle=i->angle;
        cache.Coordinates->x=i->x+124;
        cache.Coordinates->y=i->y+124;
        azimuth.append(cache);
    }
}

/**
 * Отрисовка меток азимута
 * @brief MainLocator::DrawAzimuth
 */
void EquiangularTriangleLocator::DrawAzimuth() const
{
    qreal alpha;
    for(QVector<LineEntity>::const_iterator it=azimuth.begin();it<azimuth.end();it++)
    {
        alpha=CalcAlpha(it->Coordinates->angle);
        if(alpha>.0f)
        {
            glLineWidth(it->width*settings["system"]["focus"].toDouble());
            alpha=alpha<settings["system"]["lightning"].toDouble() ? 1.0f : settings["system"]["lightning"].toDouble()/alpha;
            glBegin(GL_LINES);
            glColor4f(static_cast<GLfloat>(.925),static_cast<GLfloat>(.714),static_cast<GLfloat>(.262),alpha*settings["system"]["brightness"].toDouble());
            glVertex2d(.0f,.0f);
            glVertex2f(it->Coordinates->x,it->Coordinates->y);
            glEnd();
        }
    }
}

void EquiangularTriangleLocator::CreateEllipseTrashArea(QVector<PointsPath>&storage,qreal begin,qreal end,qreal offset_x,qreal offset_y,qreal intensity=3.0f,bool ellipse=false,bool clear=true)
{
    qreal rand;
    begin=CalcScaleValue(begin),
    end=CalcScaleValue(end);
    if(clear)
        storage.clear();
    PointsPath cache;
    for(Points *i=radians_triangle_ray+radians_size-TRIANGLE_ANGLE,*k=radians_triangle_ray+radians_size;i<k;i++)
    {
        for(quint16 l=0u,t=fmod(qrand(),intensity);l<t;l++)
        {
            if(ellipse)
            {
                rand=begin+fmod(GetRandomCoord(4u),end-begin);
                cache.x=i->x*rand+CalcScaleValue(offset_x)+GetRandomSign();//*CalcScaleValue(offset_x*rand);
                rand=begin+fmod(GetRandomCoord(4u),end-begin);
                cache.y=i->y*rand+CalcScaleValue(offset_y)+GetRandomSign();//*CalcScaleValue(offset_y*rand);
            }
            else
            {
                rand=begin+fmod(GetRandomCoord(4u),end-begin);
                cache.x=i->x*rand+CalcScaleValue(offset_x);
                cache.y=i->y*rand+CalcScaleValue(offset_y);
            }
            cache.r=qSqrt(qPow(cache.x,2u)+qPow(cache.y,2u));
            if(offset_x>.0f || offset_y>.0f)
                if(cache.x>0)
                    cache.angle=qAtan2(cache.y,cache.x);
                else if(cache.x==0)
                    cache.angle=M_PI/2;
                else
                    cache.angle=qAtan2(cache.y,cache.x);
            else
                cache.angle=i->angle;
            storage.append(cache);
        }
    }

    for(Points*i=radians_triangle_ray,*k=radians_triangle_ray+TRIANGLE_ANGLE;i<k;i++)
    {
        for(quint16 l=0u,t=fmod(qrand(),intensity);l<t;l++)
        {
            if(ellipse)
            {
                rand=begin+fmod(GetRandomCoord(4u),end-begin);
                cache.x=i->x*rand+CalcScaleValue(offset_x)+GetRandomSign();//*CalcScaleValue(offset_x*rand);
                rand=begin+fmod(GetRandomCoord(4u),end-begin);
                cache.y=i->y*rand+CalcScaleValue(offset_y)+GetRandomSign();//*CalcScaleValue(offset_y*rand);
            }
            else
            {
                rand=begin+fmod(GetRandomCoord(4u),end-begin);
                cache.x=i->x*rand+CalcScaleValue(offset_x);
                cache.y=i->y*rand+CalcScaleValue(offset_y);
            }
            cache.r=qSqrt(qPow(cache.x,2u)+qPow(cache.y,2u));
            if(offset_x>.0f || offset_y>.0f)
                if(cache.x>0)
                    cache.angle=qAtan2(cache.y,cache.x);
                else if(cache.x==0)
                    cache.angle=M_PI/2;
                else
                    cache.angle=qAtan2(cache.y,cache.x);
            else
                cache.angle=i->angle;
            storage.append(cache);
        }
    }
}
