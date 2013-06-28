#ifndef TASK_H
#define TASK_H

#include <QDateTime>

class Task
{
public:
    Task();
    QString getDuration();
    QString statusString();

    QDateTime start;
    QDateTime end;
    int duration;
    int status;
    QString name;

};

#endif // TASK_H
