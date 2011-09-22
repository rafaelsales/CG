#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnDraw, SIGNAL(pressed()), this, SLOT(draw()));
    connect(ui->rdbIterative, SIGNAL(toggled(bool)), this, SLOT(setTypeIterative(bool)));
    connect(ui->rdbRecursive, SIGNAL(toggled(bool)), this, SLOT(setTypeRecursive(bool)));
    connect(ui->sldRed, SIGNAL(valueChanged(int)), ui->oglwidget, SLOT(setColorRed(int)));
    connect(ui->sldGreen, SIGNAL(valueChanged(int)), ui->oglwidget, SLOT(setColorGreen(int)));
    connect(ui->sldBlue, SIGNAL(valueChanged(int)), ui->oglwidget, SLOT(setColorBlue(int)));

    ui->rdbRecursive->setChecked(true);
    setTypeRecursive(true);
    setTypeIterative(false);

    ui->oglwidget->setColorRed(ui->sldRed->value());
    ui->oglwidget->setColorGreen(ui->sldGreen->value());
    ui->oglwidget->setColorBlue(ui->sldBlue->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTypeRecursive(bool checked) {
    ui->spnRecursive->setEnabled(checked);
}

void MainWindow::setTypeIterative(bool checked) {
    ui->spnIterative->setEnabled(checked);
}

void MainWindow::draw() {
    ui->oglwidget->iterative = ui->rdbIterative->isChecked();
    ui->oglwidget->recursive = ui->rdbRecursive->isChecked();
    ui->oglwidget->countIterative = ui->spnIterative->value();
    ui->oglwidget->countRecursive = ui->spnRecursive->value();

    ui->oglwidget->redraw();
}
