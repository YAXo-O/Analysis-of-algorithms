#include "consumer.h"
#include "ui_consumer.h"

Consumer::Consumer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Consumer)
{
    ui->setupUi(this);

    connect(ui->resetPB, SIGNAL(clicked()), ui->consumerList, SLOT(clear()));
}

Consumer::~Consumer()
{
    delete ui;
}

void Consumer::drawResult(QString result)
{
    ui->consumerList->addItem(result);
}

void Consumer::clear()
{
    ui->consumerList->clear();

    emit clearDisplay();
}
