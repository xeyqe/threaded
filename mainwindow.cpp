#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "factthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mFactThread = new factThread(this);
    mEratThread = new eratThread(this);

    connect(mFactThread, &factThread::factResult, this, &MainWindow::factResultGet);
    connect(mFactThread, &factThread::factProgress, this, &MainWindow::factProgressGet);

    connect(this, &MainWindow::factInputSend, mFactThread, &factThread::factInput);
    connect(this, &MainWindow::deleteFactIncrementSend, mFactThread, &factThread::deleteFactIncrement);

    connect(mEratThread, &eratThread::eratIncrement, this, &MainWindow::eratIncrementGet);
    connect(mEratThread, &eratThread::eratOutput, this, &MainWindow::eratOutputGet);
    connect(mEratThread, &eratThread::eratProgress, this, &MainWindow::eratProgressGet);
    connect(mEratThread, &eratThread::eratOutArray, this, &MainWindow::eratOutArrayGet);

    connect(this, &MainWindow::eratInputSend, mEratThread, &eratThread::eratInput);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_factPauseResume_clicked()
{
    factRunTimer = !factRunTimer;
    if(factRunTimer) {
        mFactThread->Stop = false;
        int inp = ui->factInput->value();
        emit factInputSend(inp, factincrement+1, factpreoutput);
        ui->factPauseResume->setText("pause");
        ui->factOutput->setPlainText("");
        mFactThread->start();
    } else {
        ui->factPauseResume->setText("resume");
        mFactThread->Stop = true;
    }
}

void MainWindow::on_eratPauseResume_clicked()
{
    if(!mEratThread->isRunning()) {
        mEratThread->Stop = false;
        int inp = ui->eratInput->value();

        if (vct.size() == 0) {
            vct.resize(inp+1);
            vct.fill(true);
            ui->eratOutput->setPlainText("");
        }

        emit eratInputSend(inp, eratIncrementNum+1, eratIncrementNum2+1,vct);
        ui->eratPauseResume->setText("pause");
        ui->factOutput->setPlainText("");
        mEratThread->start();
    } else {
        ui->eratPauseResume->setText("resume");
        mEratThread->Stop = true;
    }
}

void MainWindow::on_factStopBu_clicked()
{
    factRunTimer = false;

    mFactThread->Stop = true;

    ui->factProgressBar->setValue(0);
    ui->factOutput->setPlainText("");
    ui->factPauseResume->setText("start");

    factincrement = 0;
    factpreoutput = "1";
}

void MainWindow::on_eratStop_clicked()
{
    mEratThread->Stop = true;
    vct.clear();

    ui->eratProgressBar->setValue(0);
    ui->eratOutput->setPlainText("");
    ui->eratPauseResume->setText("start");

    eratIncrementNum = 1;
    eratIncrementNum2 = 1;
}



void MainWindow::factResultGet(QString s)
{
    factincrement = 0;
    factpreoutput = "1";
    factoutput = 1;

    ui->factOutput->setPlainText(s);
    ui->factPauseResume->setText("start");
    factRunTimer = false;
}


void MainWindow::factProgressGet(int i,int j, QString s)
{
    factpreoutput = s;
    factincrement = j;
    ui->factProgressBar->setValue(i);
}

void MainWindow::eratProgressGet(int i)
{
    ui->eratProgressBar->setValue(i);
    if (i == 200) {
        vct.clear();
        eratIncrementNum = 1;
        eratIncrementNum2 = 1;
        eratRunTimer = false;
        ui->eratPauseResume->setText("start");
    }
}

void MainWindow::eratOutputGet(int i)
{
    eratIncrementNum2 = i;
    QTextCursor prev_cursor = ui->eratOutput->textCursor();
    ui->eratOutput->moveCursor(QTextCursor::End);
    ui->eratOutput->insertPlainText(QString::number(i)+"; ");
}

void MainWindow::eratIncrementGet(int i)
{
    eratIncrementNum = i;
}

void MainWindow::eratOutArrayGet(QVector<bool> vector)
{
    vct = vector;
}

