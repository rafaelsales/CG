#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QGLWidget>

class OGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit OGLWidget(QWidget *parent = 0);
    virtual void redraw();

    bool recursive;
    bool iterative;
    int countRecursive;
    int countIterative;
signals:

public slots:
    void setColorRed(int value);
    void setColorGreen(int value);
    void setColorBlue(int value);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void drawSierpinskiIterative();
    virtual void drawSierpinskiRecursive();
    virtual void drawSierpinskiRecursive(QPointF p1, QPointF p2, QPointF p3, int depth);

    float colorRed;
    float colorGreen;
    float colorBlue;
};

#endif // OGLWIDGET_H
