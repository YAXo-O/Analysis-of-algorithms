#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

template<typename T>
class QVector;

class Conveyer;
class Consumer;
class Producer;
class ControlPanel;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

    void setConnections();

public slots:
    void addConveyer();
    void removeConveyer();

public slots:
    void startConveyer();

private:
    ControlPanel *controlPanel;
    Producer *producer;
    QVector<Conveyer *> conveyers;
    Consumer *consumer;

};

#endif // MAINWIDGET_H
