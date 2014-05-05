#include"righttrianglelocator.h"

RightTriangleLocator::RightTriangleLocator(QWidget *parent):EquiangularTriangleLocator(parent)
{
    clockwise=true; //По часовой стрелке
    not_clean=false;
    //Color=new QColorDialog(this);
    qsrand(QTime(0u,0u,0u).secsTo(QTime::currentTime()));
    //Переведём все используемые градусы в радианы
    qreal angle=2*qFastCos(GetRadianValue(TRIANGLE_ANGLE));
    for(quint16 i=0u;i<ANGLE_RANGE;i++)
    {
        radians[i].angle=GetRadianValue(i);
        radians[i].x=qFastCos(radians[i].angle);
        radians[i].y=qFastSin(radians[i].angle);
        radians_triangle_ray[i].angle=radians[i].angle;
        radians_triangle_ray[i].x=angle;
        radians_triangle_ray[i].y=2*radians[i].y;
    }
    radians_size=ArraySize(radians);
    circle.clear();
    for(Points*i=radians,*end=radians+radians_size;i<end;circle.append(i),i+=3u); //Получаем координаты для отрисовки фона индикатора
    GenerationRay();
    ray_position=ray.begin(); //Устанавливаем стартовую позицию луча
    ChangeFPS(0);
}

void RightTriangleLocator::initializeGL()
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

void RightTriangleLocator::resizeGL(int width, int height)
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

void RightTriangleLocator::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glLoadIdentity(); // загружаем матрицу
    glPushMatrix();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    LocatorArea();
    glColor4f(static_cast<GLfloat>(.925),static_cast<GLfloat>(.714),static_cast<GLfloat>(.262),1/*settings["system"]["brightness"].toFloat()*/);//перерисовка линии
    glRotatef(.0f,.0f,.0f,1.0f);
    //qDebug()<<settings["disposition"]["vertical"].toDouble()/100;
    glTranslatef(-qFastCos(GetRadianValue(-TRIANGLE_ANGLE))+settings["disposition"]["horizontal"].toDouble()/100,qFastSin(GetRadianValue(-TRIANGLE_ANGLE))+settings["disposition"]["vertical"].toDouble()/100,.0f);
    DrawStation();
    glLineWidth(2.0f*settings["system"]["focus"].toDouble());
    glBegin(GL_LINES);
        glVertex2d(.0f,.0f);
        glVertex2d((*ray_position)->x,(*ray_position)->y);
    glEnd();
    if(!range.isEmpty())
        DrawRange();
    if(!Cache.trash.isEmpty())
        DrawTrash();
    glPopMatrix();
}

void RightTriangleLocator::LocatorArea() const
{
    qglColor(Qt::black);
    glBegin(GL_TRIANGLE_FAN);
        for(QVector<Points*>::const_iterator it=circle.begin();it<circle.end();it++)
            glVertex2d((*it)->x,(*it)->y);
    glEnd();
}

void RightTriangleLocator::GenerationRay()
{
    ray.clear();
    Points*i,*end;
    i=radians_triangle_ray,end=radians_triangle_ray+TRIANGLE_ANGLE;
    while(i<end)ray.append(clockwise ? end-- : i++);
}


void RightTriangleLocator::DrawStation() const
{
    //glTranslatef(-qFastCos(GetRadianValue(-TRIANGLE_ANGLE)),qFastSin(GetRadianValue(-TRIANGLE_ANGLE)),.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2d(.0f,.0f);
        glVertex2d(2*qFastCos(GetRadianValue(-TRIANGLE_ANGLE)),qFastSin(GetRadianValue(0)));

        glVertex2d(.0f,.0f);
        glVertex2d(2*qFastCos(GetRadianValue(TRIANGLE_ANGLE)),2*qFastSin(GetRadianValue(TRIANGLE_ANGLE)));

        glVertex2d(.15f,.0f);
        glVertex2d(2*qFastCos(GetRadianValue(TRIANGLE_ANGLE)),2*qFastSin(GetRadianValue(16)));

        glVertex2d(2*qFastCos(GetRadianValue(-TRIANGLE_ANGLE)),qFastSin(GetRadianValue(0)));
        glVertex2d(2*qFastCos(GetRadianValue(TRIANGLE_ANGLE)),2*qFastSin(GetRadianValue(TRIANGLE_ANGLE)));
    glEnd();
}

void RightTriangleLocator::ContinueSearch()
{
    updateGL();
    if(ray_position==ray.end()-1u)
    {
        if(!not_clean)
            not_clean=true;
        clockwise=!clockwise; //Для обращения в другую сторону!
        GenerationRay();
        ray_position=ray.begin();
    }
    ray_position++;
}

qreal RightTriangleLocator::CalcAlpha(qreal angle) const
{
    qreal alpha;
    if(settings["system"]["show"].toBool())
        alpha=1.0f;
    else
    {
        alpha=(clockwise ? -1 : 1)*((*ray_position)->angle-angle)-.01;
        if(!not_clean)
            return alpha;
        if(clockwise && (*ray_position)->angle-angle>0)
        {
            alpha+=GetRadianValue(TRIANGLE_ANGLE);
            alpha=1-alpha;
        }
        if(!clockwise && angle-(*ray_position)->angle>0)
        {
            alpha+=GetRadianValue(TRIANGLE_ANGLE);
            alpha=1-alpha;
        }
        //qDebug()<<(*ray_position)->angle<<"\t"<<angle;
    }
    return alpha;
}

void RightTriangleLocator::GenerationRange()
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
        cache.Coordinates=new Points[TRIANGLE_ANGLE];
        c=0u;

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

void RightTriangleLocator::DrawRange() const
{
    qreal alpha;
    for(QVector<LineEntity>::const_iterator it=range.begin();it<range.end();it++)
    {
        glLineWidth(it->width*settings["system"]["focus"].toDouble());
        glBegin(GL_LINE_STRIP);
        for(Points *i=it->Coordinates,*end=it->Coordinates+TRIANGLE_ANGLE;i<end;i++)
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

void RightTriangleLocator::CreateEllipseTrashArea(QVector<PointsPath>&storage,qreal begin,qreal end,qreal offset_x,qreal offset_y,qreal intensity=3.0f,bool ellipse=false,bool clear=true)
{
    qreal rand;
    begin=CalcScaleValue(begin),
    end=CalcScaleValue(end);
    if(clear)
        storage.clear();
    PointsPath cache;

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
