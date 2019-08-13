#include "factthread.h"
#include <QString>

factThread::factThread(QObject *parent) : QThread(parent)
{

}

void factThread::run()
{    
    int beginning = factIncrementNum;
    for(int i = beginning; i < factInputNum+1; i++)
    {
        if (Stop) break;
        else {
            factIncrementNum = i;
            factResultNum *= i;

            int percent = (i*100)/factInputNum;
            emit factProgress(percent, factIncrementNum, QString::number(factResultNum));

            this->msleep(300);
        }
    }
    if (!Stop)
        emit factResult(QString::number(factResultNum));
}

void factThread::factInput(int inp, int inrem, QString resl)
{
    factInputNum = inp;
    factIncrementNum = inrem;
    factResultNum = resl.toULongLong();
}

void factThread::deleteFactIncrement()
{
    factIncrementNum = 1;
    factResultNum = 1;
}
