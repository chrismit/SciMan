#include <QStringList>
#include <QDebug>

#include "taskmanager.h"

TaskManager::TaskManager(QObject *parent) :
    QTreeWidget()
{
    QStringList headers;
    headers << "Info" << "Task" << "Duration" << "Start" << "End" << "Predecessors";
    setHeaderLabels(headers);

    connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(slot_itemChanged(QTreeWidgetItem*, int)));
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slot_itemDoubleClicked(QTreeWidgetItem*, int)));

    //Sample tasks
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


}


void TaskManager::addTask(Task * task){
    taskMap.insert(task->start, task);
}

void TaskManager::displayTasks(){
    QMapIterator< QDateTime, Task * > it(taskMap);
    while(it.hasNext()){
        it.next();
        Task * task = it.value();
        QStringList sl;
        sl << task->statusString() << task->name << task->getDuration() << task->start.toString() << task->end.toString();
        QTreeWidgetItem * p = new QTreeWidgetItem(sl);
        p->setFlags(p->flags()|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled);
        insertTopLevelItem(0,p);
        taskItemMap.insert(p, task);
    }
}


void TaskManager::slot_itemChanged(QTreeWidgetItem * p, int col){
    qDebug()<<p<<col;
}

bool TaskManager::isEditable(int col){
    if (col != 0)
        return true;
    return false;
}

void TaskManager::slot_itemDoubleClicked(QTreeWidgetItem * p, int col){
    if (isEditable(col)){
        p->setFlags(p->flags()|Qt::ItemIsEditable);
        editItem(p, col);
    }
    else
        p->setFlags(p->flags()& ~(Qt::ItemIsEditable));
}
