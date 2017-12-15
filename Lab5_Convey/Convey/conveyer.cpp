#include <QQueue>
#include <QIntValidator>

#include "conveyer.h"
#include "ui_conveyer.h"

Conveyer::Conveyer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Conveyer)
{
    ui->setupUi(this);

    QIntValidator *val = new QIntValidator();
    ui->timeLine->setValidator(val);
}

Conveyer::~Conveyer()
{
    delete ui;
}

void Conveyer::display(QQueue<QString> queue)
{
    ui->conveyerList->clear();
    for(auto i: queue)
        ui->conveyerList->addItem(i);
}

void Conveyer::setTitle(QString title)
{
    ui->conveyerBox->setTitle(title);
}

void Conveyer::setState(const QString &string)
{
    ui->stateLab->setText(string);
}

void Conveyer::setState(const QString &&string)
{
    setState(string);
}

void Conveyer::clearDisplay()
{
    ui->conveyerList->clear();
}

void Conveyer::addToDisplay(QString product)
{
    ui->conveyerList->addItem(product);
}

int Conveyer::getTime()
{
    return ui->timeLine->text().toInt();
}

QString Conveyer::getProductSign()
{
    return ui->productSignLine->text();
}
