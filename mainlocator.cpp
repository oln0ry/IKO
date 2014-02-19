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
    targets_pos=-1;
    not_clean=false;
    show=false;
    show_trash=true;
    show_local_items=false;
    show_active_ntrash=false;
    show_active_atrash=false;
    fps=1000/24;
    options["brightness"]=1.0f;
    options["interval"]=0.6f;
    options["focus"]=1.0f;
    options["active_answer_distance"]=0.0f;
    settings["trash_intensity"]=0;
    settings["scale"]=0;
    //settings["active_ntrash_azimuth"]=25;
    //settings["active_atrash_azimuth"]=74;
    //show_active_ntrash,show_active_atrash
    Color=new QColorDialog(this);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    //Переведём все используемые градусы в радианы
    QHash<QString,qreal>radians;
    for(quint16 i=0;i<=360;i++)
    {
        radians["angle"]=GetRadianValue(i);
        radians["x"]=qFastCos(radians["angle"]);
        radians["y"]=qFastSin(radians["angle"]);
        //radians["r"]=qSqrt(qPow(radians["x"],2)+qPow(radians["y"],2));
        this->radians.append(radians);
    }

    //Михаил Круг
    for(QVector<QHash<QString,qreal> >::const_iterator it=this->radians.begin();it<this->radians.end();circle.append(it),it+=3);

    //Белка и стрелка
    for(QVector<QHash<QString,qreal> >::iterator it=this->radians.begin();it<this->radians.end();line.append(it++));

    line_position=line.begin();
    line_end=line.end()-1;

    GenerationTrash();
    GenerationRange();
    GenerationAzimuth();
    GenerationLocalItems();
    GenerationActiveNoiseTrash();
    GenerationActiveAnswerTrash();
    GenerationActiveInSyncTrash();
    GenerationTargetPaths();

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
    //glColor3f(static_cast<GLfloat>(153/255.0),static_cast<GLfloat>(204/255.0),static_cast<GLfloat>(153/255.0));//перерисовка линии
    glBegin(GL_LINES);
        glVertex2d(static_cast<GLdouble>(0.0),static_cast<GLdouble>(0.0));
        glVertex2d((**line_position)["x"],(**line_position)["y"]);
    glEnd();

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
    trash.clear();
    local_items.clear();
    active_answer_trash.clear();
    active_noise_trash.clear();
}

void MainLocator::SetSettings(const QString option,const quint16 v)
{
    settings[option]=v;
    if(option=="azimuth_marks")
        GenerationAzimuth();
    else if(option=="range_marks")
        GenerationRange();
    else if(option=="scale")
    {
        GenerationRange();
        GenerationTrash();
        GenerationLocalItems();
    }
    else if(option=="trash_intensity")
        GenerationTrash();
    else if(option=="active_ntrash_azimuth" || option=="active_noise_intensity")
        GenerationActiveNoiseTrash();
    else if(option=="active_atrash_azimuth")
        GenerationActiveAnswerTrash();
    else return;
    updateGL();
}

void MainLocator::SetSettings(const QString option,const qreal v)
{
    options[option]=v;
    if(option=="brightness");
    else if(option=="interval");
    else if(option=="focus");
    else if(option=="varu");
    else if(option=="trash_begin")
        GenerationTrash();
    else if(option=="trash_end")
        GenerationTrash();
    else if(option=="active_answer_distance")
        GenerationActiveAnswerTrash();
    else return;
    updateGL();
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
    quint16 density; //Плотность (густота, кучность) помех
    QHash<QString,qreal>cache;
    qreal rand,begin,end;
    trash.clear();

    switch(settings["scale"])
    {
        /*
        case 2:
            begin=static_cast<qreal>(options["trash_begin"])/400;
            end=static_cast<qreal>(options["trash_end"])/400;
            //distance=1.0f/400;
            break;
        case 1:
            begin=static_cast<qreal>(options["trash_begin"])/300;
            end=static_cast<qreal>(options["trash_end"])/300;
            //distance=1.0f/300;
            break;
        default:
            begin=static_cast<qreal>(options["trash_begin"])/150;
            end=static_cast<qreal>(options["trash_end"])/150;
            //distance=1.0f/150;
        */
        case 2:
            begin=static_cast<qreal>(options["trash_begin"])/150;
            end=static_cast<qreal>(options["trash_end"])/150;
            //distance=1.0f/400;
            break;
        case 1:
            begin=static_cast<qreal>(options["trash_begin"])/90;
            end=static_cast<qreal>(options["trash_end"])/90;
            //distance=1.0f/300;
            break;
        default:
            begin=static_cast<qreal>(options["trash_begin"])/45;
            end=static_cast<qreal>(options["trash_end"])/45;
        //distance=1.0f/150;

    }

    /*
    switch(settings["trash_intensity"])
    {
        case 2:
            density=20;
            break;
        case 1:
            density=10;
            break;
        default:
            density=5;
    }
    */

    //Очередной жопский костыль
    if(settings["trash_intensity"]<=0)
        density=1;
    else
        density=settings["trash_intensity"];

    for(QVector<QHash<QString,qreal> >::const_iterator it=radians.begin();it<radians.end();it++)
    {
        cache["angle"]=(*it)["angle"];
        for(qint16 k=0,t=qrand()%density;k<t;k++)
        {
            rand=begin+fmod((GetRandomCoord(6)+begin),(end-begin));
            cache["x"]=(*it)["x"]*rand;
            cache["y"]=(*it)["y"]*rand;
            cache["r"]=qSqrt(qPow(cache["x"],2)+qPow(cache["y"],2));
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
        //qDebug()<<k<<"\t"<<j<<"\t"<<k%j;
        if(k%j==0)
            cache["width"]=2.5f;
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
        cache["width"]=(it-radians.begin())%30>0 ? 1.0f : 3.5f;
        azimuth.append(cache);
    }
}

void MainLocator::GenerationLocalItems()
{
    quint8 density=3;
    QHash<QString,qreal>cache;
    qreal rand,begin=0.0f,end=15.0f;//28.0f;
    local_items.clear();
    switch(settings["scale"])
    {
    /*
        case 2:
            begin=static_cast<qreal>(begin)/400;
            end=static_cast<qreal>(end)/400;
            break;
        case 1:
            begin=static_cast<qreal>(begin)/300;
            end=static_cast<qreal>(end)/300;
            break;
        default:
            begin=static_cast<qreal>(begin)/150;
            end=static_cast<qreal>(end)/150;
    */
        case 2:
            begin=static_cast<qreal>(begin)/150;
            end=static_cast<qreal>(end)/150;
            break;
        case 1:
            begin=static_cast<qreal>(begin)/90;
            end=static_cast<qreal>(end)/90;
            break;
        default:
            begin=static_cast<qreal>(begin)/45;
            end=static_cast<qreal>(end)/45;
    }

    for(QVector<QHash<QString,qreal> >::const_iterator it=radians.begin();it<radians.end();it++)
    {
        cache["angle"]=(*it)["angle"];
        for(qint8 k=0,t=qrand()%density;k<t;k++)
        {
            rand=begin+fmod((GetRandomCoord(6)+begin),(end-begin));
            cache["x"]=(*it)["x"]*rand;
            cache["y"]=(*it)["y"]*rand;
            local_items.append(cache);
        }
    }
}

void MainLocator::GenerationActiveNoiseTrash()
{
    quint8 density=17;
    QHash<QString,qreal>cache;
    active_noise_trash.clear();

    /*
    switch(settings["active_noise_intensity"])
    {
        case 2:
            density=15;
            break;
        case 1:
            density=8;
            break;
        default:
            density=3;
    }
    */

    quint8 ceil;
    ceil=qrand()%10+20;
    QVector<QHash<QString,qreal> >::const_iterator ct;
    for(QVector<QHash<QString,qreal> >::const_iterator it=(radians.begin()+90+settings["active_ntrash_azimuth"]),ct=it;it<(ct+ceil);it++)
    {
        cache["angle"]=(*it)["angle"];
        cache["x"]=(*it)["x"];
        cache["y"]=(*it)["y"];
        cache["r"]=qSqrt(qPow(cache["x"],2)+qPow(cache["y"],2));
        cache["width"]=GetRandomCoord(4)*density;
        active_noise_trash.append(cache);
    }

    quint8 r;
    switch(settings["active_noise_intensity"])
    {
        case 2:
            for(QVector<QHash<QString,qreal> >::const_iterator rt=radians.begin();rt<radians.end();r+=40)
            {
                for(QVector<QHash<QString,qreal> >::const_iterator it=(radians.begin()+r+settings["active_ntrash_azimuth"]),ct=it;it<(ct+20);it++)
                {
                    cache["angle"]=(*it)["angle"];
                    cache["x"]=(*it)["x"];
                    cache["y"]=(*it)["y"];
                    cache["width"]=GetRandomCoord(4)*density/2-2;
                    active_noise_trash.append(cache);
                }
            }
            break;
        case 1:
            for(QVector<QHash<QString,qreal> >::const_iterator it=(radians.begin()+190+settings["active_ntrash_azimuth"]),ct=it;it<(ct+20);it++)
            {
                cache["angle"]=(*it)["angle"];
                cache["x"]=(*it)["x"];
                cache["y"]=(*it)["y"];
                cache["width"]=GetRandomCoord(4)*density/3-2;
                active_noise_trash.append(cache);
            }
            for(QVector<QHash<QString,qreal> >::const_iterator it=(radians.begin()+settings["active_ntrash_azimuth"]),ct=it;it<(ct+20);it++)
            {
                cache["angle"]=(*it)["angle"];
                cache["x"]=(*it)["x"];
                cache["y"]=(*it)["y"];
                cache["width"]=GetRandomCoord(4)*density/3.4-2;
                active_noise_trash.append(cache);
            }
            for(QVector<QHash<QString,qreal> >::const_iterator it=(radians.begin()+280+settings["active_ntrash_azimuth"]),ct=it;it<(ct+20);it++)
            {
                cache["angle"]=(*it)["angle"];
                cache["x"]=(*it)["x"];
                cache["y"]=(*it)["y"];
                cache["width"]=GetRandomCoord(4)*density/3.2-2;
                active_noise_trash.append(cache);
            }
            break;
    }

    /*
    for(QVector<QHash<QString,qreal> >::const_iterator it=(radians.begin()+75+qrand()%150),ct=it;it<(ct+30);it++)
    {
        cache["angle"]=(*it)["angle"];
        cache["x"]=(*it)["x"];
        cache["y"]=(*it)["y"];
        cache["width"]=GetRandomCoord(4)*density-2;
        active_noise_trash.append(cache);
    }*/
}

void MainLocator::GenerationActiveAnswerTrash()
{
    if(options["active_answer_distance"]<=0.0f)
        return;

    QHash<QString,qreal>cache;
    qreal i=0.0f,delta,distance;
    quint8 azimuth=0,length=0,k=0;
    active_answer_trash.clear();

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

    delta=distance*options["active_answer_distance"];

    azimuth=settings["active_atrash_azimuth"];
    length=25;
    while(i<=1)
    {
        k++;
        cache["width"]=qrand()%6;

        for(QVector<QHash<QString,qreal> >::const_iterator it=radians.begin()+90+azimuth;it<radians.begin()+90+azimuth+length;it++)
        {
            cache["angle"]=(*it)["angle"];
            cache["x"]=i*(*it)["x"];
            cache["y"]=i*(*it)["y"];
            //cache["r"]=delta;
            cache["r"]=qSqrt(qPow(cache["x"],2)+qPow(cache["y"],2));
            active_answer_trash[k*250].append(cache);
        }
        i+=delta;
    }
}

void MainLocator::GenerationActiveInSyncTrash()
{
    //if(options["active_insync_distance"]<=0.0f)
        //return;

    QHash<QString,qreal>cache;
    qreal i=0.0f,delta,distance;
    quint8 length=0,k=0;
    active_insync_trash.clear();

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

    delta=distance*6;
    length=0;
    for(quint8 r=0;r<3;r++,i=0.0f)
    {
        while(i<=1)
        {
            k++;
            cache["width"]=qrand()%6;

            for(QVector<QHash<QString,qreal> >::const_iterator it=radians.begin()+length;it<radians.begin()+length+25;it++)
            {
                cache["angle"]=(*it)["angle"];
                cache["x"]=i*(*it)["x"];
                cache["y"]=i*(*it)["y"];
                //cache["r"]=delta;
                cache["r"]=qSqrt(qPow(cache["x"],2)+qPow(cache["y"],2));
                active_insync_trash[k*250].append(cache);
            }
            length+=4;
            i+=delta;
        }
    }
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
        for(QVector<QVector<QHash<QString,qreal> >::const_iterator>::const_iterator it=circle.begin();it<circle.end();it++)
            glVertex2d((**it)["x"],(**it)["y"]);
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
    if(line_position==line_end)
    {
        if(f=f||trash.isEmpty())
            GenerationTrash();
        if(f=f||local_items.isEmpty())
            GenerationLocalItems();
        if(f=f||active_answer_trash.isEmpty())
            GenerationActiveAnswerTrash();
        if(f=f||active_noise_trash.isEmpty())
            GenerationActiveNoiseTrash();
        if(f)
            not_clean=false;
        else if(!not_clean)
            not_clean=true;
        line_position=line.begin();
        if(targets_pos>=targets.size()-1)
                targets_pos=-1;
        else if(targets_pos>=0)
            targets_pos++;
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
    glPointSize(2*options["focus"]);
    glEnable(GL_ALPHA_TEST);
    qreal alpha;
    for(QVector<QHash<QString,qreal> >::const_iterator it=trash.begin();it<trash.end();it++)
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
            alpha*=options["brightness"]-(*it)["r"]+options["varu"];
            glBegin(GL_POINTS);
            glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha);
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
        QVector<QHash<QString,qreal> >::const_iterator ct=(*it).begin();
        glLineWidth((*ct)["width"]*options["focus"]);
        glBegin(GL_LINE_STRIP);
        for(;ct<(*it).end();ct++)
        {
            if(show)
                alpha=1.0f;
            else
            {
                alpha=((**line_position)["angle"]-(*ct)["angle"]-0.01f);
                if(not_clean && alpha<0)
                    alpha+=2*M_PI;
            }
            if(alpha>0)
            {
                alpha=alpha<options["interval"] ? 1.0f : options["interval"]/alpha;
                glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha*options["brightness"]);
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
            alpha=1.0f;
        else
        {
            alpha=((**line_position)["angle"]-(*it)["angle"]-0.01f);
            if(not_clean && alpha<0)
                alpha+=2*M_PI;
        }
        if(alpha>0)
        {
            glLineWidth((*it)["width"]*options["focus"]);
            alpha=alpha<options["interval"] ? 1.0f : options["interval"]/alpha;
            glBegin(GL_LINES);
            glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha*options["brightness"]);
            //glColor4f(static_cast<GLfloat>(0.6),static_cast<GLfloat>(0.8),static_cast<GLfloat>(0.6),alpha);
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
            alpha=((**line_position)["angle"]-(*it)["angle"]-0.01f);
            if(not_clean && alpha<0)
                alpha+=2*M_PI;
        }

        if(alpha>0)
        {
            alpha=alpha<options["interval"] ? 1.0f : options["interval"]/alpha;
            glBegin(GL_POINTS);
            glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha*options["brightness"]);
            //glColor4f(static_cast<GLfloat>(0.6),static_cast<GLfloat>(0.8),static_cast<GLfloat>(0.6),alpha);
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
            alpha=((**line_position)["angle"]-(*it)["angle"]-0.01f);
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
            //glColor4f(static_cast<GLfloat>(0.6),static_cast<GLfloat>(0.8),static_cast<GLfloat>(0.6),alpha);
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
                alpha=((**line_position)["angle"]-(*ct)["angle"]-0.01f);
                if(not_clean && alpha<0)
                    alpha+=2*M_PI;
            }
            if(alpha>0)
            {
                alpha=alpha<options["interval"] ? 1.0f : options["interval"]/alpha;
                alpha*=options["brightness"]-(*ct)["r"]+options["varu"];
                glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha);
                //glColor4f(static_cast<GLfloat>(0.6),static_cast<GLfloat>(0.8),static_cast<GLfloat>(0.6),0.4/((**line_position)["angle"]-(*ct)["angle"]-0.01));
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
                alpha=((**line_position)["angle"]-(*ct)["angle"]-0.01f);
                if(not_clean && alpha<0)
                    alpha+=2*M_PI;
            }
            if(alpha>0)
            {
                alpha=alpha<options["interval"] ? 1.0f : options["interval"]/alpha;
                alpha*=options["brightness"]-(*ct)["r"]+options["varu"];
                glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha);
                //glColor4f(static_cast<GLfloat>(0.6),static_cast<GLfloat>(0.8),static_cast<GLfloat>(0.6),0.4/((**line_position)["angle"]-(*ct)["angle"]-0.01));
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
                alpha=((**line_position)["angle"]-(*ct)["angle"]-0.01f);
                if(not_clean && alpha<0)
                    alpha+=2*M_PI;
            }

            if(alpha>0)
            {
                alpha=alpha<options["interval"] ? 1.0f : options["interval"]/alpha;
                alpha*=options["brightness"]-(*ct)["r"]+options["varu"];
                glColor4f(static_cast<GLfloat>(0.925f),static_cast<GLfloat>(0.714f),static_cast<GLfloat>(0.262f),alpha);
                //glColor4f(static_cast<GLfloat>(0.6),static_cast<GLfloat>(0.8),static_cast<GLfloat>(0.6),0.4/((**line_position)["angle"]-(*ct)["angle"]-0.01));
                glVertex2d((*ct)["x"],(*ct)["y"]);
            }
        }
        glEnd();
    //}
}

void MainLocator::ChangeTargetsState()
{
    if(targets_pos<0)
        targets_pos=0;
    else
        targets_pos=-1;
}
