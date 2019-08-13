#ifndef FACTTHREAD_H
#define FACTTHREAD_H

#include <QThread>
#include <QObject>

class factThread : public QThread
{
    Q_OBJECT
public:
    explicit factThread(QObject *parent = nullptr);
    void run() override;
    bool Stop = false;

private:
    int factIncrementNum = 1;
    unsigned long long int factResultNum = 1;
    int factInputNum = 1;

signals:
    void factResult(QString);
    void factProgress(int,int,QString);

public slots:
    void factInput(int, int, QString);
    void deleteFactIncrement();
};

#endif // FACTTHREAD_H
