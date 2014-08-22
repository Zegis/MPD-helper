#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QMessageBox>
#include <cstdio>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnWidth(0,40);
    ui->AlgorithmBox->addItem("Johnson");
    ui->AlgorithmBox->addItem("FIFO");
    ui->AlgorithmBox->addItem("LPT");
    ui->AlgorithmBox->addItem("RPT");
    ui->AlgorithmBox->addItem("Hu T.C.");
    ui->tableWidget->verticalHeader()->show();

    chosenAlgorithm = 0;

    for(int i=0; i<3; ++i)
    {
        machines[i] = new Machine(i+1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;

    for(int i=0; i<3; ++i)
        delete machines[i];
}

void MainWindow::on_orderButton_clicked()
{
    ClearData();
    PrepareJobsSet();

    int MachineCount;

    if(chosenAlgorithm == 0)
    {
        MachineCount = ui->MachinesSpinBox->value();
        solution = solv.Johnson(A, MachineCount);
    }
    else if(chosenAlgorithm == 1)
    {
        MachineCount = 1;
        solution = solv.Fifo(A);
    }
    else if(chosenAlgorithm == 2)
    {
        MachineCount = ui->MachinesSpinBox->value();
        solution = solv.LPT(A,MachineCount);
    }
    else if(chosenAlgorithm == 3)
    {
        MachineCount = ui->MachinesSpinBox->value();
        solution = solv.RPT(A,MachineCount);
    }
    else if(chosenAlgorithm == 4)
    {
        MachineCount = ui->MachinesSpinBox->value();
        solution = solv.Hu(A,MachineCount);
    }


    if(solution.isOptimal())
    {
        for(int i=0; i < MachineCount; ++i)
            machines[i]->setJobs(solution.getOptimalOrderForMachine(i));

        ShowResults();

    }
    else ShowError();
}

void MainWindow::ClearData()
{
    A.clear();

    for(int i=0; i<3; ++i)
        machines[i]->clear();
}

void MainWindow::PrepareJobsSet()
{
    int JobCount = ui->JobsSpinBox->value();
    int MachineCount = ui->MachinesSpinBox->value();

    if(chosenAlgorithm == 0)
        PrepareJobsForJohnson(JobCount,MachineCount);
    else if(chosenAlgorithm == 1)
        PrepareJobsForFifo(JobCount);
    else if(chosenAlgorithm == 4)
        PrepareJobsForHu(JobCount);
    else
        PrepareJobsForParallel(JobCount);
}

void MainWindow::PrepareJobsForJohnson(int jobCount, int MachineCount)
{
    int timeOnMachine = 0;

    for(int i=0; i<jobCount; ++i)
     {
          A.append(new Job(i+1,MachineCount));

          for(int j=0; j<MachineCount; ++j)
          {
              if(ui->tableWidget->item(j,i) != NULL)
                  timeOnMachine = ui->tableWidget->item(j,i)->text().toInt();
              else
                  timeOnMachine = 0;
              A[i]->setTimeOnMachine(timeOnMachine,j+1);
          }
     }
}

void MainWindow::PrepareJobsForFifo(int jobCount)
{
    for(int i=0; i<jobCount; ++i)
    {
        A.append(new Job(i+1,1));

        A[i]->setTimeOnMachine(ui->tableWidget->item(0,i)->text().toInt(),1);
        A[i]->setRelaseTime(ui->tableWidget->item(1,i)->text().toInt());
    }
}

void MainWindow::PrepareJobsForHu(int jobCount)
{
    int proceedingJob = 0;

    for(int i=0; i<jobCount; ++i)
    {
        A.append(new Job(i+1,1));
        A[i]->setTimeOnMachine(1,1);

        for(int j=0; j<3; ++j)
        {
            proceedingJob = ui->tableWidget->item(j,i)->text().toInt();

            if(proceedingJob != 0)
                A[i]->addProceedingJob(proceedingJob);
        }
    }
}

void MainWindow::PrepareJobsForParallel(int jobCount)
{
    for(int i=0; i<jobCount; ++i)
    {
        A.append(new Job(i+1,1));

        A[i]->setTimeOnMachine(ui->tableWidget->item(0,i)->text().toInt(),1);
    }
}

void MainWindow::ShowResults()
{
    QString result = solution.getOptimalOrderAsStringForMachine(0);
    ui->Orderlabel->setText("Optymalne szeregowanie: " + result);
    int JobCount = ui->JobsSpinBox->value();
    int MachineCount = (chosenAlgorithm != 1) ? ui->MachinesSpinBox->value() : 1;

    if(chosenAlgorithm != 2 && chosenAlgorithm != 3 && chosenAlgorithm != 4)
        ui->graphicsView->setScene(plot.drawSolutionPlot(machines,MachineCount, JobCount));
    else
        ui->graphicsView->setScene(plot.drawParallelPlot(machines,MachineCount, JobCount));
    ui->graphicsView->show();

    result.setNum(solution.getTimeCriteriaForMachine(0));
    ui->ResultLabel->setText("Wartosc funkcji kryterialnej: " + result);

    if(solution.getJobSetDominance() == FirstOverSecond)
        result = "M2 zdominowana przez M1";
    else if(solution.getJobSetDominance() == ThirdOverSecond)
        result = "M2 zdominowana przez M3";

    if(chosenAlgorithm == 1 && MachineCount == 3)
        ui->DominanceLabel->setText(result);
    else
        ui->DominanceLabel->setText("");

}

void MainWindow::ShowError()
{
    ui->ResultLabel->setText(solution.getErrorMsg());
}

void MainWindow::on_JobsSpinBox_valueChanged(int arg1)
{
    ui->tableWidget->setColumnCount(arg1);

    for(int i=0; i < arg1; ++i)
        ui->tableWidget->setColumnWidth(i,40);
}

void MainWindow::on_MachinesSpinBox_valueChanged(int arg1)
{
    if(chosenAlgorithm == 0)
    {
        ui->tableWidget->setRowCount(arg1);
        ui->tableWidget->repaint();
        PrepareTableWidgetLabels(arg1);
    }
}

void MainWindow::PrepareTableWidgetLabels(int LabelsAmount)
{
    QString tmp;
    QTextStream str(&tmp);
    for(int i=0; i< LabelsAmount; ++i)
    {
        str << "P[" << i+1 << "];";
    }
    ui->tableWidget->setVerticalHeaderLabels(tmp.split(";"));
}

void MainWindow::on_actionZapisz_triggered()
{

    QString fileName =  QFileDialog::getSaveFileName(this, tr("Zapisywanie jako"), "save.txt", tr("Normal text file (*.txt)"));

    QFile file(fileName);
    QTextStream fileData(&file);

    int JobsCount = ui->JobsSpinBox->value();
    int MachinesCount = ui->MachinesSpinBox->value();
    int ChosenAlgorithm = ui->AlgorithmBox->currentIndex();

    if(file.open(QIODevice::WriteOnly))
    {
        fileData << ChosenAlgorithm << " " << JobsCount << " "<< MachinesCount << "\n\r";

        for(int i=0; i< ui->tableWidget->columnCount(); ++i)
        {
            for(int j=0; j< ui->tableWidget->rowCount(); ++j)
            {
                if(ui->tableWidget->item(j,i) != NULL)
                    fileData << ui->tableWidget->item(j,i)->text() << " ";
            }
            fileData << "\n";
        }

        file.close();
    }
    else
    {
        QMessageBox msg;
        msg.setText("Nie udalo sie dokonac zapisu!");
        msg.exec();
    }
}

void MainWindow::on_actionOtworz_triggered()
{

    QString fileName =  QFileDialog::getOpenFileName(this, tr("Otwieranie"), "", tr("Normal text file (*.txt)"));

    QFile file(fileName);


    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream fileData(&file);

        int Jobs, Machines, chosenAlgorithm;
        QString ValueToInsert;
        fileData >> chosenAlgorithm;
        ui->AlgorithmBox->setCurrentIndex(chosenAlgorithm);
        fileData >> Jobs;
        ui->JobsSpinBox->setValue(Jobs);
        fileData >> Machines;
        ui->MachinesSpinBox->setValue(Machines);

        for(int i=0; i< ui->tableWidget->columnCount(); ++i)
            for(int j=0; j < ui->tableWidget->rowCount() ; ++j)
            {
                fileData >> ValueToInsert;
                if(ui->tableWidget->item(j,i) == NULL)
                {
                    QTableWidgetItem *newItem = new QTableWidgetItem(ValueToInsert);
                    ui->tableWidget->setItem(j,i,newItem);
                }
                ui->tableWidget->item(j,i)->setText(ValueToInsert);
            }

        file.close();
    }
    else
    {
        QMessageBox msg;
        msg.setText("Nie mozna otworzyc pliku!");
        msg.exec();
    }
}

void MainWindow::on_AlgorithmBox_currentIndexChanged(int index)
{
    chosenAlgorithm = index;

    int rowsAmount;

    if(chosenAlgorithm == 0)
    {
        rowsAmount = ui->MachinesSpinBox->value();
        ui->tableWidget->setRowCount(rowsAmount);
        PrepareTableWidgetLabels(rowsAmount);
    }
    else if(chosenAlgorithm == 1)
    {
        ui->tableWidget->setRowCount(2);
        QStringList newLabels = (QStringList() << "P" << "R");
        ui->tableWidget->setVerticalHeaderLabels(newLabels);
    }
    else if(chosenAlgorithm == 4)
    {
        ui->tableWidget->setRowCount(3);
        QStringList newLabels = (QStringList() << "Prec[1]" << "Prec[2]" << "Prec[3]");
        ui->tableWidget->setVerticalHeaderLabels(newLabels);
    }
    else
    {
        rowsAmount = 1;
        ui->tableWidget->setRowCount(1);
        PrepareTableWidgetLabels(1);
    }

    ui->tableWidget->repaint();

}
