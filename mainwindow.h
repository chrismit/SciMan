#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTreeWidget>
#include <QSplitter>
#include <QTreeWidgetItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMap>

#include "task.h"
#include "gnattview.h"

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
    bool    isEditable(int);
    
    QMap< QDateTime, Task * > taskMap;
    QMap< QTreeWidgetItem *, Task * > taskItemMap;

public slots:
    void    slot_itemChanged(QTreeWidgetItem *, int);
    void    slot_itemDoubleClicked(QTreeWidgetItem *, int);

private:
    Ui::MainWindow *ui;
    QTreeWidget * tasks;
    gnattView * view;
    QSplitter * splitter;
};

#endif // MAINWINDOW_H
