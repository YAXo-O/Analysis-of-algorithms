#include <QQueue>
#include <QThread>

#include "../conveyer.h"
#include "conveyerelement.h"

#include <QDebug>

ConveyerElement::ConveyerElement(Conveyer *_conveyer): conveyer(_conveyer), bGo(true)
{
}

void ConveyerElement::start()
{
    bGo = true;
    conveyer->setState("Active");

    while(queue.size() || bGo)
    {
        if(queue.size())
        {
            QString tmp = dequeue();
            conveyer->setState(tmp);

            QThread::msleep(conveyer->getTime());
            tmp += conveyer->getProductSign();
            conveyer->setState("Active");

            if(next)
                next->enqueue(tmp);
        }
        else
            qDebug() << "Active";
    }
    qDebug() << "Inactive";

    conveyer->setState("Finished");
}

void ConveyerElement::stop()
{
    bGo = false;
    conveyer->setState("Inactive");
}

void ConveyerElement::enqueue(QString product)
{
    queue.push_back(product);
    showQueue();
}

void ConveyerElement::showQueue()
{
    if(!conveyer)
        return;

    conveyer->clearDisplay();
    for(auto i : queue)
        conveyer->addToDisplay(i);
}

QString ConveyerElement::dequeue()
{
    QString res = queue.first();
    queue.pop_front();
    showQueue();

    return res;
}
