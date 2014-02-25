#include"righttrianglelocator.h"

RightTriangleLocator::RightTriangleLocator(QWidget *parent):EquiangularTriangleLocator(parent)
{
    clockwise=true; //По часовой стрелке
    //Color=new QColorDialog(this);
    qsrand(QTime(0u,0u,0u).secsTo(QTime::currentTime()));
    //Переведём все используемые градусы в радианы
    for(quint16 i=0u;i<ANGLE_RANGE;i++)
    {
        radians[i].angle=GetRadianValue(i);
        radians[i].x=qFastCos(radians[i].angle);
        radians[i].y=qFastSin(radians[i].angle);
    }
    radians_size=ArraySize(radians);
    for(Points*i=radians,*end=radians+radians_size;i<end;circle.append(i),i+=3u); //Получаем координаты для отрисовки фона индикатора
    GenerationRay();
    ray_position=ray.begin(); //Устанавливаем стартовую позицию луча
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(ContinueSearch()));
    ChangeFPS(1000/24);
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
    glLoadIdentity();
    glViewport(static_cast<GLint>(0u),static_cast<GLint>(0u),static_cast<GLint>(width),static_cast<GLint>(height));
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
    glRotatef(0.0f, 0.0, 0.0, 1.0);
    DrawStation();
    glBegin(GL_LINES);
        glVertex2d(qFastCos(GetRadianValue(226)),qFastSin(GetRadianValue(226)));
        glVertex2d((*ray_position)->x,(*ray_position)->y);
    glEnd();
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
    i=radians,end=radians+46;
    while(i<end)ray.append(clockwise ? end-- : i++);
    i=radians+radians_size-46,end=radians+radians_size;
    while(i<end)ray.append(clockwise ? end-- : i++);
}

void RightTriangleLocator::DrawStation() const
{
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2d(qFastCos(GetRadianValue(226)),qFastSin(GetRadianValue(226)));
        glVertex2d(qFastCos(GetRadianValue(-46)),qFastSin(GetRadianValue(-46)));

        glVertex2d(qFastCos(GetRadianValue(226)),qFastSin(GetRadianValue(226)));
        glVertex2d(qFastCos(GetRadianValue(46)),qFastSin(GetRadianValue(46)));

        glVertex2d(qFastCos(GetRadianValue(236)),qFastSin(GetRadianValue(226)));
        glVertex2d(qFastCos(GetRadianValue(46)),qFastSin(GetRadianValue(345)));

        glVertex2d(qFastCos(GetRadianValue(-46)),qFastSin(GetRadianValue(-46)));
        glVertex2d(qFastCos(GetRadianValue(46)),qFastSin(GetRadianValue(46)));
    glEnd();
}

