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

    colorTab[0].setNamedColor("cyan");
    colorTab[1].setNamedColor("olive");
    colorTab[2].setNamedColor("chartreuse");
    colorTab[3].setNamedColor("chocolate");
    colorTab[4].setNamedColor("coral");
    colorTab[5].setNamedColor("crimson");
    colorTab[6].setNamedColor("olive");
    colorTab[7].setNamedColor("gold");
    colorTab[7].setNamedColor("fuchsia");
    colorTab[9].setNamedColor("tan");
}

MainWindow::~MainWindow()
{
    plot.clear();

    delete ui;
    delete first;
    delete second;
    delete third;
}

void MainWindow::sortJobsAccordingToMashine(QList<Job *> *jobs, int mashineId, int option)
{
        if(option == 1) // nonRising
        {
            for(int i=0; i < jobs->size(); ++i)
                for(int j=0; j < jobs->size() - 1 - i; ++j)
                {
                    if((*jobs)[j]->getTimeFromMashine(mashineId) > (*jobs)[j+1]->getTimeFromMashine(mashineId))
                        jobs->swap(j,j+1);
                }
        }
        else if (option == 0) // nonDecreasing
        {
            for(int i=0; i < jobs->size(); ++i)
                for(int j=0; j < jobs->size() - 1 - i; ++j)
                {
                    if((*jobs)[j]->getTimeFromMashine(mashineId) < (*jobs)[j+1]->getTimeFromMashine(mashineId))
                        jobs->swap(j,j+1);
                }
        }
}

void MainWindow::on_orderButton_clicked()
{
    ClearData();
    PrepareJobsSet();

    int MashineCount = ui->MashinesSpinBox->value();

    if(MashineCount == 3)
        JobSetDominance = CheckDominance();

    if(MashineCount == 2 || JobSetDominance != None)
    {
        DoJohnson();
        if(JohnsonCondition())
            ShowResults();
        else ShowError();
    }
    else
        ShowError();

}

void MainWindow::ClearData()
{
    A.clear();
    B.clear();
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

Dominance MainWindow::CheckDominance()
{
    Dominance ret = None;

    int maxP2 = A[0]->getTimeFromMashinePlotting(2);
    int minP1 = A[0]->getTimeFromMashinePlotting(1);
    int minP3 = A[0]->getTimeFromMashinePlotting(3);;


    int JobCount = ui->JobsSpinBox->value();

    for(int i=1; i<JobCount; ++i)
    {
        if (A[i]->getTimeFromMashinePlotting(2) > maxP2) maxP2 = A[i]->getTimeFromMashinePlotting(2);
        if (A[i]->getTimeFromMashinePlotting(1) < minP1) minP1 = A[i]->getTimeFromMashinePlotting(1);
        if (A[i]->getTimeFromMashinePlotting(3) < minP3) minP3 = A[i]->getTimeFromMashinePlotting(3);
    }

    if(minP1 >= maxP2)
        ret = FirstOverSecond;
    else if (minP3 >= maxP2)
        ret = ThirdOverSecond;
    else
        ret = None;

    return ret;
}

void MainWindow::DoJohnson()
{
    int JobCount = ui->JobsSpinBox->value();
    int MashineCount = ui->MashinesSpinBox->value();

    for(int i=0; i<JobCount;)
    {
        if(A[i]->getTimeFromMashine(1) > A[i]->getTimeFromMashine(2))
        {
            Job* tmp = A[i];

            B.append(tmp);
            A.removeAt(i);
            --JobCount;
        }
        else
            ++i;
    }

    if(A.size() > 0) sortJobsAccordingToMashine(&A,1,1);
    if(B.size() > 0) sortJobsAccordingToMashine(&B,2,0);

    first->setJobs(A+B);
    second->setJobs(A+B);
    if(MashineCount == 3) third->setJobs(A+B);
}

void MainWindow::ShowResults()
{
    QString result = first->getOrder();
    ui->Orderlabel->setText("Optymalne szeregowanie: " + result);
    int JobCount = ui->JobsSpinBox->value();
    JobCount = ui->JobsSpinBox->value();

    int offsetFor2ndJob = first->getEndingTimeForJob(1);
    int offsetFor1stJob = 0;
    int offsetFor3rdJob = 0;
    int jobWidth = 0;
    int job2Width = 0;
    int job3Width = 0;

    plot.clear();
    plot.setSceneRect(0,0,356,86);

    QPen pen(colorTab[0]);
    QBrush brush(colorTab[0]);

    int MashineCount = ui->MashinesSpinBox->value();
    int LabelsCount = JobCount * MashineCount;
    QString tmp;
    QGraphicsSimpleTextItem **TimeLabels = new QGraphicsSimpleTextItem*[LabelsCount];
    for(int i=0; i < LabelsCount; ++i)
    {
        TimeLabels[i] = new QGraphicsSimpleTextItem();
    }

    int j=0;
    for(int i=1; i < JobCount+1; ++i)
    {

        tmp.setNum(first->getJobId(i));
        tmp.insert(0,"Z");

        jobWidth = first->getJobDuration(i);

        TimeLabels[j]->setText(tmp);
        TimeLabels[j]->setPos(24+offsetFor1stJob*20,25);
        plot.addRect(20+offsetFor1stJob*20,20,20*jobWidth,20,pen,brush);
        plot.addItem(TimeLabels[j++]);

        job2Width = second->getJobDuration(i);

        if( offsetFor1stJob + jobWidth >= offsetFor2ndJob)
            offsetFor2ndJob = offsetFor1stJob + jobWidth;

        TimeLabels[j]->setText(tmp);
        TimeLabels[j]->setPos(24+offsetFor2ndJob*20,45);
        plot.addRect(20+offsetFor2ndJob*20,40,20*job2Width,20,pen,brush);
        plot.addItem(TimeLabels[j++]);

        if(MashineCount == 3)
        {
        job3Width = third->getJobDuration(i);

        if( offsetFor2ndJob + job2Width >= offsetFor3rdJob)
            offsetFor3rdJob = offsetFor2ndJob + job2Width;

        TimeLabels[j]->setText(tmp);
        TimeLabels[j]->setPos(24+offsetFor3rdJob*20,65);
        plot.addRect(20+offsetFor3rdJob*20,60,20*job3Width,20,pen,brush);
        plot.addItem(TimeLabels[j++]);
        }

        pen.setColor(colorTab[i]);
        brush.setColor(colorTab[i]);
        offsetFor1stJob = first->getEndingTimeForJob(i);

        offsetFor2ndJob += job2Width;
        offsetFor3rdJob += job3Width;
    }

    ui->graphicsView->setScene(&plot);
    ui->graphicsView->show();

    if(MashineCount == 3)
    {
        result.setNum(offsetFor3rdJob);
        PrepareLabels(offsetFor3rdJob);
    }
    else
    {
        result.setNum(offsetFor2ndJob);
        PrepareLabels(offsetFor2ndJob);
    }
    ui->ResultLabel->setText("Wartosc funkcji kryterialnej: " + result);

    if(JobSetDominance == FirstOverSecond)
        result = "M2 zdominowana przez M1";
    else
        result = "M2 zdominowana przez M3";

    if(MashineCount == 3)
        ui->DominanceLabel->setText(result);
    else
        ui->DominanceLabel->setText("");

}

void MainWindow::PrepareLabels(int maxTime)
{
    int MashineCount = ui->MashinesSpinBox->value();

    QString tmp;
    QGraphicsSimpleTextItem **MashineLabels = new QGraphicsSimpleTextItem*[MashineCount];

    for(int i=0; i < MashineCount; ++i)
    {
        tmp.setNum(i+1);
        tmp.insert(0,"M");

        MashineLabels[i] = new QGraphicsSimpleTextItem();
        MashineLabels[i]->setText(tmp);
        MashineLabels[i]->setPos(0,24+i*20);
        plot.addItem(MashineLabels[i]);

        tmp.clear();
    }

    QGraphicsSimpleTextItem **TimeLabels = new QGraphicsSimpleTextItem*[maxTime];
    for(int i=0; i < maxTime; ++i)
    {
        TimeLabels[i] = new QGraphicsSimpleTextItem();
        TimeLabels[i]->setText(tmp.setNum(i+1));
        TimeLabels[i]->setPos(24+i*20,0);
        plot.addItem(TimeLabels[i]);
    }
}

bool MainWindow::JohnsonCondition()
{
    int cmp1, cmp2;
    int JobCount = ui->JobsSpinBox->value();
    for(int i=0; i < JobCount-1; ++i)
    {
        cmp1 = (first->getJobDuration(i) < second->getJobDuration(i+1)) ? first->getJobDuration(i) : second->getJobDuration(i+1);

        cmp2 = (first->getJobDuration(i+1) < second->getJobDuration(i)) ? first->getJobDuration(i+1) : second->getJobDuration(i);

        if(cmp1 > cmp2)
            return false;
    }

    return true;
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
