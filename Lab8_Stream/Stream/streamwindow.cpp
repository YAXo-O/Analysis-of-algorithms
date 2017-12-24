#include <QDebug>
#include <QThread>

#include "streamwindow.h"
#include "ui_streamwindow.h"

StreamWindow::StreamWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StreamWindow), manager(new StreamManager)
{
    ui->setupUi(this);

    connect(ui->amplitudeSpin, SIGNAL(valueChanged(double)), manager, SIGNAL(generatorAmplitudeChanged(double)));
    connect(ui->stepSpin, SIGNAL(valueChanged(double)), manager, SIGNAL(generatorStepChanged(double)));
    connect(ui->sourceVolumeSlider, SIGNAL(valueChanged(int)), SLOT(convertVolume(int)));
    connect(this, SIGNAL(volumeChanged(double)), manager, SIGNAL(sourceVolumeChanged(double)));
    connect(manager, SIGNAL(volumeBar(int)), ui->AudioBar, SLOT(setValue(int)));

    manager->start();
}

StreamWindow::~StreamWindow()
{
    delete ui;

    delete manager;
}

void StreamWindow::convertVolume(int value)
{
    emit volumeChanged(double(value)/100);
}
