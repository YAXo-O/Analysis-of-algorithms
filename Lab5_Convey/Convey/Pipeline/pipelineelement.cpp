#include "pipelineelement.h"

PipelineElement::PipelineElement() : QObject(), next(nullptr)
{
}

PipelineElement::~PipelineElement()
{
    //if(next)
    //    delete next;
}

void PipelineElement::chain(PipelineElement *_next)
{
    //if(next)
    //    delete next;
    next = _next;
}

void PipelineElement::start()
{
}

void PipelineElement::stop()
{
}

void PipelineElement::enqueue(QString )
{
}
