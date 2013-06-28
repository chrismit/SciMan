#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMap>

#include "task.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void    displayTasks();
    void    addTask(Task *);
    void    drawGnatt();
    
    QMap< QDateTime, Task * > taskMap;

private:
    Ui::MainWindow *ui;
    QTreeWidget * tasks;
    QGraphicsView * view;
    QGraphicsScene * scene;
};

#endif // MAINWINDOW_H
