#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,40);

    first = new Mashine(1);
    second = new Mashine(2);
    third = new Mashine(3);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete first;
    delete second;
    delete third;
}

void MainWindow::on_orderButton_clicked()
{
    ClearData();
    PrepareJobsSet();

    int MashineCount = ui->MashinesSpinBox->value();


    solution = solv.Johnson(A, MashineCount);
    if(solution.getOptimalOrder().length() != 0)
    {
        first->setJobs(solution.getOptimalOrder());
        second->setJobs(solution.getOptimalOrder());
        if(MashineCount == 3) third->setJobs(solution.getOptimalOrder());
        ShowResults();

    }
    else ShowError();
}

void MainWindow::ClearData()
{
    A.clear();
    first->clear();
    second->clear();
    third->clear();
}

void MainWindow::PrepareJobsSet()
{
    int JobCount = ui->JobsSpinBox->value();
    int MashineCount = ui->MashinesSpinBox->value();

    int timeOnMashine = 0;

    for(int i=0; i<JobCount; ++i)
     {
          A.append(new Job(i+1,MashineCount));

          for(int j=0; j<MashineCount; ++j)
          {
              if(ui->tableWidget->item(j,i) != NULL)
                  timeOnMashine = ui->tableWidget->item(j,i)->text().toInt();
              else
                  timeOnMashine = 0;
              A[i]->setTimeOnMashine(timeOnMashine,j+1);
          }
     }
}

void MainWindow::ShowResults()
{
    QString result = first->getOrder();
    ui->Orderlabel->setText("Optymalne szeregowanie: " + result);
    int JobCount = ui->JobsSpinBox->value();
    int MashineCount = ui->MashinesSpinBox->value();

    ui->graphicsView->setScene(plot.drawSolutionPlot(first,second,third,JobCount,MashineCount, result));
    ui->graphicsView->show();

    ui->ResultLabel->setText("Wartosc funkcji kryterialnej: " + result);

    if(solution.getJobSetDominance() == FirstOverSecond)
        result = "M2 zdominowana przez M1";
    else if(solution.getJobSetDominance() == ThirdOverSecond)
        result = "M2 zdominowana przez M3";

    if(MashineCount == 3)
        ui->DominanceLabel->setText(result);
    else
        ui->DominanceLabel->setText("");

}

void MainWindow::ShowError()
{
    int MashineCount = ui->MashinesSpinBox->value();

    if(MashineCount == 3)
        ui->ResultLabel->setText("Zadna maszyna nie dominuje nad drugą! Nie mozna szeregować.");
    else
        ui->ResultLabel->setText("Warunek Johnsona nie zostal spelniony!");
}

void MainWindow::on_JobsSpinBox_valueChanged(int arg1)
{
    ui->tableWidget->setColumnCount(arg1);

    for(int i=0; i < arg1; ++i)
        ui->tableWidget->setColumnWidth(i,40);
}

void MainWindow::on_MashinesSpinBox_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1);
    ui->tableWidget->repaint();
    QString tmp;
    QTextStream str(&tmp);
    for(int i=0; i< arg1; ++i)
    {
        str << "P[" << i+1 << "];";
    }
    ui->tableWidget->setVerticalHeaderLabels(tmp.split(";"));
}

void MainWindow::on_actionZapisz_activated()
{

    QString fileName =  QFileDialog::getSaveFileName(this, tr("Zapisywanie jako"), "save.txt", tr("Normal text file (*.txt)"));

    QFile file(fileName);
    QTextStream fileData(&file);

    int JobsCount = ui->JobsSpinBox->value();
    int MashinesCount = ui->MashinesSpinBox->value();

    if(file.open(QIODevice::WriteOnly))
    {
        fileData << JobsCount << " "<< MashinesCount << "\n";

        for(int i=0; i<JobsCount; ++i)
        {
            for(int j=0; j<MashinesCount; ++j)
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

void MainWindow::on_actionOtw_rz_activated()
{

    QString fileName =  QFileDialog::getOpenFileName(this, tr("Otwieranie"), "", tr("Normal text file (*.txt)"));

    QFile file(fileName);
    QTextStream fileData(&file);

    if(file.open(QIODevice::ReadOnly))
    {
        int Jobs, Mashines;
        QString ValueToInsert;
        fileData >> Jobs;
        ui->JobsSpinBox->setValue(Jobs);
        fileData >> Mashines;
        ui->MashinesSpinBox->setValue(Mashines);

        for(int i=0; i< Jobs; ++i)
            for(int j=0; j < Mashines; ++j)
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
