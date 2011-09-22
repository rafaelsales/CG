#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent) :
    QGLWidget(parent),
    recursive(false), iterative(false), countRecursive(0), countIterative(0)
{
    setFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
}

void OGLWidget::initializeGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(colorRed, colorGreen, colorBlue);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void OGLWidget::resizeGL(int w, int h){
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);
    glMatrixMode(GL_PROJECTION);
    //Fazendo uma limpeza, carregando a matriz identidade
    glLoadIdentity();
    glOrtho(-10.0, width(), -10.0, height(), -4.0, 4.0);
    //Transformação dos objetos da cena
    glMatrixMode(GL_MODELVIEW);
    //Cena com objetos -> Matriz MODELVIEW
}

void OGLWidget::redraw() {
    updateGL();
    paintGL();
}

void OGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(colorRed, colorGreen, colorBlue);

    if (recursive) {
        drawSierpinskiRecursive();
    } else if (iterative) {
        drawSierpinskiIterative();
    }
}

void OGLWidget::drawSierpinskiIterative() {
    int margin = 20;
    int w = width();
    int h = height();
    GLfloat triangleVertices[3][2] = { {margin, margin}, {w / 2, h - margin}, {w - margin, margin} };

    GLfloat currentPoint[2] = {w / 2, h / 2};

    int randomTree;
    for (int i = 0; i < countIterative; i++) {
        randomTree = rand() % 3;

        currentPoint[0] = (currentPoint[0] + triangleVertices[randomTree][0]) / 2.0;
        currentPoint[1] = (currentPoint[1] + triangleVertices[randomTree][1]) / 2.0;

        glBegin(GL_POINTS);
            glVertex2fv(currentPoint);
        glEnd();
    }

}

void OGLWidget::drawSierpinskiRecursive() {
    int margin = 20;
    int w = width();
    int h = height();
    drawSierpinskiRecursive(QPointF(margin, margin), QPointF(w - margin, margin), QPointF(w / 2, h - margin), countRecursive);
}

void OGLWidget::drawSierpinskiRecursive(QPointF p1, QPointF p2, QPointF p3, int depth) {
    if (depth == 0) {
        glBegin(GL_TRIANGLES);
            glVertex2d(p1.x(), p1.y());
            glVertex2d(p2.x(), p2.y());
            glVertex2d(p3.x(), p3.y());
        glEnd();
    } else {
        depth = depth - 1;
        drawSierpinskiRecursive(p1, (p1 + p2) / 2, (p1 + p3) / 2, depth);
        drawSierpinskiRecursive(p2, (p2 + p3) / 2, (p1 + p2) / 2, depth);
        drawSierpinskiRecursive(p3, (p1 + p3) / 2, (p2 + p3) / 2, depth);
    }
}

void OGLWidget::setColorRed(int value) {
    colorRed = value / 255.0;
    redraw();
}

void OGLWidget::setColorGreen(int value) {
    colorGreen = value / 255.0;
    redraw();
}

void OGLWidget::setColorBlue(int value) {
    colorBlue = value / 255.0;
    redraw();
}
