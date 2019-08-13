#ifndef ERATTHREAD_H
#define ERATTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>

class eratThread : public QThread
{
    Q_OBJECT
public:
    explicit eratThread(QObject *parent = nullptr);
    void run() override;
    bool Stop = false;
private:
    int eratInputNum;
    int eratIncrementNum;
    int eratIncrementNum2;
    QVector<bool> vector;

signals:
    void eratProgress(int);
    void eratOutput(int);
    void eratIncrement(int);
    void eratOutArray(QVector<bool>);

public slots:
    void eratInput(int,int,int,QVector<bool>);
    //void eratInArray(QVector<bool>);

};

#endif // ERATTHREAD_H
