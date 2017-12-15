#ifndef CONVEYERMANAGER_H
#define CONVEYERMANAGER_H

#include <QObject>

class Conveyer;
class Consumer;
class Producer;
template<typename T>
class QVector;

class ConveyerManager : public QObject
{
    Q_OBJECT
public:
    explicit ConveyerManager(Producer *producer, QVector<Conveyer *> *conveyers, Consumer *consumer);

public slots:
    void go();

private:
    Producer *producer;
    QVector<Conveyer *> *conveyers;
    Consumer *consumer;
};

#endif // CONVEYERMANAGER_H
