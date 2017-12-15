#ifndef PRODUCERELEMENT_H
#define PRODUCERELEMENT_H

#include "pipelineelement.h"

class Producer;

class ProducerElement : public PipelineElement
{
    Q_OBJECT
public:
    explicit ProducerElement(Producer *producer);

public slots:
    void start() override;

private:
    Producer *producer;

signals:
    void produce();
};

#endif // PRODUCERELEMENT_H
