#ifndef GNATTVIEW_H
#define GNATTVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTreeWidget>
#include <QGraphicsRectItem>

class gnattView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit gnattView(QObject *parent = 0);
    void drawGnatt();
    
    QGraphicsScene * scene;
    QTreeWidget * tasks;
    int lastY;
    int dY;
    int dX;
    int lastX;
    int dYNeeded;
    float scaleFactor;
    bool mouseDown;
    QGraphicsRectItem * topItem;

signals:
    
public slots:
    void slot_scrollTasks(int);

protected:

    virtual void wheelEvent(QWheelEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    
};

#endif // GNATTVIEW_H
