#include <QThread>
#include <QVector>
#include <QQueue>

#include <QDebug>

#include "conveyermanager.h"

#include "Pipeline/producerelement.h"
#include "Pipeline/conveyerelement.h"
#include "Pipeline/consumerelement.h"

#include "producer.h"
#include "conveyer.h"
#include "consumer.h"

ConveyerManager::ConveyerManager(Producer *_producer, QVector<Conveyer *> *_conveyers, Consumer *_consumer):
    QObject(), producer(_producer), conveyers(_conveyers), consumer(_consumer)
{

}

void ConveyerManager::go()
{
    /* Creating new threads */
    QThread *producerThread = new QThread();
    QThread *consumerThread = new QThread();
    QVector<QThread *> conveyerThreads;

    /* Creating logic objects */
    ProducerElement *producerElement = new ProducerElement(producer);
    ConsumerElement *consumerElement = new ConsumerElement(consumer);
    QVector<ConveyerElement *> conveyerElements;

    /* Moving to threads */
    producerElement->moveToThread(producerThread);
    consumerElement->moveToThread(consumerThread);

    /* Connecting logic to thread */
    connect(producerThread, SIGNAL(started()), producerElement, SLOT(start()));
    connect(consumerThread, SIGNAL(started()), consumerElement, SLOT(start()));

    /* On finish stuff */
    connect(producerElement, SIGNAL(finished()), producerThread, SLOT(quit()));
    connect(consumerElement, SIGNAL(finished()), producerThread, SLOT(quit()));

    connect(producerElement, SIGNAL(finished()), producerElement, SLOT(deleteLater()));
    connect(producerThread, SIGNAL(finished()), producerThread, SLOT(deleteLater()));
    connect(consumerElement, SIGNAL(finished()), consumerElement, SLOT(deleteLater()));
    connect(consumerThread, SIGNAL(finished()), consumerThread, SLOT(deleteLater()));

    /* Same for conveyer + chaining */
    for(int i = 0; i < conveyers->size(); i++)
    {
        conveyerThreads.push_back(new QThread);
        conveyerElements.push_back(new ConveyerElement(conveyers->at(i)));
        conveyerElements[i]->moveToThread(conveyerThreads[i]);

        connect(conveyerThreads[i], SIGNAL(started()), conveyerElements[i], SLOT(start()));
        connect(conveyerElements[i], SIGNAL(finished()), conveyerElements[i], SLOT(deleteLater()));
        connect(conveyerThreads[i], SIGNAL(finished()), conveyerThreads[i], SLOT(deleteLater()));
    }

    /* Chaining */
    if(conveyers->size())
        producerElement->chain(conveyerElements[0]);
    else
        producerElement->chain(consumerElement);

    for(int i = 0; i < conveyerElements.size(); i++)
    {
        if(i < conveyerElements.size() - 1)
            conveyerElements[i]->chain(conveyerElements[i+1]);
        else
            conveyerElements[i]->chain(consumerElement);
    }

    /* finish */
    connect(consumer, SIGNAL(clearDisplay()), producerElement, SLOT(stop()));
    for(int i = 0; i < conveyerElements.size(); i++)
        connect(consumer, SIGNAL(clearDisplay()), conveyerElements[i], SLOT(stop()));

    /* Now we are ready to start */
    consumerThread->start();
    for(auto i : conveyerThreads)
        i->start();
    producerThread->start();
}
