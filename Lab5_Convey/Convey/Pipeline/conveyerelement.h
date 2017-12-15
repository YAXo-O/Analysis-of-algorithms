#ifndef CONVEYERELEMENT_H
#define CONVEYERELEMENT_H

#include "pipelineelement.h"

class Conveyer;
template<typename T>
class QQueue;

class ConveyerElement : public PipelineElement
{
public:
    ConveyerElement(Conveyer *conveyer);

public slots:
    void start() override;
    void stop() override;

    void enqueue(QString product) override;

private:
    Conveyer *conveyer;
    QQueue<QString> queue;

    bool bGo;

    void showQueue();
    QString dequeue();
};

#endif // CONVEYERELEMENT_H
