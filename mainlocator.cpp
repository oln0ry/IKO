#include"mainlocator.h"

MainLocator::MainLocator(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
{
    clockwise=true; //По часовой стрелке
    Color=new QColorDialog(this);
    qsrand(QTime(0u,0u,0u).secsTo(QTime::currentTime()));

    //Переведём все используемые градусы в радианы
    for(quint16 i=0u;i<ANGLE_RANGE;i++)
    {
        radians[i].angle=GetRadianValue(i);
        radians[i].x=qFastCos(radians[i].angle);
        radians[i].y=qFastSin(radians[i].angle);
    }
    radians_size=ArraySize(radians);
    circle.clear();
    for(Points*i=radians,*end=radians+radians_size;i<end;circle.append(i),i+=3u); //Получаем координаты для отрисовки фона индикатора
    GenerationRay();
    ray_position=ray.begin(); //Устанавливаем стартовую позицию луча
    ChangeFPS(0);
}

void MainLocator::timerEvent(QTimerEvent *event)
{
    if(timer.timerId()==event->timerId())
        ContinueSearch();
    QWidget::timerEvent(event);
}

MainLocator::~MainLocator()
{
    if(IsActive())
        killTimer(timer.timerId());
}

void MainLocator::initializeGL()
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

void MainLocator::resizeGL(int width, int height)
{
    glEnable(GL_MULTISAMPLE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 0.0, 0.0, 1.0, 1.0, -1.0f);
    if(width>height)
        glViewport(static_cast<GLint>(0u),static_cast<GLint>(0u),static_cast<GLint>(height),static_cast<GLint>(height));
    else
        glViewport(static_cast<GLint>(0u),static_cast<GLint>(0u),static_cast<GLint>(width),static_cast<GLint>(width));
    glMatrixMode(GL_MODELVIEW);
}

void MainLocator::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glLoadIdentity(); // загружаем матрицу
    glPushMatrix();
    glLineWidth(2.0f*1u*settings["system"]["focus"].toDouble());
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    LocatorArea();
    DrawStation();
    glColor4f(static_cast<GLfloat>(.925),static_cast<GLfloat>(.714),static_cast<GLfloat>(.262),settings["system"]["brightness"].toFloat());//перерисовка линии
    glRotatef(90.0f, 0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex2d(static_cast<GLdouble>(.0f),static_cast<GLdouble>(.0f));
        glVertex2d((*ray_position)->x,(*ray_position)->y);
    glEnd();
    if(settings["trash"]["show"].toBool() && !Cache.trash.isEmpty())
        DrawTrash();
    if(!range.isEmpty())
        DrawRange();
    if(!azimuth.isEmpty())
        DrawAzimuth();
    if(settings["local_items"]["show"].toBool() && !Cache.local_items.isEmpty())
        DrawLocalItems();
    if(settings["meteo"]["show"].toBool() && !Cache.meteo.isEmpty())
        DrawMeteo();
    if(settings["active_noise_trash"]["show"].toBool() && !Cache.active_noise_trash.isEmpty())
        DrawActiveNoiseTrash();
    /*
    if(show_active_atrash && !active_answer_trash.isEmpty())
        DrawActiveAnswerTrash();
    if(show_active_isynctrash && !active_insync_trash.isEmpty())
        DrawActiveInSyncTrash();
    if(targets_pos>=0)
        DrawTargets();
    */
    glPopMatrix();
    //swapBuffers();
}

void MainLocator::ChangeFPS(qreal fps)
{
    if(fps<=.0f && IsActive())
        timer.stop();
    if(fps>.0f)
    {
        if(IsActive())
            timer.stop();
        timer.start(fps,this);
    }
}

bool MainLocator::IsActive() const
{
    return timer.isActive();
}


void MainLocator::CleanDataBuffer()
{

}

QColor MainLocator::SelectColor(const QString option,const QString title="")
{
    if(!title.isEmpty())
        Color->setWindowTitle("title");
    return color[option]=Color->getColor();
}

void MainLocator::GenerationRay()
{
    GenerationRay(radians_size);
}

void MainLocator::GenerationRay(qint16 angle)
{
    ray.clear();
    Points*i=radians,*end=radians+angle;
    while(i<end)ray.append(clockwise ? end-- : i++);
}

qreal MainLocator::CalcAlpha(qreal angle) const
{
    qreal alpha;
    if(settings["system"]["show"].toBool())
        alpha=1.0f;
    else
    {
        alpha=(clockwise ? -1 : 1)*((*ray_position)->angle-angle)-.01;
        if(not_clean && alpha<.0f)
            alpha+=2u*M_PI;
    }
    return alpha;
}

void MainLocator::GenerationRange()
{
    qreal r=.0f,delta,distance;
    quint8 j=0u,d=0u;
    range.clear();

    distance=CalcScaleValue(1.0f);
    switch(settings["system"]["range"].toUInt())
    {
        case 1:
            delta=distance*10u;
            j=5u;
            break;
        case 0:
            return;
        default:
            delta=distance*50u;
            j=1u;
    }

    LineEntity cache;
    quint16 c;
    while(r<=1u)
    {
        cache.width=d%j==0u ? 3.5f : 1.0f;
        cache.Coordinates=new Points[radians_size];
        c=0u;
        for(Points *i=radians,*end=radians+radians_size;i<end;i++,c++)
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


/**
 * Отрисовка отметок дальности
 * @brief MainLocator::DrawRange
 */
void MainLocator::DrawRange() const
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
                alpha=alpha<settings["system"]["lightning"].toDouble() ? 1.0f : settings["system"]["lightning"].toDouble()/alpha;
                glColor4f(static_cast<GLfloat>(.925),static_cast<GLfloat>(.714),static_cast<GLfloat>(.262),alpha*settings["system"]["brightness"].toDouble());
                glVertex2d(i->x,i->y);
            }
        }
        glEnd();
    }
}

void MainLocator::GenerationAzimuth()
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
    for(Points *i=radians,*k=radians+radians_size;i<k;i+=delta)
    {
        cache.width=(i-radians)%30u>0u ? 1.0f : 3.5f;
        cache.Coordinates=new Points[1];
        cache.Coordinates->angle=i->angle;
        cache.Coordinates->x=i->x;
        cache.Coordinates->y=i->y;
        azimuth.append(cache);
    }
}

/**
 * Отрисовка меток азимута
 * @brief MainLocator::DrawAzimuth
 */
void MainLocator::DrawAzimuth() const
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

void MainLocator::CreateEllipseTrashArea(QVector<PointsPath>&storage,qreal offset_x,qreal offset_y,qreal intensity,bool ellipse,bool clear=true)
{
    return CreateEllipseTrashArea(storage,.0f,GetRandomCoord(4u)*10u,offset_x,offset_y,intensity,ellipse,clear);
}

void MainLocator::CreateEllipseTrashArea(QVector<PointsPath>&storage,qreal begin,qreal end,qreal offset_x,qreal offset_y,qreal intensity=3.0f,bool ellipse=false,bool clear=true)
{
    qreal rand;
    begin=CalcScaleValue(begin),
    end=CalcScaleValue(end);
    if(clear)
        storage.clear();
    PointsPath cache;
    for(Points*i=radians,*k=radians+radians_size;i<k;i++)
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

void MainLocator::DrawEllipseTrashArea(QVector<PointsPath>storage,quint8 size=8u) const
{
    glPointSize(size*settings["system"]["focus"].toDouble());
    glEnable(GL_ALPHA_TEST);
    qreal alpha;
    for(QVector<PointsPath>::const_iterator it=storage.begin();it<storage.end();it++)
    {
        alpha=CalcAlpha(it->angle);
        if(alpha>.0f)
        {
            alpha=alpha<settings["system"]["lightning"].toDouble() ? 1.0f : settings["system"]["lightning"].toDouble()/alpha;
            alpha*=settings["system"]["brightness"].toDouble()+it->r-(1-settings["system"]["varu"].toDouble());
            glBegin(GL_POINTS);
            glColor4f(static_cast<GLfloat>(.925),static_cast<GLfloat>(.714),static_cast<GLfloat>(.262),alpha*settings["system"]["brightness"].toDouble());
            glVertex2f(it->x,it->y);
            glEnd();
        }
    }
}

void MainLocator::GenerationTrash()
{
    CreateEllipseTrashArea(Cache.trash,settings["trash"]["begin"].toDouble(),settings["trash"]["end"].toDouble(),.0f,.0f,settings["trash"]["intensity"].toUInt() ?: 1u);
}

/**
 * Отрисовка пассивных помех
 * @brief MainLocator::DrawTrash
 */
void MainLocator::DrawTrash() const
{
    DrawEllipseTrashArea(Cache.trash,2u);
}

void MainLocator::GenerationLocalItems()
{
    CreateEllipseTrashArea(Cache.local_items,.0f,15.0f,.0f,.0f);
}

void MainLocator::DrawLocalItems() const
{
    DrawEllipseTrashArea(Cache.local_items);
}

void MainLocator::GenerationMeteo()
{
    CreateEllipseTrashArea(Cache.meteo,20.0f,20.0f,3u,true);
    CreateEllipseTrashArea(Cache.meteo,-20.0f,20.0f,3u,true,false);
    CreateEllipseTrashArea(Cache.meteo,-30.0f,-30.0f,3u,true,false);
    CreateEllipseTrashArea(Cache.meteo,-50.0f,-10.0f,3u,true,false);
}

void MainLocator::DrawMeteo() const
{
    DrawEllipseTrashArea(Cache.meteo,5);
}


void MainLocator::GenerationActiveNoiseTrash()
{
    quint8 density=17;
    qint16 angle;
    Cache.active_noise_trash.clear();

    LineEntity cache;
    switch(settings["active_noise_trash"]["intensity"].toUInt())
    {
        case 0:
            angle=settings["active_noise_trash"]["azimuth"].toUInt();
            for(Points*i=radians+radians_size-angle,*k=radians+radians_size-angle+20;i<k;i++)
            {
                cache.Coordinates=new Points[1];
                cache.Coordinates->angle=i->angle;
                cache.Coordinates->x=i->x;
                cache.Coordinates->y=i->y;
                cache.width=GetRandomCoord(4)*density;
                Cache.active_noise_trash.append(cache);
            }
            if(angle<20)
                for(Points*i=radians,*k=radians+20-angle;i<k;i++)
                {
                    cache.Coordinates=new Points[1];
                    cache.Coordinates->angle=i->angle;
                    cache.Coordinates->x=i->x;
                    cache.Coordinates->y=i->y;
                    cache.width=GetRandomCoord(4)*density;
                    Cache.active_noise_trash.append(cache);
                }
            break;
        case 1:
            angle=settings["active_noise_trash"]["azimuth"].toUInt();
            for(Points*i=radians+radians_size-angle,*k=radians+radians_size-angle+30;i<k;i++)
            {
                cache.Coordinates=new Points[1];
                cache.Coordinates->angle=i->angle;
                cache.Coordinates->x=i->x;
                cache.Coordinates->y=i->y;
                cache.width=GetRandomCoord(4)*density;
                Cache.active_noise_trash.append(cache);
            }
            angle=settings["active_noise_trash"]["azimuth"].toUInt()+100;
            for(Points*i=radians+radians_size-angle,*k=radians+radians_size-angle+20;i<k;i++)
            {
                cache.Coordinates=new Points[1];
                cache.Coordinates->angle=i->angle;
                cache.Coordinates->x=i->x;
                cache.Coordinates->y=i->y;
                cache.width=GetRandomCoord(4)*density;
                cache.width-=4*density/5;
                Cache.active_noise_trash.append(cache);
            }
            angle=settings["active_noise_trash"]["azimuth"].toUInt()+200;
            for(Points*i=radians+radians_size-angle,*k=radians+radians_size-angle+20;i<k;i++)
            {
                cache.Coordinates=new Points[1];
                cache.Coordinates->angle=i->angle;
                cache.Coordinates->x=i->x;
                cache.Coordinates->y=i->y;
                cache.width=GetRandomCoord(4)*density;
                cache.width-=4*density/5;
                Cache.active_noise_trash.append(cache);
            }
            angle=settings["active_noise_trash"]["azimuth"].toUInt()+300;
            for(Points*i=radians+radians_size-angle,*k=radians+radians_size-angle+20;i<k;i++)
            {
                cache.Coordinates=new Points[1];
                cache.Coordinates->angle=i->angle;
                cache.Coordinates->x=i->x;
                cache.Coordinates->y=i->y;
                cache.width=GetRandomCoord(4)*density;
                cache.width-=4*density/5;
                Cache.active_noise_trash.append(cache);
            }
            break;
        case 2:
            for(Points*i=radians+settings["active_noise_trash"]["azimuth"].toUInt()+260,*k=radians+settings["active_noise_trash"]["azimuth"].toUInt()+280;i<k;i++)
            {
                cache.Coordinates=new Points[1];
                cache.Coordinates->angle=i->angle;
                cache.Coordinates->x=i->x;
                cache.Coordinates->y=i->y;
                cache.width=GetRandomCoord(4)*density;
                Cache.active_noise_trash.append(cache);
            }
            break;
    }
}

void MainLocator::DrawActiveNoiseTrash() const
{
    qreal alpha;
    for(QVector<LineEntity>::const_iterator it=Cache.active_noise_trash.begin();it<Cache.active_noise_trash.end();it++)
    {
        alpha=CalcAlpha(it->Coordinates->angle);
        if(alpha>0)
        {
            glLineWidth(it->width*settings["system"]["focus"].toDouble());
            alpha=alpha<settings["system"]["lightning"].toDouble() ? 1.0f : settings["system"]["lightning"].toDouble()/alpha;
            glBegin(GL_LINES);
            glColor4f(static_cast<GLfloat>(.925f),static_cast<GLfloat>(.714f),static_cast<GLfloat>(.262f),alpha);
            glVertex2d(.0f,.0f);
            glVertex2f(it->Coordinates->x,it->Coordinates->y);
            glEnd();
        }
    }
}

void MainLocator::GenerationActiveAnswerTrash()
{

}

void MainLocator::GenerationActiveInSyncTrash()
{

}

qreal MainLocator::GetRandomCoord(quint8 accuracy,const bool rsign) const
{
    //Фикс странного бага, наблюдающегося под виндой
    if(accuracy>4u)
        accuracy=4u;

    qreal a=(qrand()%quint32(qPow(10u,accuracy)+1u))/qPow(10u,accuracy);
    if(rsign)
        return a*GetRandomSign();
    return a;
}

qint8 MainLocator::GetRandomSign() const
{
    if(rand()%2u)
        return 1u;
    return-1;
}

void MainLocator::LocatorArea() const
{
    color["locator"].isValid() ? qglColor(color["locator"]) : qglColor(Qt::black);
    glBegin(GL_TRIANGLE_FAN);
        for(QVector<Points*>::const_iterator it=circle.begin();it<circle.end();it++)
            glVertex2d((*it)->x,(*it)->y);
    glEnd();
}

/**
 * @brief MainLocator::DrawStation
 * Отрисуем прямоугольник
 */
void MainLocator::DrawStation() const
{
    glRotatef(30.0f, 0.0, 0.0, 1.0);
    glLineWidth(2.0f);
    glColor3f(static_cast<GLfloat>(.925),static_cast<GLfloat>(.714),static_cast<GLfloat>(.262));
    qreal
        distance=CalcScaleValue(1.0f),
        rx=5u*distance,
        ry=10u*distance;
    glTranslatef(rx,.0f,.0f);
    glBegin(GL_LINES);
        glVertex2d(-rx,-ry);
        glVertex2d(-rx,ry);

        glVertex2d(-rx,ry);
        glVertex2d(rx,ry);

        glVertex2d(-rx,-ry);
        glVertex2d(rx,-ry);

        glVertex2d(rx,-ry);
        glVertex2d(rx,ry);
    glEnd();
    glTranslatef(-rx,.0f,.0f);
    glRotatef(-30.0f, 0.0, 0.0, 1.0);
}

void MainLocator::ContinueSearch()
{
    updateGL();
    if(ray_position==ray.end()-1u)
        ray_position=ray.begin();
    ray_position++;
}

/*
void MainLocator::DrawActiveAnswerTrash()
{
    qreal alpha;
    for(QHash<quint16,QVector<QHash<QString,qreal> > >::const_iterator it=active_answer_trash.begin();it!=active_answer_trash.end();it++)
    {
        QVector<QHash<QString,qreal> >::const_iterator ct=(*it).begin();//Фикс для возможности установки ширины
        glLineWidth((*ct)["width"]);
        glBegin(GL_LINE_STRIP);
        for(;ct<(*it).end();ct++)
        {
            if(show)
                alpha=1.0f;
            else
            {
                alpha=(**line_position)["angle"]-(*ct)["angle"]-0.01f;
                if(not_clean && alpha<0)
                    alpha+=2*M_PI;
            }
            if(alpha>0)
            {
                alpha=alpha<options["interval"] ? 1.0f : options["interval"]/alpha;
                alpha*=options["brightness"]-(*ct)["r"]+options["varu"];
                glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha);
                glVertex2d((*ct)["x"],(*ct)["y"]);
            }
        }
        glEnd();
    }
}

void MainLocator::DrawActiveInSyncTrash()
{
    qreal alpha;
    for(QHash<quint16,QVector<QHash<QString,qreal> > >::const_iterator it=active_insync_trash.begin();it!=active_insync_trash.end();it++)
    {
        QVector<QHash<QString,qreal> >::const_iterator ct=(*it).begin();//Фикс для возможности установки ширины
        glLineWidth((*ct)["width"]);
        glBegin(GL_LINE_STRIP);
        for(;ct<(*it).end();ct++)
        {
            if(show)
                alpha=1.0f;
            else
            {
                alpha=(**line_position)["angle"]-(*ct)["angle"]-0.01f;
                if(not_clean && alpha<0)
                    alpha+=2*M_PI;
            }
            if(alpha>0)
            {
                alpha=alpha<options["interval"] ? 1.0f : options["interval"]/alpha;
                alpha*=options["brightness"]-(*ct)["r"]+options["varu"];
                glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha);
                glVertex2d((*ct)["x"],(*ct)["y"]);
            }
        }
        glEnd();
    }
}
void MainLocator::GenerationTargetPaths()
{
    QHash<QString,qreal>cache;
    qreal i=1.0f,delta,distance;
    quint8 length=0,k=0;
    targets.clear();

    switch(settings["scale"])
    {
        case 2:
            distance=1.0f/150;
            break;
        case 1:
            distance=1.0f/90;
            break;
        default:
            distance=1.0f/45;
    }

    delta=distance*8;
    length=0;
    for(quint8 r=0;r<5;r++,i=0.0f)
    {
        while(i>=0)
        {
            cache["width"]=6;

            for(QVector<QHash<QString,qreal> >::const_iterator it=radians.begin()+length;it<radians.begin()+length+10;it++)
            {
                cache["angle"]=(*it)["angle"];
                cache["x"]=i*(*it)["x"];
                cache["y"]=i*(*it)["y"];
                cache["r"]=qSqrt(qPow(cache["x"],2)+qPow(cache["y"],2));
                targets[k].append(cache);
            }
            k++;
            length+=4*GetRandomSign();
            i-=delta;
        }
    }
}
*/

void MainLocator::DrawTargets()
{
    /*
    qreal alpha;
    //for(QHash<quint16,QVector<QHash<QString,qreal> > >::const_iterator it=targets.begin();it!=targets.end();it++)
    //{
        QVector<QHash<QString,qreal> >::const_iterator ct=targets[targets_pos].begin();//Фикс для возможности установки ширины
        glLineWidth((*ct)["width"]);
        glBegin(GL_LINE_STRIP);
        for(;ct<targets[targets_pos].end();ct++)
        {
            if(show)
                alpha=1.0f;
            else
            {
                alpha=(**line_position)["angle"]-(*ct)["angle"]-0.01f;
                if(not_clean && alpha<0)
                    alpha+=2*M_PI;
            }

            if(alpha>0)
            {
                alpha=alpha<options["interval"] ? 1.0f : options["interval"]/alpha;
                alpha*=options["brightness"]-(*ct)["r"]+options["varu"];
                glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha);
                glVertex2d((*ct)["x"],(*ct)["y"]);
            }
        }
        glEnd();
    //}
    */
}

void MainLocator::ChangeTargetsState()
{
    if(targets_pos<0)
        targets_pos=0;
    else
        targets_pos=-1;
}
