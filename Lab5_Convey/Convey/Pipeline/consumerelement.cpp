#include <QQueue>
#include "../consumer.h"
#include "consumerelement.h"

ConsumerElement::ConsumerElement(Consumer *_consumer): PipelineElement(), consumer(_consumer)
{
}

void ConsumerElement::enqueue(QString product)
{
   result.append(product);
   showResult();
}

void ConsumerElement::showResult()
{
    consumer->clear();
    for(auto i : result)
        consumer->drawResult(i);
}
