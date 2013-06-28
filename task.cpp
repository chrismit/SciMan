#include <QDebug>

#include "task.h"

Task::Task()
{
}

QString Task::statusString(){
    if(status == 0)
        return "";
    else if (status == 1)
        return "complete";
    return "";
}

QString Task::getDuration(){
    int day = 60*24;
    int hour = 60;
    qDebug()<<day<<hour<<duration;
    if (day > duration){//tell duration in hours
        QString hours = QString::number(duration/hour);
        QString minutes = QString::number((float)(duration%hour)/(float)hour, 'g', 2).remove(0,1);
        qDebug()<<hours<<minutes;
        if (minutes.isEmpty())
            return hours+" hours";
        return hours+minutes+" hours";
    }
    QString days =QString::number(duration/day);
    QString hours = QString::number((float)(duration%day)/(float)day, 'g', 2).remove(0,1);
    if (hours.isEmpty())
        return days+" days";
    return days+hours+" days";
}
