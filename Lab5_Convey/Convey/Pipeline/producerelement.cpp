#include <QThread>
#include "../producer.h"
#include "producerelement.h"

#include <QDebug>

ProducerElement::ProducerElement(Producer *_producer) : PipelineElement(), producer(_producer)
{
    connect(producer, SIGNAL(produce()), this, SIGNAL(produce()));
}

void ProducerElement::start()
{
    if(!producer)
        return;

    int delay = producer->getDelay();
    for(int i = producer->getCount(); i >= 0; i--)
    {
        QString product = QString("*") + QString::number(i) + QString("*");

        QThread::msleep(delay);
        if(next)
            next->enqueue(product);
    }

    emit finished();
}
