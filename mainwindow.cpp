#include <QDebug>
#include <QSplitter>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <task.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    //make a splitter for the tasks
    QSplitter * splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(ui->taskDetails);
    splitter->addWidget(ui->gnattView);
    setCentralWidget(splitter);
    tasks = ui->taskDetails;

    //Sample task
    Task * task = new Task();
    task->start = QDateTime::fromString("2013-06-27 15:00", "yyyy-MM-dd HH:mm");
    task->end = QDateTime::fromString("2013-06-30 19:00", "yyyy-MM-dd HH:mm");
    task->status = 1;
    task->name = "Do Something";
    task->duration = task->start.secsTo(task->end)/60;
    addTask(task);
    //

    //Connections
    connect(tasks, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(slot_itemChanged(QTreeWidgetItem*, int)));
    connect(tasks, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slot_itemDoubleClicked(QTreeWidgetItem*, int)));
    //

    view = ui->gnattView;
    scene = new QGraphicsScene();
    view->setScene(scene);
    view->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    displayTasks();
    drawGnatt();
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

void MainWindow::drawGnatt(){
    int top = tasks->header()->height();
    int left= 0;
    //we draw an invisible dot in the upper left corner to keep our view
    //from putting the first item in the upper left
    scene->addRect(left,top,0.001,0.001);
    top+=5;
    for(int i=0;i<tasks->topLevelItemCount();i++){
        QTreeWidgetItem * item = tasks->topLevelItem(0);
        //draw the top item
        QDateTime start = QDateTime::fromString(item->text(3), Qt::TextDate);
        QDateTime end = QDateTime::fromString(item->text(4), Qt::TextDate);
        QRect rect = tasks->visualItemRect(item);
        //we use the notion that 1 minute is equal to 1 unit
        int minsTo = start.secsTo(end)/60;
        scene->addRect(left,top+rect.height(),minsTo,rect.height());
        top+=rect.height();
        left+=minsTo;
        qDebug()<<top<<left<<rect;
        //draw its nested elements
    }
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
