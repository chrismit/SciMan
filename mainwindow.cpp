#include <QDebug>
#include <QSplitter>
#include <QGraphicsView>
#include <QTreeWidget>
#include <QScrollBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gnattview.h"
#include "taskmanager.h"
#include <task.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    //make a splitter for the tasks
    QSplitter * splitter = new QSplitter(Qt::Horizontal);
    tasks = new TaskManager();
    splitter->addWidget(tasks);
    //our graphics view
    view = new gnattView();
    splitter->addWidget(view);
    setCentralWidget(splitter);
    view->tasks = tasks;

    //Connections
    connect(view->verticalScrollBar(), SIGNAL(valueChanged(int)), view, SLOT(slot_scrollTasks(int)));

    //our display
    tasks->displayTasks();
    view->drawGnatt();
}

MainWindow::~MainWindow(){
    delete ui;
}
