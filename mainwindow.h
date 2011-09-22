#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtOpenGL/QGLWidget>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setTypeRecursive(bool checked);
    void setTypeIterative(bool checked);
    void draw();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
