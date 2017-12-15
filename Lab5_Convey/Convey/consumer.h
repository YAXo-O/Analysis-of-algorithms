#ifndef CONSUMER_H
#define CONSUMER_H

#include <QWidget>

namespace Ui {
    class Consumer;
}

class Consumer : public QWidget
{
    Q_OBJECT

public:
    explicit Consumer(QWidget *parent = 0);
    ~Consumer();

    void drawResult(QString result);
    void clear();

private:
    Ui::Consumer *ui;

signals:
    void clearDisplay();
};

#endif // CONSUMER_H
