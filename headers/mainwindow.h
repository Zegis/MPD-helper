#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mashine.h"
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
    QList<Job *> B;

    QColor colorTab[10];

    Mashine * first;
    Mashine * second;
    Mashine * third;

    Mashine ** Mashines;

    int JobCount;
    int MashineCount;

    QGraphicsScene plot;

    void ClearData();
    void sortJobsAccordingToMashine(QList<Job*>*,int, int);
    void DoJohnson();
    void PrepareJobsSet();
    void ShowResults();
    void ShowError();
    void PrepareLabels(int maxTime);

    Dominance CheckDominance();

    Dominance JobSetDominance;

    bool JohnsonCondition();
};

#endif // MAINWINDOW_H
