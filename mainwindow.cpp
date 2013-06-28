#include <QDebug>
#include <QSplitter>
#include <QGraphicsView>
#include <QTreeWidget>
#include <QScrollBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gnattview.h"
#include <task.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    //make a splitter for the tasks
    QSplitter * splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(ui->taskDetails);
    //our graphics view
    view = new gnattView();
    splitter->addWidget(view);
    setCentralWidget(splitter);
    tasks = ui->taskDetails;
    view->tasks = tasks;

    //Sample task
    QDateTime sDate = QDateTime::fromString("2013-06-27 15:00", "yyyy-MM-dd HH:mm");
    QDateTime eDate = QDateTime::fromString("2013-06-27 19:00", "yyyy-MM-dd HH:mm");
    for(int i=0;i<1000;i++){
        Task * task = new Task();
        QDateTime nDate = sDate.addDays(i);
        QDateTime nDate2 = eDate.addDays(i);
        nDate2 = nDate2.addMSecs(i*10000);
        task->start=nDate;
        task->end=nDate2;
        //task->end = sDate-> QDateTime::fromString("2013-06-30 19:00", "yyyy-MM-dd HH:mm");
        task->status = 1;
        task->name = "Do Something";
        task->duration = task->start.secsTo(task->end)/60;
        addTask(task);
    }
    //

    //Connections
    connect(tasks, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(slot_itemChanged(QTreeWidgetItem*, int)));
    connect(tasks, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slot_itemDoubleClicked(QTreeWidgetItem*, int)));
    connect(view->verticalScrollBar(), SIGNAL(valueChanged(int)), view, SLOT(slot_scrollTasks(int)));
    //

    displayTasks();
    view->drawGnatt();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::slot_itemChanged(QTreeWidgetItem * p, int col){
    qDebug()<<p<<col;
}

bool MainWindow::isEditable(int col){
    if (col != 0)
        return true;
    return false;
}

void MainWindow::slot_itemDoubleClicked(QTreeWidgetItem * p, int col){
    if (isEditable(col)){
        tasks->editItem(p, col);
    }
}

void MainWindow::addTask(Task * task){
    taskMap.insert(task->start, task);
}

void MainWindow::displayTasks(){
    QMapIterator< QDateTime, Task * > it(taskMap);
    while(it.hasNext()){
        it.next();
        Task * task = it.value();
        QStringList sl;
        sl << task->statusString() << task->name << task->getDuration() << task->start.toString() << task->end.toString();
        QTreeWidgetItem * p = new QTreeWidgetItem(sl);
        p->setFlags(p->flags()|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsEditable);
        tasks->insertTopLevelItem(0,p);
        taskItemMap.insert(p, task);
    }
}
