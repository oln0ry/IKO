#ifndef MAINLOCATOR_H
#define MAINLOCATOR_H

#include<QGLWidget>

class MainLocator : public QGLWidget
{
    Q_OBJECT
    public:
        explicit MainLocator(QWidget *parent = 0);

    signals:

    public slots:
    protected:
        void initializeGL();
        void resizeGL(int nWidth, int nHeight);
        void paintGL();

};

#endif // MAINLOCATOR_H
