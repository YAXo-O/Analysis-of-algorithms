#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QVector>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "worldinfo.h"
#include "simulation.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), validator(new QDoubleValidator(0, 1e10, 5))
{
    ui->setupUi(this);

    setConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setConnections()
{
    connect(ui->createMatrixPB, SIGNAL(clicked()), SLOT(createMatrix()));
    connect(ui->countPB, SIGNAL(clicked()), SLOT(count()));
}

void MainWindow::createMatrix()
{
    if(ui->matrixFrame->layout())
    {
        delete ui->matrixFrame->layout();
    }

    QVBoxLayout *matrixLayout = new QVBoxLayout;
    ui->matrixFrame->setLayout(matrixLayout);

    int count = ui->citiesSpin->value();
    for(int i = 0; i < count; i++)
    {
        QHBoxLayout *layout = new QHBoxLayout;
        matrixLayout->addLayout(layout);
        for(int j = 0; j < count; j++)
        {
            QLineEdit *line = new QLineEdit;
            line->setValidator(validator);
            line->setText("0");
            if(i == j)
                line->setEnabled(false);
            layout->addWidget(line);

            lines.append(line);
        }
    }

    ui->citiesSpin->setEnabled(false);
    ui->createMatrixPB->setEnabled(false);
}

void MainWindow::count()
{
    const int citiesCount = ui->citiesSpin->value();

    WorldInfo &instance = WorldInfo::getInstance();
    instance.createMatrix(citiesCount, citiesCount);

    int row = 0;
    int col = 0;
    for(auto line : lines)
    {
        instance.setDistance(row, col, line->text().toDouble());
        col++;
        if(col == citiesCount)
        {
            col = 0;
            row++;
        }
    }

    instance.setElightFactor(ui->elightSpin->value());
    instance.setQ((ui->qSpin->value()));

    float initPheromone = ui->initialSpin->value();
    for(int row = 0; row < citiesCount; row++)
        for(int col = 0; col < citiesCount; col++)
            instance.setPheromones(row, col, initPheromone);

    instance.setLifetime(ui->lifetimeSpin->value());
    instance.setCount(ui->countSpin->value());
    instance.setCitiesCount(ui->citiesSpin->value());

    Simulation sim;
    path result = sim.start();

    QString shortestPath = "Start -> ";
    for(auto i : result.route)
        shortestPath += QString::number(i) + " -> ";
    shortestPath += "End";

    QMessageBox::information(nullptr, "Simulation", QString::number(result.length) + QString("\n") + shortestPath);
}
