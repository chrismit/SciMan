#ifndef GNATTVIEW_H
#define GNATTVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTreeWidget>

class gnattView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit gnattView(QObject *parent = 0);
    void drawGnatt();
    
    QGraphicsScene * scene;
    QTreeWidget * tasks;
    int lastY;
    float scaleFactor;

signals:
    
public slots:
    void slot_scrollTasks(int);

protected:

    virtual void wheelEvent(QWheelEvent *event);
//    virtual void mouseMoveEvent(QMouseEvent *event);
//    virtual void mousePressEvent(QMouseEvent *event);
    
};

#endif // GNATTVIEW_H
