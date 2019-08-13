#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "factthread.h"
#include "eratthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    factThread *mFactThread;
    eratThread *mEratThread;



public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_factStopBu_clicked();

    void on_factPauseResume_clicked();

    void on_eratStop_clicked();

    void on_eratPauseResume_clicked();

public slots:
     void factResultGet(QString);
     void factProgressGet(int,int,QString);

     void eratProgressGet(int);
     void eratOutputGet(int);
     void eratIncrementGet(int);
     void eratOutArrayGet(QVector<bool>);

signals:
    void factInputSend(int,int,QString);
    void deleteFactIncrementSend();

    void eratInputSend(int,int,int,QVector<bool>);

private:
    Ui::MainWindow *ui;

    bool factRunTimer = false;
    bool eratRunTimer = false;
    bool eratStop = false;
    QString factpreoutput = "1";
    unsigned long long int factoutput = 1;
    int factincrement = 0;

    int eratIncrementNum = 1;
    int eratIncrementNum2 = 1;
    QVector<bool> vct;

};

#endif // MAINWINDOW_H
