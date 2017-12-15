#ifndef PIPELINEELEMENT_H
#define PIPELINEELEMENT_H

#include <QObject>

class PipelineElement : public QObject
{
    Q_OBJECT
public:
    explicit PipelineElement();
    virtual ~PipelineElement();

    void chain(PipelineElement *next);

public slots:
    virtual void start();
    virtual void stop();

    virtual void enqueue(QString product);

signals:
    void finished();

protected:
    PipelineElement *next;

};

#endif // PIPELINEELEMENT_H
