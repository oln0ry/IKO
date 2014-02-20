#include"mainlocator.h"
#include<qmath.h>
#include<QTime>
#include<QTimer>
#include<QDebug>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

#ifndef GetRadianValue
#define GetRadianValue(radian) M_PI*radian/180
#endif

//Макрос стырен из Chromium, т.к. это пока лучшее, что можно придумать для подсчёта элементов массива
#ifndef ArraySize
template<typename T,size_t N>
char(&ArraySizeHelper(T(&array)[N]))[N];
#define ArraySize(array)(sizeof(ArraySizeHelper(array)))
#endif

MainLocator::MainLocator(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
{
    targets_pos=-1;
    not_clean=false;
    show=false;
    show_trash=true;
    show_local_items=false;
    show_active_ntrash=false;
    show_active_atrash=false;
    show_meteo=false;
    fps=1000/24;
    options["brightness"]=1.0f;
    options["interval"]=0.6f;
    options["focus"]=1.0f;
    options["active_answer_distance"]=0.0f;
    settings["trash_intensity"]=0;
    settings["scale"]=0;

    clockwise=true; //По часовой стрелке
    Color=new QColorDialog(this);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    //Переведём все используемые градусы в радианы
    QHash<QString,qreal>radians;
    for(quint16 i=0;i<ANGLE_RANGE;i++)
    {
        n_radians[i].angle=GetRadianValue(i);
        n_radians[i].x=qFastCos(n_radians[i].angle);
        n_radians[i].y=qFastSin(n_radians[i].angle);
    }
    radians_size=ArraySize(n_radians);
    for(Radians *i=n_radians,*k=n_radians+radians_size;i<k;n_circle.append(*i),i+=3); //Получаем координаты для отрисовки фона индикатора
    GenerationRay();
    ray_position=ray.begin(); //Устанавливаем стартовую позицию луча
    GenerationTrash();
    /*
    GenerationRange();
    GenerationAzimuth();
    GenerationLocalItems();
    GenerationActiveNoiseTrash();
    GenerationActiveAnswerTrash();
    GenerationActiveInSyncTrash();
    GenerationTargetPaths();
    GenerationMeteo();
    */
    timer=new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(ContinueSearch()));
    ChangeFPS(fps);
}

MainLocator::~MainLocator()
{
    //if(timer->isActive());//dtimer->stop;
    delete timer;
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

void MainLocator::resizeGL(int nWidth, int nHeight)
{
    glEnable(GL_MULTISAMPLE);
    glLoadIdentity();

    qreal ratio=static_cast<GLfloat>(nHeight)/static_cast<GLfloat>(nWidth);
    glOrtho(-1.0f/ratio, 1.0f/ratio, -1.0f, 1.0f, 0.0f, 0.0f);
    glViewport(0,0,static_cast<GLint>(nWidth),static_cast<GLint>(nHeight));
}

void MainLocator::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glLoadIdentity(); // загружаем матрицу
    glPushMatrix();
    //glRotatef(37.0f, 0.0, 0.0, 1.0);
    glLineWidth(2.0f*options["focus"]);
    //glOrtho(0,wax,way,0,1,0); // подготавливаем плоскости для матрицы
    //glOrtho(0,wax,way,0,1,0);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    LocatorArea();
    DrawStation();
    glColor4f(static_cast<GLfloat>(0.925),static_cast<GLfloat>(0.714),static_cast<GLfloat>(0.262),options["brightness"]);//перерисовка линии
    glBegin(GL_LINES);
        glVertex2d(static_cast<GLdouble>(0.0),static_cast<GLdouble>(0.0));
        glVertex2d((*ray_position).x,(*ray_position).y);
    glEnd();
    /*
    if(show_trash && !trash.isEmpty())
        DrawTrash();
    if(!range.isEmpty())
        DrawRange();
    if(!azimuth.isEmpty())
        DrawAzimuth();
    if(show_local_items && !local_items.isEmpty())
        DrawLocalItems();
    if(show_active_ntrash && !active_noise_trash.isEmpty())
        DrawActiveNoiseTrash();
    if(show_active_atrash && !active_answer_trash.isEmpty())
        DrawActiveAnswerTrash();
    if(show_active_isynctrash && !active_insync_trash.isEmpty())
        DrawActiveInSyncTrash();
    if(targets_pos>=0)
        DrawTargets();
    if(show_meteo && !meteo.isEmpty())
        DrawMeteo();
    */
    glPopMatrix();
    //swapBuffers();
}

void MainLocator::ChangeFPS(qreal fps)
{
    if(fps<=0.0f && IsActive())
        timer->stop();
    if(fps>0.0f)
        timer->start(fps);
}

bool MainLocator::IsActive()
{
    return timer->isActive();
}


void MainLocator::CleanDataBuffer()
{

}

void MainLocator::SetSettings(const QString option,const quint16 v)
{
    updateGL();
}

void MainLocator::SetSettings(const QString option,const qreal v)
{

    updateGL();
}


QColor MainLocator::SelectColor(const QString option,const QString title="")
{
    if(!title.isEmpty())
        Color->setWindowTitle("title");
    return color[option]=Color->getColor();
}

void MainLocator::GenerationRay()
{
    Radians *i=n_radians,*k=n_radians+radians_size;
    while(i<k)ray.append(clockwise ? *k-- : *i++);
}

/**
 *  Генератор помех
 *
 *  Я, честно говоря, пропинал балду, когда мы изучали распределения Гаусса и Пуассона. Поэтому вот вам моё творчество.
 *
 *  @brief MainLocator::GenerationTrash
 */

void MainLocator::GenerationTrash()
{
    /*
    Cache.trash->clear();
    quint8 intensity;
    //Очередной жопский костыль
    if(settings["trash_intensity"]<=0)
        intensity=1;
    else
        intensity=settings["trash_intensity"];

    RadiansEx cache;
    for(quint16 *it=n_radians;it<radians_size;it++)
    {
        cache.angle=(*it).angle;
        for(qint16 k=0,t=qrand()%intensity;k<t;k++)
        {
            rand=begin+fmod((GetRandomCoord(6)+begin),(end-begin));
            cache.x=(*it).x*rand;
            cache.y=(*it).y*rand;
            cache.r=qSqrt(qPow(cache.x,2)+qPow(cache.y,2));
            Cache.trash->append(cache);
        }
    }
    */
}

void MainLocator::GenerationRange()
{

}

void MainLocator::GenerationAzimuth()
{

}

void MainLocator::GenerationLocalItems()
{

}

void MainLocator::GenerationActiveNoiseTrash()
{

}

void MainLocator::GenerationActiveAnswerTrash()
{

}

void MainLocator::GenerationActiveInSyncTrash()
{

}

qreal MainLocator::GetRandomCoord(quint8 accuracy,const bool rsign)
{
    //Фикс странного бага, наблюдающегося под виндой
    if(accuracy>4)
        accuracy=4;

    qreal a=(qrand()%quint32(qPow(10,accuracy)+1))/qPow(10,accuracy);
    if(rsign)
        return a*GetRandomSign();
    return a;
}

qint8 MainLocator::GetRandomSign()
{
    if(rand()%2)
        return 1.0f;
    return-1.0f;
}

void MainLocator::LocatorArea()
{
    //glColor3f(static_cast<GLfloat>(255/255.0),static_cast<GLfloat>(153/255.0),static_cast<GLfloat>(0/255.0));// Цвет выделенной области
    color["locator"].isValid() ? qglColor(color["locator"]) : qglColor(Qt::black);
    glBegin(GL_TRIANGLE_FAN);
        for(QVector<Radians>::const_iterator it=n_circle.begin();it<n_circle.end();it++)
            glVertex2d((*it).x,(*it).y);
    glEnd();
}

/**
 * @brief MainLocator::DrawStation
 * Отрисуем прямоугольник
 */
void MainLocator::DrawStation()
{
    //if(settings["scale"]!=0)
       // return;

    glLineWidth(2.0);
    glColor3f(static_cast<GLfloat>(0.925),static_cast<GLfloat>(0.714),static_cast<GLfloat>(0.262));
    qreal distance;
    switch(settings["scale"])
    {
        /*
        case 2:
            distance=1.0f/400;
            break;
        case 1:
            distance=1.0f/300;
            break;
        default:
            distance=1.0f/150;
        */
        case 2:
            distance=1.0f/150;
            break;
        case 1:
            distance=1.0f/90;
            break;
        default:
            distance=1.0f/45;
    }

    qreal rx=5*distance,ry=10*distance;
    glTranslatef(rx, 0.0f, 0.0);
    //qreal rx = 0.1,
    //ry = 0.2;
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
    glTranslatef(-rx, 0.0f, 0.0);
}

void MainLocator::ContinueSearch()
{
    updateGL();
    bool f=0;
    if(ray_position==ray.end())
    {
        ray_position=ray.begin();
    }
    else
        //line_position++;
        ray_position++;
}

/**
 * Отрисовка отметок дальности
 * @brief MainLocator::DrawRange
 */
void MainLocator::DrawRange()
{
    qreal alpha;
    for(QHash<quint16,QVector<QHash<QString,qreal> > >::const_iterator it=range.begin();it!=range.end();it++)
    {
        QVector<QHash<QString,qreal> >::const_iterator ct=(*it).begin();
        glLineWidth((*ct)["width"]*options["focus"]);
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
                glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha*options["brightness"]);
                glVertex2d((*ct)["x"],(*ct)["y"]);
            }
        }
        glEnd();
    }
}

/**
 * Отрисовка меток азимута
 * @brief MainLocator::DrawAzimuth
 */
/*
void MainLocator::DrawAzimuth()
{
    qreal alpha;
    for(QVector<QHash<QString,qreal> >::const_iterator it=azimuth.begin();it<azimuth.end();it++)
    {
        if(show)
            alpha=1.0f;
        else
        {
            alpha=(**line_position)["angle"]-(*it)["angle"]-0.01f;
            if(not_clean && alpha<0)
                alpha+=2*M_PI;
        }
        if(alpha>0)
        {
            glLineWidth((*it)["width"]*options["focus"]);
            alpha=alpha<options["interval"] ? 1.0f : options["interval"]/alpha;
            glBegin(GL_LINES);
            glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha*options["brightness"]);
            glVertex2d(0.0f,0.0f);
            glVertex2f((*it)["x"],(*it)["y"]);
            glEnd();
        }
    }
}

void MainLocator::DrawLocalItems()
{
    glPointSize(8*options["focus"]);
    glEnable(GL_ALPHA_TEST);
    qreal alpha;
    for(QVector<QHash<QString,qreal> >::const_iterator it=local_items.begin();it<local_items.end();it++)
    {
        if(show)
            alpha=1.0f;
        else
        {
            alpha=(**line_position)["angle"]-(*it)["angle"]-0.01f;
            if(not_clean && alpha<0)
                alpha+=2*M_PI;
        }

        if(alpha>0)
        {
            alpha=alpha<options["interval"] ? 1.0f : options["interval"]/alpha;
            glBegin(GL_POINTS);
            glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha*options["brightness"]);
            glVertex2f((*it)["x"],(*it)["y"]);
            glEnd();
        }
    }
}

void MainLocator::DrawActiveNoiseTrash()
{
    qreal alpha;
    for(QVector<QHash<QString,qreal> >::const_iterator it=active_noise_trash.begin();it<active_noise_trash.end();it++)
    {
        if(show)
            alpha=1.0f;
        else
        {
            alpha=(**line_position)["angle"]-(*it)["angle"]-0.01f;
            if(not_clean && alpha<0)
                alpha+=2*M_PI;
        }
        if(alpha>0)
        {
            glLineWidth((*it)["width"]*options["focus"]);
            alpha=alpha<options["interval"] ? 1.0f : options["interval"]/alpha;
            alpha*=options["brightness"]-(*it)["r"]+options["varu"];
            glBegin(GL_LINES);
            glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha);
            glVertex2d(0.0f,0.0f);
            glVertex2f((*it)["x"],(*it)["y"]);
            glEnd();
        }
    }
}

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
}

void MainLocator::GenerationMeteo()
{

}

void MainLocator::DrawMeteo()
{

}

void MainLocator::ChangeTargetsState()
{
    if(targets_pos<0)
        targets_pos=0;
    else
        targets_pos=-1;
}
