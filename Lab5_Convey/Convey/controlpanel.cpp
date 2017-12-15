#include <QIntValidator>

#include "controlpanel.h"
#include "ui_controlpanel.h"

const int maxThreadsCount = 10;
const int minThreadsCount = 1;

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
    ui->conveyerLine->setText(QString::number(minThreadsCount));
    ui->conveyerLine->setEnabled(false);

    QIntValidator *val = new QIntValidator(minThreadsCount, maxThreadsCount);
    ui->conveyerLine->setValidator(val);

    connect(ui->increasePB, SIGNAL(clicked()), this, SLOT(increaseThreads()));
    connect(ui->decreasePB, SIGNAL(clicked()), this, SLOT(decreaseThreads()));
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::increaseThreads()
{
    int value = ui->conveyerLine->text().toInt() + 1;
    if(value <= maxThreadsCount)
    {
        ui->conveyerLine->setText(QString::number(value));

        emit threadAdded();
    }
}

void ControlPanel::decreaseThreads()
{
    int value = ui->conveyerLine->text().toInt() - 1;
    if(value >= minThreadsCount)
    {
        ui->conveyerLine->setText(QString::number(value));

        emit threadRemoved();
    }
}
