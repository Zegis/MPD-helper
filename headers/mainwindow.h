#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mashine.h"
#include "solver.h"
#include "headers/ploter.h"
#include "solution.h"
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

    void on_MachinesSpinBox_valueChanged(int arg1);

    void on_actionZapisz_triggered();

    void on_actionOtworz_triggered();

    void on_AlgorithmBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    QList<Job *> A;
    Solver solv;

    Solution solution;

    Ploter plot;

    int chosenAlgorithm;

    Machine* machines[3];

    void ClearData();
    void PrepareJobsSet();
    void PrepareJobsForJohnson(int jobCount, int MachineCount);
    void PrepareJobsForFifo(int jobCount);
    void PrepareJobsForParallel(int jobCount);
    void ShowResults();
    void ShowError();

    void PrepareTableWidgetLabels(int LabelsAmount);
};

#endif // MAINWINDOW_H
