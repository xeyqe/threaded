#include "eratthread.h"

eratThread::eratThread(QObject *parent) : QThread(parent)
{

}

void eratThread::run()
{
    for (int i = eratIncrementNum; i*i<=eratInputNum; i++)
    {
        if (Stop) break;
        else {
            eratIncrementNum = i;

            if (vector[i] == true)
            {
                for (int j=i*i; j<=eratInputNum; j += i)
                    vector[j] = false;
            }
            emit eratOutArray(vector);
            emit eratProgress((i*100)/eratInputNum);
            emit eratIncrement(i);
            this->msleep(50);
        }
    }

    for (int k=eratIncrementNum2; k<=eratInputNum; k++) {
        if (Stop) break;
        else {
            if (vector[k])
                emit eratOutput(k);
            emit eratProgress(((k*100)/eratInputNum)+100);
            this->msleep(50);
        }
    }
}

void eratThread::eratInput(int inpt, int incr, int incr2, QVector<bool> vct){
    eratInputNum = inpt;
    eratIncrementNum = incr;
    eratIncrementNum2 = incr2;
    vector = vct;
}

