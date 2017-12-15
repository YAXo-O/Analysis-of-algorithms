#ifndef CONVEYER_H
#define CONVEYER_H

#include <QWidget>

template<typename T>
class QQueue;

namespace Ui {
    class Conveyer;
}

class Conveyer : public QWidget
{
    Q_OBJECT

public:
    explicit Conveyer(QWidget *parent = nullptr);
    ~Conveyer();

    void display(QQueue<QString> queue);

    void setTitle(QString title);
    void setState(const QString &string);
    void setState(const QString &&string);

    void clearDisplay();
    void addToDisplay(QString product);

    int getTime();
    QString getProductSign();

private:
    Ui::Conveyer *ui;
};

#endif // CONVEYER_H
