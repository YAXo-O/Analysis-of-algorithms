#include <QHBoxLayout>
#include <QVector>

#include "conveyer.h"
#include "controlpanel.h"
#include "producer.h"
#include "consumer.h"
#include "mainwidget.h"

#include "conveyermanager.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent),
    controlPanel(new ControlPanel), producer(new Producer), consumer(new Consumer)
{
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(controlPanel);
    layout->addWidget(producer);
    layout->addWidget(consumer);
    setLayout(layout);

    addConveyer();
    setConnections();
}

void MainWidget::setConnections()
{
    connect(controlPanel, SIGNAL(threadAdded()), this, SLOT(addConveyer()));
    connect(controlPanel, SIGNAL(threadRemoved()), this, SLOT(removeConveyer()));
    connect(producer, SIGNAL(produce()), this, SLOT(startConveyer()));
}

void MainWidget::addConveyer()
{
    Conveyer *c = new Conveyer();
    layout()->removeWidget(consumer);
    layout()->addWidget(c);
    layout()->addWidget(consumer);

    conveyers.append(c);
}

void MainWidget::removeConveyer()
{
    if(conveyers.count())
    {
        Conveyer *c = conveyers.back();
        conveyers.pop_back();
        layout()->removeWidget(c);

        delete c;
    }
}

void MainWidget::startConveyer()
{
    ConveyerManager *manager = new ConveyerManager(producer, &conveyers, consumer);
    manager->go();
}
