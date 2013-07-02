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
//    setDragMode(ScrollHandDrag);
    scene = new QGraphicsScene();
    setScene(scene);
//    setAlignment(Qt::AlignLeft|Qt::AlignTop);
    scaleFactor = 1.0;
    scale(0.1,1.0);
}

void gnattView::wheelEvent(QWheelEvent *event){
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    if (event->delta() > 0)
        scaleFactor = scaleFactor+0.05;
    else
        scaleFactor = 1.0/(scaleFactor+0.05);
    scale(scaleFactor,1);
//    setTransformationAnchor(QGraphicsView::NoAnchor);
}

void gnattView::mouseMoveEvent(QMouseEvent *event){
    if (mouseDown){
        int mX=0, mY=0;
        if (lastY){
            dY += lastY-event->y();
            QPoint point = mapFromScene(topItem->pos());
            if (dY >= dYNeeded){
                dY = 0;
                mY = -1*dYNeeded;
                QScrollBar * scroll = tasks->verticalScrollBar();
                scroll->setValue(scroll->value()+1);

            }
            else if (dY <= -1*dYNeeded){
                dY = 0;
                if (point.y() != 0){
                    mY = dYNeeded;
                    QScrollBar * scroll = tasks->verticalScrollBar();
                    scroll->setValue(scroll->value()-1);
                }
            }
        }
        if (lastX){
            dX = lastX-event->x();
            mX = -1*dX;

        }
        translate(mX,mY);
        lastY = event->y();
        lastX = event->x();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void gnattView::mousePressEvent(QMouseEvent *event){
    setTransformationAnchor(QGraphicsView::NoAnchor);
    mouseDown = true;
    lastY=0;
    lastX = 0;
    dY = 0;
    dX = 0;
    QGraphicsView::mousePressEvent(event);
}

void gnattView::mouseReleaseEvent(QMouseEvent *event){
//    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    mouseDown = false;
    lastY=0;
    lastX=0;
    dY = 0;
    dX = 0;
    QGraphicsView::mouseReleaseEvent(event);
}

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
        QGraphicsRectItem * it = scene->addRect(left,top+rect.height(),minsTo,rect.height());
        if (i==0)
            topItem = it;
        top+=rect.height();
        left+=minsTo;
        qDebug()<<top<<left<<rect;
        dYNeeded=rect.height();
        //draw its nested elements
    }
}
