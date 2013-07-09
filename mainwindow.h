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
#include "taskmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

private:
    Ui::MainWindow *ui;
    TaskManager * tasks;
    gnattView * view;
    QSplitter * splitter;
};

#endif // MAINWINDOW_H
