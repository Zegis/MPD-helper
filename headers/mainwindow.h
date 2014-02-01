#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mashine.h"
#include "solver.h"
#include <Qlist>
#include <QGraphicsScene>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QGraphicsSimpleTextItem>
#include <QFile>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_orderButton_clicked();

    void on_JobsSpinBox_valueChanged(int arg1);

    void on_MashinesSpinBox_valueChanged(int arg1);

    void on_actionZapisz_activated();

    void on_actionOtw_rz_activated();

private:
    Ui::MainWindow *ui;

    QList<Job *> A;
    Solver solv;

    QColor colorTab[10];

    Mashine * first;
    Mashine * second;
    Mashine * third;

    QGraphicsScene plot;

    void ClearData();
    void PrepareJobsSet();
    void ShowResults();
    void ShowError();
    void PrepareLabels(int maxTime);

    Dominance JobSetDominance;
};

#endif // MAINWINDOW_H
