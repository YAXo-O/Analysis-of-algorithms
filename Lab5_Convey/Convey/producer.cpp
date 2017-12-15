#include "producer.h"
#include "ui_producer.h"

Producer::Producer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Producer)
{
    ui->setupUi(this);

    connect(ui->producePB, SIGNAL(clicked()), this, SIGNAL(produce()));
}

Producer::~Producer()
{
    delete ui;
}

int Producer::getCount() const
{
    return ui->productSpinBox->value();
}

int Producer::getDelay() const
{
    return ui->productDelaySpinBox->value();
}
