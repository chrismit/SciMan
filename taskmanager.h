#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QTreeWidget>
#include <QDateTime>
#include <QTreeWidgetItem>

#include "task.h"

class TaskManager : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TaskManager(QObject *parent = 0);
    void addTask(Task *);
    void displayTasks();
    bool isEditable(int);
    QMap< QDateTime, Task * > taskMap;
    QMap< QTreeWidgetItem *, Task * > taskItemMap;
signals:

public slots:

    void slot_itemChanged(QTreeWidgetItem *, int);
    void slot_itemDoubleClicked(QTreeWidgetItem *, int);

protected:

};

#endif // TASKMANAGER_H
