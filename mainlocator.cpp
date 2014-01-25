#include"mainlocator.h"
#include<qmath.h>
#include<QTime>
#include<QTimer>
#include"QDebug"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

#define GetRadianValue(radian) M_PI*radian/180

MainLocator::MainLocator(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
{
    not_clean=false;
    Color=new QColorDialog(this);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    //Переведём все используемые градусы в радианы
    QHash<QString,qreal>radians;
    for(quint16 i=0;i<360;i++)
    {
        radians["angle"]=GetRadianValue(i);
        radians["x"]=qFastCos(radians["angle"]);
        radians["y"]=qFastSin(radians["angle"]);
        this->radians.append(radians);
    }

    //Михаил Круг
    for(QVector<QHash<QString,qreal> >::const_iterator it=this->radians.begin();it<this->radians.end();circle.append(it),it+=5);

    //Белка и стрелка
    for(QVector<QHash<QString,qreal> >::const_iterator it=this->radians.begin();it<this->radians.end();line.append(it++));

    line_position=line.begin();
    line_end=line.end()-1;

    GenerationTrash();
    GenerationRange();
    GenerationAzimuth();

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
    //glEnable(GL_BLEND);
    //glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
    //glEnable(GL_DEPTH_TEST);
}

void MainLocator::resizeGL(int nWidth, int nHeight)
{
    glEnable(GL_MULTISAMPLE);
    glLoadIdentity();

    qreal ratio=static_cast<GLfloat>(nHeight)/static_cast<GLfloat>(nWidth);
    glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, 0.0, 0.0);
    glViewport(0,0,static_cast<GLint>(nWidth),static_cast<GLint>(nHeight));
}

void MainLocator::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glLoadIdentity(); // загружаем матрицу
    glPushMatrix();
    glLineWidth(2.0);
    //glOrtho(0,wax,way,0,1,0); // подготавливаем плоскости для матрицы
    //glOrtho(0,wax,way,0,1,0);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    LocatorArea();

    glColor3f(static_cast<GLfloat>(0.925),static_cast<GLfloat>(0.714),static_cast<GLfloat>(0.262));//перерисовка линии
    //glColor3f(static_cast<GLfloat>(153/255.0),static_cast<GLfloat>(204/255.0),static_cast<GLfloat>(153/255.0));//перерисовка линии
    glBegin(GL_LINES);
        glVertex2d(static_cast<GLdouble>(0.0),static_cast<GLdouble>(0.0));
        glVertex2d((**line_position)["x"],(**line_position)["y"]);
    glEnd();

    if(!trash.isEmpty())
        DrawTrash();
    if(!range.isEmpty())
        DrawRange();
    if(!azimuth.isEmpty())
        DrawAzimuth();
    glPopMatrix();
    //swapBuffers();
}

void MainLocator::ChangeFPS(qreal fps)
{
    if(IsActive())
        timer->stop();
    if(fps>0)
        timer->start(fps);
}

bool MainLocator::IsActive()
{
    return timer->isActive();
}

void MainLocator::SetSettings(const QString option,const quint8 v)
{
    settings[option]=v;
    if(option=="azimuth_marks")
        GenerationAzimuth();
    else if(option=="range_marks")
        GenerationRange();
    else if(option=="scale")
        GenerationRange();
}

QColor MainLocator::SelectColor(const QString option,const QString title="")
{
    if(!title.isEmpty())
        Color->setWindowTitle("title");
    return color[option]=Color->getColor();
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
    quint8 density=20; //Плотность (густота, кучность) помех
    QHash<QString,qreal>cache;
    qreal begin=0,
          end=30,
          rand;
    for(QVector<QHash<QString,qreal> >::const_iterator it=radians.begin();it<radians.end();it++)
    {
        cache["angle"]=(*it)["angle"];
        for(qint8 k=0,t=qrand()%density;k<t;k++)
        {
            rand=GetRandomCoord(6);
            cache["x"]=end*(*it)["x"]*(rand+begin);
            cache["y"]=end*(*it)["y"]*(rand+begin);
            trash.append(cache);
        }
    }
}

void MainLocator::GenerationRange()
{
    QHash<QString,qreal>cache;
    qreal i=0.0f,delta,distance;
    quint8 j=0,k=0;
    range.clear();

    switch(settings["scale"])
    {
        case 2:
            distance=1.0f/400;
            break;
        case 1:
            distance=1.0f/300;
            break;
        default:
            distance=1.0f/150;
    }

    switch(settings["range_marks"])
    {
        case 1:
            delta=distance*10;
            j=5;
            break;
        case 0:
            return;
        default:
            delta=distance*50;
            j=1;
    }

    while(i<=1)
    {
        if(k%j==0)
            cache["width"]=3.5f;
        else
            cache["width"]=1.0f;
        k++;

        for(QVector<QHash<QString,qreal> >::const_iterator it=radians.begin();it<radians.end();it++)
        {
            cache["angle"]=(*it)["angle"];
            cache["x"]=i*(*it)["x"];
            cache["y"]=i*(*it)["y"];
            range[i*250].append(cache);
        }
        i+=delta;
    }
}

void MainLocator::GenerationAzimuth()
{
    QHash<QString,qreal>cache;
    quint8 delta;
    azimuth.clear();
    switch(settings["azimuth_marks"])
    {
        case 1:
            delta=30;
            break;
        case 0:
            return;
        default:
            delta=10;
    }

    for(QVector<QHash<QString,qreal> >::const_iterator it=radians.begin();it<radians.end();it+=delta)
    {
        cache["angle"]=(*it)["angle"];
        cache["x"]=(*it)["x"];
        cache["y"]=(*it)["y"];
        cache["width"]=(it-radians.begin())%30>0 ? 1.0 : 3.5;
        azimuth.append(cache);
    }
}

qreal MainLocator::GetRandomCoord(const quint8 accuracy,const bool rsign)
{
    qreal a=(qrand()%quint32(qPow(10,accuracy)+1))/qPow(10,accuracy);
    if(rsign)
        return a*GetRandomSign();
    return a;
}

qint8 MainLocator::GetRandomSign()
{
    if(rand()%2)
        return 1.0;
    return-1.0;
}

void MainLocator::LocatorArea()
{
    //glColor3f(static_cast<GLfloat>(255/255.0),static_cast<GLfloat>(153/255.0),static_cast<GLfloat>(0/255.0));// Цвет выделенной области
    color["locator"].isValid() ? qglColor(color["locator"]) : qglColor(Qt::black);
    glBegin(GL_TRIANGLE_FAN);
        for(QVector<QVector<QHash<QString,qreal> >::const_iterator>::const_iterator it=circle.begin();it<circle.end();it++)
            glVertex2d((**it)["x"],(**it)["y"]);
    glEnd();
}

void MainLocator::ContinueSearch()
{
    updateGL();
    if(line_position==line_end)
    {
        if(!not_clean)
            not_clean=true;
        line_position=line.begin();
    }
    else
        line_position++;
}

/**
 * Отрисовка пассивных помех
 * @brief MainLocator::DrawTrash
 */
void MainLocator::DrawTrash()
{
    glPointSize(2);
    glEnable(GL_ALPHA_TEST);
    qreal alpha;
    for(QVector<QHash<QString,qreal> >::const_iterator it=trash.begin();it<trash.end();it++)
    {
        if(show)
            alpha=1;
        else
        {
            alpha=((**line_position)["angle"]-(*it)["angle"]-0.01);
            if(not_clean && alpha<0)
                alpha+=2*M_PI;
        }

        if(alpha>0)
        {
            alpha=alpha<0.6 ? 1 : 0.6/alpha;
            glBegin(GL_POINTS);
            glColor4f(static_cast<GLfloat>(0.925),static_cast<GLfloat>(0.714),static_cast<GLfloat>(0.262),alpha);
            //glColor4f(static_cast<GLfloat>(0.6),static_cast<GLfloat>(0.8),static_cast<GLfloat>(0.6),alpha);
            glVertex2f((*it)["x"],(*it)["y"]);
            glEnd();
        }
    }
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
        glBegin(GL_LINE_STRIP);
        //glLineWidth((*ct)["width"]);
        for(QVector<QHash<QString,qreal> >::const_iterator ct=(*it).begin();ct<(*it).end();ct++)
        {
            if(show)
                alpha=1;
            else
            {
                alpha=((**line_position)["angle"]-(*ct)["angle"]-0.01);
                if(not_clean && alpha<0)
                    alpha+=2*M_PI;
            }
            if(alpha>0)
            {

                alpha=alpha<0.4 ? 1 : 0.4/alpha;
                glColor4f(static_cast<GLfloat>(0.925),static_cast<GLfloat>(0.714),static_cast<GLfloat>(0.262),alpha);
                //glColor4f(static_cast<GLfloat>(0.6),static_cast<GLfloat>(0.8),static_cast<GLfloat>(0.6),0.4/((**line_position)["angle"]-(*ct)["angle"]-0.01));
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
void MainLocator::DrawAzimuth()
{
    qreal alpha;
    for(QVector<QHash<QString,qreal> >::const_iterator it=azimuth.begin();it<azimuth.end();it++)
    {
        if(show)
            alpha=1;
        else
        {
            alpha=((**line_position)["angle"]-(*it)["angle"]-0.01);
            if(not_clean && alpha<0)
                alpha+=2*M_PI;
        }
        if(alpha>0)
        {
            glLineWidth((*it)["width"]);
            alpha=alpha<0.6 ? 1 : 0.6/alpha;
            glBegin(GL_LINES);
            glColor4f(static_cast<GLfloat>(0.925),static_cast<GLfloat>(0.714),static_cast<GLfloat>(0.262),alpha);
            //glColor4f(static_cast<GLfloat>(0.6),static_cast<GLfloat>(0.8),static_cast<GLfloat>(0.6),alpha);
            glVertex2d(0.0,0.0);
            glVertex2f((*it)["x"],(*it)["y"]);
            glEnd();
        }
    }
}
