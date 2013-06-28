#include "gnattview.h"

#include <QWheelEvent>
#include <QTreeWidget>
#include <QDateTime>
#include <QScrollBar>
#include <QDebug>
#include <QTreeWidgetItem>

gnattView::gnattView(QObject *parent) :
    QGraphicsView()
{
    setDragMode(ScrollHandDrag);
    scene = new QGraphicsScene();
    setScene(scene);
    setAlignment(Qt::AlignLeft|Qt::AlignTop);
    scaleFactor = 1.0;
    scale(0.1,scaleFactor);
}

void gnattView::wheelEvent(QWheelEvent *event){
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    if (event->delta() > 0)
        scaleFactor = scaleFactor+0.1;
    else
        scaleFactor = 1.0/(scaleFactor+0.1);
    scale(scaleFactor,1);
}

//void gnattView::mouseMoveEvent(QMouseEvent *event){
//    qDebug()<<event->x()<<event->y();
//    if (lastY){
//        tasks->
//    }
//    lastY = event->y();
//    QGraphicsView::mouseMoveEvent(event);
//}

//void gnattView::mousePressEvent(QMouseEvent *event){
//    lastY=0;
//    QGraphicsView::mousePressEvent(event);
//}

void gnattView::slot_scrollTasks(int to){
    float to2 = (float)to;
    tasks->verticalScrollBar()->setValue(to2/scaleFactor);
}

void gnattView::drawGnatt(){
    int top = 0;
    int left= 0;
    //we draw an invisible dot in the upper left corner to keep our view
    //from putting the first item in the upper left
    scene->addRect(left,top,0.001,0.001);
    top+=5;
    for(int i=0;i<tasks->topLevelItemCount();i++){
        qDebug()<<i;
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
