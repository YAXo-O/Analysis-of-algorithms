#ifndef CONSUMERELEMENT_H
#define CONSUMERELEMENT_H

#include "pipelineelement.h"

class Consumer;
template<typename T>
class QQueue;

class ConsumerElement: public PipelineElement
{
public:
    ConsumerElement(Consumer *consumer);

public slots:
    void enqueue(QString product) override;

private:
    Consumer *consumer;
    QQueue<QString> result;

    void showResult();
};

#endif // CONSUMERELEMENT_H
