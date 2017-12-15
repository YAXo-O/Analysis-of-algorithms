#ifndef PRODUCER_H
#define PRODUCER_H

#include <QWidget>

namespace Ui {
    class Producer;
}

class Producer : public QWidget
{
    Q_OBJECT

public:
    explicit Producer(QWidget *parent = 0);
    ~Producer();

    int getCount() const;
    int getDelay() const;

private:
    Ui::Producer *ui;

signals:
    void produce();
};

#endif // PRODUCER_H
