#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>

namespace Ui {
    class ControlPanel;
}

class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();

public slots:
    void increaseThreads();
    void decreaseThreads();

signals:
    void threadAdded();
    void threadRemoved();

private:
    Ui::ControlPanel *ui;
};

#endif // CONTROLPANEL_H
